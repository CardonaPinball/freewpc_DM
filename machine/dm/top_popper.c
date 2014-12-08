/*
 * demolition man
 * top_popper.c
 *
 * written by James Cardona
 *
 * Location Description:
 *
 * Scoring Description: (original game)
 *
 *
 * Scoring Description: (my rules)
 * same as above except
 *
 */
/* CALLSET_SECTION (top_popper, __machine4__) */


#include <freewpc.h>
#include "search.h"
#include "dm/global_constants.h"
#include "eye_bits.h"
#include "box_bits.h"


//constants
#define 		top_popperAwardsNumOfSounds  5

const sound_code_t top_popperAwardsSoundsArray[] = {	SPCH_ILUMINATE,
														SPCH_AMAZING_WES,			SPCH_AMAZING_SLY,
														SPCH_GLORIOUS,				SPCH_OUTSTANDING};

//local variables
U8 			top_popper_MessageCounter;
U8 			top_popperSwitchDebouncer;
__boolean 	top_popper_inBall_search;


//external variables


//internally called function prototypes  --external found at protos.h
void top_popper_lights_task (void);


/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
CALLSET_ENTRY (top_popper, start_player, start_ball) {
	top_popperSwitchDebouncer = 0;
	top_popper_MessageCounter = 0;
	top_popper_inBall_search = FALSE;
}



CALLSET_ENTRY (top_popper, ball_search) { 		top_popper_inBall_search = TRUE; }
CALLSET_ENTRY (top_popper, ball_search_end, end_ball) { top_popper_inBall_search = FALSE; }



/****************************************************************************
 *
 * body
 *
 ****************************************************************************/
//called from /common/replay.c
CALLSET_ENTRY (top_popper, award_extra_ball_effect) {
	leff_start (LEFF_TOP_POPPER);
	deff_start (DEFF_EXTRA_BALL_EFFECT);
}//end of function



//sw_top_popper
CALLSET_ENTRY (top_popper, dev_top_sol_enter) {
				//EXTRABALL AWARD
				if (flag_test (FLAG_IS_EXTRABALL_LIT) ) {
					score_extraball();
					task_sleep_sec(3);
				}//end of EB

				//BACK IN FRIDGE WIZARD MODE
				if (flag_test(FLAG_BACK_IN_THE_FRIDGE_ACTIVATED)) {
					ball_search_monitor_stop ();
					start_back_in_the_fridge ();
					task_sleep_sec(1);
					ball_search_monitor_start ();
				}

				//START MULTIBALL
				if (	!get_back_in_the_fridge_running()
						&&	!get_back_in_the_fridge_ending()
					&&	flag_test (FLAG_IS_MULTIBALL_ENABLED) ) {
					ball_search_monitor_stop ();
					multiball_start();
					ball_search_monitor_start ();
				}//end of multiball start

				//START VIDEO MODE
				if (  (system_config.disable_kaboom  == NO || system_config.disable_simon_says == NO || system_config.disable_shooter == NO)
						&& 	flag_test (FLAG_VIDEO_MODE_ENABLED)
						&& 	!get_back_in_the_fridge_running()
						&&	!get_back_in_the_fridge_ending()
						&& 	!get_fortress_running ()
						&& 	!get_museum_running ()
						&& 	!get_cryoprison_running ()
						&& 	!get_wasteland_running ()
						&& 	!get_demotime_running ()) { //this is set at combos
							ball_search_monitor_stop ();
							switch (get_next_video_mode()) {
								case 0: start_kaboom(); 		break;
								case 1: start_simon_says(); 	break;
								case 2: start_shooter(); 		break;
								}//end of switch
							combo_rehit_check (); //check to see if enough combos to relight video mode
							//we just returned from video mode so flash the lights before you fire the coil
							leff_start (LEFF_TOP_POPPER);
							task_sleep (TIME_500MS);
							sol_request_async (SOL_TOP_POPPER);
							ball_search_monitor_start ();
					}//end of start video mode

				//VM not running
				else {
					//if nothing special, do normal display effects, otherwise pop ball immediately
					if (  		!get_back_in_the_fridge_running()
							&&	!get_back_in_the_fridge_ending()
							&& 	!get_fortress_running ()
							&& 	!get_museum_running ()
							&& 	!get_cryoprison_running ()
							&& 	!get_wasteland_running ()
							&& 	!get_demotime_running ()
							&& 	!is_carchase_mode_running ()
							&& 	!is_explode_mode_running ()
							&& 	!is_acmag_running ()
							&& 	!is_capture_simon_running ()
							&& 	!is_prison_break_running ()
							&& 	!is_sjets_running ()
							&& 	!is_frenzy_running () ) {
						score (TOP_POP_SCORE);
						deff_start_sync (DEFF_TOP_POPPER_EFFECT);
						task_sleep (TIME_300MS);
					}
					//nothing special or displays are done so give back ball
					//we don't come here if in a VM so ball is released above in that case
					sol_request_async (SOL_TOP_POPPER);
					leff_start (LEFF_TOP_POPPER);
				}//end of else NOTHING SPECIAL
}//end of function



/****************************************************************************
 *
 * lighting effects
 *
 ****************************************************************************/
void top_popper_leff (void) {
	U8 i;
	for (i = 0; i < 6; i++) {
		flasher_pulse (FLASH_LEFT_RAMP_UP);
		task_sleep (TIME_66MS);
		flasher_pulse (FLASH_DIVERTER_FLASHER);
		task_sleep (TIME_66MS);
		flasher_pulse (FLASH_RIGHT_RAMP_UP);
		sound_start (ST_EFFECT, ZAPP_3_MED, SL_2S, PRI_GAME_QUICK2);
		task_sleep (TIME_100MS);
	}
	leff_exit();
}//end of function







/****************************************************************************
 *
 * display effects
 *
 ****************************************************************************/
//nothing is going on effect - top popper mystery award
void top_popper_effect_deff(void) {
	U16 fno;
	U8 i;
	i = 0;
	if (++top_popper_MessageCounter > 3) top_popper_MessageCounter = 0;

	dmd_alloc_pair_clean ();// Clean both pages

	switch (top_popper_MessageCounter) {

		case 0:
			sound_start (ST_EFFECT, TRAIN_PULL_IN, SL_2S, SP_NORMAL);
			for (fno = IMG_SIMON_E_END-2; fno >= IMG_SIMON_E_START; fno -= 2) {
				dmd_alloc_pair ();
				frame_draw(fno);
				dmd_show2 ();
				task_sleep (TIME_100MS);
			}//end of for loop
			sound_start (ST_EFFECT, TRAIN_PULL_IN, SL_2S, SP_NORMAL);
			dmd_map_overlay ();
			dmd_clean_page_low ();
			font_render_string_center (&font_term6, DMD_MIDDLE_X, DMD_MED_CY_1, "LIGHT ALL M T L");
			font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_MED_CY_2, "5 TIMES TO");
			font_render_string_center (&font_fixed6, DMD_MIDDLE_X, DMD_MED_CY_BOTTOM_LINE, "LIGHT EXTRA BALL");
			dmd_text_outline ();
			dmd_alloc_pair ();
			frame_draw(IMG_SIMON_E_START);
			dmd_overlay_outline ();
			dmd_show2 ();
			task_sleep (TIME_1S);

			dmd_map_overlay ();
			dmd_clean_page_low ();
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X + 20, DMD_MED_CY_1 + 5, "ONE");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X + 20, DMD_MED_CY_BOTTOM_LINE, "MILLION");
			dmd_text_outline ();
			dmd_alloc_pair ();
			frame_draw(IMG_SIMON_E_START);
			dmd_overlay_outline ();
			dmd_show2 ();
			task_sleep (TIME_1S);
		break;

		case 1:
			if (system_config.extra_sounds == YES || system_config.swear_sounds == YES)
				 sound_start (ST_SPEECH, SPCH_1_CREDIT_VIOLATION_MAN, SL_2S, PRI_GAME_QUICK3);
			sound_start (ST_ANY, TRAIN_PULL_IN, SL_2S, SP_NORMAL);
			do {
				dmd_alloc_low_clean ();
				if (i < 2 ) 		bitmap_blit (box1_bits, 95, 0);
				else if (i < 4 )    bitmap_blit (box2_bits, 95, 0);
				else if (i < 6 )    bitmap_blit (box3_bits, 95, 0);
				else if (i < 8 )    bitmap_blit (box4_bits, 95, 0);
				else if (i < 10 )   bitmap_blit (box5_bits, 95, 0);
				else if (i < 12 )   bitmap_blit (box6_bits, 95, 0);
				else if (i < 14 )   bitmap_blit (box5_bits, 95, 0);
				else if (i < 16 )   bitmap_blit (box4_bits, 95, 0);
				else if (i < 18 )   bitmap_blit (box3_bits, 95, 0);
				else if (i < 20 )   bitmap_blit (box2_bits, 95, 0);
				else				bitmap_blit (box1_bits, 95, 0);
				if (i > 3 )  font_render_string_center (&font_fixed6, DMD_MIDDLE_X - 10, DMD_MED_CY_1, "VIOLATION");
				if (i > 8 )  font_render_string_center (&font_term6, DMD_MIDDLE_X - 20, DMD_MED_CY_2 - 1, "ONE");
				if (i > 12 ) font_render_string_center (&font_fixed10, DMD_MIDDLE_X - 20, DMD_MED_CY_BOTTOM_LINE, "MILLION");

				dmd_show_low ();
				task_sleep (TIME_100MS);
			} while (i++ < 23);
			task_sleep (TIME_1S);
		break;

		case 2:
			sound_start (ST_SPEECH, SPCH_YOU_LOOK_GREAT_TODAY, SL_2S, SP_NORMAL);
			sound_start (ST_ANY, SPRAY_CAN, SL_2S, SP_NORMAL);
			do {
					dmd_alloc_low_clean ();
					if (i < 3 ) 		bitmap_blit (jets_eye3_bits, 2, 4);
					else if (i < 6 )    bitmap_blit (jets_eye4_bits, 2, 4);
					else if (i < 9 )    bitmap_blit (jets_eye5_bits, 2, 4);
					else if (i < 12 )   bitmap_blit (jets_eye6_bits, 2, 4);
					else if (i < 15 )   bitmap_blit (jets_eye5_bits, 2, 4);
					else if (i < 18 )   bitmap_blit (jets_eye4_bits, 2, 4);
					else				bitmap_blit (jets_eye3_bits, 2, 4);

					if (i > 3 )  font_render_string_center (&font_fixed6, DMD_MIDDLE_X, DMD_MED_CY_1, "YOU");
					if (i > 8 )	 font_render_string_center (&font_var5, DMD_MIDDLE_X + 39, DMD_MED_CY_1, "LOOK");
					if (i > 12 ) font_render_string_center (&font_fixed6, DMD_MIDDLE_X + 18, DMD_MED_CY_2 + 1, "GREAT");
					if (i > 15 ) font_render_string_center (&font_term6, DMD_MIDDLE_X + 20, DMD_MED_CY_BOTTOM_LINE, "TODAY");
					dmd_show_low ();
					task_sleep (TIME_66MS);
			} while (i++ < 21);
			task_sleep (TIME_1S);
			sound_start (ST_ANY, TRAIN_PULL_IN, SL_2S, SP_NORMAL);
			dmd_alloc_low_clean ();
			bitmap_blit (jets_eye3_bits, 2, 4);
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X + 20, DMD_MED_CY_1 + 5, "ONE");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X + 20, DMD_MED_CY_BOTTOM_LINE, "MILLION");
			dmd_show_low ();
			task_sleep (TIME_1S);
		break;

		case 3:
			if (system_config.extra_sounds == YES || system_config.swear_sounds == YES)
							sound_start (ST_SPEECH, SPCH_ENHANCE_YOUR_CALM_MAN, SL_2S, PRI_GAME_QUICK3);
			sound_start (ST_ANY, TRAIN_PULL_IN, SL_2S, SP_NORMAL);
			do {
					dmd_alloc_low_clean ();
					if (i < 2 ) 		bitmap_blit (box1_bits, 95, 0);
					else if (i < 4 )    bitmap_blit (box2_bits, 95, 0);
					else if (i < 6 )    bitmap_blit (box3_bits, 95, 0);
					else if (i < 8 )    bitmap_blit (box4_bits, 95, 0);
					else if (i < 10 )   bitmap_blit (box5_bits, 95, 0);
					else if (i < 12 )   bitmap_blit (box6_bits, 95, 0);
					else if (i < 14 )   bitmap_blit (box5_bits, 95, 0);
					else if (i < 16 )   bitmap_blit (box4_bits, 95, 0);
					else if (i < 18 )   bitmap_blit (box3_bits, 95, 0);
					else if (i < 20 )   bitmap_blit (box2_bits, 95, 0);
					else				bitmap_blit (box1_bits, 95, 0);
					if (i > 3 )  font_render_string_center (&font_fixed6, DMD_MIDDLE_X - 10, DMD_MED_CY_1, "ENHANCE");
					if (i > 8 )  font_render_string_center (&font_fixed6, DMD_MIDDLE_X - 18, DMD_MED_CY_2 + 2, "YOUR");
					if (i > 12 ) font_render_string_center (&font_term6, DMD_MIDDLE_X - 20, DMD_MED_CY_BOTTOM_LINE, "CALM");
					dmd_show_low ();
					task_sleep (TIME_100MS);
			} while (i++ < 23);
			task_sleep (TIME_1S);
			sound_start (ST_ANY, TRAIN_PULL_IN, SL_2S, SP_NORMAL);
			dmd_alloc_low_clean ();
			bitmap_blit (box1_bits, 95, 0);
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X - 20, DMD_MED_CY_1 + 5, "ONE");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X - 20, DMD_MED_CY_BOTTOM_LINE, "MILLION");
			dmd_show_low ();
			task_sleep (TIME_1S);
		break;
	}//END OF SWITCH
	task_sleep (TIME_1S);
	deff_exit ();
}//end of mode_effect_deff







