/*
 * demolition man
 * eject.c
 *
 * written by James Cardona
 *
 * Location Description:
 * Retina Scan: This is the leftmost shot of the game. The ball passes through a gate
 * and into an eject that feeds the left inlane.
 * If hit hard enough through the gate, it will hit the captive eyeball.
 *
 */
/* CALLSET_SECTION (eject, __machine4__) */

#include <freewpc.h>
#include "dm/global_constants.h"
#include "search.h"
#include "ballsave.h"



//local variables
U8 eject_killer_counter;
U8 retina_scan_multiplier;
U8 ejectDeffCounter;
score_t temp_score;
U8 eject_kick_attempts;
__boolean is_normal_eject_killed;


//external variables
extern __local__ U8 jet_shots_made;//external ref to eject.c


//internally called function prototypes  --external found at protos.h
void eject_reset (void);
void player_eject_reset (void);



/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
void eject_reset (void) {
	retina_scan_multiplier = 1;
	is_normal_eject_killed = FALSE;
}//end of function




void player_eject_reset (void) {
	eject_killer_counter = 0;
	eject_reset ();
	ejectDeffCounter = 0;
	eject_kick_attempts = 0;
}//end of function




CALLSET_ENTRY (eject, start_player) 	{ player_eject_reset(); }
CALLSET_ENTRY (eject, start_ball) 		{ eject_reset(); }

CALLSET_ENTRY (eject, amode_start) 		{
	if (switch_poll_logical (SW_EJECT) ) 	sol_request (SOL_EJECT); //request to fire the eject sol
}//end of function


/****************************************************************************
 * eject saucer
 ****************************************************************************/
__boolean get_normal_eject_killed_status (void) {
		if (is_normal_eject_killed) return TRUE;
		else return FALSE;
}//end of function



void set_normal_eject_killed_status (__boolean status) {
		is_normal_eject_killed = status;
}//end of function



//this should reach her if there are two balls on the saucer in rapid succession or if first ball doesn't leave
CALLSET_ENTRY (eject, dev_eyeball_eject_kick_failure) {
	eject_kick_attempts++;
	task_sleep (TIME_1S);
	sol_request (SOL_EJECT); //request to fire the eject sol
}//end of function




//this is a 2 second ball save timer for eject coil - see below
void eject_switch_task (void) {
	task_sleep_sec(2);
	task_exit();
}//end of function





//if eject coil just fired then this was probably an inadvertent drain so give the ball back
CALLSET_ENTRY (eject, sw_left_outlane) {
	//if eject accidently cause a left drain then give the ball back
	//immediately - unless ball save is active in which case the ball will come back
	//anyway
	if (in_game && !in_tilt && task_kill_gid(GID_EJECT_1) && !ballsave_test_active() ) 	serve_ball_auto ();
}//end of function





CALLSET_ENTRY (eject, dev_eyeball_eject_enter) {
	if (!in_game) {
		sol_request (SOL_EJECT);
		task_sleep (TIME_1S);
	}
	else {
			//HUXLEY MADE
			if ( !get_back_in_the_fridge_running()
				&&	!get_back_in_the_fridge_ending()
				&&	task_kill_gid(GID_LEFT_INLANE_MADE)  && !in_tilt) {
				is_normal_eject_killed = TRUE;
				huxley_made();
				return;
			}//end of huxley made

			//START VIDEO MODE
			else if (  (system_config.disable_kaboom  == NO || system_config.disable_simon_says == NO || system_config.disable_shooter == NO)
					&&	flag_test (FLAG_VIDEO_MODE_ENABLED)
					&&  !in_tilt
					&&	!get_back_in_the_fridge_running()
					&&	!get_back_in_the_fridge_ending()
					&& !get_fortress_running ()
					&& !get_museum_running ()
					&& !get_cryoprison_running ()
					&& !get_wasteland_running ()
					&& !get_demotime_running ()
					&& !is_frenzy_running () ) {       //this is here since starting frenzy dumps ball into eject hole
					switch (get_next_video_mode() ) {
							case 0: start_kaboom(); 		break;
							case 1: start_simon_says(); 	break;
							case 2: start_shooter(); 		break;
							}//end of switch
							combo_rehit_check (); //check to see if enough combos to relight video mode
							//we just returned from video mode so flash the lights before you fire the coil
							leff_start (LEFF_EJECT);
							task_sleep (TIME_500MS);

							sol_request (SOL_EJECT); //request to fire the eject sol
							task_create_gid1 (GID_EJECT_1, eject_switch_task);
							ball_search_monitor_start ();
							task_sleep (TIME_300MS);
			}//end of start video mode

			//NORMAL RETINA SCAN
			else if (!is_normal_eject_killed ) {
					if (!in_tilt) {
						score (EJECT_SCORE);
						//100k per jet hit here
						if (jet_shots_made > 0) {
							score_zero (temp_score);//zero out temp score
							score_add (temp_score, score_table[SC_100K]);//multiply 100K by jet count
							score_mul (temp_score, jet_shots_made);//multiply 100K by jet count
							score_long (temp_score); //add temp score to player's score
						}//end of if

						if (retina_scan_multiplier == 2)	{
							sound_start(ST_SPEECH, SPCH_DOUBLE_RETINA_SCAN, SL_4S, PRI_GAME_QUICK4);
							score (EJECT_SCORE);
							score_long (temp_score); //add temp score to player's score
						}

						leff_start (LEFF_EJECT);
						sound_start (ST_SAMPLE, RETINA_SCAN_LONG, SL_4S, PRI_GAME_QUICK1);
						deff_start (DEFF_EJECT_EFFECT);
						task_sleep (TIME_300MS);
					}//end of not in tilt
						sol_request (SOL_EJECT); //request to fire the eject sol
						task_create_gid1 (GID_EJECT_1, eject_switch_task);//this is a 2 second ball save timer for eject coil
			}//end of else !is_normal_eject_killed = FALSE
	}//end of else in game
}//end of function




//called from comp award at underground.c
void comp_award_doub_retina(void) {
	retina_scan_multiplier = 2;
}//end of function



/****************************************************************************
 *
 * lighting effects
 *
 ****************************************************************************/
void eject_leff (void){
	lamp_tristate_flash(LM_RETINA_SCAN);
	flasher_pulse (FLASH_EJECT_FL);
	task_sleep (TIME_100MS);
	flasher_pulse (FLASH_EJECT_FL);
	task_sleep (TIME_100MS);
	flasher_pulse (FLASH_EJECT_FL);
	task_sleep (TIME_100MS);
	flasher_pulse (FLASH_EJECT_FL);
	task_sleep (TIME_100MS);
	flasher_pulse (FLASH_EJECT_FL);
	task_sleep (TIME_100MS);
	flasher_pulse (FLASH_EJECT_FL);
	task_sleep (TIME_100MS);
	flasher_pulse (FLASH_EJECT_FL);
	task_sleep (TIME_100MS);
	flasher_pulse (FLASH_EJECT_FL);
	task_sleep (TIME_100MS);
	flasher_pulse (FLASH_EJECT_FL);
	task_sleep (TIME_100MS);
	flasher_pulse (FLASH_EJECT_FL);
	lamp_tristate_off(LM_RETINA_SCAN);
	leff_exit();
}//end of function




/****************************************************************************
 *
 * DISPLAY EFFECTS
 *
 ****************************************************************************/
void eject_effect_deff(void) {
	U16 fno;
	dmd_clean_page_high ();//
	dmd_clean_page_low ();//
	switch (++ejectDeffCounter % 2) {
		default:
		case 0:
					for (fno = IMG_EYE_B_START; fno <= IMG_EYE_B_END; fno += 2) {
							dmd_alloc_pair ();
							frame_draw(fno);
							dmd_show2 ();
							task_sleep (TIME_66MS);
						}//end of inner loop

					for (fno = IMG_EYE_B_END - 2; fno >= IMG_EYE_B_START + 6; fno -= 2) {
							dmd_alloc_pair ();
							frame_draw(fno);
							dmd_show2 ();
							task_sleep (TIME_66MS);
						}//end of inner loop

					for (fno = IMG_EYE_B_START + 4; fno >= IMG_EYE_B_START + 2; fno -= 2) {
						dmd_map_overlay ();
						dmd_clean_page_low ();
							font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "RETINA");
							font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "SCAN");
						dmd_text_outline ();
						dmd_alloc_pair ();
						frame_draw(fno);
						dmd_overlay_outline ();
						dmd_show2 ();
						task_sleep (TIME_66MS);
					}//end of inner loop
			break;
		case 1:
					for (fno = IMG_EYE_START; fno <= IMG_EYE_27; fno += 2) {
						dmd_alloc_pair ();
						frame_draw(fno);
						dmd_show2 ();
						task_sleep (TIME_66MS);
					}//end of inner loop

				dmd_alloc_pair_clean ();// Clean both pages
				for (fno = IMG_EYE_28; fno <= IMG_EYE_END; fno += 2) {
					dmd_map_overlay ();
					dmd_clean_page_low ();
						font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "RETINA");
						font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "SCAN");
					dmd_text_outline ();
					dmd_alloc_pair ();
					frame_draw(fno);
					dmd_overlay_outline ();
					dmd_show2 ();
					task_sleep (TIME_66MS);
				}//end of inner loop
			break;
		}//end of switch
	deff_exit ();
}//end of mode_effect_deff



