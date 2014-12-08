/*
 * demolition man
 * written by James Cardona
 * */
/* CALLSET_SECTION (dm_modes_locals, __machine5__) */

#include <freewpc.h>


//local variables
__local__ U8 dm_modes_completed;
__local__ U8 dm_modes_completed2;



void set_dm_mode (U8 mode_flag) {
		dm_modes_completed |= mode_flag;  // flag or unflag the bit
}//end of function

//clear out flags for claw - but not others
void reset_dm_mode (void) {
		dm_modes_completed &= 0xE0;
}//end of function



__boolean get_dm_mode (U8 mode_flag) {
		if (dm_modes_completed & mode_flag) return TRUE;
		else return FALSE;
}//end of function




void set_dm_mode2 (U8 mode_flag) {
		dm_modes_completed2 |= mode_flag;  // flag or unflag the bit
}//end of function





__boolean get_dm_mode2 (U8 mode_flag) {
		if (dm_modes_completed2 & mode_flag) return TRUE;
		else return FALSE;
}//end of function




CALLSET_ENTRY (dm_modes_locals, start_player) 	{
	dm_modes_completed = 0x0;  // clear
	dm_modes_completed2 = 0x0;  // clear
}//end of function



