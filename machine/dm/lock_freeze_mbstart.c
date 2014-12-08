/*
 * demolition man
 * lock_freeze_mbstart.c
 * 
 * written by James Cardona
 *
 * handles the lock freezes and the trigger of multiballs
 *
 *
 */
/* CALLSET_SECTION (lock_freeze_mbstart, __machine3__) */

#include <freewpc.h>
#include "dm/global_constants.h"
#include "shaker.h"


//local variables
U8			lock_SoundCounter;
U8			freeze_MessageCounter;
__local__ 	U8			NumBallsFrozen;
__local__ 	U8			NumMBsDone;


//external variables


//internally called function prototypes  --external found at protos.h
void check_multiball_requirements(void);




/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
CALLSET_ENTRY (lock_freeze_mbstart, start_player) {
	NumBallsFrozen = 0;
	lock_SoundCounter = 0;
	NumMBsDone = 0;
	freeze_MessageCounter = 0;
	lamp_tristate_off (LM_FREEZE_1);
	lamp_tristate_off (LM_FREEZE_2);
	lamp_tristate_off (LM_FREEZE_3);
	lamp_tristate_off (LM_FREEZE_4);
}



CALLSET_ENTRY (lock_freeze_mbstart, start_ball) {
	multiball_light_off();//goto orbits.c to turn off light and flag
	if (NumBallsFrozen > (NumMBsDone % 4) ) {
		multiball_light_on();//goto orbits.c
		flag_on(FLAG_IS_MULTIBALL_ENABLED);
	}


	lamp_tristate_off (LM_FREEZE_1);
	lamp_tristate_off (LM_FREEZE_2);
	lamp_tristate_off (LM_FREEZE_3);
	lamp_tristate_off (LM_FREEZE_4);

	switch (NumBallsFrozen) {
		case 1:	lamp_tristate_on (LM_FREEZE_1);	break;
		case 2:
				lamp_tristate_on (LM_FREEZE_1);
				lamp_tristate_on (LM_FREEZE_2);
				break;
		case 3:
				lamp_tristate_on (LM_FREEZE_1);
				lamp_tristate_on (LM_FREEZE_2);
				lamp_tristate_on (LM_FREEZE_3);
				break;
		case 4:
				lamp_tristate_on (LM_FREEZE_1);
				lamp_tristate_on (LM_FREEZE_2);
				lamp_tristate_on (LM_FREEZE_3);
				lamp_tristate_on (LM_FREEZE_4);
		break;
	}//end of switch
}



CALLSET_ENTRY (lock_freeze_mbstart, end_ball) {
	multiball_light_off();//goto orbits.c to turn off light and flag
	lamp_tristate_off (LM_FREEZE_1);
	lamp_tristate_off (LM_FREEZE_2);
	lamp_tristate_off (LM_FREEZE_3);
	lamp_tristate_off (LM_FREEZE_4);
}



/****************************************************************************
 * body
 *
 ***************************************************************************/
CALLSET_ENTRY (lock_freeze_mbstart, music_refresh) { if (in_game && valid_playfield && flag_test(FLAG_IS_MULTIBALL_ENABLED) )	music_request (MUS_MB_READY, PRI_GAME_MODE1); }



void maximize_freeze(void) {
	NumBallsFrozen = 4; //see note below
	increment_freeze(); //will add another here
}//end of function




void increment_freeze(void) {
	sound_start (ST_EFFECT, LOCK_FREEZE_PLOINK, SL_1S, PRI_GAME_QUICK1);
	if (NumBallsFrozen < 5)
			switch (++NumBallsFrozen) {
			case 1:
					lamp_tristate_flash(LM_FREEZE_1);
					task_sleep (TIME_500MS);
					lamp_tristate_on (LM_FREEZE_1);
					break;
			case 2:
					lamp_tristate_flash(LM_FREEZE_2);
					task_sleep (TIME_500MS);
					lamp_tristate_on (LM_FREEZE_1);
					lamp_tristate_on (LM_FREEZE_2);
					break;
			case 3:
					lamp_tristate_flash(LM_FREEZE_3);
					task_sleep (TIME_500MS);
					lamp_tristate_on (LM_FREEZE_1);
					lamp_tristate_on (LM_FREEZE_2);
					lamp_tristate_on (LM_FREEZE_3);
					break;
			case 4:
					lamp_tristate_flash(LM_FREEZE_4);
					task_sleep (TIME_500MS);
					lamp_tristate_on (LM_FREEZE_1);
					lamp_tristate_on (LM_FREEZE_2);
					lamp_tristate_on (LM_FREEZE_3);
					lamp_tristate_on (LM_FREEZE_4);
					break;
			case 5://THERE ARE ONLY 4 LIGHTS, this is just here of for the case of maximize freezes, to prevent any from flashing
					lamp_tristate_on (LM_FREEZE_1);
					lamp_tristate_on (LM_FREEZE_2);
					lamp_tristate_on (LM_FREEZE_3);
					lamp_tristate_on (LM_FREEZE_4);
					break;
			}//end of switch
	deactivate_left_ramp_quickfreeze();//goto ramps.c
	light_quick_freeze_light_off();//goto inlanes.c
	if (	!get_back_in_the_fridge_running()
		&&	!get_back_in_the_fridge_ending() ) check_multiball_requirements();
}//end of function




void check_multiball_requirements(void) {
	//if requirements met for next mb - light left loop shot to start mb
	//Fortress Multiball 	= 1 ball min needs to be frozen
	//Museum Multiball	 	= 2 ball min needs to be frozen
	//Cryoprison Multiball	= 3 ball min needs to be frozen
	//Wasteland Multiball 	= 4 ball min needs to be frozen
	if (NumBallsFrozen > (NumMBsDone % 4) ) { // % is modulus
				multiball_light_on();//goto orbits.c
				flag_on(FLAG_IS_MULTIBALL_ENABLED);
				if ( (lock_SoundCounter++ % 2) == 0 )//check if even
					sound_start (ST_SPEECH, SPCH_MULTIBALL_ACTIVATED, SL_4S, PRI_GAME_QUICK4);
				else
				sound_start (ST_SPEECH, SPCH_SHOOT_LEFT_LOOP, SL_4S, PRI_GAME_QUICK4);
	}  //end of if (NumBallsFrozen > (NumMBsDone % 4) )

	if (system_config.disable_shaker == NO) {
		if (system_config.extra_shaker == YES) 	shaker_start (SHAKER_HALF_ON, 2);
		else									shaker_start (SHAKER_ONE_QUARTER_ON, 2);
	}//end of shaker call

	leff_start(LEFF_FREEZE);
	deff_start (DEFF_FREEZE_EFFECT);
}//end of function





//this is called from left loop shot at orbits.c
void multiball_start (void) {
	if 		( (NumMBsDone % 4) == 0) 	fortress_start(NumBallsFrozen);
	else if ( (NumMBsDone % 4) == 1) 	museum_start(NumBallsFrozen);
	else if ( (NumMBsDone % 4) == 2) 	wasteland_start(NumBallsFrozen);
	else if ( (NumMBsDone % 4) == 3) 	cryoprison_start(NumBallsFrozen);
}//end of function






//after we are sure we have a valid MB start, we reset everything for next time
void multiball_started(void) {
	NumMBsDone++;
	flag_off(FLAG_IS_MULTIBALL_ENABLED);
	NumBallsFrozen = 0;
	multiball_light_off();//goto orbits.c to turn off light and flag
	lamp_tristate_off (LM_FREEZE_1);
	lamp_tristate_off (LM_FREEZE_2);
	lamp_tristate_off (LM_FREEZE_3);
	lamp_tristate_off (LM_FREEZE_4);
}//end of function





/****************************************************************************
 *
 * display effects
 *
 ****************************************************************************/
void freeze_effect_deff(void) {
	U16 fno;
	dmd_alloc_pair_clean ();
	sound_start (ST_EFFECT, SIREN, SL_4S, PRI_GAME_QUICK2);

	for (fno = IMG_QUICK_FREEZE_START; fno <= IMG_QUICK_FREEZE_END; fno += 2) {
			dmd_alloc_pair_clean ();
			frame_draw(fno);
			dmd_show2 ();
			task_sleep (TIME_100MS);
		}//end of inner loop

		dmd_alloc_pair_clean ();// Clean both pages
		dmd_map_overlay ();
		dmd_clean_page_low ();
		if ( flag_test(FLAG_IS_MULTIBALL_ENABLED) ) {
					font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "MULTIBALL");
					font_render_string_center (&font_halobold12, DMD_MIDDLE_X + 10, DMD_BIG_CY_Bot, "READY");
		}
		else {
					font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "FREEZE");
		}
		dmd_text_outline ();
		dmd_alloc_pair ();
		frame_draw(IMG_QUICK_FREEZE_END);
		dmd_overlay_outline ();
		dmd_show2 ();

	if (DM_IN_DMD_TEST) freeze_MessageCounter++;
	if (flag_test(FLAG_IS_MULTIBALL_ENABLED)) {
		if ( (lock_SoundCounter++ % 2) == 0 )//check if even
			sound_start (ST_SPEECH, SPCH_MULTIBALL_ACTIVATED, SL_4S, PRI_GAME_QUICK4);
		else
			sound_start (ST_SPEECH, SPCH_SHOOT_LEFT_LOOP, SL_4S, PRI_GAME_QUICK4);
	}

	task_sleep_sec (1);
	deff_exit ();
}//end of mode_effect_deff

