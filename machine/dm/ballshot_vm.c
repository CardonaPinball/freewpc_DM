/* CALLSET_SECTION (ballshot_vm, __machine4__) */

#include <freewpc.h>
#include "dm/global_constants.h"
#include "ballshot_vm.h"
#include "search.h"


//constants
#define TOTAL_BULLETS 42
#define TOTAL_TARGETS 40
#define SEND_DELAY 2
#define MOVE_DELAY 2
#define MOVE_DISTANCE 4
#define MOVE_DISTANCE2 6
#define SPEED  1
#define SPEED1 2
#define SPEED2 3
#define SPEED3 4


//local variables
score_t 	target_score;
U8 			target_speed;
U8 			num_targets_shot;
U8 			num_targets_shot;
U8			target_index; //points to next target in queue to release
U8			Rtarget_index; //points to next target to be shot on right hand side
U8			Ltarget_index; //points to next target to be shot on left hand side
U8			shooter_frame_counter;
U8			target_shooter_frame_counter;
U8 			num_bullets_left;
U8 			face_to_show;
__boolean 	isPlayerBitten;
__boolean 	isShooterVMOver;
__boolean 	wasRightGunFired;
__boolean 	wasLeftGunFired;
__boolean	IsRightSideClosestTarget_Targeted;
__boolean	IsLeftSideClosestTarget_Targeted; //17 VARS TO HERE
__boolean 	is_shooter_running;


/*
 * target_state works as follows:
 * if 0 = unreleased
 * if 255 = shot and splash explosion effect is already displayed
 * if between 1 and 32 is on screen and # corresponds to y position on screen
 * if between 201 and 232 is just shot and # corresponds to y position on screen
 *
 */
U8 			target_state[TOTAL_TARGETS];
//new way - only 17 + TOTAL_TARGETS = 57 vars


//external variables


//internally called function prototypes  --external found at protos.h
static void target_init (void);
static void target_sleep (void);
static void target_engine (void);



/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
void start_shooter (void) {
	ball_search_monitor_stop ();
	flag_off (FLAG_VIDEO_MODE_ENABLED);
	flag_on (FLAG_VIDEO_MODE_RUNNING);
	is_shooter_running = TRUE;

	//suspend running modes until VM completed, then restart them
	if (is_acmag_running() ) 				pause_acmag (TRUE);
	if (is_prison_break_running() ) 		pause_prison_break (TRUE);
	if (is_capture_simon_running() ) 		pause_capture_simon (TRUE);
	if (is_huxley_running() ) 				pause_huxley (TRUE);

	flipper_disable ();
	turn_off_gi ();

	target_init();

	__boolean abort;
	abort = FALSE;

	deff_start (DEFF_SHOOTER_INTRO);
	task_sleep (TIME_100MS);
	while (deff_get_active() == DEFF_SHOOTER_INTRO) {
		if (switch_poll_logical (SW_LAUNCH_BUTTON) &&  switch_poll_logical (SW_LEFT_HANDLE_BUTTON) ) abort = TRUE;
		task_sleep (TIME_100MS);
	}

	if (!abort && !in_tilt) {
			target_engine();

			if (!global_flag_test (GLOBAL_FLAG_COIN_DOOR_OPENED)  && !in_tilt)
					deff_start_sync (DEFF_SHOOTER_END);
	}
	else	{
		score (SHOOTER_ABORT_SCORE);
		score_add (target_score, score_table[SHOOTER_ABORT_SCORE]);
		//deff_start_sync (DEFF_SHOOTER_ABORT);
		deff_start (DEFF_SHOOTER_ABORT);
		task_sleep (TIME_300MS);

	}

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
	is_shooter_running = FALSE;
}//end of function






static void target_init (void) {
	wasLeftGunFired = FALSE;
	wasRightGunFired = FALSE;
	target_speed = SPEED;
	num_targets_shot = 0;
	target_index = 0;
	Rtarget_index = 0;
	Ltarget_index = 1;
	shooter_frame_counter = 0;
	target_shooter_frame_counter = 0;
	score_zero (target_score);
	isPlayerBitten = FALSE;
	isShooterVMOver = FALSE;
	IsRightSideClosestTarget_Targeted = FALSE;
	IsLeftSideClosestTarget_Targeted = FALSE;
	num_bullets_left = TOTAL_BULLETS;
	face_to_show = 1;

	U8 i;
	for (i = 0; i < TOTAL_TARGETS; i++ ) {
		target_state[i] = 0;
	}//end of for loop
}//end of func





/****************************************************************************
 * external event listeners
 ****************************************************************************/
CALLSET_ENTRY (target, music_refresh) 	{ if (in_game && flag_test(FLAG_VIDEO_MODE_RUNNING) && is_shooter_running )	music_request (MUS_MB_A, PRI_GAME_VMODE); }

CALLSET_ENTRY (target, start_player) 	{ is_shooter_running = FALSE; }



CALLSET_ENTRY (target, tilt) {
	if (is_shooter_running) {
		is_shooter_running = FALSE;
			isShooterVMOver = TRUE;
	}
}//end of function



CALLSET_ENTRY (target, sw_right_button, sw_upper_right_button, sw_launch_button) 	{
	if (flag_test(FLAG_VIDEO_MODE_RUNNING) && is_shooter_running  && num_bullets_left > 0)	wasRightGunFired = TRUE;
}//end function


CALLSET_ENTRY (target, sw_left_button, sw_upper_left_button, sw_left_handle_button) 	{
	if (flag_test(FLAG_VIDEO_MODE_RUNNING) && is_shooter_running && num_bullets_left > 0)	wasLeftGunFired = TRUE;
}//end function




/****************************************************************************
 * body
 ***************************************************************************/
static void target_sleep (void) {
	switch (target_speed) {
		case 0:		task_sleep (TIME_133MS);		break; //testing only
		case 1:		task_sleep (TIME_100MS);		break;
		case 2:		task_sleep (TIME_66MS);			break;
		case 3:		task_sleep (TIME_33MS);			break;
		default:
		case 4:		task_sleep (TIME_16MS);			break;
	}// end of switch
}//end of function





static void target_engine (void){
	U8 i;
	U8 target_send_delay;
	target_send_delay = 0;
	U8 move_delay;
	move_delay = 0;
	shooter_frame_counter = 3;

	while (!isShooterVMOver && !global_flag_test (GLOBAL_FLAG_COIN_DOOR_OPENED) ) {
		shooter_frame_counter++;
		face_to_show = 1;
		if (++move_delay > MOVE_DELAY) move_delay = 0;

		//*******************************************************************//
		//check to see if gun fired and no target avail to shoot
		//*******************************************************************//
		if (!move_delay) {
			if (wasRightGunFired && !IsRightSideClosestTarget_Targeted && num_bullets_left > 0) {
				sound_start (ST_EFFECT, GUNSHOT_MUFFLED, SL_1S, PRI_GAME_QUICK3);
				wasRightGunFired = FALSE;
				num_bullets_left--;
				face_to_show = 2;
			}

			if (wasLeftGunFired && !IsLeftSideClosestTarget_Targeted && num_bullets_left > 0) {
				sound_start (ST_EFFECT, GUNSHOT_MUFFLED, SL_1S, PRI_GAME_QUICK3);
				wasLeftGunFired = FALSE;
				num_bullets_left--;
				face_to_show = 0;
			}
		}


		//*******************************************************************//
		//check to see if gun fired and target shot
		//*******************************************************************//
		if (!move_delay) {
			if (wasRightGunFired && IsRightSideClosestTarget_Targeted && num_bullets_left > 0) {
				sound_start (ST_EFFECT, GUNSHOT_MUFFLED, SL_1S, PRI_GAME_QUICK3);
				wasRightGunFired = FALSE;
				num_targets_shot++;
				num_bullets_left--;
				target_state [Rtarget_index] += 200;
				IsRightSideClosestTarget_Targeted = FALSE;
				face_to_show = 2;
				score (SHOOTER_SCORE);
				score_add (target_score, score_table[SHOOTER_SCORE]);
				if (target_state [Rtarget_index + 2] > 0 && target_state [Rtarget_index + 2] < 200) { //check and see if the next closest target is already on screen, if so target that one next, if not do nothing
					Rtarget_index += 2;
					IsRightSideClosestTarget_Targeted = TRUE;
				}
			}

			if (wasLeftGunFired && IsLeftSideClosestTarget_Targeted && num_bullets_left > 0) {
				sound_start (ST_EFFECT, GUNSHOT_MUFFLED, SL_1S, PRI_GAME_QUICK3);
				wasLeftGunFired = FALSE;
				num_targets_shot++;
				num_bullets_left--;
				target_state [Ltarget_index] += 200;
				IsLeftSideClosestTarget_Targeted = FALSE;
				face_to_show = 0;
				score (SHOOTER_SCORE);
				score_add (target_score, score_table[SHOOTER_SCORE]);
				if (target_state [Ltarget_index + 2] > 0 && target_state [Ltarget_index + 2] < 200) {
					Ltarget_index += 2;
					IsLeftSideClosestTarget_Targeted = TRUE;
				}
			}
		}

		//*******************************************************************//
		//check to see if target bites player
		//*******************************************************************//
		if (!move_delay) {
			for(i = 0; i < TOTAL_TARGETS; i++) {
				if ( target_state[i] < 200 && target_state[i] >= 24 ) { //target is height 7
					isPlayerBitten = TRUE;
					isShooterVMOver = TRUE;
					sound_start (ST_SPEECH, SPCH_COW_MOO, SL_1S, PRI_GAME_QUICK3);
				}
			}//END OF LOOP
		}


		//*******************************************************************//
		//move target
		//*******************************************************************//
		if (!move_delay) {
			for(i = 0; i < TOTAL_TARGETS; i++)
				if ( target_state[i] && target_state[i] < 200 ) {
					if (num_targets_shot >= 20) 	target_state[i] += MOVE_DISTANCE2;
					else 							target_state[i] += MOVE_DISTANCE;
				}
		}




		//*******************************************************************//
		//check to see if time to send new target
		//*******************************************************************//
		if (	target_send_delay > SEND_DELAY
			&&	target_index < TOTAL_TARGETS ) {
						if (target_index % 2 == 0 || target_index == 0) { //even so right hand side
							target_state[target_index] = 1;
							if (!IsRightSideClosestTarget_Targeted) { //if another target is not targeted then target this one
								Rtarget_index = target_index;
								IsRightSideClosestTarget_Targeted = TRUE;
							} //end of inner if
						}//end of if
						else {											//odd so left hand side
							target_state[target_index] = 1;
							if (!IsLeftSideClosestTarget_Targeted) {
								Ltarget_index = target_index;
								IsLeftSideClosestTarget_Targeted = TRUE;
							} //end of inner if
						} //end of else

						target_send_delay = 0;
						target_index++;
		}
		else target_send_delay++;




		//*******************************************************************//
		//display update
		//*******************************************************************//
		if (!move_delay)
			deff_start (DEFF_SHOOTER);




		//*******************************************************************//
		//check to see if all targets gone
		//*******************************************************************//
		if ( num_targets_shot >= TOTAL_TARGETS ) {
			isShooterVMOver = TRUE;
			// since all targets shot, award a bonus = to # targets
			for(i = 0; i < num_targets_shot / 2; i++) {
				score (SHOOTER_SCORE);
				score_add (target_score, score_table[SHOOTER_SCORE]);
			}
		}



		//*******************************************************************//
		// pause
		//*******************************************************************//
		if (num_targets_shot >= 14) 	target_speed = SPEED3;
		else if (num_targets_shot >= 9) 	target_speed = SPEED2;
		else if (num_targets_shot >= 4) 	target_speed = SPEED1;

		target_sleep ();
	}//end of while
}//end of function









/****************************************************************************
 * display effects
 ****************************************************************************/
void shooter_deff (void) {
	U8 i;
	dmd_alloc_pair_clean ();
	dmd_map_overlay ();
	dmd_clean_page_low ();

	dmd_draw_thin_border (dmd_low_buffer);

	sprintf ("%d", num_targets_shot);
	font_render_string_left (&font_var5, 2, 2, sprintf_buffer);



	//*******************************************************************//
	//draw bullets across bottom of screen
	//*******************************************************************//
	for(i = 0; i < num_bullets_left; i++) {
		if (i < 32) bitmap_blit (bullet_bits, i * 4, 29);
//		if (i < 32) font_render_string_left (&font_dmgraphs, i * 4, 29, "Z");
	}


	//*******************************************************************//
	//draw target
	//*******************************************************************//
	for(i = 0; i <TOTAL_TARGETS; i++) {
			if ( target_state[i] && target_state[i] < 200 ) { //released and not shot
				U8 x;
				x = 118;
				switch (i % 6) {
					case 2: x = 88; break;
					case 4: x = 103; break;
					case 0: x = 118; break; //- 128 is end
					case 1: x = 10; break; //- 0 is start
					case 5: x = 25; break;
					case 3: x = 40; break; //- 64 is center
				}//end of switch

				if (target_state[i] < 5) 	font_render_string_left (&font_dmgraphs, x, target_state[i], "A");
				else { switch ( (i + shooter_frame_counter) % 2) {
							case 0: font_render_string_left (&font_dmgraphs, x, target_state[i], "B"); break;
							case 1: font_render_string_left (&font_dmgraphs, x, target_state[i], "C"); break;
							case 2: font_render_string_left (&font_dmgraphs, x, target_state[i], "D"); break;
							case 3: font_render_string_left (&font_dmgraphs, x, target_state[i], "E"); break;
						} //END OF SWITCH
				}//end of else
			}//end of if target_state[i] && target_state[i] != 255
		}// end of loop



	//*******************************************************************//
	//draw splash if just shot
	//*******************************************************************//
	for (i = 0; i <TOTAL_TARGETS; i++) {
			if ( target_state[i] > 200 && target_state[i] != 255 ) { //released and shot
				U8 x;
				x = 118;
				switch (i % 6) {
					case 2: x = 88; break;
					case 4: x = 103; break;
					case 0: x = 118; break; //- 128 is end
					case 1: x = 10; break; //- 0 is start
					case 5: x = 25; break;
					case 3: x = 40; break; //- 64 is center
				}//end of switch
				bitmap_blit (splash_bits, x, target_state[i] - 200);
				target_state[i] = 255;
			}//end of if
	}//end of loop




	//*******************************************************************//
	//draw player
	//*******************************************************************//
		dmd_text_outline ();
		dmd_alloc_pair_clean ();
		if (face_to_show == 1) 			frame_draw (IMG_SHOOTER_CENTER);
		else if (face_to_show == 0) 	frame_draw (IMG_SHOOTER_LEFT);
		else 						 	frame_draw (IMG_SHOOTER_RIGHT);
		dmd_overlay_outline ();
		dmd_show2 ();

	//*******************************************************************//
	//here we are relying on the fact that this deff is restartable, then
	//it should never wait this full sec.  we only put this delay here
	//to prevent the default score display from showing
	//*******************************************************************//
	task_sleep (TIME_1S);
	deff_exit ();
}//end function






void shooter_abort_deff (void) {
	sound_start (ST_EFFECT, LOW_HORN, SL_1S, PRI_GAME_QUICK3);

	dmd_alloc_low_clean ();
		font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "ABORT");
		sprintf_score (target_score);
		font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, sprintf_buffer);
	dmd_copy_low_to_high ();
	dmd_show_low ();
	dmd_invert_page (dmd_low_buffer);
	deff_swap_low_high (3, TIME_100MS);
	deff_exit ();
}//end function






void shooter_intro_deff (void) {
	U8 i;
	for (i = 0; i < 4; i++) {
		dmd_alloc_low_clean ();
		sound_start (ST_EFFECT, LOW_HORN, SL_1S, PRI_GAME_QUICK3);
		font_render_string_center (&font_var5, 64, 2, "PRESS THUMBS TO ABORT");
		font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_MIDDLE_Y, "SHOOTER");
		if (i == 1)	font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot+1, "3");
		if (i == 2)	font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot+1, "2");
		if (i == 3)	font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot+1, "1");
		dmd_show_low ();
		task_sleep (TIME_500MS);
	}
	deff_exit ();
}//end function






void shooter_end_deff (void) {
	U16 fno;
	U8 i;
	for (i = 0; i < 4; i++) {
		for (fno = IMG_MUSEUM_D3_START; fno <= IMG_MUSEUM_D3_END; fno += 2) {
			dmd_alloc_pair ();
			frame_draw(fno);
			dmd_show2 ();
			sound_start (ST_EFFECT, GUNSHOT_MUFFLED, SL_1S, PRI_GAME_QUICK3);
			task_sleep (TIME_66MS);
		}//end of inner loop
			if (i == 3) 	sound_start (ST_EFFECT, GUNSHOT, SL_1S, PRI_GAME_QUICK3);
	}//end of outer loop

	dmd_alloc_low_clean ();
	sprintf ("%d SHOT", num_targets_shot);
		font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_MIDDLE_Y, sprintf_buffer);
	dmd_sched_transition (&trans_scroll_down);
	dmd_show_low ();

	if (num_targets_shot > 35) 	sound_start (ST_SPEECH, SPCH_GLORIOUS, SL_4S, PRI_GAME_QUICK3);
	else						sound_start (ST_SPEECH, SPCH_SIMON_LAUGH_LONG, SL_4S, PRI_GAME_QUICK3);
	task_sleep (TIME_500MS);

	if (num_targets_shot >= 40) {
		dmd_alloc_low_clean ();
			font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_MIDDLE_Y, "COMPLETED");
		dmd_sched_transition (&trans_scroll_down);
		dmd_show_low ();
		task_sleep (TIME_500MS);
	}

	dmd_alloc_low_clean ();
	sprintf_score (target_score);
	font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_MIDDLE_Y, sprintf_buffer);
	dmd_sched_transition (&trans_scroll_down);
	dmd_show_low ();
	task_sleep (TIME_500MS);
	deff_exit ();
}//end function
