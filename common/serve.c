#include <freewpc.h>
#include <search.h>
#include <ballsave.h>
/**
 * This module implements ball serving, both for manual and auto plunges.
 * The two main APIs exposed here are serve_ball() and serve_ball_auto().
 * These add a single ball to play, either at the manual or auto plunger.
 * There is also set_ball_count() which attempts to set the global ball
 * count to an arbitrary number.
 */

__boolean MB_SERVING;

CALLSET_ENTRY (serve, start_player) { MB_SERVING = FALSE; }

/* Use HAVE_AUTO_SERVE around code which deals with autoplunger hardware.
Such code will not compile on machines where there is no such thing. */
#if defined(MACHINE_LAUNCH_SWITCH) && \
	defined(MACHINE_LAUNCH_SOLENOID) && \
	defined(MACHINE_SHOOTER_SWITCH)

#define HAVE_AUTO_SERVE

/* When using an autoplunger, LAUNCH_DELAY says how much time to wait
after launching a ball, before trying to launch another one (could be
another ball served, or the same ball which failed to launch OK). */
#define LAUNCH_DELAY TIME_1S

/*this is how long we wait after ball hits to the shooter lane
 * to auto fire the ball*/
#define MACHINE_SHOOTER_SWITCH_DELAY TIME_500MS
#endif

#define SET_BALL_COUNT_TASK_DELAY TIME_2S + TIME_500MS

/* Indicates how many balls we want to be in play.  Eventually,
live_balls == live_balls_wanted if everything works OK. */
U8 live_balls_wanted;


/**
 * Returns true if the machine supports autoplunging balls.
 */
static inline bool have_auto_serve_p (void) {
#ifdef HAVE_AUTO_SERVE
	return TRUE;
#endif
	return FALSE;
} //end of function


/**
 * Serve a new ball to the manual shooter lane.
 * This function is the preferred method to serve a ball to a manual
 * plunger at the beginning of a ball and after a ball lock.
 * It is not used for autoplunges.
 */
void serve_ball (void) {
	valid_playfield = FALSE;
	callset_invoke (serve_ball);
	effect_update_request ();
	device_request_kick (device_entry (DEVNO_TROUGH));
} //end of function


/**
 * Activate the autolaunch mechanism.  A ball must already have
 * been served from the trough- this just fires the launch solenoid.
 */
static void launch_ball_task (void) {
	sol_request_async (MACHINE_LAUNCH_SOLENOID);
	task_sleep (LAUNCH_DELAY); //a two times wait here to prevent cycling the solenoid
	task_sleep (LAUNCH_DELAY);
	task_exit ();
} //end of function


// this is called by pushing launch button, pushing flipper buttons if
// enabled, timed plunger or any callset that may call this such as ball save
// see plunger.c
void launch_ball (void) {
	/* If ball launch is already in progress, do not restart it. */
	task_create_gid1 (GID_LAUNCH_BALL, launch_ball_task);
} //end of function




/**
 * Autolaunch a new ball into play from the trough.  This is the
 * preferred API to use by ballsavers.
 */
void serve_ball_auto (void) {
		set_valid_playfield ();
		device_request_kick (device_entry (DEVNO_TROUGH));
} //end of function





/**
 * A background task that attempts to set the number of balls
 * in play to 'live_balls_wanted'.
 */
#ifdef DEVNO_TROUGH
static void set_ball_count_task (void) {
	device_t *dev = device_entry (DEVNO_TROUGH);
	U8 max_live_balls;
	U8 retries;
	U8 	temp_live_balls_wanted;

	max_live_balls = live_balls;
	temp_live_balls_wanted = live_balls_wanted - live_balls;
	retries = 2;

	//first pass - quick fire balls
	MB_SERVING = TRUE;
	while (temp_live_balls_wanted) {
		temp_live_balls_wanted--;
		sol_request_async (SOL_BALLSERVE);
		task_sleep (LAUNCH_DELAY); //worked good at 700 - just giving a little margin here
		sol_request_async (MACHINE_LAUNCH_SOLENOID);
		task_sleep (MACHINE_SHOOTER_SWITCH_DELAY);//worked good at 300 - just giving a little margin here
	}//end of rapid fire serving
	MB_SERVING = FALSE;

	//check trough to see if live balls is accurate
			task_sleep (TIME_1S);
			live_balls = (5 - device_recount(device_entry (DEVNO_TROUGH)) );
			max_live_balls = live_balls;

	//if still not all balls out there, retry slower - 2 times
	// we will usually arrive at this place on a ball-saving type multiball
	//where balls are constantly draining and refiring
	//this is okay, since the refiring will slow down which is sort of a punishment to
	//the player for allowing the balls to drain so fast
	while (max_live_balls < live_balls_wanted && retries) {
		retries--;

		/* Are there enough balls in the trough to satisfy another kick request?
		 * If not, then we need to add the balls from somewhere else.*/
		if (dev->actual_count < dev->kicks_needed)	callset_invoke (trough_rescue);
		else										serve_ball_auto ();

		task_sleep (SET_BALL_COUNT_TASK_DELAY);

		/* As long as there is a ball on the shooter, wait before trying
		to continue.  This flag will clear once the shooter switch
		has cleared for a few seconds. */
		while (global_flag_test (GLOBAL_FLAG_BALL_AT_PLUNGER))
			task_sleep (TIME_133MS);

		/* See if the ball count went up, indicating success */
		if (live_balls > max_live_balls)
			max_live_balls = live_balls;
	}//end of retry section

	task_exit ();
} //end of function




/* Set the total number of balls in play to COUNT. */
void set_ball_count (U8 count) {
	if (count <= live_balls) return;
	live_balls_wanted = count;
	task_recreate_gid (GID_SET_BALL_COUNT, set_ball_count_task);
} //end of function




/* Add COUNT balls into play from the trough. */
void add_ball_count (U8 count) {
	set_ball_count (live_balls + count);
} //end of function
#endif


/**
 * If a ball is already on the shooter, or a previous autolaunch
 * request is still in progress, then delay kicking further balls.
 */
CALLSET_BOOL_ENTRY (serve, dev_trough_kick_request) {
	/* TODO - ball at plunger should block ALL kick requests? */
	if (global_flag_test (GLOBAL_FLAG_BALL_AT_PLUNGER))	return FALSE;
	else if (task_find_gid (GID_LAUNCH_BALL))			return FALSE;
	else												return TRUE;
} //end of function


/**
 * When valid playfield is already set, the player does not have
 * to press Launch to fire the ball; it is automatic.  Schedule
 * this launch as soon as we know a ball exited the trough (we
 * do not have to see the shooter).
 */
CALLSET_ENTRY (serve, dev_trough_kick_success) {
#ifndef MACHINE_DEMO_MAN
	#ifdef HAVE_AUTO_SERVE
		if (valid_playfield) {
			task_sleep (TIME_200MS);
			launch_ball ();
		}
	#endif
#endif
} //end of function


/**
 * If we see the shooter at any other time than a trough kick,
 * we will autolaunch it but not if the door is open or we are
 * in tournament mode.
 */
CALLSET_ENTRY (serve, sw_shooter) {
#ifdef MACHINE_SHOOTER_SWITCH
	if (!switch_poll_logical (MACHINE_SHOOTER_SWITCH))		return;

	if (	valid_playfield //only if ball already in play (ball save)
		&& (!tournament_mode_enabled || ( tournament_mode_enabled && ballsave_test_active() ) )
		&& !global_flag_test (GLOBAL_FLAG_COIN_DOOR_OPENED) //don't send if coin door open
		&& !MB_SERVING ) {
			ball_search_timer_reset ();
			task_sleep (MACHINE_SHOOTER_SWITCH_DELAY);
			launch_ball ();
	}//end of if
	else
		if (!in_test && !in_game) {
			task_sleep (MACHINE_SHOOTER_SWITCH_DELAY);
			launch_ball ();
		}
#endif
} //end of function




CALLSET_ENTRY (serve, valid_playfield) {
#ifdef MACHINE_LAUNCH_LAMP
	lamp_tristate_off (MACHINE_LAUNCH_LAMP);
#endif
} //end of function




CALLSET_ENTRY (serve, start_ball) {
#ifdef MACHINE_LAUNCH_LAMP
	lamp_tristate_flash (MACHINE_LAUNCH_LAMP);
#endif
} //end of function
