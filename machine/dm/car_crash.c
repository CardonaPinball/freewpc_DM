/*
 * demolition man
 * car_crash.c
 *
 * written by James Cardona
 *
 * Location Description:
 * Located to the left and above the retina scan is the Car Crash target.
 * the Car Crash contains two captive cars (yes, that's right ... captive cars) behind the impact target.
 * Triggering the switch causes two miniature cars to crash.
 * The ball will rocket off this target, but there's a ballsaver if it goes STDM.
 *
 * Scoring Description: (original game)
 * Hitting the target adds to the Car Crash value and lights an additional Car Crash light.
 * Hitting the target with three lights lit award the Car Crash value.
 * Car Crash is worth three, then six, then ten million (for 1/2/3 hits) and is doubled
 * if the top car hits the target at the end of the captive lane.
 * Car Crash lights Car Chase on the left/right lamps.
 * once 10 million shot is lit, it stays lit
 *
 * Scoring Description: (my rules)
 * same as above except:
 * first switch hit is 250K, first car (2nd switch) is three, then six, then ten million.
 * Second car (Third switch) still doubles
 *
 * Also, car chase is not a single lit ramp after a car crash hit but an entire mode
 * The car chase mode is lit after a predefined number of car crashes where the second car makes the switch.  Then
 * the mode starts and lights both ramps for car chases.  The car chase stays lit until ball drain
 * or until car crash is hit.  Car chase ramps score 15 million per shot.
 *
 * once 10 million shot is lit, it starts mode and car crash lights reset to lowest value
 *
 * estimate of average carcrash mode score: 45 million to 90 million
 * estimate of average car score: 9 million to 21 million
 *
 */
/* CALLSET_SECTION (car_crash, __machine2__) */

#include <freewpc.h>
#include "dm/global_constants.h"
#include "shaker.h"


//constants
#define 	CAR_CRASH_EASY_GOAL  2
#define 	CAR_CRASH_GOAL_STEP  4
#define 	CAR_CRASH_GOAL_MAX  50


//local variables
U8 			carCrashFirstSwitchDebouncer;
U8 			carCrashSecondSwitchDebouncer;
U8			carCrashThirdSwitchDebouncer;
__boolean 	carcrash_ballsave;
__local__ U8			car_crash_multiplier;
__local__ U8 			car_crash_shots_made;	//non-mode shots made counter
__local__ U8 			car_crash_goal;		//goal to reach mode
score_t					car_crash_display_score;

//external variables

//internally called function prototypes  --external found at protos.h
void car_crash_reset (void);
void player_car_crash_reset (void);
void car_crash_first_switch_task (void);
void car_crash_second_switch_task (void);
void car_crash_third_switch_task (void);
void cc_lights_task (void);
void carcrash_ten_on(void);
void carcrash_six_on(void);
void carcrash_three_on(void);
void carcrash_ten_off(void);
void carcrash_six_off(void);
void carcrash_three_off(void);


/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
void car_crash_reset (void) {
	carCrashFirstSwitchDebouncer = 0;
	carCrashSecondSwitchDebouncer = 0;
	carCrashThirdSwitchDebouncer = 0;

	//reduce car crash scoring by one level
	if (flag_test (FLAG_IS_CC10_LIT)) {
		carcrash_ten_off();
		carcrash_six_on();
		carcrash_three_on();
	}
	else if (flag_test (FLAG_IS_CC6_LIT)) {
		carcrash_six_off();
		carcrash_three_on();
	}
	else if (flag_test (FLAG_IS_CC3_LIT)) {
		carcrash_three_off();
	}
	else {
		carcrash_three_off();
		carcrash_six_off();
		carcrash_ten_off();
	}
	carcrash_ballsave = FALSE;

	task_sleep (TIME_1S);
	if (flag_test(FLAG_IS_CARCHASE_MODE_ENABLED) )		leff_start (LEFF_CAR_CRASH_RUNNER);
	else 												leff_stop (LEFF_CAR_CRASH_RUNNER);
}//end of function



void player_car_crash_reset (void) {
	car_crash_multiplier = 1;
	car_crash_shots_made = 0;
	car_crash_goal = CAR_CRASH_EASY_GOAL;
	car_crash_reset();
	if (car_crash_shots_made >= car_crash_goal - 1 )	flag_on(FLAG_IS_CARCHASE_MODE_ENABLED);
	else 												flag_off(FLAG_IS_CARCHASE_MODE_ENABLED);

	#ifdef CONFIG_DIFFICULTY_LEVEL
	car_crash_goal = system_config.num2chase;
	#endif
}//end of function



CALLSET_ENTRY (car_crash, start_ball) { car_crash_reset (); }
CALLSET_ENTRY (car_crash, start_player) { player_car_crash_reset (); }




CALLSET_ENTRY (car_crash, end_ball) {
	lamp_tristate_off (LM_CAR_CRASH_TOP);
	lamp_tristate_off (LM_CAR_CRASH_CENTER);
	lamp_tristate_off (LM_CAR_CRASH_BOTTOM);
	leff_stop (LEFF_CAR_CRASH_RUNNER);
}//end of function



/****************************************************************************
 * playfield lights and flags
 ***************************************************************************/
void carcrash_three_on(void) {
	flag_on (FLAG_IS_CC3_LIT);
	lamp_tristate_flash(LM_CAR_CRASH_BOTTOM);
	task_sleep (TIME_1S);
	lamp_tristate_on (LM_CAR_CRASH_BOTTOM);
}//end of function

void carcrash_three_off(void) {
	flag_off (FLAG_IS_CC3_LIT);
	lamp_tristate_off (LM_CAR_CRASH_BOTTOM);
}//end of function

void carcrash_six_on(void) {
	flag_on (FLAG_IS_CC6_LIT);
	lamp_tristate_flash(LM_CAR_CRASH_CENTER);
	task_sleep (TIME_1S);
	lamp_tristate_on (LM_CAR_CRASH_CENTER);
}//end of function

void carcrash_six_off(void) {
	flag_off (FLAG_IS_CC6_LIT);
	lamp_tristate_off (LM_CAR_CRASH_CENTER);
}//end of function

void carcrash_ten_on(void) {
	flag_on (FLAG_IS_CC10_LIT);
	lamp_tristate_flash(LM_CAR_CRASH_TOP);
	task_sleep (TIME_1S);
	lamp_tristate_on (LM_CAR_CRASH_TOP);
}//end of function

void carcrash_ten_off(void) {
	flag_off (FLAG_IS_CC10_LIT);
	lamp_tristate_off (LM_CAR_CRASH_TOP);
}//end of function

//used when awarding triple car crash to allow temporarily flashing of lights
void restore_carcrash_lights_state(void) {
	if (flag_test (FLAG_IS_CC6_LIT))  	lamp_tristate_on (LM_CAR_CRASH_CENTER);
	else 	lamp_tristate_off (LM_CAR_CRASH_CENTER);

	if (flag_test (FLAG_IS_CC10_LIT))  	lamp_tristate_on (LM_CAR_CRASH_TOP);
	else 	lamp_tristate_off (LM_CAR_CRASH_TOP);

	if (flag_test (FLAG_IS_CC3_LIT))  	lamp_tristate_on (LM_CAR_CRASH_BOTTOM);
	else 	lamp_tristate_off (LM_CAR_CRASH_BOTTOM);
}//end of function

/****************************************************************************
 *
 * body
 *
 ***************************************************************************/
//if the first car was hit then both institute a quick ball saver and
//also debounce the switch since sometimes the car bounces a bit
void car_crash_first_switch_task (void) {
	task_sleep_sec(1);
	task_sleep (TIME_500MS);
	carcrash_ballsave = FALSE;
	carCrashFirstSwitchDebouncer = 0;
	task_exit();
}//end of function



//first car switch at bottom of car lane
CALLSET_ENTRY (car_crash, sw_chase_car_1) {
	carcrash_ballsave = TRUE;
	if (in_game && !in_tilt && ++carCrashFirstSwitchDebouncer == 1) {
				sound_start (ST_SAMPLE, CAR_SKID, SL_2S, PRI_GAME_QUICK2);
				score (CARCRASH_SCORE_CAR1);
				flasher_pulse (FLASH_CAR_CHASE_LOWER);

				if (is_carchase_mode_running() )		car_chase_ramp_made(); //goto carchase.c for scoring
	}//end of if DEBOUNCER
	task_create_gid1 (GID_CAR_CRASH_1, car_crash_first_switch_task);
}//end of function



void car_crash_second_switch_task (void) {
	task_sleep_sec(4);
	carCrashSecondSwitchDebouncer = 0;
	task_exit();
}//end of function



//second car switch at bottom of car lane
CALLSET_ENTRY (car_crash, sw_chase_car_2) {
/*
	if (in_game && !in_tilt) {
			if (++carCrashSecondSwitchDebouncer == 1) {
				U8 i;
				for (i = 1; i <= car_crash_multiplier; i++){
					if 		(flag_test (FLAG_IS_CC10_LIT)) 	score (SC_10M);
					else if (flag_test (FLAG_IS_CC6_LIT)) 	score (SC_6M);
					else if (flag_test (FLAG_IS_CC3_LIT))  	score (SC_3M);
					else score (CARCRASH_SCORE_CAR2);
				}//end of loop
			}//end of if DEBOUNCER
			task_create_gid1 (GID_CAR_CRASH_2, car_crash_second_switch_task);
	}
*/
}//end of function



void car_crash_third_switch_task (void) {
	task_sleep_sec(3);
	carCrashThirdSwitchDebouncer = 0;
	task_exit();
}//end of function


//second car switch at top of car lane
CALLSET_ENTRY (car_crash, sw_car_chase_standup) {
	if (in_game && !in_tilt) {
			if (++carCrashThirdSwitchDebouncer == 1) {
					++car_crash_shots_made;
					sound_start (ST_SAMPLE, CAR_CRASH, SL_2S, PRI_GAME_QUICK2);
					flasher_pulse (FLASH_CAR_CHASE_UPPER);

					//goal made then start mode
					if (!get_back_in_the_fridge_running() &&	car_crash_shots_made >= car_crash_goal)  {
						flag_off(FLAG_IS_CARCHASE_MODE_ENABLED);
						leff_stop (	LEFF_CAR_CRASH_RUNNER);
						car_crash_shots_made = 0;
						//increment goal for next time
						if (car_crash_goal < CAR_CRASH_GOAL_MAX)  car_crash_goal += CAR_CRASH_GOAL_STEP;

						huxley_increment();
						//start ramp mode
						start_car_chase(); //at car_chase_mode.c
						//turn off car crash lights
//						carcrash_three_off();
//						carcrash_six_off();
//						carcrash_ten_off();
					}//end of (!get_back_in_the_fridge_running() &&	car_crash_shots_made >= car_crash_goal)

					//if car chase already running then score it
					else
						if (is_carchase_mode_running() ) {
							car_chase_ramp_made ();
							//we have to do this here since on ramp calls it is done on first switch not second
							if (system_config.disable_shaker == NO) {
								if (system_config.extra_shaker == YES) 	shaker_start (SHAKER_HALF_ON, 2);
								else									shaker_start (SHAKER_ONE_QUARTER_ON, 2);
							}//end of shaker call
						}//end of else if (is_carchase_mode_running() )

						else { //no car chase yet - normal effects
							//set up flag if one shot away from car chase
							if (car_crash_shots_made >= car_crash_goal - 1 ) flag_on(FLAG_IS_CARCHASE_MODE_ENABLED);

							//set point values and lights for car crash
							if (car_crash_shots_made == 1) {
								if (!flag_test (FLAG_IS_CC3_LIT))  		carcrash_three_on();
							}
							else if (car_crash_shots_made == 2) {
								if (!flag_test (FLAG_IS_CC6_LIT))  		carcrash_six_on();
								if (!flag_test (FLAG_IS_CC3_LIT))  		carcrash_three_on();
							}
							else if (car_crash_shots_made >= 3) {
								if (!flag_test (FLAG_IS_CC10_LIT)) 		carcrash_ten_on();
								if (!flag_test (FLAG_IS_CC6_LIT)) 		carcrash_six_on();
								if (!flag_test (FLAG_IS_CC3_LIT)) 		carcrash_three_on();
							}//end of if
						}//end of else no chase yet

					//effectively increase the score by multiplied
					score_zero (car_crash_display_score);
					U8 i;
					for (i = 1; i <= car_crash_multiplier; i++){
						if 		(flag_test (FLAG_IS_CC10_LIT))	{ score (SC_10M); score_add (car_crash_display_score, score_table[SC_10M]); }
						else if (flag_test (FLAG_IS_CC6_LIT))	{ score (SC_6M);  score_add (car_crash_display_score, score_table[SC_6M]); }
						else if (flag_test (FLAG_IS_CC3_LIT)) 	{ score (SC_3M);  score_add (car_crash_display_score, score_table[SC_3M]); }
						else 									{ score (SC_1M); score_add (car_crash_display_score, score_table[SC_1M]); }
					}//end of loop
					//now that we know the score, we can display it
					deff_start (DEFF_CARCRASH_EFFECT);
			}//end of if (++carCrashThirdSwitchDebouncer == 1)

			task_create_gid1 (GID_CAR_CRASH_3, car_crash_third_switch_task);
	}//end of if (in_game && !in_tilt)
}//end of function




//called from comp award at underground.c
void comp_award_trip_car_crash(void) {
	car_crash_multiplier = 3;
}//end of function






/****************************************************************************
 *
 * DMD display
 *
 ****************************************************************************/
U8	carcrash_MessageCounter;
void carcrash_effect_deff(void) {
	U16 fno;
	dmd_alloc_pair_clean ();

	if (DM_IN_DMD_TEST) {	if (++carcrash_MessageCounter > 1) carcrash_MessageCounter = 0; }
	else
	if (car_crash_multiplier > 1) carcrash_MessageCounter = 6;
//	else	carcrash_MessageCounter = random_scaled(6);
	else	if (++carcrash_MessageCounter > 5) carcrash_MessageCounter = 0;

	for (fno = IMG_CAR_CRASH_MARIO_START; fno <= IMG_CAR_CRASH_MARIO_END; fno += 2) {
		dmd_alloc_pair ();
		frame_draw(fno);
		dmd_show2 ();
		task_sleep (TIME_100MS);
	}//end of inner loop

	dmd_alloc_pair_clean ();// Clean both pages
	dmd_map_overlay ();
	dmd_clean_page_low ();

	switch (carcrash_MessageCounter) {
		default:
			sprintf_score (car_crash_display_score);
			font_render_string_center (&font_term6, DMD_MIDDLE_X, DMD_MED_CY_1, sprintf_buffer);
			sprintf ("%d FOR", car_crash_goal - car_crash_shots_made );
			font_render_string_center (&font_term6, DMD_MIDDLE_X, DMD_MED_CY_2, sprintf_buffer);
			font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "CHASE");
			break;
		case 1:
			font_render_string_center (&font_term6, DMD_MIDDLE_X, DMD_MED_CY_1, "EXPLODE AND CHASE");
			font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_MED_CY_2, "LEAD TO");
			font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "HUXLEY");
			break;
		case 6:
			font_render_string_center (&font_term6, DMD_MIDDLE_X, DMD_MED_CY_1, "TRIPLE");
			sprintf_score(car_crash_display_score);
			font_render_string_center (&font_fixed6, DMD_MIDDLE_X, DMD_BIG_CY_Bot, sprintf_buffer);
			break;
	}//end of switch

	dmd_text_outline ();
	dmd_alloc_pair ();
	frame_draw(IMG_CAR_CRASH_MARIO_END);
	dmd_overlay_outline ();
	dmd_show2 ();
	task_sleep_sec (1);
	deff_exit ();
}//end of standard_effect_deff




