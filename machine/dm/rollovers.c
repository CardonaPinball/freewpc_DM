/*
 * demolition man
 * rollovers.c
 *
 * written by James Cardona
 *
 * Location Description:
 * MTL rollovers: In the top right corner are three rollovers which advance
 * the bonus multiplier. Balls leave the rollovers into the jet bumpers.
 * These are very hard to see from the player's point of view.
 * Especially the leftmost (M) rollover.
 *
 * MTL rollovers
 * are actually left, center, right but
 * are labeled middle, top, lower where
 * left is called middle
 * center is called top
 * right is called lower
 *
 * Scoring Description: (original game)
 * MTL Rollovers light an increasing bonus (2x, 3x, 4x, 5x) multiplier. The bonus
 * multiplier is not scored until the end of the ball.
 * Getting the 5x bonus multiplier also lights the extra ball on the left loop (orbit).
 * Each completed MTL rollover sequence lights Access Claw at the left inlane.
 * Hitting an unlit 250k, lit one 100k
 * all 3 500k bonus
 *
 * Scoring Description: (my rules)
 * same as original
 *
 */
/* CALLSET_SECTION (rollovers, __machine__) */


#include <freewpc.h>
#include "dm/global_constants.h"

//constants
#define			max_rollover_bonus_multiplier  5

//local variables
__boolean 			middle_rollover_activated;
__boolean 			top_rollover_activated;
__boolean 			lower_rollover_activated;
U8 					rollover_bonus_multiplier; // 0 to 5
U8					rollover_SoundCounter;
U8					rollover_MessageCounter;

//external variables


//internally called function prototypes  --external found at protos.h
void rollover_reset (void);
void all_rollover_made (void);
void rollover_sounds_already_lit(void);
void rollovers_mtl_effect(void);

/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
void rollover_reset (void) {
	rollover_SoundCounter = 0;
	rollover_MessageCounter = 0;
	middle_rollover_activated = TRUE;
	top_rollover_activated = FALSE;
	lower_rollover_activated = FALSE;
	rollover_bonus_multiplier = 1;

	lamp_tristate_on(LM_MIDDLE_ROLLOVER);
	lamp_tristate_off(LM_TOP_ROLLOVER);
	lamp_tristate_off(LM_LOWER_ROLLOVER);
}//end of rollover_reset

void player_rollover_reset (void) { }//end of function

CALLSET_ENTRY (rollovers, start_player) { player_rollover_reset(); }
CALLSET_ENTRY (rollovers, start_ball) { rollover_reset(); }


/****************************************************************************
 * body
 ***************************************************************************/
void all_rollover_made (void){
	lamp_tristate_flash(LM_MIDDLE_ROLLOVER);
	lamp_tristate_flash(LM_TOP_ROLLOVER);
	lamp_tristate_flash(LM_LOWER_ROLLOVER);
	if (rollover_bonus_multiplier < max_rollover_bonus_multiplier) {
		++rollover_bonus_multiplier;
		deff_start (DEFF_ALL_ROLLOVERS_EFFECT);
	}
	else if (rollover_bonus_multiplier == max_rollover_bonus_multiplier) start_extraball();
	task_sleep (TIME_2S);
	lamp_tristate_off(LM_MIDDLE_ROLLOVER);
	lamp_tristate_off(LM_TOP_ROLLOVER);
	lamp_tristate_off(LM_LOWER_ROLLOVER);
	middle_rollover_activated = FALSE;
	top_rollover_activated = FALSE;
	lower_rollover_activated = FALSE;
	score (ALL_ROLLOVERS_SCORE);
	//light access claw
	increment_access_claw_light_on();//at inlanes.c
}//end of function


//note that switch is called left rollover corresponds to light called middle rollover
CALLSET_ENTRY (rollovers, sw_left_rollover) {
	if (in_game && !in_tilt) {
			//if already lit
			if (middle_rollover_activated) {
				rollover_sounds_already_lit();
				score (ROLLOVERS_SCORE1);
				}
			else { //else - not already lit, so activate rollover
				lamp_tristate_flash(LM_MIDDLE_ROLLOVER);
				task_sleep (TIME_500MS);
				lamp_tristate_on(LM_MIDDLE_ROLLOVER);
				middle_rollover_activated = TRUE;
				score (ROLLOVERS_SCORE2);
				//check to see if this is the third rollover to activate
				if (top_rollover_activated && lower_rollover_activated) all_rollover_made();
				else 	deff_start (DEFF_ROLLOVERS_EFFECT);
			}//end of else - not already lit, so activate rollover
	}//end of 	if (in_game && !in_tilt)
}//end of function rollovers_sw_middle_rollover



//note that switch is called center rollover corresponds to light called top rollover
CALLSET_ENTRY (rollovers, sw_center_rollover) {
	if (in_game && !in_tilt) {
			if (top_rollover_activated) {
				rollover_sounds_already_lit();
				score (ROLLOVERS_SCORE1);
				}
			else { //activate rollover
				lamp_tristate_flash(LM_TOP_ROLLOVER);
				task_sleep (TIME_500MS);
				lamp_tristate_on(LM_TOP_ROLLOVER);
				top_rollover_activated = TRUE;
				score (ROLLOVERS_SCORE2);
				//check to see if this is the third rollover to activate
				if (middle_rollover_activated && lower_rollover_activated)  all_rollover_made();
				else 	deff_start (DEFF_ROLLOVERS_EFFECT);
			}//end of else - not already lit, so activate rollover
	}//end of 	if (in_game && !in_tilt)
}//end of function rollovers_sw_top_rollover



//note that switch called right rollover corresponds to light called lower rollover
CALLSET_ENTRY (rollovers, sw_right_rollover) {
	if (in_game && !in_tilt) {
			if (lower_rollover_activated) {
				rollover_sounds_already_lit();
				score (ROLLOVERS_SCORE1);
				}
			else { //activate rollover
				lamp_tristate_flash(LM_LOWER_ROLLOVER);
				task_sleep (TIME_500MS);
				lamp_tristate_on(LM_LOWER_ROLLOVER);
				lower_rollover_activated = TRUE;
				score (ROLLOVERS_SCORE2);
				//check to see if this is the third rollover to activate
				if (middle_rollover_activated && top_rollover_activated)  all_rollover_made();
				else 	deff_start (DEFF_ROLLOVERS_EFFECT);
			}//end of else - not already lit, so activate rollover
	}//end of 	if (in_game && !in_tilt)
}//end of function rollovers_sw_lower_rollover



	/****************************************************************************
	 * rotate rollovers when buttons pressed
	 ***************************************************************************/
CALLSET_ENTRY (rollovers, sw_left_button, sw_upper_left_button) {
	if (in_game && !in_tilt && valid_playfield && 	!flag_test(FLAG_VIDEO_MODE_RUNNING) ) {
			if (top_rollover_activated && lower_rollover_activated) { //left (M) not activated
				lamp_tristate_on(LM_MIDDLE_ROLLOVER);
				lamp_tristate_on(LM_TOP_ROLLOVER);
				lamp_tristate_off(LM_LOWER_ROLLOVER);
				middle_rollover_activated = TRUE;
				top_rollover_activated = TRUE;
				lower_rollover_activated = FALSE;
				}
			else if (middle_rollover_activated && lower_rollover_activated) { //center (T) not activated
				lamp_tristate_off(LM_MIDDLE_ROLLOVER);
				lamp_tristate_on(LM_TOP_ROLLOVER);
				lamp_tristate_on(LM_LOWER_ROLLOVER);
				middle_rollover_activated = FALSE;
				top_rollover_activated = TRUE;
				lower_rollover_activated = TRUE;
				}
			else if (middle_rollover_activated && top_rollover_activated) { //right (L) not activated
				lamp_tristate_on(LM_MIDDLE_ROLLOVER);
				lamp_tristate_off(LM_TOP_ROLLOVER);
				lamp_tristate_on(LM_LOWER_ROLLOVER);
				middle_rollover_activated = TRUE;
				top_rollover_activated = FALSE;
				lower_rollover_activated = TRUE;
				}
			else if (middle_rollover_activated) { //center and right not activated
				lamp_tristate_off(LM_MIDDLE_ROLLOVER);
				lamp_tristate_off(LM_TOP_ROLLOVER);
				lamp_tristate_on(LM_LOWER_ROLLOVER);
				middle_rollover_activated = FALSE;
				lower_rollover_activated = TRUE;
				top_rollover_activated = FALSE;
				}
			else if (top_rollover_activated) { //left and right not activated
				lamp_tristate_on(LM_MIDDLE_ROLLOVER);
				lamp_tristate_off(LM_TOP_ROLLOVER);
				lamp_tristate_off(LM_LOWER_ROLLOVER);
				middle_rollover_activated = TRUE;
				top_rollover_activated = FALSE;
				lower_rollover_activated = FALSE;
				}
			else if (lower_rollover_activated) { //left and center not activated
				lamp_tristate_off(LM_MIDDLE_ROLLOVER);
				lamp_tristate_on(LM_TOP_ROLLOVER);
				lamp_tristate_off(LM_LOWER_ROLLOVER);
				middle_rollover_activated = FALSE;
				top_rollover_activated = TRUE;
				lower_rollover_activated = FALSE;
				}
	}//end of if (in_live_game)
}//end of function to rotate left



//rotate rollovers when buttons pressed
CALLSET_ENTRY (rollovers, sw_right_button, sw_upper_right_button) {
	if (in_game && !in_tilt && valid_playfield && 	!flag_test(FLAG_VIDEO_MODE_RUNNING) ) {
			if (top_rollover_activated && lower_rollover_activated) { //left not activated
				lamp_tristate_on(LM_MIDDLE_ROLLOVER);
				lamp_tristate_off(LM_TOP_ROLLOVER);
				lamp_tristate_on(LM_LOWER_ROLLOVER);
				middle_rollover_activated = TRUE;
				top_rollover_activated = FALSE;
				lower_rollover_activated = TRUE;
				}
			else if (middle_rollover_activated && lower_rollover_activated) { //center not activated
				lamp_tristate_on(LM_MIDDLE_ROLLOVER);
				lamp_tristate_on(LM_TOP_ROLLOVER);
				lamp_tristate_off(LM_LOWER_ROLLOVER);
				middle_rollover_activated = TRUE;
				top_rollover_activated = TRUE;
				lower_rollover_activated = FALSE;
				}
			else if (middle_rollover_activated && top_rollover_activated) { //right not activated
				lamp_tristate_off(LM_MIDDLE_ROLLOVER);
				lamp_tristate_on(LM_TOP_ROLLOVER);
				lamp_tristate_on(LM_LOWER_ROLLOVER);
				middle_rollover_activated = FALSE;
				top_rollover_activated = TRUE;
				lower_rollover_activated = TRUE;
				}
			else if (middle_rollover_activated) { //center and right not activated
				lamp_tristate_off(LM_MIDDLE_ROLLOVER);
				lamp_tristate_on(LM_TOP_ROLLOVER);
				lamp_tristate_off(LM_LOWER_ROLLOVER);
				middle_rollover_activated = FALSE;
				top_rollover_activated = TRUE;
				lower_rollover_activated = FALSE;
				}
			else if (top_rollover_activated) { //left and right not activated
				lamp_tristate_off(LM_MIDDLE_ROLLOVER);
				lamp_tristate_off(LM_TOP_ROLLOVER);
				lamp_tristate_on(LM_LOWER_ROLLOVER);
				middle_rollover_activated = FALSE;
				top_rollover_activated = FALSE;
				lower_rollover_activated = TRUE;
				}
			else if (lower_rollover_activated) { //left and center not activated
				lamp_tristate_on(LM_MIDDLE_ROLLOVER);
				lamp_tristate_off(LM_TOP_ROLLOVER);
				lamp_tristate_off(LM_LOWER_ROLLOVER);
				middle_rollover_activated = TRUE;
				top_rollover_activated = FALSE;
				lower_rollover_activated = FALSE;
				}
	}//end of 	if (in_live_game)
}//end of function to rotate right






/****************************************************************************
 *
 * sound effects
 *
 ****************************************************************************/
void rollover_sounds_already_lit(void) {
	rollover_SoundCounter = random_scaled(2);//from kernal/random.c
	if ( rollover_SoundCounter  == 0 ) {
	sound_start (ST_EFFECT, TOINK1, SL_2S, PRI_GAME_QUICK2);
	task_sleep (TIME_100MS);
	sound_start (ST_EFFECT, TOINK1, SL_2S, PRI_GAME_QUICK2);
	task_sleep (TIME_100MS);
	sound_start (ST_EFFECT, TOINK1, SL_2S, PRI_GAME_QUICK2);
	task_sleep (TIME_100MS);
	sound_start (ST_EFFECT, TOINK1, SL_2S, PRI_GAME_QUICK2);
	}
else if ( rollover_SoundCounter  == 1 ) {
	sound_start (ST_EFFECT, TOINK2, SL_2S, PRI_GAME_QUICK2);
	task_sleep (TIME_100MS);
	sound_start (ST_EFFECT, TOINK2, SL_2S, PRI_GAME_QUICK2);
	task_sleep (TIME_100MS);
	sound_start (ST_EFFECT, TOINK2, SL_2S, PRI_GAME_QUICK2);
	task_sleep (TIME_100MS);
	sound_start (ST_EFFECT, TOINK2, SL_2S, PRI_GAME_QUICK2);
}
}//end of function


void all_rollovers_sound (void) {
	rollover_SoundCounter = random_scaled(3);//from kernal/random.c
	if ( rollover_SoundCounter  == 0 ) 		sound_start (ST_EFFECT, STORM1_SHORT, SL_2S, PRI_GAME_QUICK2);
	else if ( rollover_SoundCounter  == 1 ) sound_start (ST_EFFECT, STORM1_MED, SL_2S, PRI_GAME_QUICK2);
	else if ( rollover_SoundCounter  == 2 ) sound_start (ST_EFFECT, STORM1_LONG, SL_2S, PRI_GAME_QUICK2);
}



void rollovers_sound (void) {
	rollover_SoundCounter = random_scaled(3);//from kernal/random.c
	if ( rollover_SoundCounter  == 0 ) 		sound_start (ST_EFFECT, MACHINE1_SHORT, SL_2S, PRI_GAME_QUICK2);
	else if ( rollover_SoundCounter  == 1 ) sound_start (ST_EFFECT, MACHINE1_MED, SL_2S, PRI_GAME_QUICK2);
	else if ( rollover_SoundCounter  == 2 ) sound_start (ST_EFFECT, MACHINE1_LONG, SL_2S, PRI_GAME_QUICK2);
}



/****************************************************************************
 *
 * display effects
 *
 ****************************************************************************/
void rollovers_animation_display_effect (U16 start_frame, U16 end_frame){
	U16 fno;
	for (fno = start_frame; fno <= end_frame; fno += 2) {
		dmd_alloc_pair ();
		frame_draw(fno);
		dmd_show2 ();
		task_sleep (TIME_100MS);
	}//end of inner loop
}//end of function



void all_rollovers_effect_deff(void) {
	if (DM_IN_DMD_TEST) {
		if (rollover_bonus_multiplier <= 2) rollover_MessageCounter = 1;
		if (++rollover_bonus_multiplier > 5) rollover_MessageCounter = 2;
	}

	dmd_alloc_pair_clean ();// Clean both pages
	all_rollovers_sound ();
	rollovers_animation_display_effect (IMG_MTL_COMPLETE_START, IMG_MTL_COMPLETE_END);
	all_rollovers_sound ();
	dmd_alloc_pair_clean ();// Clean both pages
	dmd_map_overlay ();
	dmd_clean_page_low ();
	dmd_sched_transition (&trans_bitfade_slow);
	switch (rollover_bonus_multiplier) {
		default:
		case 2:  sprintf ("2X"); break;
		case 3:  sprintf ("3X"); break;
		case 4:  sprintf ("4X"); break;
		case 5:	 sprintf ("5X"); break;
		}//end of switch
	font_render_string_center (&font_halobold12, DMD_MIDDLE_X - 42, DMD_SMALL_CY_2, sprintf_buffer);
	font_render_string_center (&font_halobold12, DMD_MIDDLE_X + 42, DMD_SMALL_CY_2, sprintf_buffer);
	font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_BOTTOM_LINE, "CLAW LIT            CLAW LIT");
	dmd_text_outline ();
	dmd_alloc_pair ();
	frame_draw(IMG_MTL_COMPLETE_END);
	dmd_overlay_outline ();
	dmd_show2 ();
	task_sleep_sec (2);
	deff_exit ();
}//end of mode_effect_deff




void rollovers_effect_deff(void) {
	if (DM_IN_DMD_TEST) {	if (++rollover_MessageCounter > 2) rollover_MessageCounter = 0; }
	else						rollover_MessageCounter = random_scaled(3);

	dmd_alloc_pair_clean ();// Clean both pages
	rollovers_sound ();
	rollovers_animation_display_effect (IMG_MTL_START, IMG_MTL_END);

	dmd_alloc_pair_clean ();// Clean both pages
	dmd_map_overlay ();
	dmd_clean_page_low ();
	dmd_sched_transition (&trans_bitfade_slow);
	switch (rollover_MessageCounter) {
		default:
		case 0:
			font_render_string_center (&font_term6, DMD_MIDDLE_X, DMD_MED_CY_1, "LIGHT M T L");
			font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_3, "TO");
			font_render_string_center (&font_fixed6, DMD_MIDDLE_X, DMD_MED_CY_BOTTOM_LINE, "ADVANCE BONUS X");
			break;
		case 1:
			font_render_string_center (&font_term6, DMD_MIDDLE_X, DMD_MED_CY_1, "LIGHT M T L");
			font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_3, "TO");
			font_render_string_center (&font_fixed6, DMD_MIDDLE_X, DMD_MED_CY_BOTTOM_LINE, "LIGHT CRYOCLAW");
			break;
		case 2:
			font_render_string_center (&font_term6, DMD_MIDDLE_X, DMD_MED_CY_1, "LIGHT M T L");
			font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_MED_CY_2, "5 TIMES TO");
			font_render_string_center (&font_fixed6, DMD_MIDDLE_X, DMD_MED_CY_BOTTOM_LINE, "LIGHT EXTRA BALL");
			break;
	}//end of switch
	dmd_text_outline ();
	dmd_alloc_pair ();
	frame_draw(IMG_MTL_END);
	dmd_overlay_outline ();
	dmd_show2 ();
	rollovers_sound ();
	task_sleep_sec (1);
	deff_exit ();
}//end of mode_effect_deff

