/* CALLSET_SECTION (leffs, __machine4__) */

#include <freewpc.h>
#include "dm/global_constants.h"

#define upper_right 1
#define upper_left  2
#define lower_right 3
#define lower_left  4

/****************************************************************************
 *
 * gi lighting effects
 *
 ****************************************************************************/

// turn off GIs for a time
void no_gi_onesec_leff (void) {
	gi_leff_allocate (PINIO_GI_STRINGS);
	gi_leff_disable (PINIO_GI_STRINGS);
	task_sleep_sec (1);
	gi_leff_enable (PINIO_GI_STRINGS);
	gi_leff_free (PINIO_GI_STRINGS);
	leff_exit ();
}// end of function




// turn off GIs for a time
void no_gi_twosec_leff (void) {
	gi_leff_allocate (PINIO_GI_STRINGS);
	gi_leff_disable (PINIO_GI_STRINGS);
	task_sleep_sec (2);
	gi_leff_enable (PINIO_GI_STRINGS);
	gi_leff_free (PINIO_GI_STRINGS);
	leff_exit ();
}// end of function


bool gi_off;

void turn_off_gi_leff (void) {
	gi_leff_allocate (PINIO_GI_STRINGS);
	while (gi_off) {
		gi_leff_disable (PINIO_GI_STRINGS);
		task_sleep (TIME_1S);
	}
	gi_leff_free (PINIO_GI_STRINGS);
	leff_exit ();
}// end of function



void turn_off_gi (void) {
	gi_off = TRUE;
	leff_start(LEFF_TURN_OFF_GI);
}// end of function




void turn_on_gi (void) {
	gi_off = FALSE;
}// end of function




void flash_gi_leff (void) {
	U8 i;
	gi_leff_allocate (PINIO_GI_STRINGS);
	for (i = 1; i < 4; i++) {
		gi_leff_disable (PINIO_GI_STRINGS);
		task_sleep (TIME_300MS);
		gi_leff_enable (PINIO_GI_STRINGS);
		task_sleep (TIME_300MS);
	}//end of loop
	gi_leff_enable (PINIO_GI_STRINGS);
	gi_leff_free (PINIO_GI_STRINGS);
	leff_exit ();
}// end of function




//flash lower left GI string
void flash_ll_gi_leff (void) {
	U8 i;
	gi_leff_allocate (PINIO_GI_STRINGS);
		for (i = 1; i < 4; i++) {
			gi_leff_enable (TRIAC_GI_STRING(lower_left) );
			task_sleep (TIME_100MS);
			gi_leff_disable (TRIAC_GI_STRING(lower_left) );
			task_sleep (TIME_100MS);
		}
	gi_leff_enable (PINIO_GI_STRINGS); //turn on gi
	gi_leff_free (PINIO_GI_STRINGS);
	leff_exit();
}//end of function




//flash upper left GI string
void flash_ul_gi_leff (void) {
	U8 i;
	gi_leff_allocate (PINIO_GI_STRINGS);
		for (i = 1; i < 4; i++) {
			gi_leff_enable (TRIAC_GI_STRING(upper_left) );
			task_sleep (TIME_100MS);
			gi_leff_disable (TRIAC_GI_STRING(upper_left) );
			task_sleep (TIME_100MS);
		}
	gi_leff_enable (PINIO_GI_STRINGS); //turn on gi
	gi_leff_free (PINIO_GI_STRINGS);
	leff_exit();
}//end of function




//flash upper right GI string
void flash_ur_gi_leff (void) {
	U8 i;
	gi_leff_allocate (PINIO_GI_STRINGS);
		for (i = 1; i < 4; i++) {
			gi_leff_enable (TRIAC_GI_STRING(upper_right) );
			task_sleep (TIME_100MS);
			gi_leff_disable (TRIAC_GI_STRING(upper_right) );
			task_sleep (TIME_100MS);
		}
	gi_leff_enable (PINIO_GI_STRINGS); //turn on gi
	gi_leff_free (PINIO_GI_STRINGS);
	leff_exit();
}//end of function




//flash lower right GI string
void flash_lr_gi_leff (void) {
	U8 i;
	gi_leff_allocate (PINIO_GI_STRINGS);
		for (i = 1; i < 4; i++) {
			gi_leff_enable (TRIAC_GI_STRING(lower_right) );
			task_sleep (TIME_100MS);
			gi_leff_disable (TRIAC_GI_STRING(lower_right) );
			task_sleep (TIME_100MS);
		}
	gi_leff_enable (PINIO_GI_STRINGS); //turn on gi
	gi_leff_free (PINIO_GI_STRINGS);
	leff_exit();
}//end of function







/****************************************************************************
 *
 * paging lighting effects
 *
 ****************************************************************************/


void flash_all_leff (void) {
	U8 i;
//	lamplist_set_apply_delay (0);
	lamplist_apply_leff_alternating (LAMPLIST_AMODE_ALL, 0); //turn all lamps off
	for (i=0; i < 34; i++) {
		lamplist_apply (LAMPLIST_AMODE_ALL, leff_toggle); //toggle
		task_sleep (TIME_66MS);
	}//end of loop
	lamplist_apply (LAMPLIST_AMODE_ALL, leff_on); //restore to previous state
	task_sleep_sec (1);
	leff_exit ();
}// end of function




void bot2top_leff (void) {
	lamplist_set_apply_delay (TIME_16MS);
	lamplist_apply (LAMPLIST_BOTTOM_TOP, leff_toggle); //toggle
	task_sleep (TIME_100MS);
	lamplist_apply (LAMPLIST_TOP_BOTTOM, leff_toggle); //toggle
	task_sleep (TIME_100MS);
	leff_exit ();
}// end of function




void top2bot_leff (void) {
	lamplist_set_apply_delay (TIME_16MS);
	lamplist_apply (LAMPLIST_TOP_BOTTOM, leff_toggle); //toggle
	task_sleep (TIME_100MS);
	lamplist_apply (LAMPLIST_BOTTOM_TOP, leff_toggle); //toggle
	task_sleep (TIME_100MS);
	leff_exit ();
}// end of function




void left2right_leff (void) {
	lamplist_set_apply_delay (TIME_16MS);
	lamplist_apply (LAMPLIST_LEFT_RIGHT, leff_toggle); //toggle
	task_sleep (TIME_100MS);
	lamplist_apply (LAMPLIST_RIGHT_LEFT, leff_toggle); //toggle
	task_sleep (TIME_100MS);
	leff_exit ();
}// end of function




void right2left_leff (void) {
	lamplist_set_apply_delay (TIME_16MS);
	lamplist_apply (LAMPLIST_RIGHT_LEFT, leff_toggle); //toggle
	task_sleep (TIME_100MS);
	lamplist_apply (LAMPLIST_LEFT_RIGHT, leff_toggle); //toggle
	task_sleep (TIME_100MS);
	leff_exit ();
}// end of function



/****************************************************************************
 *
 * acmag lighting effects
 *
 ****************************************************************************/
void acmag_leff (void) {
	lamplist_set_apply_delay (TIME_16MS);
	lamplist_apply (LAMPLIST_TOP_BOTTOM, leff_toggle); //toggle
	task_sleep (TIME_33MS);
	leff_exit ();
}// end of function





/****************************************************************************
 *
 * standup frenzy lighting effects
 *
 ****************************************************************************/
//run a circle out originating at standup target #x
void frenzy1_leff (void) {
	lamplist_set_apply_delay (TIME_16MS);
	lamplist_apply (LAMPLIST_CIRCLE_OUT1, leff_toggle);
	task_sleep (TIME_33MS);
	leff_exit ();
}// end of function




//run a circle out originating at standup target #x
void frenzy2_leff (void) {
	lamplist_set_apply_delay (TIME_16MS);
	lamplist_apply (LAMPLIST_CIRCLE_OUT2, leff_toggle);
	task_sleep (TIME_33MS);
	leff_exit ();
}// end of function





//run a circle out originating at standup target #x
void frenzy3_leff (void) {
	lamplist_set_apply_delay (TIME_16MS);
	lamplist_apply (LAMPLIST_CIRCLE_OUT3, leff_toggle);
	task_sleep (TIME_33MS);
	leff_exit ();
}// end of function





//run a circle out originating at standup target #x
void frenzy4_leff (void) {
	lamplist_set_apply_delay (TIME_16MS);
	lamplist_apply (LAMPLIST_CIRCLE_OUT4, leff_toggle);
	task_sleep (TIME_33MS);
	leff_exit ();
}// end of function





//run a circle out originating at standup target #x
void frenzy5_leff (void) {
	lamplist_set_apply_delay (TIME_16MS);
	lamplist_apply (LAMPLIST_CIRCLE_OUT5, leff_toggle);
	task_sleep (TIME_33MS);
	leff_exit ();
}// end of function






/****************************************************************************
 *
 * car chase lighting effects
 *
 ****************************************************************************/
void car_chase_leff (void) {
	lamplist_set_apply_delay (TIME_16MS);
	lamplist_apply_step (LAMPLIST_LEFT_RIGHT, leff_toggle); //toggle
	task_sleep (TIME_1S);
	leff_exit ();
}// end of function






/****************************************************************************
 *
 * explode lighting effects
 *
 ****************************************************************************/
void explode_leff (void) {
	U8 i;
	gi_leff_disable (PINIO_GI_STRINGS); //turn off gi
		for (i = 0; i < 4; i++) {
			gi_leff_enable (TRIAC_GI_STRING(lower_left) ); //4 = lower left
			task_sleep (TIME_66MS);
			gi_leff_disable (TRIAC_GI_STRING(lower_left) );
			task_sleep (TIME_66MS);
		}
		gi_leff_enable (TRIAC_GI_STRING(lower_left) ); //4 = lower left

		for (i = 0; i < 4; i++) {
			gi_leff_enable (TRIAC_GI_STRING(upper_left) );
			gi_leff_disable (TRIAC_GI_STRING(lower_right) );
			task_sleep (TIME_66MS);
			gi_leff_disable (TRIAC_GI_STRING(upper_left) );
			gi_leff_enable (TRIAC_GI_STRING(lower_right) );
			task_sleep (TIME_66MS);
		}
		gi_leff_enable (TRIAC_GI_STRING(upper_left) );
	gi_leff_enable (PINIO_GI_STRINGS); //turn on gi
	leff_exit();
}//end of function






/****************************************************************************
 *
 * ramps lighting effects
 *
 ****************************************************************************/
void ramp_quickfreeze_leff (void) {
	for (;;) {
		//listed from botton to top
		leff_on (LM_QUICK_FREEZE);
		task_sleep (TIME_100MS);
		leff_off (LM_QUICK_FREEZE);
		leff_on (LM_LEFT_RAMP_CAR_CHASE);
		task_sleep (TIME_100MS);
		leff_off (LM_LEFT_RAMP_CAR_CHASE);
		leff_on (LM_LEFT_RAMP_EXPLODE);
		task_sleep (TIME_100MS);
		leff_off (LM_LEFT_RAMP_EXPLODE);
		leff_on (LM_LEFT_RAMP_JACKPOT);
		task_sleep (TIME_100MS);
		leff_off (LM_LEFT_RAMP_JACKPOT);
		leff_on (LM_LEFT_RAMP_ARROW);
		task_sleep (TIME_100MS);
		leff_off (LM_LEFT_RAMP_ARROW);
		task_sleep (TIME_100MS);

		if (flag_test(FLAG_IS_LRAMP_QUICKFREEZE_ACTIVATED)) 	leff_on (LM_QUICK_FREEZE);
		if (is_carchase_mode_running() )								leff_on (LM_LEFT_RAMP_CAR_CHASE);
		if (is_explode_mode_running() )						 		leff_on (LM_LEFT_LOOP_EXPLODE);
		if (get_jackpot_arrows(lramp_mask) ) 					leff_on (LM_LEFT_RAMP_JACKPOT);
		if (flag_test(FLAG_IS_L_RAMP_ARROW_ACTIVATED)) 			leff_on (LM_LEFT_RAMP_ARROW);
		task_sleep (TIME_1S);

		leff_off (LM_QUICK_FREEZE);
		leff_off (LM_LEFT_RAMP_CAR_CHASE);
		leff_off (LM_LEFT_RAMP_EXPLODE);
		leff_off (LM_LEFT_RAMP_JACKPOT);
		leff_off (LM_LEFT_RAMP_ARROW);
		task_sleep (TIME_200MS);
	}//END OF LOOP
	leff_exit();
}//end of function



void ramp_clawready_leff (void) {
	for (;;) {
		//listed from botton to top
		leff_on (LM_CLAW_READY);
		task_sleep (TIME_100MS);
		leff_off (LM_CLAW_READY);
		leff_on (LM_RIGHT_RAMP_CAR_CHASE);
		task_sleep (TIME_100MS);
		leff_off (LM_RIGHT_RAMP_CAR_CHASE);
		leff_on (LM_RIGHT_RAMP_EXPLODE);
		task_sleep (TIME_100MS);
		leff_off (LM_RIGHT_RAMP_EXPLODE);
		leff_on (LM_RIGHT_RAMP_JACKPOT);
		task_sleep (TIME_100MS);
		leff_off (LM_RIGHT_RAMP_JACKPOT);
		leff_on (LM_RIGHT_RAMP_ARROW);
		task_sleep (TIME_100MS);
		leff_off (LM_RIGHT_RAMP_ARROW);
		task_sleep (TIME_100MS);

		if (flag_test(FLAG_IS_R_RAMP_CLAWREADY)) 			leff_on (LM_CLAW_READY);
		if (is_carchase_mode_running() )							leff_on (LM_RIGHT_RAMP_CAR_CHASE);
		if (is_explode_mode_running() )							leff_on (LM_RIGHT_LOOP_EXPLODE);
		if (get_jackpot_arrows(rramp_mask) ) 				leff_on (LM_RIGHT_RAMP_JACKPOT);
		if (flag_test(FLAG_IS_R_RAMP_ARROW_ACTIVATED)) 		leff_on (LM_RIGHT_RAMP_ARROW);
		task_sleep (TIME_1S);

		leff_off (LM_CLAW_READY);
		leff_off (LM_RIGHT_RAMP_CAR_CHASE);
		leff_off (LM_RIGHT_RAMP_EXPLODE);
		leff_off (LM_RIGHT_RAMP_JACKPOT);
		leff_off (LM_RIGHT_RAMP_ARROW);
		task_sleep (TIME_200MS);
	}//END OF LOOP
	leff_exit();
}//end of function




void left_ramp_leff (void) {
	U8 i;
	for (i = 0; i < 5; i++) {
		flasher_pulse (FLASH_LEFT_RAMP_UP);
		flasher_pulse (FLASH_LEFT_RAMP_LOWER);
		task_sleep (TIME_100MS);
	}
	leff_exit();
}//end of function



void right_ramp_leff (void) {
	U8 i;
	for (i = 0; i < 5; i++) {
		flasher_pulse (FLASH_RIGHT_RAMP_UP);
		flasher_pulse (FLASH_RIGHT_RAMP);
		task_sleep (TIME_100MS);
	}
	leff_exit();
}//end of function



void center_ramp_leff (void) {
	U8 i;
	for (i = 0; i < 9; i++) {
		leff_toggle (LM_CENTER_RAMP_MIDDLE);
		leff_toggle (LM_CENTER_RAMP_OUTER);
		leff_toggle (LM_CENTER_RAMP_INNER);
		flasher_pulse (FLASH_CENTER_RAMP);
		flasher_pulse (FLASH_DIVERTER_FLASHER);
		task_sleep (TIME_100MS);
	}// end of loop
	leff_exit();
}//end of function




void side_ramp_leff (void) {
	U8 i;
	for (i = 0; i < 9; i++) {
		flasher_pulse (FLASH_SIDE_RAMP);
		flasher_pulse (FLASH_DIVERTER_FLASHER);
		task_sleep (TIME_100MS);
	}// end of loop
	leff_exit();
}//end of function







/****************************************************************************
 *
 * inlanes lighting effects
 *
 ****************************************************************************/
void inlane_quick_freeze_leff (void) {
	U8 i;
	for (i = 0; i < 10; i++) {
		lamplist_apply (LAMPLIST_LEFT_RAMP_AWARDS, leff_toggle);
		task_sleep (TIME_133MS);
	}//end of loop
	leff_exit ();
}//end of function



void inlane_cryoclaw_leff (void) {
	U8 i;
	for (i = 0; i < 10; i++) {
		lamplist_apply (LAMPLIST_RIGHT_RAMP_AWARDS, leff_toggle);
		task_sleep (TIME_133MS);
	}//end of loop
	leff_exit ();
}//end of function




/****************************************************************************
 *
 * orbits lighting effects
 *
 ****************************************************************************/
void orbits_runner_leff (void) {  //left loop
	for (;;) {
		//listed from botton to top
		leff_on (LM_EXTRA_BALL);
		task_sleep (TIME_100MS);
		leff_off (LM_EXTRA_BALL);
		leff_on (LM_START_MULTIBALL);
		task_sleep (TIME_100MS);
		leff_off (LM_START_MULTIBALL);
		leff_on (LM_LEFT_LOOP_EXPLODE);
		task_sleep (TIME_100MS);
		leff_off (LM_LEFT_LOOP_EXPLODE);
		leff_on (LM_LEFT_LOOP_JACKPOT);
		task_sleep (TIME_100MS);
		leff_off (LM_LEFT_LOOP_JACKPOT);
		leff_on (LM_LEFT_LOOP_ARROW);
		task_sleep (TIME_100MS);
		leff_off (LM_LEFT_LOOP_ARROW);
		task_sleep (TIME_100MS);

		if (flag_test(FLAG_IS_EXTRABALL_LIT)) 				leff_on (LM_EXTRA_BALL);
		if (flag_test(FLAG_IS_MULTIBALL_ENABLED)) 			leff_on (LM_START_MULTIBALL);
		if (is_explode_mode_running() )					 		lamp_tristate_flash (LM_LEFT_LOOP_EXPLODE);
		if (get_jackpot_arrows(lloop_mask)) 				leff_on (LM_LEFT_LOOP_JACKPOT);
		if (flag_test(FLAG_IS_L_LOOP_ARROW_ACTIVATED)) 		leff_on (LM_LEFT_LOOP_ARROW);
		task_sleep (TIME_2S);

		leff_off (LM_EXTRA_BALL);
		leff_off (LM_START_MULTIBALL);
		leff_off (LM_LEFT_LOOP_EXPLODE);
		leff_off (LM_LEFT_LOOP_JACKPOT);
		leff_off (LM_LEFT_LOOP_ARROW);
		task_sleep (TIME_100MS);
	}//end of loop
	leff_exit();
}//end of function





/****************************************************************************
 *
 *  lock freeze lighting effects
 *
 ****************************************************************************/
void freeze_leff(void) {
	gi_leff_disable (PINIO_GI_STRINGS); //turn off gi
	leff_start(LEFF_LEFT2RIGHT);
	leff_start(LEFF_RIGHT2LEFT);
	gi_leff_enable (PINIO_GI_STRINGS); //turn on gi
	task_sleep_sec (TIME_1S);
	leff_exit();
}//end of function




/****************************************************************************
 *
 * cryo claw lighting effects
 *
 ****************************************************************************/
void claw_leff (void) {
	U8 i;
	gi_leff_disable (PINIO_GI_STRINGS); //turn off gi
	lamplist_apply_leff_alternating (LAMPLIST_AMODE_ALL, 0); //turn all lamps off
		for (i=0; i < 34; i++) {
			lamplist_apply (LAMPLIST_AMODE_ALL, leff_toggle); //toggle
			task_sleep (TIME_33MS);
		}//end of loop
	lamplist_apply (LAMPLIST_AMODE_ALL, leff_on); //restore to previous state
	gi_leff_enable (PINIO_GI_STRINGS); //turn on gi
	leff_exit();
}//end of function





/****************************************************************************
 *
 * MultiBall start lighting effects
 *
 ****************************************************************************/
void mb_start_leff (void) {
	gi_leff_disable (PINIO_GI_STRINGS); //turn off gi
	leff_start(LEFF_BOT2TOP);
	task_sleep (TIME_66MS);
	leff_start(LEFF_TOP2BOT);
	gi_leff_enable (PINIO_GI_STRINGS); //turn on gi
	leff_exit();
}//end of function




void jackpot1_leff (void) {
	U8 i, j;
	gi_leff_disable (PINIO_GI_STRINGS); //turn off gi
	for (j = 1; j <= 2; j++) {
		for (i = 0; i < 4; i++) {
			gi_leff_enable (TRIAC_GI_STRING(j) );
			task_sleep (TIME_33MS);
			gi_leff_disable (TRIAC_GI_STRING(j) );
			task_sleep (TIME_33MS);
		}
	}
	gi_leff_enable (PINIO_GI_STRINGS); //turn on gi
	leff_exit();
}//end of function




void jackpot2_leff (void) {
	U8 i, j;
	gi_leff_disable (PINIO_GI_STRINGS); //turn off gi
	for (j = 3; j <= 4; j++) {
		for (i = 0; i < 4; i++) {
			gi_leff_enable (TRIAC_GI_STRING(j) );
			task_sleep (TIME_33MS);
			gi_leff_disable (TRIAC_GI_STRING(j) );
			task_sleep (TIME_33MS);
		}
	}
	gi_leff_enable (PINIO_GI_STRINGS); //turn on gi
	leff_exit();
}//end of function




void jackpot3_leff (void) {
	U8 i, j;
	gi_leff_disable (PINIO_GI_STRINGS); //turn off gi
	for (j = 2; j <= 4; j += 2) {
		for (i = 0; i < 4; i++) {
			gi_leff_enable (TRIAC_GI_STRING(j) );
			task_sleep (TIME_33MS);
			gi_leff_disable (TRIAC_GI_STRING(j) );
			task_sleep (TIME_33MS);
		}
	}
	gi_leff_enable (PINIO_GI_STRINGS); //turn on gi
	leff_exit();
}//end of function




void jackpot4_leff (void) {
	U8 i, j;
	gi_leff_disable (PINIO_GI_STRINGS); //turn off gi
	for (j = 1; j <= 3; j += 2) {
		for (i = 0; i < 4; i++) {
			gi_leff_enable (TRIAC_GI_STRING(j) );
			task_sleep (TIME_33MS);
			gi_leff_disable (TRIAC_GI_STRING(j) );
			task_sleep (TIME_33MS);
		}
	}
	gi_leff_enable (PINIO_GI_STRINGS); //turn on gi
	leff_exit();
}//end of function




void jackpot_leff (void) {
	U8 i, j;
	gi_leff_disable (PINIO_GI_STRINGS); //turn off gi
	for (j = 2; j <= 3; j++) {
		for (i = 0; i < 4; i++) {
			gi_leff_enable (TRIAC_GI_STRING(j) );
			task_sleep (TIME_33MS);
			gi_leff_disable (TRIAC_GI_STRING(j) );
			task_sleep (TIME_33MS);
		}
	}
	gi_leff_enable (PINIO_GI_STRINGS); //turn on gi
	leff_exit();
}//end of function




void super_jackpot_leff (void) {
	U8 i, j;
	gi_leff_disable (PINIO_GI_STRINGS); //turn off gi
	for (j = 1; j <= 4; j++) {
		for (i = 0; i < 4; i++) {
			gi_leff_enable (TRIAC_GI_STRING(j) );
			task_sleep (TIME_33MS);
			gi_leff_disable (TRIAC_GI_STRING(j) );
			task_sleep (TIME_33MS);
		}
	}
	gi_leff_enable (PINIO_GI_STRINGS); //turn on gi
	leff_exit();
}//end of function




/****************************************************************************
 *
 *   simple switches lighting effects
 *
 ****************************************************************************/
void upper_rebound_leff (void) {
	flasher_pulse (FLASH_LEFT_RAMP_UP);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_DIVERTER_FLASHER);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_RIGHT_RAMP_UP);
	task_sleep (TIME_100MS);

	flasher_pulse (FLASH_LEFT_RAMP_UP);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_DIVERTER_FLASHER);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_RIGHT_RAMP_UP);
	task_sleep (TIME_100MS);

	flasher_pulse (FLASH_LEFT_RAMP_UP);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_DIVERTER_FLASHER);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_RIGHT_RAMP_UP);
	leff_exit ();
}//end of function



void lower_rebound_leff (void) {
	flasher_pulse (FLASH_LOWER_REBOUND);
	task_sleep (TIME_100MS);
	flasher_pulse (FLASH_LOWER_REBOUND);
	task_sleep (TIME_100MS);
	flasher_pulse (FLASH_LOWER_REBOUND);
	task_sleep (TIME_100MS);
	flasher_pulse (FLASH_LOWER_REBOUND);
	leff_exit ();
}//end of function



/****************************************************************************
 *
 * underground and computer award lighting effects
 *
 ****************************************************************************/
void underground_leff (void) {
	flasher_pulse (FLASH_DIVERTER_FLASHER);
	flasher_pulse (FLASH_LEFT_RAMP_UP);
	task_sleep (TIME_100MS);

	flasher_pulse (FLASH_RIGHT_RAMP_UP);
	flasher_pulse (FLASH_DIVERTER_FLASHER);
	task_sleep (TIME_100MS);

	flasher_pulse (FLASH_LEFT_RAMP_UP);
	flasher_pulse (FLASH_RIGHT_RAMP_UP);
	task_sleep (TIME_100MS);

	flasher_pulse (FLASH_DIVERTER_FLASHER);
	flasher_pulse (FLASH_LEFT_RAMP_UP);
	task_sleep (TIME_100MS);

	flasher_pulse (FLASH_RIGHT_RAMP_UP);
	flasher_pulse (FLASH_DIVERTER_FLASHER);
	task_sleep (TIME_100MS);

	flasher_pulse (FLASH_LEFT_RAMP_UP);
	flasher_pulse (FLASH_RIGHT_RAMP_UP);
	task_sleep (TIME_100MS);
	leff_exit ();
}//end of function




void computer_award_leff(void) {
	U8 i;
	gi_leff_disable (PINIO_GI_STRINGS); //turn off gi
//			lamplist_set_apply_delay (0);
			lamplist_apply_leff_alternating (LAMPLIST_AMODE_ALL, 0); //turn all lamps off
			for (i=0; i < 34; i++) {
				lamplist_apply (LAMPLIST_AMODE_ALL, leff_toggle); //toggle
				task_sleep (TIME_66MS);
			}//end of loop
			lamplist_apply (LAMPLIST_AMODE_ALL, leff_on); //restore to previous state
	gi_leff_enable (PINIO_GI_STRINGS); //turn on gi
	task_sleep_sec (TIME_1S);
	leff_exit();
}//end of function






/****************************************************************************
 *
 * eyeball lighting effects
 *
 ****************************************************************************/
void eyeball_leff (void){
	U8 i;
	for (i = 0; i < 10; i++) {
		leff_toggle(LM_RETINA_SCAN);
		flasher_pulse (FLASH_EYEBALL);
		task_sleep (TIME_100MS);
	}// end of loop
	leff_exit();
}//end of function






/****************************************************************************
 *
 * skillshot lighting effects
 *
 ****************************************************************************/
void skillshot_leff (void) {
	flasher_pulse (FLASH_ELEVATOR_1);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_ELEVATOR_2);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_CLAW_FLASHER);
	task_sleep (TIME_100MS);

	flasher_pulse (FLASH_CLAW_FLASHER);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_ELEVATOR_2);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_ELEVATOR_1);
	task_sleep (TIME_100MS);

	flasher_pulse (FLASH_ELEVATOR_1);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_CLAW_FLASHER);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_ELEVATOR_2);
	task_sleep (TIME_100MS);

	flasher_pulse (FLASH_LEFT_RAMP_UP);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_DIVERTER_FLASHER);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_RIGHT_RAMP_UP);
	task_sleep (TIME_100MS);

	flasher_pulse (FLASH_LEFT_RAMP_UP);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_DIVERTER_FLASHER);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_RIGHT_RAMP_UP);
	task_sleep (TIME_100MS);

	flasher_pulse (FLASH_LEFT_RAMP_UP);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_DIVERTER_FLASHER);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_RIGHT_RAMP_UP);
	leff_exit ();
}//end of function






/****************************************************************************
 *
 * attract mode lighting effects
 *
 ***************************************************************************/
void amode_leff (void) {
	U8 i;
	gi_leff_enable (PINIO_GI_STRINGS);
	lamplist_set_apply_delay (TIME_16MS);
	for (;;) {
			lamplist_apply (LAMPLIST_BOTTOM_TOP, leff_toggle); //toggle
			task_sleep (TIME_100MS);
			lamplist_apply (LAMPLIST_TOP_BOTTOM, leff_toggle); //toggle
			task_sleep (TIME_100MS);

			for (i=0; i < 10; i++) {
				lamplist_apply (LAMPLIST_AMODE_ALL, leff_toggle); //toggle
				task_sleep (TIME_100MS);
			}//end of loop

			lamplist_apply (LAMPLIST_LEFT_RIGHT, leff_toggle); //toggle
			task_sleep (TIME_100MS);
			lamplist_apply (LAMPLIST_RIGHT_LEFT, leff_toggle); //toggle
			task_sleep (TIME_100MS);

			for (i=0; i < 10; i++) {
				lamplist_apply (LAMPLIST_AMODE_ALL, leff_toggle); //toggle
				task_sleep (TIME_100MS);
			}//end of loop
}//end of endless loop
	task_exit ();
}//end of function






/****************************************************************************
 *
 * car crash lighting effects
 *
 ****************************************************************************/
void car_crash_runner_leff (void) {
for (;;) {
			//listed from botton to top
			leff_on (LM_CAR_CRASH_BOTTOM);
			task_sleep (TIME_200MS);
			leff_off (LM_CAR_CRASH_BOTTOM);
			leff_on (LM_CAR_CRASH_CENTER);
			task_sleep (TIME_200MS);
			leff_off (LM_CAR_CRASH_CENTER);
			leff_on (LM_CAR_CRASH_TOP);
			task_sleep (TIME_200MS);
			leff_off (LM_CAR_CRASH_TOP);
			task_sleep (TIME_200MS);

			if (flag_test (FLAG_IS_CC3_LIT)) 	leff_on (LM_CAR_CRASH_BOTTOM);
			if (flag_test (FLAG_IS_CC6_LIT)) 	leff_on (LM_CAR_CRASH_CENTER);
			if (flag_test (FLAG_IS_CC10_LIT)) 	leff_on (LM_CAR_CRASH_TOP);
			task_sleep (TIME_1S);

			leff_off (LM_CAR_CRASH_BOTTOM);
			leff_off (LM_CAR_CRASH_CENTER);
			leff_off (LM_CAR_CRASH_TOP);
			task_sleep (TIME_200MS);
	}//END OF LOOP
	leff_exit();
}//end of function



