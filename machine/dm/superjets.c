/*
 * demolition man
 * superjets.c
 * written by James Cardona
 *
 * Location Description:
 * Jet Bumpers: There are two regular jet bumpers and a top slingshot
 * which scores the same as a jet bumper. They advance the
 * Retina Scan value. The left jet bumper can also be hit from
 * the center ramp -- it acts as the right wall of the center ramp.
 *
 * Scoring Description: (original game)
 * The Jet Bumpers increase the Retina Value.(eyeball)
 * It starts at 5M and goes up 100K per jet.
 * There are two Jet Bumpers and one slingshot ... the slingshot counts as a jet bumper.
 * Jet Bumpers award 250k a Pop.
 * superjets mode award 1 million each
 *
 * Scoring Description: (my rules)
 * same as above except
 * superjets mode award 2 million each
 * successive modes award more
 *
 * estimate of average superjets mode score: 20 million to 80 million
 *
 */
/* CALLSET_SECTION (superjets, __machine3__) */



#include <freewpc.h>
#include "dm/global_constants.h"
#include "clawmagnet.h"
#include "ballsave.h"
#include <coin.h>


//constants
#define SUPERJETS_EASY_GOAL  20
#define SUPERJETS_MED_GOAL  30
#define SUPERJETS_HARD_GOAL  40
#define SUPERJETS_GOAL_STEP  10
#define SUPERJETS_GOAL_MAX  100


//local variables
U8 					superjets_mode_shots_made;
U8					superjets_mode_timer;
score_t 			superjets_mode_score;
score_t 			superjets_mode_next_score;
score_t 	superjets_mode_score_total_score;
U8 					superjets_goal;
U8 			sj_counter; //counter used for display effects


//external variables


//internally called function prototypes  --external found at protos.h
void superjets_effect_deff(void);
void superjets_mode_init (void);
void superjets_mode_expire (void);
void superjets_mode_exit (void);
void superjets_goal_award(void);

/****************************************************************************
 * mode definition structure
 ***************************************************************************/
struct timed_mode_ops superjets_mode = {
	DEFAULT_MODE,
	.init = superjets_mode_init,
	.exit = superjets_mode_exit,
	.gid = GID_SUPERJETS_MODE_RUNNING,
	.music = MUS_MD_SUPERJETS,
//	.deff_starting = DEFF_SUPERJETS_START_EFFECT,
	.deff_running = DEFF_SUPERJETS_EFFECT,
//	.deff_ending = DEFF_SUPERJETS_END_EFFECT,
	.prio = PRI_GAME_MODE3,
	.init_timer = 58,
	.timer = &superjets_mode_timer,
	.grace_timer = 2, //default is 2
//	.pause = system_timer_pause,
};



/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
CALLSET_ENTRY (superjets, start_ball) 		{
	if (get_dm_mode(SJETS_COMPLETED)) 		lamp_tristate_on (LM_CLAW_SUPER_JETS);
	else 									lamp_tristate_off (LM_CLAW_SUPER_JETS);
}//end of function


CALLSET_ENTRY (superjets, end_ball, tilt) 		{
	if (timed_mode_running_p(&superjets_mode) ) timed_mode_end (&superjets_mode);
}//end of function



CALLSET_ENTRY (superjets, start_player) 	{
	superjets_mode_shots_made = 0; //these need to be zeroed in before we enter the mode so bonus doesn't fake trigger
	score_zero(superjets_mode_score_total_score);
	superjets_goal = SUPERJETS_EASY_GOAL;
}//end of function



void superjets_mode_init (void) {
		//the claw mode can expire on its own and since it is a lower priority it will not display
		//	callset_invoke (end_claw_mode); // this seemed to cause occasional crashes
			clawmagnet_off ();
			global_flag_off(GLOBAL_FLAG_IS_BALL_ON_CLAW);
			flipper_enable ();
			//reset counter if first time run, otherwise do not - player may restart acmag while currently running
	sound_start (ST_SPEECH, SPCH_SUPERJETS_ACTIVATED, SL_4S, PRI_GAME_QUICK3);
	ballsave_add_time (system_config.mode_ballsave);
	//flash lamp for a time
	lamp_tristate_flash(LM_CLAW_SUPER_JETS);
	task_sleep(TIME_500MS);
	lamp_tristate_on(LM_CLAW_SUPER_JETS);
	if (get_dm_mode(SJETS_COMPLETED)) 	{
		score_add(superjets_mode_next_score, score_table[SUPERJETS_HIT_SCORE2]);
		score_add(superjets_mode_score, score_table[SUPERJETS_START_SCORE2]);
		score(SUPERJETS_START_SCORE2);
	}
	else {
		superjets_mode_shots_made = 0;
		score_zero(superjets_mode_score);
		score_zero(superjets_mode_next_score);
		score_add(superjets_mode_next_score, score_table[SUPERJETS_HIT_SCORE1]);
		score_add(superjets_mode_score, score_table[SUPERJETS_START_SCORE1]);
		score(SUPERJETS_START_SCORE1);
	}
}//end of function



void superjets_mode_exit (void) {
	set_dm_mode(SJETS_COMPLETED); //for next time
}//end of function


/****************************************************************************
 * external event listeners
 ****************************************************************************/
CALLSET_ENTRY (superjets, music_refresh)  	{ if (in_game) timed_mode_music_refresh (&superjets_mode); }
CALLSET_ENTRY (superjets, display_update) 	{ if (in_game && !flag_test(FLAG_VIDEO_MODE_RUNNING) )	 timed_mode_display_update (&superjets_mode); }



/****************************************************************************
 * body
 *
 ***************************************************************************/
bool is_sjets_running (void) {
	return timed_mode_running_p (&superjets_mode);
}//end of function



CALLSET_ENTRY (superjets, sw_claw_super_jets) {
	if (in_game && !in_tilt) {
		demotime_increment();
		timed_mode_begin (&superjets_mode);//start mode
	}
}//end of function



CALLSET_ENTRY (superjets, sw_jet) {
	if (in_game && !in_tilt && timed_mode_running_p(&superjets_mode) ) {
			++superjets_mode_shots_made;

			leff_start (LEFF_FLASH_UR_GI);

			//score higher if mode done more than once
			if (get_dm_mode(SJETS_COMPLETED)) 	{
				score (SUPERJETS_HIT_SCORE2);
				score_add (superjets_mode_score, score_table[SUPERJETS_HIT_SCORE2]);
			}
			else {
				score (SUPERJETS_HIT_SCORE1);
				score_add (superjets_mode_score, score_table[SUPERJETS_HIT_SCORE1]);
			}
			if (superjets_mode_shots_made >= superjets_goal) 	superjets_goal_award();
			else {
				U8 superjets_SoundCounter;
				superjets_SoundCounter = random_scaled(3);//from kernal/random.c - pick number from 0 to 2
				if ( (superjets_SoundCounter) == 0 ) 		sound_start (ST_SPEECH, SPCH_DULCH, SL_2S, PRI_GAME_QUICK2);
				else if ( (superjets_SoundCounter) == 1 ) 	sound_start (ST_SPEECH, SPCH_WOOH, SL_2S, PRI_GAME_QUICK2);
				else 										sound_start (ST_SPEECH, SPCH_WOW, SL_2S, PRI_GAME_QUICK2);
			}
		}//end of if
}//end of function



void superjets_goal_award (void) {
	sound_start (ST_SPEECH, SPCH_SUPERJETS_COMPLETED, SL_4S, PRI_GAME_QUICK3);
	score (SUPERJETS_GOAL_SCORE);
	score_add (superjets_mode_score, score_table[SUPERJETS_GOAL_SCORE]);
	if (superjets_goal < SUPERJETS_GOAL_MAX)  superjets_goal += SUPERJETS_GOAL_STEP;
	timed_mode_end (&superjets_mode);
}//END OF FUNCTION




/****************************************************************************
 *
 * display effects
 *
 ****************************************************************************/
void superjets_effect_deff(void) {
	U8 sj_swap = 0;
	U8 TOGGLE = 0;
	dmd_alloc_pair_clean ();// Clean both pages
	for (;;) {
		dmd_map_overlay ();
		dmd_clean_page_low ();
//right side status display
		ll_score_draw_ball ();

//left side display
		sprintf_score (superjets_mode_score);
		font_render_string_right (&font_var5, 98, 25, sprintf_buffer);

		if (ballsave_test_active()) {
			sprintf ("%d BALL SAVE", ballsave_get_timer());
		}
		else {
		sprintf ("%d SEC,  %d TO GOAL", superjets_mode_timer, superjets_goal - superjets_mode_shots_made);
		}
		font_render_string_right (&font_var5, 98, 0, sprintf_buffer);
		dmd_text_outline ();
		dmd_alloc_pair ();
		sj_counter++;
		if (sj_counter % 3 == 1) 	frame_draw(IMG_SUPERJETS_1);
		if (sj_counter % 3 == 2)	frame_draw(IMG_SUPERJETS_2);
		if (sj_counter % 3 == 0) 	frame_draw(IMG_SUPERJETS_3);
		dmd_overlay_outline ();
		dmd_show2 ();
		task_sleep (TIME_500MS);
		if (++sj_swap % 4 == 0) { if (++TOGGLE > 1) TOGGLE = 0; } //change TOGGLE once xx second
		dmd_alloc_pair_clean ();// Clean both pages
	}//END OF ENDLESS LOOP
	deff_exit();
}//end of mode_effect_deff

