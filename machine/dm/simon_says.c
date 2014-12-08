/* CALLSET_SECTION (simon_says, __machine4__) */

#include <freewpc.h>
#include "dm/global_constants.h"
#include "simon_says.h"
#include "search.h"


//constants

//local variables
U8 simon_says_MessageCounter;
U8 simon_says_speed;
__boolean simon_says_LF_buttons_pressed;
__boolean simon_says_LR_buttons_pressed;
__boolean simon_says_RF_buttons_pressed;
__boolean simon_says_RR_buttons_pressed;
__boolean is_simon_says_engine_running;
__boolean is_simon_says_running;
__boolean wrong_button_pressed;
U8 	num_buttons_pressed;
U8  buttons_to_press[35];
U8 	temp_button_pointer;
U8  button_end_pointer;
U8  max_buttons_pressed;
score_t simon_says_score;

//external variables

//internally called function prototypes  --external found at protos.h
static void simon_says_init (void);
static void simon_says_engine (void);



/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
void start_simon_says (void) {
	ball_search_monitor_stop ();
	flag_off (FLAG_VIDEO_MODE_ENABLED);
	flag_on (FLAG_VIDEO_MODE_RUNNING);
	is_simon_says_running = TRUE;

	//suspend running modes until VM completed, then restart them
	if (is_acmag_running() ) 				pause_acmag (TRUE);
	if (is_prison_break_running() ) 		pause_prison_break (TRUE);
	if (is_capture_simon_running() ) 		pause_capture_simon (TRUE);
	if (is_huxley_running() ) 				pause_huxley (TRUE);

		flipper_disable ();
		turn_off_gi ();
		simon_says_init();

	__boolean abort;
	abort = FALSE;

	deff_start (DEFF_SIMON_SAYS_INTRO);
	task_sleep (TIME_100MS);
	while (deff_get_active() == DEFF_SIMON_SAYS_INTRO) {
		if (switch_poll_logical (SW_LAUNCH_BUTTON) &&  switch_poll_logical (SW_LEFT_HANDLE_BUTTON) ) abort = TRUE;
		task_sleep (TIME_100MS);
	}

	if (!abort && !in_tilt) {
			simon_says_engine();
			if (!global_flag_test (GLOBAL_FLAG_COIN_DOOR_OPENED)  && !in_tilt) deff_start_sync (DEFF_SIMON_SAYS_END);
			is_simon_says_running = FALSE; //this is here to kill main deff
	}
	else	{ //user aborted
		score (SHOOTER_ABORT_SCORE);
		score_add (simon_says_score, score_table[SHOOTER_ABORT_SCORE]);
		//deff_start_sync (DEFF_SIMON_SAYS_ABORT);
		deff_start (DEFF_SIMON_SAYS_ABORT);
		task_sleep (TIME_300MS);
}
	//end of VM cleanup
	turn_on_gi ();
	task_sleep (TIME_200MS);

	//restart running modes
	if (is_acmag_running() ) 			pause_acmag (FALSE);
	if (is_prison_break_running() ) 	pause_prison_break (FALSE);
	if (is_capture_simon_running() ) 	pause_capture_simon (FALSE);
	if (is_huxley_running() ) 			pause_huxley (FALSE);

	if (!in_tilt) flipper_enable ();
	flag_off (FLAG_VIDEO_MODE_RUNNING);
	flag_off (FLAG_VIDEO_MODE_ENABLED);
}//end of function



static void simon_says_init (void) {
	U8 i;
	max_buttons_pressed = 0;
	simon_says_speed = 0;
	score_zero (simon_says_score);
	temp_button_pointer = 0;
	button_end_pointer = 2;
	wrong_button_pressed = FALSE;
	for(i = 0; i < 35; i++) buttons_to_press[i] = random_scaled(4);
}//end of func





/****************************************************************************
 * external event listeners
 ****************************************************************************/
CALLSET_ENTRY (simon_says, music_refresh) 	{ if (in_game && flag_test(FLAG_VIDEO_MODE_RUNNING) && 	is_simon_says_running)	music_request (MUS_MB_A, PRI_GAME_VMODE); }

CALLSET_ENTRY (simon_says, display_update) 	{ if (in_game && flag_test(FLAG_VIDEO_MODE_RUNNING) && is_simon_says_running)	deff_start (DEFF_SIMON_SAYS); }


CALLSET_ENTRY (simon_says, start_player) 	{
	is_simon_says_running = FALSE;
	score_zero (simon_says_score);
}//END OF START PLAYER



CALLSET_ENTRY (simon_says, tilt) {
	if (is_simon_says_running) {
			is_simon_says_running = FALSE;
			is_simon_says_engine_running = FALSE;
	}
}//end of function



CALLSET_ENTRY (simon_says, sw_right_button, sw_upper_right_button) 	{
	if (flag_test(FLAG_VIDEO_MODE_RUNNING) && is_simon_says_running )	simon_says_RF_buttons_pressed = TRUE;
}//end function


CALLSET_ENTRY (simon_says, sw_launch_button) 	{
	if (flag_test(FLAG_VIDEO_MODE_RUNNING) && is_simon_says_running )	simon_says_RR_buttons_pressed = TRUE;
}//end function


CALLSET_ENTRY (simon_says, sw_left_button, sw_upper_left_button) 	{
	if (flag_test(FLAG_VIDEO_MODE_RUNNING) && is_simon_says_running)	simon_says_LF_buttons_pressed = TRUE;
}//end function


CALLSET_ENTRY (simon_says, sw_left_handle_button) 	{
	if (flag_test(FLAG_VIDEO_MODE_RUNNING) && is_simon_says_running)	simon_says_LR_buttons_pressed = TRUE;
}//end function




/****************************************************************************
 * body
 ***************************************************************************/
static void simon_says_engine (void){
	__boolean 	checking_buttons;
	U8 			buttonPress_counter;
	is_simon_says_engine_running = TRUE;


	while (is_simon_says_engine_running && !global_flag_test (GLOBAL_FLAG_COIN_DOOR_OPENED) ) {

		// show the current buttons to press
		deff_start_sync (DEFF_SIMON_SAYS_WATCH); //display words
		deff_start_sync (DEFF_SIMON_SAYS_RUNNER); //display current buttons to press
		deff_start_sync (DEFF_SIMON_SAYS_READY); //display ready words

		// check if correct button has been pressed
		checking_buttons = TRUE;
		temp_button_pointer = 0;

		while (checking_buttons) {
			simon_says_RF_buttons_pressed = simon_says_RR_buttons_pressed = simon_says_LF_buttons_pressed = simon_says_LR_buttons_pressed = FALSE;
			buttonPress_counter = 0;
			//wait for a button press
			while (!simon_says_RF_buttons_pressed && !simon_says_RR_buttons_pressed && !simon_says_LF_buttons_pressed && !simon_says_LR_buttons_pressed) {
				task_sleep (TIME_33MS);
				buttonPress_counter++;
				if (buttonPress_counter > 120) break; //wait xx secs and quit
			}

			if ( (simon_says_LF_buttons_pressed && !buttons_to_press[temp_button_pointer] && !simon_says_LR_buttons_pressed && !simon_says_RF_buttons_pressed && !simon_says_RR_buttons_pressed)
				|| (simon_says_LR_buttons_pressed && buttons_to_press[temp_button_pointer] == 1 && !simon_says_RF_buttons_pressed && !simon_says_RR_buttons_pressed)
				|| (simon_says_RF_buttons_pressed && buttons_to_press[temp_button_pointer] == 2 && !simon_says_RR_buttons_pressed)
				|| (simon_says_RR_buttons_pressed && buttons_to_press[temp_button_pointer] == 3) )
				temp_button_pointer++; //correct button pressed so advance
			else { //wrong button pressed
				checking_buttons = FALSE;
				is_simon_says_engine_running = FALSE;
				wrong_button_pressed = TRUE;
			}

			//play button pressed animation regardless if it is correct or not
			deff_start_sync (DEFF_SIMON_SAYS_INDY);


			//if last button then end checking loop
			if (temp_button_pointer >= button_end_pointer) checking_buttons = FALSE;
		}//end of while

		if (wrong_button_pressed) {
			deff_start_sync (DEFF_SIMON_SAYS_WRONG); //display ready words
			if (temp_button_pointer > max_buttons_pressed) max_buttons_pressed = temp_button_pointer;
		}
		else
		//end game if we have reached max buttons to press
		if (button_end_pointer >= 33) {
			checking_buttons = FALSE;
			is_simon_says_engine_running = FALSE;
			max_buttons_pressed = temp_button_pointer;
		}

		//update for next button combo if all were pressed correctly and we are not at end yet
		else {
			button_end_pointer += 3;
			simon_says_speed++;
			max_buttons_pressed = temp_button_pointer;
		}

		// pause
		task_sleep (TIME_1S);

	}//end of while
	//we are here if loop ends which happens either if wrong button is pressed or full loop is done

	score_t temp_score;
	score_zero (temp_score);//zero out temp score
	score_add (temp_score, score_table[SC_750K]);//multiply by button count
	score_mul (temp_score, max_buttons_pressed);
	score_long (temp_score); //add temp score to player's score
	score_add (simon_says_score, temp_score);
}//end of function






/****************************************************************************
 * display effects
 ****************************************************************************/
void simon_says_deff (void) {
	dmd_alloc_pair_clean ();// Clean both pages
	dmd_map_overlay ();
	dmd_clean_page_low ();
	dmd_draw_thin_border (dmd_low_buffer);
	dmd_alloc_pair ();
	frame_draw(IMG_SIMON_SAYS);
	dmd_overlay_outline ();
	dmd_show2 ();
	task_sleep (TIME_4S);
	deff_exit ();
}//end function




void simon_says_watch_deff (void) {
	sound_start (ST_ANY, SPCH_SIMON_SAYS, SL_1S, PRI_GAME_QUICK3);
	dmd_alloc_pair_clean ();// Clean both pages
	dmd_map_overlay ();
	dmd_clean_page_low ();
	dmd_draw_thin_border (dmd_low_buffer);
		font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "WATCH!");
	dmd_text_outline ();
	dmd_alloc_pair ();
	frame_draw(IMG_SIMON_SAYS);
	dmd_overlay_outline ();
	dmd_show2 ();
	task_sleep (TIME_300MS);
	deff_exit ();
}//end function



void simon_says_wrong_deff (void) {
	dmd_alloc_low_clean ();
		font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_MIDDLE_Y, "WRONG");
	dmd_copy_low_to_high ();
	dmd_show_low ();
	dmd_invert_page (dmd_low_buffer);
	deff_swap_low_high (5, TIME_100MS);
	deff_exit ();
}//end function



void simon_says_abort_deff (void) {
	sound_start (ST_ANY, LOW_HORN, SL_1S, PRI_GAME_QUICK3);

	dmd_alloc_low_clean ();
		font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "ABORT");
		sprintf_score (simon_says_score);
		font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, sprintf_buffer);
	dmd_copy_low_to_high ();
	dmd_show_low ();
	dmd_invert_page (dmd_low_buffer);
	deff_swap_low_high (3, TIME_100MS);
	deff_exit ();
}//end function





void simon_says_ready_deff (void) {
	dmd_alloc_pair_clean ();// Clean both pages
	dmd_map_overlay ();
	dmd_clean_page_low ();
	dmd_draw_thin_border (dmd_low_buffer);
		font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "GO");
	dmd_text_outline ();
	dmd_alloc_pair ();
	frame_draw(IMG_SIMON_SAYS);
	dmd_overlay_outline ();
	dmd_show2 ();
	task_sleep (TIME_300MS);
	deff_exit ();
}//end function





void simon_says_indy_deff (void) {
	if (DM_IN_DMD_TEST && ++simon_says_MessageCounter >= 4) simon_says_MessageCounter = 0;

	dmd_alloc_pair_clean ();
	dmd_map_overlay ();
	dmd_clean_page_low ();
	dmd_draw_thin_border (dmd_low_buffer);

	//draw current arrow
	if ( simon_says_LF_buttons_pressed || (DM_IN_DMD_TEST && simon_says_MessageCounter == 0) ) bitmap_blit (right_arrow_bits,  38, 15);
	if	(simon_says_LR_buttons_pressed || (DM_IN_DMD_TEST && simon_says_MessageCounter == 1) ) bitmap_blit (left_arrow_bits,   15, 5);
	if	(simon_says_RF_buttons_pressed || (DM_IN_DMD_TEST && simon_says_MessageCounter == 2) ) bitmap_blit (left_arrow_bits,   82, 15);
	if	(simon_says_RR_buttons_pressed || (DM_IN_DMD_TEST && simon_says_MessageCounter == 3) ) bitmap_blit (right_arrow_bits, 103, 5);

	if (!wrong_button_pressed ){
		if (simon_says_LF_buttons_pressed || (DM_IN_DMD_TEST && simon_says_MessageCounter == 0)) sound_start (ST_ANY, CHORD1, SL_1S, PRI_GAME_QUICK3);
		if (simon_says_LR_buttons_pressed || (DM_IN_DMD_TEST && simon_says_MessageCounter == 1)) sound_start (ST_ANY, CHORD2, SL_1S, PRI_GAME_QUICK3);
		if (simon_says_RF_buttons_pressed || (DM_IN_DMD_TEST && simon_says_MessageCounter == 2)) sound_start (ST_ANY, CHORD3, SL_1S, PRI_GAME_QUICK3);
		if (simon_says_RR_buttons_pressed || (DM_IN_DMD_TEST && simon_says_MessageCounter == 3)) sound_start (ST_ANY, CHORD1, SL_1S, PRI_GAME_QUICK3);
	}
	else sound_start (ST_ANY, LOW_HORN, SL_1S, PRI_GAME_QUICK3);

	dmd_text_outline ();
	dmd_alloc_pair ();
	frame_draw(IMG_SIMON_SAYS);
	dmd_overlay_outline ();
	dmd_show2 ();
	task_sleep (TIME_200MS);
	deff_exit ();
}//end function




void simon_says_runner_deff (void) {
	U8 temp_button_pointer;
	temp_button_pointer = 0;

	if (DM_IN_DMD_TEST ) {
		U8 i;
		button_end_pointer = 20;
		for (i = 0; i < 20; i++) buttons_to_press[i] = random_scaled(4);
	}

	while (temp_button_pointer < button_end_pointer) {
		dmd_alloc_pair_clean ();
		dmd_map_overlay ();
		dmd_clean_page_low ();
		dmd_draw_thin_border (dmd_low_buffer);

		sprintf ("%d", buttons_to_press[temp_button_pointer]);
		font_render_string_center (&font_fixed6, 8, 8, sprintf_buffer);

		sprintf ("%d", temp_button_pointer);
		font_render_string_center (&font_var5, 5, 27, sprintf_buffer);

		//draw current arrow
		switch (buttons_to_press[temp_button_pointer]){
			case 0: 	bitmap_blit (right_arrow_bits,  38, 15);  sound_start (ST_ANY, CHORD1, SL_1S, PRI_GAME_QUICK3); break; //LF
			case 1: 	bitmap_blit (left_arrow_bits,   15, 5);   sound_start (ST_ANY, CHORD2, SL_1S, PRI_GAME_QUICK3); break; //LR
			case 2: 	bitmap_blit (left_arrow_bits,   82, 15);  sound_start (ST_ANY, CHORD3, SL_1S, PRI_GAME_QUICK3); break; //RF
			case 3: 	bitmap_blit (right_arrow_bits, 103, 5);   sound_start (ST_ANY, CHORD1, SL_1S, PRI_GAME_QUICK3); break; //RR
		}

		dmd_text_outline ();
		dmd_alloc_pair ();
		frame_draw(IMG_SIMON_SAYS);
		dmd_overlay_outline ();
		dmd_show2 ();
		switch (simon_says_speed) { //show arrow time
			case 0:		task_sleep (TIME_500MS); break;
			case 1:		task_sleep (TIME_500MS); break;
			case 2:		task_sleep (TIME_133MS); task_sleep (TIME_200MS);		break;
			case 3:		task_sleep (TIME_133MS); task_sleep (TIME_133MS);		break;
			case 4:		task_sleep (TIME_200MS);		break;
			default:
			case 5:		task_sleep (TIME_133MS); break;
		}// end of switch


		dmd_alloc_pair_clean ();
		dmd_map_overlay ();
		dmd_clean_page_low ();
		dmd_draw_thin_border (dmd_low_buffer);

		sprintf ("%d", temp_button_pointer);
		font_render_string_center (&font_var5, 5, 27, sprintf_buffer);

		//	dmd_text_outline ();
		dmd_alloc_pair ();
		frame_draw(IMG_SIMON_SAYS);
		dmd_overlay_outline ();
		dmd_show2 ();
		switch (simon_says_speed) { //pause between time
			case 0:		task_sleep (TIME_133MS); task_sleep (TIME_200MS); break;
			case 1:		task_sleep (TIME_133MS); task_sleep (TIME_200MS);		break;
			case 2:		task_sleep (TIME_200MS);		break;
			case 3:		task_sleep (TIME_133MS); break;
			default:
			case 4:		task_sleep (TIME_66MS); break;
		}// end of switch

		temp_button_pointer++;
	}//end of while loop
	deff_exit ();
}//end function





void simon_says_intro_deff (void) {
	U8 i;
	for (i = 0; i < 4; i++) {
		dmd_alloc_low_clean ();
		font_render_string_center (&font_var5, 64, 3, "PRESS THUMBSTO ABORT");
					font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_MIDDLE_Y, "SIMON SAYS");
		if (i == 1)	font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot+1, "3");
		if (i == 2)	font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot+1, "2");
		if (i == 3)	font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot+1, "1");
		dmd_show_low ();
		task_sleep (TIME_500MS);
		if (i == 0)	sound_start (ST_ANY, SPCH_PREPARE_FOR_SIMON, SL_1S, PRI_GAME_QUICK3);
		if (i == 2)	sound_start (ST_ANY, SPCH_SIMON_SAYS_SLY, SL_1S, PRI_GAME_QUICK3);
	}
	deff_exit ();
}//end function






void simon_says_end_deff (void) {
	dmd_alloc_low_clean ();
		font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_MIDDLE_Y, "SIMON SAYS");
	dmd_copy_low_to_high ();
	dmd_show_low ();
	dmd_invert_page (dmd_low_buffer);
	deff_swap_low_high (3, TIME_100MS);

	dmd_alloc_low_clean ();
	sprintf ("%d CORRECT", max_buttons_pressed);
		font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_MIDDLE_Y, sprintf_buffer);
	dmd_show_low ();
	task_sleep (TIME_500MS);

	dmd_alloc_low_clean ();
	sprintf_score (simon_says_score);
	font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_MIDDLE_Y, sprintf_buffer);
	dmd_show_low ();
	task_sleep (TIME_500MS);
	deff_exit ();
}//end function
