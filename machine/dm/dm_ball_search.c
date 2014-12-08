/* CALLSET_SECTION (dm_ball_search, __machine5__) */

#include <freewpc.h>
#include "dm/global_constants.h"
#include "search.h"
#include "elevator.h"
#include "claw.h"
#include "clawmagnet.h"

//constants


//local variables
__boolean already_searching;


//external variables
extern U8 ball_search_timer;


//prototypes



/****************************************************************************
 * body
 *
 ****************************************************************************/
CALLSET_ENTRY (dm_ball_search, player_start) {already_searching = FALSE; }



void ball_search_trough_task (void) {
	//VERIFY WE DON'T HAVE ALL THE BALLS IN THE TROUGH AND JUST LOST COUNT
	U8 temp_live_balls;
	temp_live_balls = (5 - device_recount(device_entry (DEVNO_TROUGH) ));
	if (live_balls > temp_live_balls) live_balls = temp_live_balls;
	if (live_balls == 0) { //if we are here then all balls are in trough
				device_remove_live ();
				callset_invoke (ball_search_end);
				ball_search_timer_reset ();
	}
	task_exit ();
}//end of task






void ball_search_coils_task (void) {
	if (ball_search_count == 1  || ball_search_count == 4) {
				task_sleep (TIME_200MS);
				sol_reset();
				task_sleep (TIME_200MS);
	}

	sol_request (SOL_EJECT);
	task_sleep (TIME_200MS);
	sol_request (SOL_TOP_POPPER);
	task_sleep (TIME_200MS);
	sol_request (SOL_BOTTOM_POPPER);
	task_sleep (TIME_200MS);
	sol_request (SOL_LEFT_SLING);
	task_sleep (TIME_200MS);
	sol_request (SOL_RIGHT_SLING);
	task_sleep (TIME_200MS);
	sol_request (SOL_LEFT_JET);
	task_sleep (TIME_200MS);
	sol_request (SOL_RIGHT_JET);
	task_sleep (TIME_200MS);
	sol_request (SOL_TOP_SLING);
	task_sleep (TIME_200MS);
	sol_request (SOL_EJECT); //since we can jam up more than 1 ball here
	task_sleep (TIME_200MS);
	sol_request (SOL_TOP_POPPER); //since we can jam up more than 1 ball here
	task_sleep (TIME_200MS);
	sol_request (SOL_BOTTOM_POPPER); //since we can jam up more than 1 ball here
	task_exit ();
}//end of task







CALLSET_ENTRY (dm_ball_search, ball_search){
	if (!already_searching) {
		already_searching = TRUE;
		//VERIFY WE DON'T HAVE ALL THE BALLS IN THE TROUGH AND JUST LOST COUNT
		U8 temp_live_balls;
		temp_live_balls = (5 - device_recount(device_entry (DEVNO_TROUGH) ));
		if (live_balls > temp_live_balls) live_balls = temp_live_balls;
		if (live_balls == 0) { //if we are here then all balls are in trough
					device_remove_live ();
					ball_search_timer_reset ();
		}
		task_sleep (TIME_100MS);
		//lost ball wasn't in trough, search playfield
		if (ball_search_timed_out()) callset_invoke (ball_search_claw); //at cryoclaw.c
		if (ball_search_timed_out()) task_create_gid1 (GID_BALL_SEARCH_COILS, ball_search_coils_task); //above
	}
	already_searching = FALSE;
}//end of callset




CALLSET_ENTRY (dm_ball_search, force_ball_search){
	if (!already_searching) {
		already_searching = TRUE;
		//VERIFY WE DON'T HAVE ALL THE BALLS IN THE TROUGH AND JUST LOST COUNT
		U8 temp_live_balls;
		temp_live_balls = (5 - device_recount(device_entry (DEVNO_TROUGH) ));
		if (live_balls > temp_live_balls) live_balls = temp_live_balls;
		if (live_balls == 0) { //if we are here then all balls are in trough
					device_remove_live ();
					ball_search_timer_reset ();
		}
		task_sleep (TIME_100MS);
		callset_invoke (ball_search_claw); //at cryoclaw.c
		task_create_gid1 (GID_BALL_SEARCH_COILS, ball_search_coils_task); //above
	}
	already_searching = FALSE;
}//end of callset
