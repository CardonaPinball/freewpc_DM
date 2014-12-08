#include <freewpc.h>

CALLSET_ENTRY (trough, dev_trough_enter) {
	/* Audit center drains (outlanes are audited in their respective switches) */
	if (!event_did_follow (any_outlane, center_drain)) audit_increment (&system_audits.center_drains);
	device_remove_live ();
}



CALLSET_ENTRY (trough, dev_trough_kick_success) {
	device_add_live ();
}



CALLSET_ENTRY (trough, dev_trough_recount) {
	U8 temp_live_balls;
	//# of balls on playfield is total minus number in trough
	temp_live_balls = (5 - device_recount(device_entry (DEVNO_TROUGH) ) );
	//if logic thinks there is more than that then reset it
	if (live_balls > temp_live_balls) live_balls = temp_live_balls;
}




//this is used to kill stacked trough kick requests at end of LITZ or BITF
CALLSET_ENTRY (trough, trough_zero_out_kick_request) {
		device_t *dev;
		dev = device_entry (DEVNO_TROUGH);
		dev->kicks_needed = 0;
		dev->kick_errors = 0;
}




//while in MB recount the trough every 5 secs or so
void mb_trough_recount_timer_task (void) {
	U8 mb_recount_timer = 0;
	while (in_game) {
				task_sleep (TIME_1S);
				mb_recount_timer++;
				if (mb_recount_timer > 5) {
						mb_recount_timer = 0;
						U8 temp_live_balls;
						//# of balls on playfield is total minus number in trough
						temp_live_balls = (5 - device_recount(device_entry (DEVNO_TROUGH) ) );
						//if logic thinks there is more than that then reset it
						if (live_balls > temp_live_balls) live_balls = temp_live_balls;

						//if BITF running and balls are in trough then send them out
						if (get_is_back_in_the_fridge_in_ball_save() ) set_ball_count (5); // THIS JUST MAKES IT FASTER
						else {
										// this is a work around, this call is also made at device_remove_live()
										//but if we drain several balls at once, sometimes the single_ball_play call
										//is missed so we recheck for it here
										if (live_balls + device_entry (DEVNO_TROUGH)->kicks_needed == 1) {
												callset_invoke (single_ball_play);
										}
										else if (live_balls + device_entry (DEVNO_TROUGH)->kicks_needed == 0) {
											end_ball ();
										}
						}
				}//end of if
	}//end of outer while loop
	task_exit ();
}//end of function





CALLSET_ENTRY (trough, mb_trough_recount_timer_start) {
	task_create_gid1 (GID_MB_TROUGH_RECOUNT, mb_trough_recount_timer_task);
}


CALLSET_ENTRY (trough, mb_trough_recount_timer_exit) {
	task_kill_gid (GID_MB_TROUGH_RECOUNT);
}
