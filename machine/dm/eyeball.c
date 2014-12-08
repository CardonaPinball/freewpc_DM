/*
 * demolition man
 * eyeball.c
 *
 * written by James Cardona
 *
 * Location Description:
 * Retina Scan: This is the leftmost shot of the game. The ball passes through a gate
 * and into an eject that feeds the left inlane.
 * If hit hard enough through the gate, it will hit the captive eyeball.
 *
 * Scoring Description: (original game)
 * Shots that knock the captive eyeball into the upper target award the Retina Scan value.
 * The Jet Bumpers increase the Retina Value.(eyeball)
 * It starts at 5M and goes up 100K per jet.
 *
 * At certain numbers of Retina Scans hits, Explode Hurry Up is activated.
 *
 */
/* CALLSET_SECTION (eyeball, __machine4__) */

#include <freewpc.h>
#include "dm/global_constants.h"
#include "eyeball.h"
#include <ballsave.h>

//constants
#define EYE_EASY_GOAL  2
#define EYE_HARD_GOAL  5
#define EYE_GOAL_STEP  3
#define EYE_GOAL_MAX  11

#define EYE_EB_EASY_GOAL  10
#define EYE_EB_HARD_GOAL  22

//local variables
U8	eyeball_MessageCounter;
U8 eyeball_eb_goal; //num of hits to light extraball - since set by game difficulty is same for every player
U8	eyeball_switch_debounce;
__local__ U8 eyeball_shots_made;
__local__ U8 eyeball_goal; //num of hits to start explode



//internally called function prototypes  --external found at protos.h
void eyeball_reset (void);
void player_eyeball_reset (void);
void eyeball_goal_award (void);
void eyeball_eb_award (void);

/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
void player_eyeball_reset (void) {
	eyeball_shots_made = 0;
	flag_off(FLAG_IS_EYEBALL_EB_MADE);
	eyeball_switch_debounce = 0;

	eyeball_goal = EYE_EASY_GOAL;
	eyeball_eb_goal = EYE_EB_EASY_GOAL;

	if (eyeball_goal <= 1) flag_on(FLAG_IS_EXPLODE_MODE_ENABLED);
	else flag_off (FLAG_IS_EXPLODE_MODE_ENABLED);

	#ifdef CONFIG_DIFFICULTY_LEVEL
		eyeball_goal = system_config.num2explode;
		eyeball_eb_goal = system_config.eyeball_eb;
	#endif
}//end of function

/****************************************************************************
 * external event listeners
 ****************************************************************************/
CALLSET_ENTRY (eyeball, start_player) 	{ player_eyeball_reset(); }



/****************************************************************************
 *
 * body
 *
 ***************************************************************************/
void eyeball_goal_award (void) {
	flag_off(FLAG_IS_EXPLODE_MODE_ENABLED);
	eyeball_shots_made = 0;
	if (eyeball_goal < EYE_GOAL_MAX)  eyeball_goal += EYE_GOAL_STEP;
	start_explode();//start explode mode
}//end of function



void eyeball_eb_award (void) {
	flag_on(FLAG_IS_EYEBALL_EB_MADE);
		sound_start (ST_SPEECH, SPCH_LOVE_WHEN_THAT_HAPPENS, SL_2S, PRI_GAME_QUICK2);
		start_extraball();
}//end of function




void eyeball_switch_debounce_task (void) {
	task_sleep_sec(2);
	eyeball_switch_debounce = 0;
	task_exit();
}//end of function



CALLSET_ENTRY (eyeball, sw_eyeball_standup) {
	if (in_game && !in_tilt) {
			if (++eyeball_switch_debounce == 1) {
						ballsave_add_time (1);
						++eyeball_shots_made;
						sound_start (ST_SAMPLE, EXPLOSION1_MED, SL_2S, PRI_GAME_QUICK1);
						leff_start(LEFF_EYEBALL);
						score (EYEBALL_SCORE);

						if (	!flag_test(FLAG_IS_EYEBALL_EB_MADE)
							&& (eyeball_shots_made >= eyeball_eb_goal) )  		eyeball_eb_award();//award extraball

						else
							if (!get_back_in_the_fridge_running()
								&&	!get_back_in_the_fridge_ending()
								&& eyeball_shots_made >= eyeball_goal) 			eyeball_goal_award();//start explode
						else
							if (is_explode_mode_running() ) 		{
											explode_made(); //EXPLODE ALREADY RUNNING SO SCORE IT
							}
						else {
							deff_start (DEFF_EYEBALL_EFFECT);
							if (eyeball_goal - eyeball_shots_made <= 1) flag_on(FLAG_IS_EXPLODE_MODE_ENABLED);//set flag if one shot away
						}//end of else
			}//end of if DEBOUNCER
			task_create_gid1 (GID_EYEBALL_DEBOUNCE, eyeball_switch_debounce_task);
	}
}//end of function





/****************************************************************************
 *
 * display effects
 *
 ****************************************************************************/
void eyeball_effect_deff(void) {
	dmd_alloc_pair_clean ();
	dmd_sched_transition (&trans_scroll_up);

	switch (++eyeball_MessageCounter % 4) {
		case 0:
			dmd_map_overlay ();
			dmd_clean_page_low ();
			font_render_string_center (&font_term6, DMD_MIDDLE_X, DMD_MED_CY_1-1, "EXPLODE AND CHASE");
			font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_MED_CY_2-1, "LEAD TO");
				font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "HUXLEY");
			dmd_text_outline ();
			dmd_alloc_pair ();
			frame_draw(IMG_HUXLEY_B2_START);
			dmd_overlay_outline ();
			dmd_show2 ();
			break;
		case 1:
			font_render_string_center (&font_term6, DMD_MIDDLE_X + 20, DMD_MED_CY_1-1, "JETS");
			font_render_string_center (&font_var5, DMD_MIDDLE_X + 20, DMD_MED_CY_2-1, "INCREASE");
				font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "RETINA");
			bitmap_blit (eye3SM_bits, 15, 2);
			dmd_show_low ();
			break;
		case 2:
			font_render_string_center (&font_term6, DMD_MIDDLE_X - 25, DMD_MED_CY_1-1, "EXPLODE");
			font_render_string_center (&font_term6, DMD_MIDDLE_X - 25, DMD_MED_CY_2-1, "AT");
			sprintf ("%d HITS", eyeball_goal - eyeball_shots_made);
				font_render_string_center (&font_halobold12, DMD_MIDDLE_X - 25, DMD_BIG_CY_Bot, sprintf_buffer);
			bitmap_blit (eye3_bits, 86, 2);
			dmd_show_low ();
			break;
		case 3:
				font_render_string_center (&font_halobold14, DMD_MIDDLE_X + 25, DMD_BIG_CY_Top, "OH MY");
				font_render_string_center (&font_halobold14, DMD_MIDDLE_X + 25, DMD_BIG_CY_Bot, "EYE");
			bitmap_blit (eye3_bits, 2, 2);
			dmd_show_low ();
			break;
	}//END OF SWITCH

	task_sleep (TIME_1S);
	task_sleep (TIME_500MS);
	deff_exit ();
}//end of mode_effect_deff


