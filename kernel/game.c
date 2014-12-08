/*
 * Copyright 2006, 2007, 2008, 2009, 2010, 2011 by Brian Dominy <brian@oddchange.com>
 *
 * This file is part of FreeWPC.
 *
 * FreeWPC is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * FreeWPC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FreeWPC; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <freewpc.h>
#include <coin.h>
#include <test.h>
#include <player.h>
#include <highscore.h>
#include <amode.h>
#include <search.h>
#include <eb.h>
#include <game.h>

/**
 * \file
 * \brief The main game state machine logic.
 *
 * This module implements the standard state machine of a pinball game.
 * The lifecycle is generally:
 * <ol>
 * <li>Attract mode
 * <li>Start game
 * <li>Start player
 * <li>Start ball
 * <li>End ball
 * <li>End player
 * <li>End game
 * <li>High score entry
 * <li>Match
 * </ol>
 *
 * Bonus is not really a separate state, but is part of endball.
 *
 * There is experimental support here for timed game, aka Safecracker.
 *
 * The main inputs to this module are the start button, for initiating
 * a game, and the end-of-ball condition, which is signalled based on
 * trough entry (when only one ball is in play).
 */

/* TODO : this code isn't important enough to stay in the system page. */

/** Nonzero if a game is currently in progress. */
__fastram__ U8 in_game;
__fastram__ U8 in_ending;

/** Nonzero if the current game is currently in bonus count */
__fastram__ U8 in_bonus;

/** Nonzero if the current game is currently in tilt mode */
__fastram__ U8 in_tilt;

/* Equivalent to (win_top != NULL), but as a byte, this can
 * be tested with a single instruction.
 * IDEA: these two variables could be overlapped into a union. */
__fastram__ enum test_mode in_test;

/** Nonzero if the current ball has reached valid playfield; i.e.
 * ball loss is allowed to end the ball.  When zero,
 * ball loss is not allowed and will result in a new ball being
 * delivered to the plunger lane. */
U8 valid_playfield;

/** The IDs of up to two playfield switches that have activated
 * at ball start and were marked 'novalid'. */
switchnum_t novalid_sw[2];

/** The number of players in the current game */
__permanent__ U8 num_players;

/** The number of the player that is currently up. */
U8 player_up;

/** The number of the current ball in play */
U8 ball_up;

/** Nonzero if the current ball will automatically end after a certain
period of time.  The value indicates the number of seconds. */
U8 timed_game_timer;

U8 timed_game_suspend_count;



/** Starts the attract mode */
void amode_start (void) {
	deff_start (DEFF_AMODE);
	leff_start (LEFF_AMODE);
#ifdef CONFIG_GI
	gi_enable (PINIO_GI_STRINGS);
#endif
	flipper_disable ();
	far_task_recreate_gid (GID_DEVICE_PROBE, device_probe, COMMON_PAGE);
	task_yield ();
	callset_invoke (amode_start);
}






/** Stops the attract mode */
void amode_stop (void) {
	deff_stop_all ();
	leff_stop_all ();
	lamp_all_off ();
	effect_update_request ();
	callset_invoke (amode_stop);
}






#ifdef DEBUGGER
/** Dump the game state to the debugger port */
void dump_game (void)
{
	extern U8 extra_balls;

	dbprintf ("Game : %d    Bonus: %d    Tilt: %d\n",
		in_game, in_bonus, in_tilt);
	dbprintf ("Valid : %d\n", valid_playfield);
	dbprintf ("Player Up : %d of %d\n", player_up, num_players);
	dbprintf ("Ball : %d    EBs : %d\n", ball_up, extra_balls);
}
#endif






static void end_game_task (void) {
	deff_stop_all ();
	leff_stop_all ();
	deff_start_sync (DEFF_DM_GAME_OVER);
	flipper_disable ();
	in_ending = TRUE;
	in_game = FALSE;
	in_bonus = FALSE;
	in_tilt = FALSE;
	player_up = 0;
	ball_up = 0;
	valid_playfield = FALSE;
	callset_invoke (end_game);
	high_score_check ();      //check for high score and allow entering initials
	log_event (SEV_INFO, MOD_GAME, EV_STOP, 0);
	lamp_all_off ();
	amode_start (); 	//this kills sounds
	task_exit ();
}//end of function




/* To limit stack size, spawn this in a separate
 * task context.  We are already nested pretty deeply here, and
 * end game effects will need to sleep to do synchronous deffs.  I've
 * observed stack overflow here when running the stress test.
 * Ensure that this task doesn't get killed due to any duration
 * change - notably entering test mode. */
void end_game (void) {
	task_remove_duration (TASK_DURATION_GAME);
	task_create_gid1 (GID_END_GAME, end_game_task);
	task_sleep (TIME_16MS);
}


__boolean bitf_just_ended;

/**
 * Handle end-of-ball.  This is called from the ball device
 * subsystem whenever it detects that the number of balls in play
 * is zero.  Some error checking is done in case this is not
 * really end-of-ball.  Normally though, this function will
 * not return.
 */
void end_ball (void) {
	/* Abort if not in the middle of a game.  We can get here
	 * in test mode/attract mode also, because the device subsystem
	 * tracks ball counts always. */
	if (!in_game) return;

	/*
	 * If valid_playfield never set, then either the ball drained
	 * before touching any playfield switches, or the ball serve
	 * failed and it fell back into the trough.  Return the
	 * ball to the plunger lane in these cases, and don't
	 * count as end-of-ball.  */
	if (!valid_playfield && !in_tilt) {
		serve_ball ();
		return;
	}

	/* Here, we are committed to ending the ball.
	Do not sleep from here on out, except while in_bonus = TRUE (below).
	This flag protects the function from being re-entered due to
	spurious switch activity while endball is running. */
	task_remove_duration (TASK_DURATION_BALL);
	task_duration_expire (TASK_DURATION_BALL);

	/* Change the running task group, so that we are no longer in
	 * the context of the trough device update. */
	task_setgid (GID_END_BALL);

	if (system_config.no_bonus_flips) flipper_disable ();
	audit_increment (&system_audits.balls_played);
	ball_search_monitor_stop ();
	callset_invoke (end_ball);
	/* If the ball was not tilted, start bonus. */
	if (!in_tilt) {
			if (get_back_in_the_fridge_ending() ) {
				kill_back_in_the_fridge ();
				in_bonus = TRUE;  //this also starts the bonus music
				callset_invoke (bitf_end); //show modified bonus display effects
				bitf_just_ended = TRUE;
				callset_invoke (mb_trough_recount_timer_exit);
			}
			else {
				in_bonus = TRUE;  //this also starts the bonus music
				callset_invoke (bonus);
//				task_create_gid1 (GID_END_BALL_TASK, end_ball_task);
			}
	} // if tilted, player gets no bonus
	else callset_invoke (bonus_complete); //this also clears tilt flag
	task_exit ();
}//end of function









CALLSET_ENTRY(game, bonus_complete){
	task_kill_gid(GID_END_BALL_TASK);
	end_ball2 ();
}//end of function




void end_ball2 (void) {
	//assume this is the last ball for the moment - this is so that sound does not blip
	//in the sound server, this will never happen as long as in_game is true
	in_ending = TRUE;
	in_bonus = FALSE;

	/* If the player has extra balls stacked, then start the
	 * next ball without changing the current player up. */
	if (decrement_extra_balls ()) {
#ifdef DEFF_SHOOT_AGAIN
		deff_start (DEFF_SHOOT_AGAIN);
#endif
#ifdef LEFF_SHOOT_AGAIN
		leff_start (LEFF_SHOOT_AGAIN);
#endif
//		callset_invoke (shoot_again);
		in_ending = FALSE;
		start_ball ();
		return;
	}


	// Advance to the next player in a multiplayer game
	if (num_players > 1) {
			player_save ();
			player_up++;
			if (player_up <= num_players) {
						player_restore ();
						in_ending = FALSE;
						start_ball ();
						return;
			}
			else {
						player_up = 1;
						player_restore ();
			}
	}

	/* Once all players have had a turn, then increment the
	 * current ball number.
	 */
		ball_up++;
		if (ball_up <= system_config.balls_per_game) {
			in_ending = FALSE;
			start_ball ();
			return;
		}

	/* After the max balls per game have been played, go into end game */
	end_game ();
}









/** Handle start-of-ball. */
void start_ball (void)
{
	in_tilt = FALSE;
	valid_playfield = FALSE;
	music_enable ();
	novalid_sw[0] = novalid_sw[1] = 0;

	/* Since lamp effects from previous balls could have been killed,
	ensure that no lamps for leffs are allocated, causing incorrect
	lamp matrix draw.  Do this early, before the start_ball hook is
	invoked which might want to start up a leff. */
	leff_stop_all ();

	/* On the first ball for each player, generate the
	start_player event, which initializes all player-local variables. */
	if (		ball_up == 1
			&& 	extra_balls_earned_this_bip == 0
			&&  bitf_just_ended == FALSE) { //if BITF happened on ball one, we don't want to restart player
					callset_invoke (start_player);
					task_yield ();
	}
	else bitf_just_ended = FALSE;

	/* At the start of ball 2, any partial credits are cleared */
	units_clear ();

	/* Reset the pointer to the current player's score */
	current_score = scores[player_up - 1];

	//notify anyone that needs to know that we are starting a new ball
	callset_invoke (start_ball);

	/* Ensure that the scores are shown briefly at the start of
	 * ball, via a high priority display effect.
	 *
	 * If this is the final ball for the player, then also
	 * display the 'goal', i.e. replay or extra ball target score;
	 * or the next high score level.
	 */
	deff_start (DEFF_SCORES_IMPORTANT);
	if ((ball_up == system_config.balls_per_game) || config_timed_game)
	{
		deff_start (DEFF_SCORE_GOAL);

		/* Chalk game played audits at the start of the final ball
		for the first player */
		if (player_up == 1)
		{
			audit_add (&system_audits.total_plays, num_players);
			audit_increment (&system_audits.nplayer_games[num_players-1]);
		}
	}

	/* Serve a ball to the plunger, by requesting a kick from the
	 * trough device.  However, if a ball is detected on the shooter switch
	 * for whatever reason, then don't kick a new ball, just use the
	 * one that is there.  In that case, need to increment live ball count
	 * manually. */
#if defined(MACHINE_SHOOTER_SWITCH)
	if (switch_poll_logical (MACHINE_SHOOTER_SWITCH))
		device_add_live ();
	else
#endif
		serve_ball ();

	flipper_enable ();
#ifdef CONFIG_GI
	gi_enable (PINIO_GI_STRINGS);
#endif
	ball_search_timeout_set (15);
	ball_search_monitor_start ();
}






/** Called when the ball is marked as 'in play'.  This happens on
most, but not all, playfield switch closures.  After valid
playfield is set, end-of-ball is allowed to happen.  Prior to
that, end-of-ball just causes a re-serve from the trough. */
void set_valid_playfield (void)
{
	if (in_game && !valid_playfield)
	{
		valid_playfield = TRUE;		
		callset_invoke (valid_playfield);
		effect_update_request ();
//		ball_search_timeout_set (15);
	}
}






/** Called prior to valid playfield, when a switch closure
occurs that does not automatically set valid playfield. */
void try_validate_playfield (U8 swno)
{
	/* If this switch has already been seen since ball start,
	   then ignore it. */
	if (novalid_sw[0] == swno)
		return;
	else if (novalid_sw[1] == swno)
		return;

	/* If the total number of other switches seen that are 'novalid'
	   is less than 2, then add this switch to the tracker. */
	else if (novalid_sw[0] == 0)
		novalid_sw[0] = swno;
	else if (novalid_sw[1] == 0)
		novalid_sw[1] = swno;

	/* Here, this is the third different 'novalid' switch we've
	   seen, so go ahead and declare valid playfield anyway. */
	else
		set_valid_playfield ();
}






/** Adds an additional player to the current game in progress */
void add_player (void)
{
	remove_credit ();
	num_players++;
	audit_increment (&system_audits.games_started);
	if (price_config.free_play) audit_increment (&system_audits.total_free_plays);
	callset_invoke (add_player);

	/* Acknowledge the new player by showing the scores briefly */
	deff_start (DEFF_SCORES_IMPORTANT);
	score_update_request ();
}






/** Starts a new game */
void start_game (void) {
	if (!in_game) {
		task_kill_gid (GID_END_GAME);
		in_game = TRUE;
		in_bonus = FALSE;
		in_ending = FALSE;
		in_tilt = FALSE;
		bitf_just_ended = FALSE;
		num_players = 0;
		scores_reset ();
		high_score_reset_check ();
	
		add_player ();
		player_up = 1;
		ball_up = 1;
	
		amode_stop ();
		log_event (SEV_INFO, MOD_GAME, EV_START, 0);

		/* Going through all of the start game hooks can take a while,
		 * so sleep before/after to keep the system scheduling OK. */
		task_sleep (TIME_33MS);
//		timestamp_update (&system_timestamps.last_game_start);
		callset_invoke (start_game);
		task_sleep (TIME_33MS);

		/* Note: explicitly call this out last, after all other events
		for start_game have been handled
		this resets all the memory to blank */
		player_start_game ();
		start_ball ();
	}
}




/**
 * stop_game is called whenever a game is restarted, or test mode
 * is entered.  It is functionally equivalent to end_game aside
 * from normal end game features like match, high score check, etc.
 */
void stop_game (void) {
	/* If a game was aborted before it completed, then end_player
	   was not necessarily thrown for all players. */
	if (in_game && ball_up <= system_config.balls_per_game) {
		do {
			callset_invoke (end_player);
			player_up--;
		} while (player_up > 0);
	}

	in_ending = TRUE;
	in_game = FALSE;
	in_bonus = FALSE;
	in_tilt = FALSE;
	player_up = 0;
	ball_up = 0;
	valid_playfield = FALSE;

	callset_invoke (stop_game);

	deff_stop_all ();
	leff_stop_all ();

	/* Forcibly stop tasks that should run only during a game.
	Do this last, so that the stop_game event handlers gives modules
	a chance to do cleanup before this happens. */
	task_remove_duration (TASK_DURATION_GAME);
	task_duration_expire (TASK_DURATION_GAME);
}




/** Perform final checks before allowing a game to start. */
static bool verify_start_ok (void)
{
#ifndef DEVNO_TROUGH
	return FALSE;
#endif

	/* check enough credits */
	if (!has_credits_p ())
		return FALSE;

	/* check ball devices stable */
	if (!in_game && !device_check_start_ok ())
		return FALSE;

	/* Give other modules a chance to decide if game start
	is OK.  Return FALSE whenever start should be denied. */
	return callset_invoke_boolean (game_start_allowed);
}




CALLSET_ENTRY (game, start_button_handler) {
#ifdef MACHINE_START_SWITCH
	/* If not enough credits to start game/add player,
	 * return.  Alert the player of this outside of a game. */
	if (!has_credits_p ()){
		if (!in_game){
			deff_start (DEFF_CREDITS);
			callset_invoke (start_without_credits);
		}
		return;
	}

	/* If a game is already in progress and is tilted, do not allow
	further players to be added.  Also do not allow when in test mode. */
	if (in_test || in_tilt) return;

	/* See if a game is already in progress. */
	if (!in_game) {
		/* Nope, we might be able to start a new game.
		 * Go through some more checks first. */
		if (verify_start_ok ()) {
			/* OK, we can start a game. */
			start_game ();
		}
		else
		{
			/* For some reason, game couldn't be started...
			 * verify_start_ok() should display an error to the
			 * player if possible, depending on what's wrong. */
		}
	}
	else if (num_players < system_config.max_players) {
		/* A game is already in progress.  If still at
		 * ball 1, and we haven't reached the maximum number
		 * of players, we can add a new player. */
		if (ball_up == 1) {
			add_player ();
		}

		/* Nope, can't add a player.  Treat this as a
		 * request to restart a new game. */
		else if (verify_start_ok ()) {
			switch (system_config.game_restart) {
				case GAME_RESTART_SLOW:
					task_sleep_sec (1);
					if (!switch_poll_logical (MACHINE_START_SWITCH)) break;
					task_sleep_sec (1);
					if (!switch_poll_logical (MACHINE_START_SWITCH)) break;
					/* fallthru if start button held down */

				case GAME_RESTART_ALWAYS:
					stop_game ();
					start_game ();
					break;

				default:
				case GAME_RESTART_NEVER:
					break;
			}
		}
	}

#ifdef DEBUGGER
	dump_game ();
#endif
#endif /* MACHINE_START_SWITCH */
}

void validate_num_players (void)
{
	/* Make sure this value is sane */
	if ((num_players == 0) || (num_players > MAX_PLAYERS))
	{
		num_players = 1;
	}
}


/**
 * Provide a default background effect when nothing else
 * is happening.  In a game, this would be the default
 * score screen; otherwise, it is the attract mode effect.
 */
CALLSET_ENTRY (game, display_update)
{
	if (in_game)
	{
		deff_start_bg (DEFF_SCORES, PRI_SCORES);
	}
	else if (sys_init_complete)
	{
		deff_start_bg (DEFF_AMODE, PRI_AMODE);
	}
}


/** Because num_players is tracked across resets in
 * protected memory, it needs an initializer at factory
 * reset time.
 */
CALLSET_ENTRY (game, factory_reset)
{
	num_players = 1;
}


/** Initialize the game subsystem.  */
CALLSET_ENTRY (game, init)
{
	validate_num_players ();
	in_game = FALSE;
	in_bonus = FALSE;
	in_tilt = FALSE;
	in_ending = FALSE;
	valid_playfield = FALSE;
	player_up = 0;
	ball_up = 0;
}



