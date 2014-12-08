/*
 * demolition man
 * inlanes.c
 * 
 * written by James Cardona
 *
 * Location Description:
 * inlanes are lanes that feed to flippers as opposed to outlanes which feed
 * to the drain
 *
 * Scoring Description: (original game)
 * an unlit or lit lane score 5770
 * if lit, you recieve whatever the light says - access claw on left
 * will move the claw diverter to open it - when the diverter moves, the
 * light goes out
 * on the right inlane is quick freeze, getting this inlane will then
 * light quick freeze light on left ramp and to freeze a ball you must then shoot
 * the left ramp.  The light quick freeze inlane light does not go out until
 * the left ramp is shot and the ball is frozen
 *
 * access claw can be lit by completing MTL rollovers,
 *
 * Depending on machine settings, One, Two, or Three sets of
 * standup targets must be completed to light Quick Freeze, depending on
 * whether Quick Freeze is set to easy, medium, or hard.
 *
 * Scoring Description: (my rules)
 * same as above
 *
 *
 * */


#include <freewpc.h>
#include "dm/global_constants.h"

//local variables
__local__ U8 increment_access_claw_light;  //needed for situation where player stacks lights but not yet collected
__local__ U8 increment_quick_freeze_light; //needed for situation where player stacks lights but not yet collected

//external variables

//prototypes
void left_inlane_task (void);



/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
CALLSET_ENTRY (inlanes, start_player) {
	flag_on(FLAG_IS_ACCESS_CLAW_ACTIVATED);
	lamp_tristate_on(LM_ACCESS_CLAW);
	flag_on(FLAG_IS_QUICK_FREEZE_ACTIVATED);
	lamp_tristate_on(LM_LIGHT_QUICK_FREEZE);
	increment_access_claw_light = 0;
	increment_quick_freeze_light = 1;
}//end of reset

CALLSET_ENTRY (inlanes, end_ball) {
	lamp_tristate_off(LM_ACCESS_CLAW);
	lamp_tristate_off(LM_LIGHT_QUICK_FREEZE);
}


CALLSET_ENTRY (inlanes, start_ball) {
	if (flag_test(FLAG_IS_ACCESS_CLAW_ACTIVATED)) lamp_tristate_on (LM_ACCESS_CLAW); else  lamp_tristate_off (LM_ACCESS_CLAW);
	if (flag_test(FLAG_IS_QUICK_FREEZE_ACTIVATED)) lamp_tristate_on (LM_LIGHT_QUICK_FREEZE); else lamp_tristate_off (LM_LIGHT_QUICK_FREEZE);
}//end of function




/****************************************************************************
 * left inlane
 *
 * access claw can be lit by:
 * 			 	completing MTL rollovers,
 * 				random award from computer (subway shot), or
 * 				completing certain number of arrow shots
 *
 ***************************************************************************/
void increment_access_claw_light_on(void) {
	increment_access_claw_light++;
	if (!flag_test(FLAG_IS_ACCESS_CLAW_ACTIVATED)) access_claw_light_on();
}//end of function



void check_access_claw_relight (void) {
	if (increment_access_claw_light) access_claw_light_on();
}//end of function



void access_claw_light_on(void) {
	increment_access_claw_light--;
	flag_on(FLAG_IS_ACCESS_CLAW_ACTIVATED);
	lamp_tristate_flash(LM_ACCESS_CLAW);
	task_sleep (TIME_500MS);
	lamp_tristate_on (LM_ACCESS_CLAW);
}//end of function



void access_claw_light_off(void) {
	if (!increment_access_claw_light) {
		flag_off(FLAG_IS_ACCESS_CLAW_ACTIVATED);
		lamp_tristate_flash(LM_ACCESS_CLAW);
		task_sleep (TIME_500MS);
		lamp_tristate_off (LM_ACCESS_CLAW);
	}
}//end of function


//this task is here to detect a HUXLEY shot
void left_inlane_task (void) { task_sleep_sec(1); task_sleep (TIME_500MS); task_exit(); }




CALLSET_ENTRY (inlanes, sw_left_inlane) {
	if (in_game && !in_tilt) {
		task_create_gid1 (GID_LEFT_INLANE_MADE, left_inlane_task);
		score(INLANE_SCORE);
		sound_start (ST_SAMPLE, INLANE_SOUND, SL_2S, PRI_GAME_QUICK2);

		//enable claw but do not actually move diverter yet
		if (		flag_test(FLAG_IS_ACCESS_CLAW_ACTIVATED)
				&& !flag_test(FLAG_IS_R_RAMP_CLAWREADY)
				&& !is_cryoclaw_mode_running () ) 	{
					flag_on(FLAG_IS_R_RAMP_CLAWREADY);
					access_claw_light_off();
					sound_start (ST_SPEECH, SPCH_CRYOCLAW_ACTIVATED, SL_4S, PRI_GAME_QUICK5);
					leff_start (LEFF_INLANE_CRYOCLAW);
					deff_start (DEFF_CLW_INLANES_EFFECT);
		}//end of if

		//actually move diverter if nothing else is running that needs the right ramp
		if (!get_back_in_the_fridge_running()
			&&	!get_back_in_the_fridge_ending()
			&& 	flag_test(FLAG_IS_R_RAMP_CLAWREADY)
			&&	!get_fortress_running ()
			&&	!get_museum_running ()
			&&	!get_cryoprison_running ()
			&&	!get_wasteland_running ()
			&&	!get_capture_simon_arrows (CAPSIM_RIGHTRAMP)
			&&	!is_huxley_running ()
			&&	!get_demotime_running ()
			&&	!is_cryoclaw_mode_running () ) {
						rramp_clawready_on();//at ramps.c - diverter moved there
		}//end of if
	}
}//end of function



/****************************************************************************
 * right inlane
 ***************************************************************************/
void increment_light_quick_freeze_light (void) {
	increment_quick_freeze_light++;
	if (!flag_test(FLAG_IS_QUICK_FREEZE_ACTIVATED)) light_quick_freeze_light_on();
}//end of function



void light_quick_freeze_light_on (void) {
	flag_on(FLAG_IS_QUICK_FREEZE_ACTIVATED);
	sound_start (ST_SPEECH, SPCH_QUICK_FREEZE_ACTIVATED, SL_4S, PRI_GAME_QUICK5);
	lamp_tristate_flash(LM_LIGHT_QUICK_FREEZE);
	task_sleep (TIME_500MS);
	lamp_tristate_on (LM_LIGHT_QUICK_FREEZE);
}//end of function


//called by lock_freeze...c when left ramp is hit and freeze is inc'ed
void light_quick_freeze_light_off(void) {
	if (--increment_quick_freeze_light <= 0){
		increment_quick_freeze_light = 0;
		flag_off(FLAG_IS_QUICK_FREEZE_ACTIVATED);
		lamp_tristate_flash(LM_LIGHT_QUICK_FREEZE);
		task_sleep (TIME_500MS);
		lamp_tristate_off (LM_LIGHT_QUICK_FREEZE);
	}
}//end of function



CALLSET_ENTRY (inlanes, sw_right_inlane) {
	if (in_game && !in_tilt) {
		score(INLANE_SCORE);
		sound_start (ST_SAMPLE, INLANE_SOUND, SL_2S, PRI_GAME_QUICK2);
		if (!flag_test(FLAG_IS_LRAMP_QUICKFREEZE_ACTIVATED) && 	flag_test(FLAG_IS_QUICK_FREEZE_ACTIVATED)) {
			activate_left_ramp_quickfreeze();//at ramps.c
			deff_start (DEFF_QF_INLANES_EFFECT);
		}
	}
}//end of function




/****************************************************************************
 *
 * display effects
 *
 ****************************************************************************/
void clw_inlanes_effect_deff(void) {
	U16 i;
	for (i = IMG_CRYOCLAW_MARIO_START; i < IMG_CRYOCLAW_MARIO_END; i+=2) {
			dmd_map_overlay ();
			dmd_clean_page_low ();
				font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "RIGHT RAMP");
			dmd_text_outline ();
			dmd_alloc_pair ();
			frame_draw(i);
			dmd_overlay_outline ();
			dmd_show2 ();
		task_sleep (TIME_100MS);
	}//END OF LOOP
	deff_exit ();
}//end of mode_effect_deff





void qf_inlanes_effect_deff(void) {
	U16 fno;
	for (fno = IMG_QUICK_FREEZE_START; fno <= IMG_QUICK_FREEZE_END; fno += 2) {
		dmd_alloc_pair_clean ();
		frame_draw(fno);
		dmd_show2 ();
		task_sleep (TIME_100MS);
	}//end of inner loop
	dmd_alloc_pair_clean ();// Clean both pages
		dmd_map_overlay ();
		dmd_clean_page_low ();
			font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "FREEZE");
			font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "LEFT RAMP");
		dmd_text_outline ();
		dmd_alloc_pair ();
		frame_draw(IMG_QUICK_FREEZE_END);
		dmd_overlay_outline ();
		dmd_show2 ();
	task_sleep_sec (1);
	deff_exit ();
}//end of mode_effect_deff

