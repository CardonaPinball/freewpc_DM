
/* CALLSET_SECTION (super_jackpot_reminder, __machine3__) */

#include <freewpc.h>
#include "dm/global_constants.h"


U8 	super_jackpot_reminder_SoundCounter;
__boolean is_super_jackpot_lit;


void super_jackpot_reminder_task (void) {
	for (;;) {
		if ( (super_jackpot_reminder_SoundCounter++ % 4) == 0 ) 	sound_start (ST_SPEECH, SPCH_GET_SUPER_JACKPOT, SL_4S, PRI_GAME_QUICK3);
		else 														sound_start (ST_SPEECH, SPCH_GET_SUPER_JACKPOT, SL_4S, PRI_GAME_QUICK3);
		task_sleep_sec(15);
	}//end of loop
	task_exit();
}//end of function



void start_super_jackpot_reminder(void) {
	is_super_jackpot_lit = TRUE;
	lamp_tristate_on (LM_SUPER_JACKPOT);
	task_create_gid1 (GID_SUPER_JACKPOT_REMINDER, super_jackpot_reminder_task);
}//end of function



void end_super_jackpot_reminder(void) {
	is_super_jackpot_lit = FALSE;
	lamp_tristate_off (LM_SUPER_JACKPOT);
	task_kill_gid(GID_SUPER_JACKPOT_REMINDER);
}//end of function



CALLSET_ENTRY (super_jackpot_reminder, end_ball, start_player) {
	is_super_jackpot_lit = FALSE;
	lamp_tristate_off (LM_SUPER_JACKPOT);
	task_kill_gid(GID_SUPER_JACKPOT_REMINDER);
}//end of function


__boolean get_is_super_jackpot_lit(void) {
	return is_super_jackpot_lit;
}


