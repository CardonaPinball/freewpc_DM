/* CALLSET_SECTION (kaboom, __machine4__) */

#include <freewpc.h>
#include "dm/global_constants.h"
#include "kaboom.h"
#include "search.h"


//constants
#define NUM_BOMBS 35


//local variables
U8 kaboom_bucket_ypos;
U8 kaboom_bucket_xpos;
U8 kaboom_bomb_xpos[NUM_BOMBS];
U8 kaboom_speed;
U8 num_bombs_caught;
__boolean kaboom_buttons_pressed;
__boolean bomb_not_dropped;
__boolean all_bomb_caught;
__boolean is_kaboom_running;
U8 	num_bombs_to_drop;
U8	frame_counter;
U8	bomb_caught_frame_counter;
U8 bombs_released_index;
score_t kaboom_score;
__local__ U8 kaboom_level; //local means to store data per player
/*
 * target_state works as follows:
 * if 0 = unreleased
 * if 255 = caught
 * if between 1 and 32 is on screen and # corresponds to y position on screen */
U8 kaboom_bomb_state[NUM_BOMBS];




//external variables


//internally called function prototypes  --external found at protos.h
static void kaboom_init (void);
static void kaboom_sleep (void);
static void kaboom_engine (void);



/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
void start_kaboom (void) {
	ball_search_monitor_stop ();
	flag_off (FLAG_VIDEO_MODE_ENABLED);
	flag_on (FLAG_VIDEO_MODE_RUNNING);
	is_kaboom_running = TRUE;

	//suspend running modes until VM completed, then restart them
	if (is_acmag_running() ) 				pause_acmag (TRUE);
	if (is_prison_break_running() ) 		pause_prison_break (TRUE);
	if (is_capture_simon_running() ) 		pause_capture_simon (TRUE);
	if (is_huxley_running() ) 				pause_huxley (TRUE);

	flipper_disable ();
	turn_off_gi ();
	kaboom_init();

	__boolean abort;
	abort = FALSE;

	deff_start (DEFF_KABOOM_INTRO);
	task_sleep (TIME_100MS);
	while (deff_get_active() == DEFF_KABOOM_INTRO) {
		if (switch_poll_logical (SW_LAUNCH_BUTTON) &&  switch_poll_logical (SW_LEFT_HANDLE_BUTTON) ) abort = TRUE;
		task_sleep (TIME_100MS);
	}

	if (!abort && !in_tilt) {
			kaboom_engine();
			if (!global_flag_test (GLOBAL_FLAG_COIN_DOOR_OPENED)  && !in_tilt) deff_start_sync (DEFF_KABOOM_END);
	}
	else {  //game was aborted or tilted during intro screen
		score (SHOOTER_ABORT_SCORE);
		score_add (kaboom_score, score_table[SHOOTER_ABORT_SCORE]);
//		deff_start_sync (DEFF_KABOOM_ABORT); // this sometimes causes a page fault. why??????
		deff_start (DEFF_KABOOM_ABORT);
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
	is_kaboom_running = FALSE;
}//end of function





static void kaboom_init (void) {
	kaboom_bucket_xpos 	= 64;
	kaboom_bucket_ypos 	= 26;
	kaboom_speed = kaboom_level;

	switch(kaboom_level) {
		case 1: num_bombs_to_drop = 20; break;
		case 2: num_bombs_to_drop = 25; break;
		case 3: num_bombs_to_drop = 30; break;
		case 4: num_bombs_to_drop = 33; break;
		default:
		case 5: num_bombs_to_drop = NUM_BOMBS; break;//35
	}//end of switch

	bomb_not_dropped = TRUE;
	all_bomb_caught = FALSE;

	bombs_released_index = 0;
	num_bombs_caught = 0;
	U8 i;
	for(i = 0; i <NUM_BOMBS; i++) {
		kaboom_bomb_state[i]	= 0;
		kaboom_bomb_xpos[i]	= 0;
	}
	score_zero (kaboom_score);
}//end of func





/****************************************************************************
 * external event listeners
 ****************************************************************************/
CALLSET_ENTRY (kaboom, music_refresh) 	{ if (in_game && flag_test(FLAG_VIDEO_MODE_RUNNING) && is_kaboom_running )	music_request (MUS_MB_A, PRI_GAME_VMODE); }




CALLSET_ENTRY (kaboom, start_player) 	{
	is_kaboom_running = FALSE;
	kaboom_level = 1;
#ifdef CONFIG_DIFFICULTY_LEVEL
		kaboom_level = system_config.vm_level;
#endif
}//END OF START PLAYER



CALLSET_ENTRY (kaboom, tilt) {
	if (is_kaboom_running) {
			is_kaboom_running = FALSE;
			bomb_not_dropped = FALSE;
	}
}//end of function



CALLSET_ENTRY (kaboom, sw_right_button, sw_upper_right_button, sw_launch_button) 	{
	if (flag_test(FLAG_VIDEO_MODE_RUNNING) && 	is_kaboom_running )	{
		if (kaboom_bucket_xpos < 107) kaboom_bucket_xpos += 5;
		else kaboom_bucket_xpos = 112;
	}//end if
}//end function




CALLSET_ENTRY (kaboom, sw_left_button, sw_upper_left_button, sw_left_handle_button) 	{
	if (flag_test(FLAG_VIDEO_MODE_RUNNING) && is_kaboom_running  )	{
		if (kaboom_bucket_xpos > 5) kaboom_bucket_xpos -= 5;
		else kaboom_bucket_xpos = 0;
	}// end if
}//end function




/****************************************************************************
 * body
 ***************************************************************************/
static void kaboom_sleep (void) {
	switch (kaboom_speed) {
//		case 0:		task_sleep (TIME_133MS);		break; //this for testing only - too slow
		case 1:		task_sleep (TIME_100MS);		break;
		case 2:		task_sleep (TIME_66MS);			break;
		case 3:		task_sleep (TIME_66MS);			break;
		case 4:		task_sleep (TIME_50MS);			break;
		case 5:		task_sleep (TIME_50MS);			break;
		default:
		case 6:		task_sleep (TIME_33MS);			break;
	}// end of switch
}//end of function






static void kaboom_engine (void){
	U8 i;
	frame_counter = 3;
	bomb_caught_frame_counter = 0;

	while (bomb_not_dropped && !global_flag_test (GLOBAL_FLAG_COIN_DOOR_OPENED) ) {
		frame_counter++;

		//*******************************************************************//
		//move bomb
		//*******************************************************************//
		for(i = 0; i < num_bombs_to_drop; i++) {
			if (kaboom_bomb_state[i] > 0 && kaboom_bomb_state[i] < 254) kaboom_bomb_state[i] += 2;
		}//end of loop


		//*******************************************************************//
		//check to see if bomb caught
		//*******************************************************************//
		for(i = 0; i <num_bombs_to_drop; i++) {
			if (	kaboom_bomb_state[i] > 0 && kaboom_bomb_state[i] < 254
				&&	kaboom_bomb_state[i] + bomb_height >= kaboom_bucket_ypos 					//bottom edge of bomb is below top edge of bucket
				&&	kaboom_bomb_xpos[i] + 1 > kaboom_bucket_xpos								//left edge of bomb is to left of left edge of bucket
				&&	kaboom_bomb_xpos[i] + bomb_width - 1 < kaboom_bucket_xpos + bucket_width) { //right edge of bomb is to right of right edge of bucket)
					kaboom_bomb_state[i] = 255;
					bomb_caught_frame_counter = frame_counter;
					num_bombs_caught++;

					score (KABOOM_BOMB_CAUGHT);
					score_add(kaboom_score, score_table[KABOOM_BOMB_CAUGHT]);
					sound_start (ST_EFFECT, PLONK, SL_1S, PRI_GAME_QUICK3);
			} //end of if
		}//end of loop


		//*******************************************************************//
		//check to see if time to drop new bomb
		//*******************************************************************//
		if (	frame_counter % 5 == 0
			&&	bombs_released_index < num_bombs_to_drop) {
				kaboom_bomb_state[bombs_released_index] = 1;

//			if (kaboom_level < 7) {
			if (bombs_released_index == 0) kaboom_bomb_xpos[bombs_released_index] = random_scaled(40) + 44; //start at middle of screen for first bomb only
			else if (kaboom_bomb_xpos[bombs_released_index - 1] < 25) kaboom_bomb_xpos[bombs_released_index] = random_scaled(50);
			else if (kaboom_bomb_xpos[bombs_released_index - 1] > 100) kaboom_bomb_xpos[bombs_released_index] = 70 + random_scaled(50); //is left side of bomb so only go to 120
			else kaboom_bomb_xpos[bombs_released_index] = (kaboom_bomb_xpos[bombs_released_index - 1]) -23 + random_scaled(45);

//			}
//			else { //level 7 or greater - make bombs fall farther apart
//				if (bombs_released_index == 0) kaboom_bomb_xpos[bombs_released_index] = random_scaled(60) + 34; //start at middle of screen for first bomb only
///					else if (kaboom_bomb_xpos[bombs_released_index - 1] < 30) kaboom_bomb_xpos[bombs_released_index] = random_scaled(60);
//					else if (kaboom_bomb_xpos[bombs_released_index - 1] > 90) kaboom_bomb_xpos[bombs_released_index] = 60 + random_scaled(60);
//					else kaboom_bomb_xpos[bombs_released_index] = (kaboom_bomb_xpos[bombs_released_index - 1] - 30) + random_scaled(60);
//			}
			bombs_released_index++;
			sound_start (ST_EFFECT, WIPE, SL_1S, PRI_GAME_QUICK3);
		}//end of if time to drop new bomb


		//*******************************************************************//
		//display update
		//*******************************************************************//
		deff_start (DEFF_KABOOM);


		//*******************************************************************//
		//check to see if bomb dropped or all bombs caught
		//*******************************************************************//
		if (kaboom_bomb_state[num_bombs_to_drop-1]==255) {	//last bomb is caught
				bomb_not_dropped = FALSE;
				all_bomb_caught = TRUE;
				kaboom_level++;
				// since all bombs were caught, award a bonus = to # bombs
				for(i = 0; i < num_bombs_to_drop / 2; i++) {
					score (KABOOM_BOMB_CAUGHT);
					score_add(kaboom_score, score_table[KABOOM_BOMB_CAUGHT]);
				}
		}//end of if
		else
		for(i = 0; i < num_bombs_to_drop; i++) {
			if (	kaboom_bomb_state[i] < 254		//bomb has not been caught
				&& 	kaboom_bomb_state[i] >= 28 ) {	//top edge of bomb hit floor
							bomb_not_dropped = FALSE;
							i = num_bombs_to_drop; // end the loop after this pass
			}//end of if
		}//end of loop

		//*******************************************************************//
		// pause
		//*******************************************************************//
		kaboom_sleep ();
	}//end of while
}//end of function









/****************************************************************************
 * display effects
 ****************************************************************************/
void kaboom_deff (void) {
	U8 i;
	dmd_alloc_pair_clean ();
	dmd_draw_thin_border (dmd_low_buffer);

	sprintf ("%d", num_bombs_caught);
	font_render_string_center (&font_fixed6, 10, 10, sprintf_buffer);

	//*******************************************************************//
	//draw bucket
	//*******************************************************************//
	bitmap_blit (bucket_bits, kaboom_bucket_xpos, kaboom_bucket_ypos);

	//*******************************************************************//
	//draw bomb
	//*******************************************************************//
	for(i = 0; i <num_bombs_to_drop; i++) {
	if ( kaboom_bomb_state[i] > 0 && kaboom_bomb_state[i] < 254 )
		bitmap_blit (bomb_bits, kaboom_bomb_xpos[i], kaboom_bomb_state[i]);
	}// end of loop

	//*******************************************************************//
	//draw splash if a bomb was just caught
	//*******************************************************************//
	if ((bomb_caught_frame_counter + kaboom_speed) > frame_counter) //draw this only for about 300ms
		bitmap_blit (splash_bits, kaboom_bucket_xpos + 4, kaboom_bucket_ypos - splash_height);

	//*******************************************************************//
	//draw bomber
	//*******************************************************************//
	else if (kaboom_bomb_xpos[bombs_released_index - 1] < 25) 		bitmap_blit (bomber_bits, 20 + random_scaled(30), 0);
	else if (kaboom_bomb_xpos[bombs_released_index - 1] > 100) 		bitmap_blit (bomber_bits, 70 + random_scaled(30), 0);
	else bitmap_blit (bomber_bits, kaboom_bomb_xpos[bombs_released_index - 1] - 15 + random_scaled(30), 0);


	//*******************************************************************//
	//here we are relying on the fact that this deff is restartable, then
	//it should never wait this full sec.  we only put this delay here
	//to prevent the default score display from showing
	//*******************************************************************//
	dmd_show_low ();
	task_sleep (TIME_1S);
	deff_exit ();
}//end function





void kaboom_abort_deff (void) {
	sound_start (ST_EFFECT, LOW_HORN, SL_1S, PRI_GAME_QUICK3);

	dmd_alloc_low_clean ();
		font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "ABORT");
		sprintf_score (kaboom_score);
		font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, sprintf_buffer);
	dmd_copy_low_to_high ();
	dmd_show_low ();
	dmd_invert_page (dmd_low_buffer);
	deff_swap_low_high (3, TIME_100MS);
	deff_exit ();
}//end function




void kaboom_intro_deff (void) {
	U8 i;
	for (i = 0; i < 4; i++) {
		dmd_alloc_low_clean ();
		sound_start (ST_EFFECT, LOW_HORN, SL_1S, PRI_GAME_QUICK3);
		font_render_string_center (&font_var5, 64, 2, "PRESS THUMBS TO ABORT");
		font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_MIDDLE_Y, "KABOOM");
		if (i == 1)	font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot+1, "3");
		if (i == 2)	font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot+1, "2");
		if (i == 3)	font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot+1, "1");
		dmd_show_low ();
		task_sleep (TIME_500MS);
	}
	deff_exit ();
}//end function





void kaboom_end_deff (void) {
	dmd_alloc_low_clean ();
	sound_start (ST_EFFECT, LOW_HORN, SL_1S, PRI_GAME_QUICK3);
	if (all_bomb_caught) {
					font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "KABOOM");
					font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "KOMPLETE");
	}
	else			font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_MIDDLE_Y, "KABOOM");

	dmd_copy_low_to_high ();
	dmd_show_low ();
	dmd_invert_page (dmd_low_buffer);
	deff_swap_low_high (5, TIME_100MS);

	dmd_alloc_low_clean ();
	sound_start (ST_EFFECT, LOW_HORN, SL_1S, PRI_GAME_QUICK3);
	sprintf ("%d CAUGHT", num_bombs_caught);
		font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_MIDDLE_Y, sprintf_buffer);
	dmd_sched_transition (&trans_scroll_down);
	dmd_show_low ();
	task_sleep (TIME_500MS);

	if (all_bomb_caught) {
		dmd_alloc_low_clean ();
			font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_MIDDLE_Y, "COMPLETED");
		dmd_sched_transition (&trans_scroll_down);
		dmd_show_low ();
		task_sleep (TIME_500MS);
	}

	dmd_alloc_low_clean ();
	sound_start (ST_EFFECT, LOW_HORN, SL_1S, PRI_GAME_QUICK3);
	sprintf_score (kaboom_score);
	font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_MIDDLE_Y, sprintf_buffer);
	dmd_sched_transition (&trans_scroll_down);
	dmd_show_low ();
	task_sleep (TIME_500MS);
	deff_exit ();
}//end function
