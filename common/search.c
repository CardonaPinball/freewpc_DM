#include <freewpc.h>
#include <search.h>
#include <coin.h>


/**
 * Ball search is triggered based on idle time during a game with no
 * playfield switch closures.  While a game is in progress, a monitor
 * task runs which decrements a timer.  Various conditions are checked
 * that pause the timer; e.g. when the ball is known to be at the
 * plunger.  The switch module resets the timer every time a playfield
 * switch closes.  If the timer hits zero, it triggers an actual ball
 * search, which pulses all of the playfield solenoids that might
 * legitimiately free the ball.  This logic avoids drives attached
 * to flashers or to any game-defined devices that should be avoided,
 * like the knocker or device kickout coils.
 */

U8 ball_search_timer; 		// The current value of the timer, which counts up from zero at the last switch closure.
U8 ball_search_timeout; 	// The threshold for the timer at which ball search should begin
U8 ball_search_count;
U16 ball_time; 				// The amount of time in seconds that this ball has lasted
__local__ U16 game_time; 	// The amount of time in seconds that this game has lasted. This is a per-player variable




bool ball_search_timed_out (void) { return (ball_search_timer >= ball_search_timeout); }





void ball_search_timer_reset (void) {
	if (ball_search_timer >= ball_search_timeout) 	callset_invoke (ball_search_end);
	ball_search_timer = 0;
	ball_search_count = 0;
}



//this is called from device at startup if balls missing from trough
void ball_search_run_task (void) {
	ball_search_count++;
	callset_invoke (force_ball_search);
//	deff_start (DEFF_BALLSEARCH);
	task_sleep (TIME_4S);
	task_sleep (TIME_1S);
	task_exit ();
}



//this is called from device at startup if balls missing from trough
void ball_search_now (void) { task_create_gid1 (GID_BALL_SEARCH_FORCE, ball_search_run_task); }







// Set the amount of time in seconds before the next ball search will occur.
void ball_search_timeout_set (U8 secs) { ball_search_timeout = secs; }




void ballsearch_deff (void) {
	dmd_alloc_low_clean ();
	//right side status display
			dmd_draw_vert_line (dmd_low_buffer, 100);
			if (flag_test (FLAG_IS_EXPLODE_MODE_ENABLED) ) { sprintf ("E"); font_render_string_right (&font_var5, 106, 0, sprintf_buffer); }
			if (flag_test (FLAG_IS_CARCHASE_MODE_ENABLED) ){ sprintf ("C"); font_render_string_right (&font_var5, 111, 0, sprintf_buffer); }
			if (flag_test (FLAG_VIDEO_MODE_ENABLED) ) {		 sprintf ("V"); font_render_string_right (&font_var5, 117, 0, sprintf_buffer); }
			if (flag_test (FLAG_BACK_IN_THE_FRIDGE_ACTIVATED) ) { sprintf ("F"); font_render_string_right (&font_var5, 122, 0, sprintf_buffer); }
			if (flag_test (FLAG_IS_HUXLEY_ENABLED) ) {		 sprintf ("H"); font_render_string_right (&font_var5, 128, 0, sprintf_buffer); }
			if (TROUGH_TEST) {								sprintf ("L%d", live_balls); font_render_string_right (&font_var5, 110, 6, sprintf_buffer);
			sprintf ("%d", missing_balls); font_render_string_right (&font_var5, 119, 6, sprintf_buffer);
			sprintf ("T%d", balls_in_trough); font_render_string_right (&font_var5, 128, 6, sprintf_buffer); }
			sprintf ("P%d", player_up); font_render_string_right (&font_fixed6, 126, 11, sprintf_buffer);
			sprintf ("BALL %1i", ball_up); font_render_string_right (&font_var5, 128, 21, sprintf_buffer);
			credits_render (); font_render_string_right (&font_var5, 128, 27, sprintf_buffer);

	//left side display
			sprintf ("%d", ball_search_count);
			font_render_string_left (&font_fixed6, 1, 1, sprintf_buffer);
			font_render_string_center (&font_halobold12, 50, 20, "SEARCH");
			dmd_show_low();
			task_sleep (TIME_4S);
			deff_exit ();
}





/** A monitor task that checks whether or not a ball search is
 * necessary.  This task periodically bumps a counter, which is
 * normally reset as scoring switches are triggered.  If the
 * counter reaches a threshold, and ball search is allowed to run,
 * then it is initiated.
 *
 * This task is also responsible for incrementing the ball time
 * statistic, when ball search is not necessary. */
void ball_search_monitor_task (void) {
	while (in_game) {
				task_sleep (TIME_1S); //THIS IS OUR COUNT DOWN
				if (!in_test && !in_bonus && (live_balls || !valid_playfield)
					#ifdef MACHINE_SHOOTER_SWITCH
					&& !switch_poll_logical (MACHINE_SHOOTER_SWITCH)
					#endif
					&& !switch_poll_logical (SW_LEFT_BUTTON)
					&& !switch_poll_logical (SW_RIGHT_BUTTON)
					&& !switch_poll_logical (SW_U_L_FLIPPER_BUTTON)
					&& !switch_poll_logical (SW_U_R_FLIPPER_BUTTON) ) {

								ball_time++;
								ball_search_timer++;

								if (ball_search_timer >= ball_search_timeout) {
										ball_search_count++;
										task_sleep (TIME_100MS);
										deff_start (DEFF_BALLSEARCH);
										callset_invoke (ball_search);
										task_sleep_sec (5);
										if (ball_search_count >= 15)	fatal (ERR_BALL_SEARCH_TIMEOUT);
								}//end of if (ball_search_timed_out ())
				}//end of if (!in_test && !in_bonus && (live_balls || !valid_playfield)
	}//end of outer while loop
	task_exit ();
}//end of function



//in tilt we need to make sure search is running in case tilt happened during
//time search is disabled such as video mode or when ball on claw
void tilt_force_ball_search (void) {
	ball_search_timeout_set (BS_TIMEOUT_DEFAULT);
	ball_search_timer += ball_search_timeout;
	task_create_gid1_while (GID_BALL_SEARCH_MONITOR, ball_search_monitor_task, TASK_DURATION_INF);
}





void ball_search_monitor_start (void) {
	ball_search_timeout_set (BS_TIMEOUT_DEFAULT);
	//attempt to make infinite duration so that not killed by tilt calls:
	task_create_gid1_while (GID_BALL_SEARCH_MONITOR, ball_search_monitor_task, TASK_DURATION_INF);
	ball_search_count = 0;
	ball_search_timer = 0;
}





void ball_search_monitor_stop (void) { task_kill_gid (GID_BALL_SEARCH_MONITOR); }






CALLSET_ENTRY (ball_search, init) {
	ball_search_timeout_set (BS_TIMEOUT_DEFAULT);
}





/*
 * Initialize the total game time statistic per player.
 */
CALLSET_ENTRY (ball_search, start_player) { game_time = 0; }






/*
 * At the beginning of a ball, initialize the ball time
 * statistic.  This variable will count up during the course of
 * the ball, in seconds.
 */
CALLSET_ENTRY (ball_search, start_ball) { ball_time = 0; 	ball_search_count = 0; }






/*
 * At the end of a ball, add the ball time to the
 * total time for the player.  Take care that it doesn't
 * overflow (unlikely, but still).
 */
CALLSET_ENTRY (ball_search, end_ball) {
	game_time += ball_time;
	if (game_time < ball_time) game_time = 0xFFFFUL;
}







/*
 * At the end of the game for each player, log their
 * game time into the histograms.  A game is only considered
 * complete at the start of the last ball.
 */
CALLSET_ENTRY (ball_search, end_player) {
	if (ball_up == system_config.balls_per_game) score_histogram_add (game_time);
}

/** Returns true if the chase ball feature is enabled.
 * When true, after 5 unsuccessful ball searches, all balls in play
 * are marked as missing, and endball is called.
 */
//static bool chase_ball_enabled (void) 				{
//	return FALSE;
//	return system_config.allow_chase_ball == YES;
//}





