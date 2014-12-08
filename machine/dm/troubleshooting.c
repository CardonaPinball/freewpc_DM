/*
 * demolition man
 * troubleshooting.c
 *
 * written by James Cardona
 * 
 *
 * */
/* CALLSET_SECTION (troubleshooting, __machine4__) */


#include <freewpc.h>
#include "dm/global_constants.h"
#include "shaker.h"


//constants

//local variables
U8	secretCodeCount;

//external variables

//prototypes

/****************************************************************************
 * body
 *
 ****************************************************************************/
CALLSET_ENTRY (troubleshooting, start_player) { secretCodeCount = 0; }


//secret testing button
CALLSET_ENTRY (troubleshooting, sw_left_handle_button) {
	if (DM_IN_CAB_TEST) {
		secretCodeCount++;
//		if (secretCodeCount == 3) huxley_increment_all();

		if (secretCodeCount == 3) start_extraball();

		if (secretCodeCount == 5) enable_back_in_the_fridge();

		if (secretCodeCount == 6) demotime_increment_all();

//		increment_freeze();

		//second number
		//16 = about 1 second
		//
		// SHAKER_ONE_QUARTER_ON with 16 caused reboot
		// SHAKER_ONE_QUARTER_ON with 8 caused reboot
		// SHAKER_ONE_QUARTER_ON with 4 was ok
		// SHAKER_ONE_QUARTER_ON with 2 was ok
		// SHAKER_ONE_QUARTER_ON with 1 was ok

		//SHAKER_HALF_ON  with 8 caused reboot
		//SHAKER_HALF_ON with 4 was ok
		//SHAKER_HALF_ON with 2 was ok
		//SHAKER_HALF_ON with 1 was ok

		//SHAKER_THREEQUARTER_ON with 4 caused reboot
		//SHAKER_THREEQUARTER_ON with 2 caused reboot
		//SHAKER_THREEQUARTER_ON with 1 caused reboot

		//also noted that if shaker is called many times in a short period of time it
		//will cause a soft reboot - basically game will restart in mid game
		//and everything will be confused

//			if (secretCodeCount % 9 == 0) shaker_start (SHAKER_OFF, 1);
//		else if (secretCodeCount % 9 == 1) shaker_start (SHAKER_ONE_QUARTER_ON, 1);
//		else if (secretCodeCount % 9 == 2) shaker_start (SHAKER_HALF_ON, 1);
//		else if (secretCodeCount % 9 == 3) shaker_start (SHAKER_ONE_QUARTER_ON, 2);
//		else if (secretCodeCount % 9 == 4) shaker_start (SHAKER_HALF_ON, 2);
//		else if (secretCodeCount % 9 == 5) shaker_start (SHAKER_ONE_QUARTER_ON, 4);
//		else if (secretCodeCount % 9 == 6) shaker_start (SHAKER_HALF_ON, 4);
//		else if (secretCodeCount % 9 == 7) shaker_start (SHAKER_ONE_QUARTER_ON, 8);
//		else if (secretCodeCount % 9 == 8) shaker_start (SHAKER_HALF_ON, 8);

		deff_start (DEFF_TROUBLESHOOTING);
	}//END OF IN TEST
}//end of function


//secret testing button
CALLSET_ENTRY (troubleshooting, sw_escape) { if (DM_IN_CAB_TEST)  scores_reset (); }


/****************************************************************************
 *
 * trouble shooting deffs
 *
 ****************************************************************************/
void troubleshooting_deff(void) {
	dmd_alloc_low_clean ();

	sprintf ("%d", secretCodeCount);
	font_render_string_center (&font_var5, 60, 6, sprintf_buffer);

		if (secretCodeCount % 9 == 0) sprintf ("SHAKER_OFF");
//	else if (secretCodeCount % 9 == 1)  sprintf ("ONE_QUARTER - TIME 1");
//	else if (secretCodeCount % 9 == 2) sprintf ("HALF - TIME 1");
	else if (secretCodeCount % 9 == 3)  sprintf ("ONE_QUARTER - TIME 2");
	else if (secretCodeCount % 9 == 4) sprintf ("HALF - TIME 2");
	else if (secretCodeCount % 9 == 5)  sprintf ("ONE_QUARTER - TIME 4");
	else if (secretCodeCount % 9 == 6) sprintf ("HALF - TIME 4");
	else if (secretCodeCount % 9 == 7)  sprintf ("ONE_QUARTER - TIME 8");
	else if (secretCodeCount % 9 == 8) sprintf ("_HALF - TIME 8");


	font_render_string_center (&font_var5, 60, 16, sprintf_buffer);


	//	sprintf_score (REPLAY_SCORE_OFFSET);
//	font_render_string_left (&font_var5, 70, 8, sprintf_buffer);
//	sprintf ("REPLAY SCORE OFFSET");
//	font_render_string_right (&font_var5, 64, 8, sprintf_buffer);

//	sprintf_score (current_score);
//	font_render_string_left (&font_var5, 70, 16, sprintf_buffer);
//	sprintf ("CURRENT SCORE");
//	font_render_string_right (&font_var5, 64, 16, sprintf_buffer);

//	sprintf_score (current_score + REPLAY_SCORE_OFFSET);
//	font_render_string_left (&font_var5, 70, 23, sprintf_buffer);
//	sprintf ("CURR *");
//	font_render_string_right (&font_var5, 64, 23, sprintf_buffer);


//curr = (replay_score_t *)(current_score + REPLAY_SCORE_OFFSET);


/*trough and ball checking*/
/*
	sprintf ("LIVE BALLS   %d", live_balls);
	font_render_string_center (&font_var5, 64, 5, sprintf_buffer);

	sprintf ("TROUGH COUNT   %d", 	device_recount(device_entry (DEVNO_TROUGH)) );
	font_render_string_center (&font_var5, 64, 10, sprintf_buffer);

	if (switch_poll_logical(SW_TROUGH_1) ) font_render_string_center (&font_var5,  5, 19, "1");
	if (switch_poll_logical(SW_TROUGH_2) ) font_render_string_center (&font_var5, 10, 19, "2");
	if (switch_poll_logical(SW_TROUGH_3) ) font_render_string_center (&font_var5, 15, 19, "3");
	if (switch_poll_logical(SW_TROUGH_4) ) font_render_string_center (&font_var5, 20, 19, "4");
	if (switch_poll_logical(SW_TROUGH_5) ) font_render_string_center (&font_var5, 25, 19, "5");
 */




/*	if (in_live_game) sprintf ("ILG");
 	 font_render_string_center (&font_var5, 25, 5, sprintf_buffer);

	#if defined(HAVE_AUTO_SERVE) sprintf ("SRV");
	font_render_string_center (&font_var5, 25 , 11, sprintf_buffer);
	#endif

if (global_flag_test (GLOBAL_FLAG_BALL_AT_PLUNGER)) sprintf ("BALL");
	font_render_string_center (&font_var5, 50 , 11, sprintf_buffer);
*/

	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}//end of deff


