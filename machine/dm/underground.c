/*
 * demolition man
 * underground.c
 *
 * written by James Cardona
 *
 * Location Description:
 * subway / underground is a scoop across from the upper flipper and to the left of the jets
 * and to the right of the center ramp, with the opening on the left side. It is an easy
 * shot from the upper left flipper, and it can also be made with a little luck from either
 * of the lower flippers. The Computer and Demolition Time are awarded here. The
 * Underground has a Jackpot lamp and a Combo arrow. The ball is returned, via a VUK
 * to the right ramp habitrail. The Computer and Demolition time are indicated by
 * yellow and blue lights mounted over the Underground entrance.
 *
 * The Computer is accessed via the UnderGround shot and is lit by a yellow lamp
 * immediately above. Lit every 10 combos, the Computer is a random award like
 * the Camera on Twilight Zone. Awards seen so far :
 * Light Extra Ball
 * Light Explodes (lights all four explode 10M lamps)
 * 3x Car Crash
 * 2x Retina Scan
 * Light Arrows (lights Laser millions on all combo shots)
 * Maximize Freezes (freezes four balls and lights multiball)
 * Collect Bonus (complete with bonus music!)
 * Collect Standups (awards all the lit yellow targets)
 *
 * Scoring Description: (original game)
 *
 *
 * Scoring Description: (my rules)
 * same as above except
 *
 */
/*CALLSET_SECTION (underground, __machine2__)*/
#include <freewpc.h>
#include "dm/global_constants.h"
#include "search.h"



//constants

//local variables
bool 	one_button_held;
bool 	both_buttons_held;
U8 			undergroundSwitchDebouncer;
U8 			MessageCounter;
U8			underground_SoundCounter;
__boolean 	underground_inBall_search;
__boolean 	computer_award_just_awarded;
score_t		ca_bonus_scored;
score_t		ca_total_bonus;
score_t 	ca_bonus_scored2;
__local__ U8 	nextcomputerAwardsChooser;

//for tournament mode - all players receive same awards in same order
U8 				TM_nextcomputerAwardsChooser[10];
__local__ U8 	TM_nextcomputerAwardsChooser_PlayerPointer;


//external variables
extern __local__ U8 		car_crash_shots_made; 				//from car_crash.c
extern __local__ U8 		eyeball_shots_made;
extern __local__ U8 		combo_counter;						//from combos.c
extern __local__ U8 		standupFrenzyNumHits;
extern __local__ U8 		standup_num_of_hits;

extern U8 		rollover_bonus_multiplier;  	//not local okay - reset each new ball

//internally called function prototypes  --external found at protos.h
void underground_reset (void);
void underground_task (void);
void square_draw (U8 sq);
void show_text_on_squares (U8 times);
void square_init (void);
void computer_light_off (void);

/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
CALLSET_ENTRY (underground, start_ball) {
	undergroundSwitchDebouncer = 0;
	underground_inBall_search = FALSE;
	computer_award_just_awarded = FALSE;
	computer_award_light_recheck(); //this is here in the case BITF just ended
}//end of function




CALLSET_ENTRY (underground, start_player) {
	if (DM_IN_CAB_TEST) 	nextcomputerAwardsChooser = 0;
	else {
		if (system_config.tournament_mode == NO) nextcomputerAwardsChooser = random_scaled(10);		//normal computer award
		else
		if (player_up == 1) {
			U8 i;
			for (i = 0; i < 10; i++) TM_nextcomputerAwardsChooser[i] = random_scaled(10);	//tournament mode computer awards - pick 10 different ones
		}
	} //end of else cab not in test

	TM_nextcomputerAwardsChooser_PlayerPointer = 0;
	MessageCounter = 0;
	underground_SoundCounter = 0;
}//end of function




CALLSET_ENTRY (underground, ball_search) { 		underground_inBall_search = TRUE; }
CALLSET_ENTRY (underground, ball_search_end) { 	underground_inBall_search = FALSE; }

CALLSET_ENTRY (underground, end_game) { 		computer_light_off(); }



/****************************************************************************
 * playfield lights and flags
 ***************************************************************************/
void underground_jackpot_light_on(void) {
	lamp_tristate_on (LM_UNDERGROUND_JACKPOT);
}//end of function

void underground_jackpot_light_off(void) {
	lamp_tristate_off (LM_UNDERGROUND_JACKPOT);
}//end of function

void underground_arrow_light_on(void) {
	flag_on (FLAG_IS_UGROUND_ARROW_ACTIVATED);
	if (get_capture_simon_arrows (CAPSIM_UNDERGRND)) 	lamp_tristate_flash (LM_UNDERGROUND_ARROW);
	else 												lamp_tristate_on (LM_UNDERGROUND_ARROW);
}//end of function

void underground_arrow_light_off(void) {
	flag_off (FLAG_IS_UGROUND_ARROW_ACTIVATED);
	lamp_tristate_off (LM_UNDERGROUND_ARROW);
}//end of function

void computer_light_on(void) {
	flag_on (FLAG_IS_COMPUTER_ACTIVATED);
	//if we are in a MB, then do not light it just yet
	if (	!get_back_in_the_fridge_running()
		&&	!get_back_in_the_fridge_ending()
		&&	!get_fortress_running ()
		&&	!get_museum_running ()
		&&  !get_cryoprison_running ()
		&&  !get_wasteland_running ()
		&&  !get_demotime_running () )
		lamp_tristate_flash (LM_COMPUTER);
}//end of function


//if MB just ended, then check to see if all MBs are over and
// if so then relight CA light if it should be lit
void computer_award_light_recheck (void){
	if (	!get_back_in_the_fridge_running()
		&&	!get_back_in_the_fridge_ending()
		&&	!get_fortress_running ()
		&&	!get_museum_running ()
		&&  !get_cryoprison_running ()
		&&  !get_wasteland_running ()
		&&  !get_demotime_running ()
		&& 	flag_test (FLAG_IS_COMPUTER_ACTIVATED) )
		lamp_tristate_flash (LM_COMPUTER);
}

// if comp award is lit and we start a MB, then stop the light
// from flashing as it is not available now
void computer_light_temp_off (void) {
	lamp_tristate_off (LM_COMPUTER);
}//end of function


void computer_light_off(void) {
	flag_off (FLAG_IS_COMPUTER_ACTIVATED);
	lamp_tristate_off (LM_COMPUTER);
}//end of function



/****************************************************************************
 *
 * body
 *
 ****************************************************************************/
//sw_bottom_popper
CALLSET_ENTRY (underground, dev_subway_vuk_enter) {
	if (!underground_inBall_search && !get_is_capture_simon_initial_start () ){
					ball_search_monitor_stop ();
					computer_award_just_awarded = FALSE;
					score (BOT_POP_SCORE);//located in kernal/score.c

					//CALLS			*****************************
					if (get_skill_shot_enabled() ) 								award_skill_shot (1);
					if (get_back_in_the_fridge_running() ) 						back_in_the_fridge_shot_made();
					if (flag_test(FLAG_IS_DEMOTIME_ENABLED) ) 					demotime_start();
					if (is_huxley_running () )									huxley_mode_shot_made();
					if (get_jackpot_arrows(ugrnd_mask) ) 						score_jackpot();
					if (get_capture_simon_arrows (CAPSIM_UNDERGRND) )			capture_simon_made();
					if (is_prison_break_running () )   							prison_break_made();
					if (	!get_back_in_the_fridge_running()
						&&	!get_back_in_the_fridge_ending()
						&& !get_fortress_running ()
						&& !get_museum_running ()
						&& !get_cryoprison_running ()
						&& !get_wasteland_running ()
						&& !get_demotime_running ()
						&&	flag_test(FLAG_IS_COMPUTER_ACTIVATED) ) 			{ deff_start_sync (DEFF_COMPUTER_AWARD); computer_award_just_awarded = TRUE; }

					if ( flag_test(FLAG_IS_COMBO_UNDER_ACTIVATED)) 				combo_hit();
					else if (get_is_combos_killed ()
						&&	 get_is_combos_restartable () ) 					combo_init();

			//if nothing special, do normal effects
					if(		!is_prison_break_running ()
						&& 	!get_capture_simon_arrows (CAPSIM_UNDERGRND)
						&& 	!computer_award_just_awarded
						&& 	!get_jackpot_arrows(ugrnd_mask)
						&&	!get_demotime_starting () ) {
										deff_start (DEFF_UNDERGROUND_EFFECT);
					}//end of if nothing special

					computer_award_just_awarded = FALSE;

					if (	!get_demotime_starting () ) {
						leff_start (LEFF_UNDERGROUND);
						sol_request_async(SOL_BOTTOM_POPPER);
					}
					ball_search_monitor_start ();
		}//end of !get_is_capture_simon_initial_start ()
}//end of function







/****************************************************************************
 *
 * display effects
 *
 ****************************************************************************/
void underground_effect_deff(void) {
	U16 fno;

	if (DM_IN_DMD_TEST) { if (++MessageCounter > 4) MessageCounter = 0; }

	underground_SoundCounter = random_scaled(2);//from kernal/random.c
	dmd_alloc_pair_clean ();// Clean both pages

	//one shot away from HUXLEY so tell the player so
	if ((DM_IN_DMD_TEST && MessageCounter == 0) || flag_test(FLAG_IS_HUXLEY_ENABLED) ) {
		sound_start (ST_EFFECT, SUBWAY2, SL_2S, SP_NORMAL);
		for (fno = IMG_JOHN_SPARTAN_A_START; fno <= IMG_JOHN_SPARTAN_A_END; fno += 2) {
					dmd_alloc_pair ();
					frame_draw(fno);
					dmd_show2 ();
					task_sleep (TIME_100MS);
		}//end of for loop
		sound_start (ST_EFFECT, SUBWAY2, SL_2S, SP_NORMAL);
		for (fno = IMG_JOHN_SPARTAN_A_END; fno >= IMG_JOHN_SPARTAN_A_START; fno -= 2) {
				dmd_map_overlay ();
				dmd_clean_page_low ();
					font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "HUXLEY");
					font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "READY");
					dmd_text_outline ();
					dmd_alloc_pair ();
					frame_draw(fno);
					dmd_overlay_outline ();
					dmd_show2 ();
					task_sleep (TIME_100MS);
		}//end of for loop
	}//END OF - one shot away from HUXLEY so tell the player so

	else

	//one shot away from car chase so tell the player so
	if ((DM_IN_DMD_TEST && MessageCounter == 1) || flag_test(FLAG_IS_CARCHASE_MODE_ENABLED)) {
		sound_start (ST_EFFECT, SUBWAY2, SL_2S, SP_NORMAL);
		for (fno = IMG_PHOENIX_A2_START; fno <= IMG_PHOENIX_A2_END; fno += 2) {
					dmd_alloc_pair ();
					frame_draw(fno);
					dmd_show2 ();
					task_sleep (TIME_100MS);
		}//end of for loop
		sound_start (ST_EFFECT, SUBWAY2, SL_2S, SP_NORMAL);
		for (fno = IMG_PHOENIX_A2_END; fno >= IMG_PHOENIX_A2_START; fno -= 2) {
				dmd_map_overlay ();
				dmd_clean_page_low ();
					font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "CAR CHASE");
					font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "READY");
					dmd_text_outline ();
					dmd_alloc_pair ();
					frame_draw(fno);
					dmd_overlay_outline ();
					dmd_show2 ();
					task_sleep (TIME_100MS);
		}//end of for loop
	}//END OF - one shot away from car chase so tell the player so

	else

	//one shot away from explode so tell the player so
	if ((DM_IN_DMD_TEST && MessageCounter == 2) || flag_test(FLAG_IS_EXPLODE_MODE_ENABLED) ) {
		sound_start (ST_EFFECT, SUBWAY2, SL_2S, SP_NORMAL);
		for (fno = IMG_JOHN_SPARTAN_A_START; fno <= IMG_JOHN_SPARTAN_A_END; fno += 2) {
					dmd_alloc_pair ();
					frame_draw(fno);
					dmd_show2 ();
					task_sleep (TIME_100MS);
		}//end of for loop
		sound_start (ST_EFFECT, SUBWAY2, SL_2S, SP_NORMAL);
		for (fno = IMG_JOHN_SPARTAN_A_END; fno >= IMG_JOHN_SPARTAN_A_START; fno -= 2) {
				dmd_map_overlay ();
				dmd_clean_page_low ();
					font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "EXPLODE");
					font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "READY");
					dmd_text_outline ();
					dmd_alloc_pair ();
					frame_draw(fno);
					dmd_overlay_outline ();
					dmd_show2 ();
					task_sleep (TIME_100MS);
		}//end of for loop
	}//END OF - one shot away from explode so tell the player so

	else

	//one shot away from video mode so tell the player so
	if ((DM_IN_DMD_TEST && MessageCounter == 3) || flag_test(FLAG_VIDEO_MODE_ENABLED) ) {
		sound_start (ST_EFFECT, SUBWAY2, SL_2S, SP_NORMAL);
		for (fno = IMG_PHOENIX_A2_START; fno <= IMG_PHOENIX_A2_END; fno += 2) {
					dmd_alloc_pair ();
					frame_draw(fno);
					dmd_show2 ();
					task_sleep (TIME_100MS);
		}//end of for loop
		sound_start (ST_EFFECT, SUBWAY2, SL_2S, SP_NORMAL);
		for (fno = IMG_PHOENIX_A2_END; fno >= IMG_PHOENIX_A2_START; fno -= 2) {
				dmd_map_overlay ();
				dmd_clean_page_low ();
					font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "VIDEO MODE");
					font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "READY");
					dmd_text_outline ();
					dmd_alloc_pair ();
					frame_draw(fno);
					dmd_overlay_outline ();
					dmd_show2 ();
					task_sleep (TIME_100MS);
		}//end of for loop
	}//END OF - one shot away from video mode so tell the player so

	else { // STANDARD DISPLAY OR (DM_IN_DMD_TEST && MessageCounter == 4)
		sound_start (ST_EFFECT, SUBWAY2, SL_2S, SP_NORMAL);
		for (fno = IMG_SIMON_FIRE1_START; fno <= IMG_SIMON_FIRE1_END; fno += 2) {
					dmd_alloc_pair ();
					frame_draw(fno);
					dmd_show2 ();
					task_sleep (TIME_100MS);
		}//end of for loop
		sound_start (ST_EFFECT, SUBWAY2, SL_2S, SP_NORMAL);
		for (fno = IMG_SIMON_FIRE1_END; fno >= IMG_SIMON_FIRE1_START; fno -= 2) {
			sprintf ("SUBWAY");
				dmd_map_overlay ();
				dmd_clean_page_low ();
					font_render_string_center (&font_halobold14, DMD_MIDDLE_X - 10, DMD_BIG_CY_Bot, sprintf_buffer);
					dmd_text_outline ();
					dmd_alloc_pair ();
					frame_draw(fno);
					dmd_overlay_outline ();
					dmd_show2 ();
					task_sleep (TIME_100MS);
		}//end of for loop
	}//end of else

	task_sleep (TIME_500MS);
		deff_exit ();
}//end of mode_effect_deff








void computer_award_adder(char * words, U8 scoreAmount, U8 multiplier) {
		sound_start1 (ST_EFFECT, BONUS_SHORT);
		dmd_alloc_low_clean ();
		score_zero (ca_bonus_scored);
		switch (scoreAmount) {
			case 1: 	score_add (ca_bonus_scored, score_table[SC_25K]);	break;
			case 2: 	score_add (ca_bonus_scored, score_table[SC_50K]); 	break;
			case 3: 	score_add (ca_bonus_scored, score_table[SC_100K]); break;
			case 4: 	score_add (ca_bonus_scored, score_table[SC_500K]); break;
			case 5: 	score_add (ca_bonus_scored, score_table[SC_1M]);	break;
			case 6: 	score_add (ca_bonus_scored, score_table[SC_3M]); 	break;
		}

		if (multiplier > 1) { //multiply bonus scored by multiplier
					score_t copy;
					score_copy (copy, ca_bonus_scored);
					do {
						score_add (ca_bonus_scored, copy);
					} while (--multiplier > 1);
		}
		score_add (ca_total_bonus, ca_bonus_scored);
}//end of FUNCTION


/****************************************************************************
 *
 * CA bonus helper functions
 *
 ****************************************************************************/
/* Speed up the bonus if flipper buttons are pressed */
void ca_bonus_button_monitor (void) {
	for (;;) {
		if (	( switch_poll_logical (SW_LEFT_BUTTON) && switch_poll_logical (SW_RIGHT_BUTTON) )
			||	( switch_poll_logical (SW_U_L_FLIPPER_BUTTON) && switch_poll_logical (SW_U_R_FLIPPER_BUTTON) ) )
			both_buttons_held = TRUE;

		else
			if (	switch_poll_logical (SW_LEFT_BUTTON)
				||	switch_poll_logical (SW_RIGHT_BUTTON)
				||	switch_poll_logical (SW_U_L_FLIPPER_BUTTON)
				||	switch_poll_logical (SW_U_R_FLIPPER_BUTTON) )
				one_button_held = TRUE;

		task_sleep (TIME_100MS);
	}//end of for loop
}//end of function





/* Function so we can call two different transistions
 * depending on whether the buttons were pressed */
void ca_bonus_sched_transition (void) {
	if (both_buttons_held || one_button_held)
		dmd_sched_transition (&trans_scroll_down_fast);
	else
		dmd_sched_transition (&trans_scroll_down);
}//end of function




void ca_bonus_pause (void) {
	if (both_buttons_held)		task_sleep (TIME_33MS);
	else if (one_button_held) 	task_sleep (TIME_100MS);
	else 					{ 	task_sleep (TIME_500MS); task_sleep (TIME_133MS); }
}//end of function










void computer_award_deff(void) {
	U8 i;
	U8 ca_rnd_sound;
	U8 CAChooser;
	ball_search_monitor_stop ();

	if (system_config.swear_sounds == YES) {
		//this doubles the chance that a swear would occur
		ca_rnd_sound = random_scaled(5);
		if (ca_rnd_sound == 4) ca_rnd_sound = 3;
	}
	else 											ca_rnd_sound = random_scaled(3);

	switch (ca_rnd_sound) {
		case 0: 	sound_start (ST_SPEECH, SPCH_ACCESSING, SL_2S, PRI_GAME_QUICK3); break;
		case 1: 	sound_start (ST_SPEECH, SPCH_COMPUTER_AWARD, SL_2S, PRI_GAME_QUICK3); break;
		case 2: 	sound_start (ST_SPEECH, COMPUTER1, SL_2S, PRI_GAME_QUICK3); break;
		case 3: 	sound_start (ST_SPEECH, SPCH_ACCESSING, SL_2S, PRI_GAME_QUICK3); break;
	}

	dmd_alloc_low_clean ();
	dmd_draw_thin_border (dmd_low_buffer);
	sprintf ("COMPUTER AWARD");
	font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);
	dmd_show_low ();
	task_sleep_sec (1);

	leff_start(LEFF_FLASH_ALL);
	task_sleep (TIME_100MS);

	dmd_map_overlay ();
	dmd_clean_page_high ();
	dmd_clean_page_low ();
	dmd_draw_thin_border (dmd_low_buffer);
	sprintf ("COMPUTER AWARD");
	font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);

	sound_start (ST_EFFECT, COMPUTER_ADDING, SL_3S, PRI_GAME_QUICK6);

	show_text_on_squares (10);//5 times per second

	switch (ca_rnd_sound) {
		case 0: 	sound_start (ST_SPEECH, COMPUTER_AWARD_LONG, SL_2S, PRI_GAME_QUICK3); break;
		case 1: 	sound_start (ST_SPEECH, COMPUTER_AWARD_SMALL, SL_2S, PRI_GAME_QUICK3); break;
		case 2: 	sound_start (ST_SPEECH, COMPUTER2, SL_2S, PRI_GAME_QUICK3); break;
		case 3: 	sound_start (ST_SPEECH, SPCH_VLGR_LIKE_TO_HAVE_SEX_SNDRA, SL_2S, PRI_GAME_QUICK3); break;
	}
	task_sleep(TIME_2S);

	dmd_alloc_low_clean ();
	if (system_config.tournament_mode == NO) 	CAChooser = nextcomputerAwardsChooser;
	else {  //tournament mode
		CAChooser = TM_nextcomputerAwardsChooser[TM_nextcomputerAwardsChooser_PlayerPointer];
	} //end of else tournament mode

//	CAChooser = 0;

	switch (CAChooser) {
//COLLECT BONUS
	case 0 :
			one_button_held = FALSE;
			both_buttons_held = FALSE;
			/* Start a task to monitor the buttons - if buttons are held bonus runs faster*/
			task_recreate_gid (GID_BONUS_BUTTON_MONITOR, ca_bonus_button_monitor);

			dmd_draw_thin_border (dmd_low_buffer);
			sound_start(ST_SPEECH, SPCH_COLLECT_BONUS, SL_4S, PRI_GAME_QUICK3);
			sprintf ("COLLECT");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Top, sprintf_buffer);
			sprintf ("BONUS");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, sprintf_buffer);
			dmd_show_low ();
			task_sleep (TIME_500MS);
			task_sleep (TIME_133MS);

			in_bonus = TRUE;
			sound_start1 (ST_ANY, BONUS_SHORT);
			score_zero (ca_total_bonus);	/* Clear the bonus score */
			/* Show Initial bonus screen */
			dmd_alloc_low_clean ();
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, "BONUS");
			dmd_sched_transition (&trans_scroll_down);
			dmd_show_low ();
			task_sleep (TIME_500MS);
			task_sleep (TIME_133MS);

			/**
			 * *car crash scoring and display *
			 * **/
			if (car_crash_shots_made > 0) {
					computer_award_adder ("CAR CRASH", 2, car_crash_shots_made);

					sprintf_score (ca_bonus_scored);
					font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, sprintf_buffer);
					sprintf ("CAR CRASH");
					font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);
					ca_bonus_sched_transition ();
					dmd_show_low ();
					ca_bonus_pause ();
			}/***end of car crash scoring and display ***/


			/**
			 * *eyeball scoring and display *
			 * **/
			if (eyeball_shots_made > 0) {
					sound_start1 (ST_ANY, BONUS_SHORT);
					dmd_alloc_low_clean ();
					computer_award_adder ("EYEBALLS", 3, eyeball_shots_made);

					sprintf_score (ca_bonus_scored);
					font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, sprintf_buffer);
					sprintf ("EYEBALLS");
					font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);
					ca_bonus_sched_transition ();
					dmd_show_low ();
					ca_bonus_pause ();
			}/***end of eyeball scoring and display ***/

			/**
			 * *combos scoring and display *
			 * **/
			if (combo_counter > 0) {
					sound_start1 (ST_ANY, BONUS_SHORT);
					dmd_alloc_low_clean ();
					computer_award_adder ("COMBOS", 1, combo_counter);

					sprintf_score (ca_bonus_scored);
					font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, sprintf_buffer);
					sprintf ("COMBOS");
					font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);
					ca_bonus_sched_transition ();
					dmd_show_low ();
					ca_bonus_pause ();
			}/***end of combos scoring and display ***/

			/**
			 * *car chase scoring and display *
			 * **/
			if (get_dm_mode(CHASE_COMPLETED)) {
					sound_start1 (ST_ANY, BONUS_SHORT);
					dmd_alloc_low_clean ();
					computer_award_adder ("CAR CHASE", 5, 1);

					sprintf_score (ca_bonus_scored);
					font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, sprintf_buffer);
					sprintf ("CAR CHASE");
					font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);
					ca_bonus_sched_transition ();
					dmd_show_low ();
					ca_bonus_pause ();
			}/***end of car chase scoring and display ***/

			/**
			 * *explode scoring and display *
			 * **/
			if (get_dm_mode(EXPLODE_COMPLETED)) {
					sound_start1 (ST_ANY, BONUS_SHORT);
					dmd_alloc_low_clean ();
					computer_award_adder ("EXPLODE", 5, 1);

					sprintf_score (ca_bonus_scored);
					font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, sprintf_buffer);
					sprintf ("EXPLODE");
					font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);
					ca_bonus_sched_transition ();
					dmd_show_low ();
					ca_bonus_pause ();
			}/***end of explode scoring and display ***/

			/**
			 * *acmag scoring and display *
			 * **/
			if (get_dm_mode(ACMAG_COMPLETED)) {
					sound_start1 (ST_ANY, BONUS_SHORT);
					dmd_alloc_low_clean ();
					computer_award_adder ("ACMAG", 6,  1);

					sprintf_score (ca_bonus_scored);
					font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, sprintf_buffer);
					sprintf ("ACMAG");
					font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);
					ca_bonus_sched_transition ();
					dmd_show_low ();
					ca_bonus_pause ();
			}/***end of acmag scoring and display ***/

			/**
			 * *capture_simon scoring and display *
			 * **/
			if (get_dm_mode(CAP_SIM_COMPLETED)) {
					sound_start1 (ST_ANY, BONUS_SHORT);
					dmd_alloc_low_clean ();
					computer_award_adder ("CAPTURE SIMON", 6,  1);
					sprintf_score (ca_bonus_scored);
					font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, sprintf_buffer);
					sprintf ("CAPTURE SIMON");
					font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);
					ca_bonus_sched_transition ();
					dmd_show_low ();
					ca_bonus_pause ();
			}/***end of capture_simon scoring and display ***/

			/**
			 * *prison_break scoring and display *
			 * **/
			if (get_dm_mode(BREAKOUT_COMPLETED)) {
					sound_start1 (ST_ANY, BONUS_SHORT);
					dmd_alloc_low_clean ();
					computer_award_adder ("BREAKOUT", 6,  1);

					sprintf_score (ca_bonus_scored);
					font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, sprintf_buffer);
					sprintf ("BREAKOUT");
					font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);
					ca_bonus_sched_transition ();
					dmd_show_low ();
					ca_bonus_pause ();
			}/***end of prison_break scoring and display ***/

			/**
			 * *superjets scoring and display *
			 * **/
			if (get_dm_mode(SJETS_COMPLETED)) {
					sound_start1 (ST_ANY, BONUS_SHORT);
					dmd_alloc_low_clean ();
					computer_award_adder ("SUPER JETS", 6,  1);

					sprintf_score (ca_bonus_scored);
					font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, sprintf_buffer);
					sprintf ("SUPERJETS");
					font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);
					ca_bonus_sched_transition ();
					dmd_show_low ();
					ca_bonus_pause ();
			}/***end of superjets scoring and display ***/

			/**
			 * *standupFrenzy scoring and display *
			 * **/
			if (standupFrenzyNumHits > 0) {
					sound_start1 (ST_ANY, BONUS_SHORT);
					dmd_alloc_low_clean ();
					computer_award_adder ("FRENZY", 2,  standupFrenzyNumHits);

					sprintf_score (ca_bonus_scored);
					font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, sprintf_buffer);
					sprintf ("FRENZY");
					font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);
					ca_bonus_sched_transition ();
					dmd_show_low ();
					ca_bonus_pause ();
			}/***end of standupFrenzy scoring and display ***/

			/**
			 * *fortress scoring and display *
			 * **/
			if (get_dm_mode2(FORTRESS_COMPLETED)) {
					sound_start1 (ST_ANY, BONUS_SHORT);
					dmd_alloc_low_clean ();
					computer_award_adder ("FORTRESS", 5,  1);

					sprintf_score (ca_bonus_scored);
					font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, sprintf_buffer);
					sprintf ("FORTRESS");
					font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);
					ca_bonus_sched_transition ();
					dmd_show_low ();
					ca_bonus_pause ();
			}/***end of fortress scoring and display ***/

			/**
			 * *museum scoring and display *
			 * **/
			if (get_dm_mode2(MUSEUM_COMPLETED)) {
					sound_start1 (ST_ANY, BONUS_SHORT);
					dmd_alloc_low_clean ();
					computer_award_adder ("MUSEUM", 5,  2);

					sprintf_score (ca_bonus_scored);
					font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, sprintf_buffer);
					sprintf ("MUSEUM");
					font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);
					ca_bonus_sched_transition ();
					dmd_show_low ();
					ca_bonus_pause ();
			}/***end of museum scoring and display ***/

			/**
			 * *wasteland scoring and display *
			 * **/
			if (get_dm_mode2(WASTELAND_COMPLETED)) {
					sound_start1 (ST_ANY, BONUS_SHORT);
					dmd_alloc_low_clean ();
					computer_award_adder ("WASTELAND", 5,  3);

					sprintf_score (ca_bonus_scored);
					font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, sprintf_buffer);
					sprintf ("WASTELAND");
					font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);
					ca_bonus_sched_transition ();
					dmd_show_low ();
					ca_bonus_pause ();
			}/***end of wasteland_ scoring and display ***/

			/**
			 * *cryoprison scoring and display *
			 * **/
			if (get_dm_mode2(CRYO_COMPLETED)) {
					sound_start1 (ST_ANY, BONUS_SHORT);
					dmd_alloc_low_clean ();
					computer_award_adder ("CRYOPRISON", 5,  4);

					sprintf_score (ca_bonus_scored);
					font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, sprintf_buffer);
					sprintf ("CRYOPRISON");
					font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);
					ca_bonus_sched_transition ();
					dmd_show_low ();
					ca_bonus_pause ();
			}/***end of cryoprison_ scoring and display ***/

			/**
			 * *demotime scoring and display *
			 * **/
			if (get_dm_mode2(DTIME_COMPLETED)) {
					sound_start1 (ST_ANY, BONUS_SHORT);
					dmd_alloc_low_clean ();
					computer_award_adder ("DEMO TIME", 6,  5);

					sprintf_score (ca_bonus_scored);
					font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, sprintf_buffer);
					sprintf ("DEMO TIME");
					font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);
					ca_bonus_sched_transition ();
					dmd_show_low ();
					ca_bonus_pause ();
			}/***end of demotime_ scoring and display ***/

			/**
			 * *huxley scoring and display *
			 * **/
			if (get_dm_mode(HUXLEY_COMPLETED)) {
					sound_start1 (ST_ANY, BONUS_SHORT);
					dmd_alloc_low_clean ();
					computer_award_adder ("HUXLEY", 6,  3);

					sprintf_score (ca_bonus_scored);
					font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, sprintf_buffer);
					sprintf ("HUXLEY");
					font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);
					ca_bonus_sched_transition ();
					dmd_show_low ();
					ca_bonus_pause ();
			}/***end of huxley scoring and display ***/

			/**
			 * *back_in_the_fridge scoring and display *
			 * **/
			if (get_dm_mode2(BITF_COMPLETED)) {
					sound_start1 (ST_ANY, BONUS_SHORT);
					dmd_alloc_low_clean ();
					computer_award_adder ("FRIDGE", 6,  5);

					sprintf_score (ca_bonus_scored);
					font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, sprintf_buffer);
					sprintf ("FRIDGE");
					font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);
					ca_bonus_sched_transition ();
					dmd_show_low ();
					ca_bonus_pause ();
			}/***end of back_in_the_fridge scoring and display ***/


			/**
			 * *rollover_bonus_multiplier scoring and display *
			 * **/
			if (rollover_bonus_multiplier > 1) {
					sound_start1 (ST_ANY, BONUS_SHORT);
					dmd_alloc_low_clean ();
					score_zero (ca_bonus_scored);
					score_add (ca_bonus_scored, ca_total_bonus);
					score_mul (ca_bonus_scored, rollover_bonus_multiplier-1);
					score_add (ca_total_bonus, ca_bonus_scored);

					sprintf_score (ca_bonus_scored);
					font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, sprintf_buffer);
					sprintf ("X ROLLOVER X");
					font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);
					ca_bonus_sched_transition ();
					dmd_show_low ();
					ca_bonus_pause ();
			}/***end of rollover_bonus_multiplier scoring and display ***/


			/* Show final score */
			sound_start1 (ST_ANY, BONUS_LONG);
			score_long (ca_total_bonus); // Add to total bonus to player score
			dmd_alloc_low_clean ();
			scores_draw ();
			dmd_sched_transition (&trans_scroll_up);
			dmd_show_low ();
			task_kill_gid (GID_BONUS_BUTTON_MONITOR);
			task_sleep (TIME_500MS);
			in_bonus = FALSE;
			break;

//TRIPLE CAR CRASH
	case 1 :
			dmd_draw_thin_border (dmd_low_buffer);
			sound_start(ST_SPEECH, SPCH_TRIPLE_CAR_CRASH, SL_4S, PRI_GAME_QUICK3);
			sprintf ("TRIPLE");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Top, sprintf_buffer);
			sprintf ("CAR CRASH");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, sprintf_buffer);
			dmd_show_low ();
			comp_award_trip_car_crash();
			task_sleep_sec (1);
						lamp_tristate_flash (LM_CAR_CRASH_TOP);
						lamp_tristate_flash (LM_CAR_CRASH_CENTER);
						lamp_tristate_flash (LM_CAR_CRASH_BOTTOM);
						for (i = 0; i < 3; i++) {
							sound_start (ST_EFFECT, ZAPP_3_SHORT, SL_2S, PRI_GAME_QUICK2);
							flasher_pulse (FLASH_CAR_CHASE_LOWER);
							flasher_pulse (FLASH_CAR_CHASE_UPPER);
							task_sleep (TIME_300MS);
						}
						for (i = 0; i < 3; i++) {
							sound_start (ST_EFFECT, ZAPP_3_MED, SL_2S, PRI_GAME_QUICK2);
							flasher_pulse (FLASH_CAR_CHASE_LOWER);
							flasher_pulse (FLASH_CAR_CHASE_UPPER);
							task_sleep (TIME_500MS);
						}
						task_sleep_sec (1);
						sound_start (ST_EFFECT, ZAPP_3_LONG, SL_2S, PRI_GAME_QUICK3);
						restore_carcrash_lights_state();
			task_sleep_sec (1);
			break;

	//COLLECT STANDUPS
	case 2 :
			dmd_draw_thin_border (dmd_low_buffer);
			sound_start(ST_SPEECH, SPCH_COLLECT_STANDUPS, SL_4S, PRI_GAME_QUICK3);
			sprintf ("COLLECT");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Top, sprintf_buffer);
			sprintf ("STANDUPS");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, sprintf_buffer);
			dmd_show_low ();
			task_sleep_sec (2);
			/////////////////////collectstandups deff
				U8 collect_standups_counter = 0;
				U8 digit_counter = 0;
					for (collect_standups_counter = 0; collect_standups_counter <= standup_num_of_hits; collect_standups_counter++) {
							score (SC_500K);

							dmd_alloc_pair ();
							dmd_clean_page_low ();

//							sprintf ("%d", standup_num_of_hits - collect_standups_counter);
							if (collect_standups_counter == 0) 		sprintf ("500 THOUSAND");
							else if (collect_standups_counter %2 == 1) { digit_counter++; 	sprintf ("%d MILLION", digit_counter); }
							else if (collect_standups_counter %2 == 0) { 					sprintf ("%d.5 MILLION", digit_counter); }

							font_render_string_center(&font_fixed10, DMD_MIDDLE_X, DMD_MIDDLE_Y, sprintf_buffer);
							dmd_copy_low_to_high ();
							dmd_show_low ();
							dmd_invert_page (dmd_low_buffer);
							deff_swap_low_high (1, TIME_100MS);


							if (collect_standups_counter < 3 )		{
								sound_start (ST_EFFECT, ZAPP_3_LONG, SL_2S, PRI_GAME_QUICK2);
								task_sleep (TIME_500MS);
								task_sleep (TIME_250MS);
							} else if (collect_standups_counter < 6) {
								sound_start (ST_EFFECT, ZAPP_3_MED, SL_2S, PRI_GAME_QUICK3);
								task_sleep (TIME_500MS);
							} else 	{
								sound_start (ST_EFFECT, ZAPP_3_SHORT, SL_2S, PRI_GAME_QUICK2);
								task_sleep (TIME_300MS);
							}
					}//end of loop
			task_sleep_sec (1);
			break;

	//LIGHT ARROWS
	case 3 :
			score (SC_3M);
			dmd_draw_thin_border (dmd_low_buffer);
			sound_start(ST_SPEECH, SPCH_LIGHT_ARROWS, SL_4S, PRI_GAME_QUICK3);
			sprintf ("LIGHT");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Top, sprintf_buffer);
			sprintf ("ARROWS");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, sprintf_buffer);
			dmd_show_low ();
			task_sleep_sec (1);

			dmd_alloc_low_clean ();
			dmd_draw_thin_border (dmd_low_buffer);
			sprintf ("THREE");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Top, sprintf_buffer);
			sprintf ("MILLION");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, sprintf_buffer);
			dmd_show_low ();
			task_sleep_sec (1);

						lamp_tristate_flash (LM_SIDE_RAMP_ARROW);
						lamp_tristate_flash (LM_LEFT_RAMP_ARROW);
						lamp_tristate_flash (LM_RIGHT_RAMP_ARROW);
						lamp_tristate_flash (LM_UNDERGROUND_ARROW);
						lamp_tristate_flash (LM_CENTER_RAMP_ARROW);
						lamp_tristate_flash (LM_LEFT_LOOP_ARROW);
						lamp_tristate_flash (LM_RIGHT_LOOP_ARROW);

						for (i = 0; i < 3; i++) {
							sound_start (ST_EFFECT, ZAPP_3_SHORT, SL_2S, PRI_GAME_QUICK2);
							task_sleep (TIME_300MS);
						}
						for (i = 0; i < 2; i++) {
						sound_start (ST_EFFECT, ZAPP_3_MED, SL_2S, PRI_GAME_QUICK2);
						task_sleep (TIME_500MS);
						}
						for (i = 0; i < 2; i++) {
						sound_start (ST_EFFECT, ZAPP_3_LONG, SL_2S, PRI_GAME_QUICK2);
						task_sleep (TIME_500MS);
						}

			comp_award_light_arrows(); // combos.c
			task_sleep_sec (1);
			break;

	//LIGHT EXTRA BALL
	case 4 :
			dmd_draw_thin_border (dmd_low_buffer);
			sound_start(ST_SPEECH, SPCH_LIGHT_EXTRA_BALL, SL_4S, PRI_GAME_QUICK3);
			sprintf ("LIGHT");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Top, sprintf_buffer);
			sprintf ("EXTRA BALL");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, sprintf_buffer);
			dmd_show_low ();

			flasher_pulse (FLASH_ELEVATOR_1);
			task_sleep (TIME_33MS);
			flasher_pulse (FLASH_ELEVATOR_2);
			task_sleep (TIME_33MS);
			flasher_pulse (FLASH_CLAW_FLASHER);
			sound_start (ST_EFFECT, ZAPP_3_SHORT, SL_2S, PRI_GAME_QUICK2);
			task_sleep (TIME_100MS);

			flasher_pulse (FLASH_CLAW_FLASHER);
			task_sleep (TIME_33MS);
			flasher_pulse (FLASH_ELEVATOR_2);
			task_sleep (TIME_33MS);
			flasher_pulse (FLASH_ELEVATOR_1);
			sound_start (ST_EFFECT, ZAPP_3_SHORT, SL_2S, PRI_GAME_QUICK2);
			task_sleep (TIME_100MS);

			flasher_pulse (FLASH_ELEVATOR_1);
			task_sleep (TIME_33MS);
			flasher_pulse (FLASH_CLAW_FLASHER);
			task_sleep (TIME_33MS);
			flasher_pulse (FLASH_ELEVATOR_2);
			sound_start (ST_EFFECT, ZAPP_3_MED, SL_2S, PRI_GAME_QUICK2);
			task_sleep (TIME_100MS);

			for (i = 0; i < 6; i++) {
				flasher_pulse (FLASH_LEFT_RAMP_UP);
				task_sleep (TIME_33MS);
				flasher_pulse (FLASH_DIVERTER_FLASHER);
				task_sleep (TIME_33MS);
				flasher_pulse (FLASH_RIGHT_RAMP_UP);
				sound_start (ST_EFFECT, ZAPP_3_MED, SL_2S, PRI_GAME_QUICK2);
				task_sleep (TIME_100MS);
			}

			start_extraball();
			task_sleep_sec (1);
			break;

//MAXIMIZE FREEZES
	case 5 :
			dmd_draw_thin_border (dmd_low_buffer);
			sound_start(ST_SPEECH, SPCH_MAXIMIZE_FREEZES, SL_4S, PRI_GAME_QUICK3);
			sprintf ("MAXIMIZE");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Top, sprintf_buffer);
			sprintf ("FREEZES");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, sprintf_buffer);
			dmd_show_low ();

			lamp_tristate_flash (LM_FREEZE_1);
			lamp_tristate_flash (LM_FREEZE_2);
			lamp_tristate_flash (LM_FREEZE_3);
			lamp_tristate_flash (LM_FREEZE_4);

			for (i = 0; i < 3; i++) {
				sound_start (ST_EFFECT, ZAPP_3_SHORT, SL_2S, PRI_GAME_QUICK2);
				task_sleep (TIME_300MS);
			}
			sound_start (ST_EFFECT, ZAPP_3_MED, SL_2S, PRI_GAME_QUICK2);
			task_sleep (TIME_500MS);
			sound_start (ST_EFFECT, ZAPP_3_MED, SL_2S, PRI_GAME_QUICK2);
			task_sleep (TIME_500MS);

			sound_start (ST_EFFECT, ZAPP_3_LONG, SL_2S, PRI_GAME_QUICK2);
			task_sleep (TIME_500MS);
			sound_start (ST_EFFECT, ZAPP_3_LONG, SL_2S, PRI_GAME_QUICK2);
			task_sleep (TIME_500MS);

			maximize_freeze();
			task_sleep_sec (1);
			break;

//DOUBLE RETINA SCAN
		case 6 :
			dmd_draw_thin_border (dmd_low_buffer);
			sound_start(ST_SPEECH, SPCH_DOUBLE_RETINA_SCAN, SL_4S, PRI_GAME_QUICK3);
			sprintf ("DOUBLE");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Top, sprintf_buffer);
			sprintf ("RETINA SCAN");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, sprintf_buffer);
			dmd_show_low ();

			lamp_tristate_flash(LM_RETINA_SCAN);
			for (i = 0; i < 3; i++) {
				flasher_pulse (FLASH_EJECT_FL);
				flasher_pulse (FLASH_EYEBALL);
				flasher_pulse (FLASH_EJECT_FL);
				flasher_pulse (FLASH_EYEBALL);
				sound_start (ST_EFFECT, ZAPP_3_SHORT, SL_2S, PRI_GAME_QUICK2);
				task_sleep (TIME_300MS);
			}
			for (i = 0; i < 4; i++) {
				flasher_pulse (FLASH_EJECT_FL);
				flasher_pulse (FLASH_EYEBALL);
				flasher_pulse (FLASH_EJECT_FL);
				flasher_pulse (FLASH_EYEBALL);
				sound_start (ST_EFFECT, ZAPP_3_MED, SL_2S, PRI_GAME_QUICK2);
				task_sleep (TIME_500MS);
			}
			comp_award_doub_retina();
			lamp_tristate_off(LM_RETINA_SCAN);
			task_sleep_sec (1);
			break;

	//BIG POINTS
		case 7 :
			score (SC_10M);
			dmd_draw_thin_border (dmd_low_buffer);
			sprintf ("BIG POINTS");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Top, sprintf_buffer);
			sprintf ("10 MILLION");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, sprintf_buffer);
			dmd_show_low ();

			for (i = 0; i < 5; i++) {
				flasher_pulse (FLASH_LEFT_RAMP_UP);
				task_sleep (TIME_33MS);
				flasher_pulse (FLASH_DIVERTER_FLASHER);
				task_sleep (TIME_33MS);
				flasher_pulse (FLASH_RIGHT_RAMP_UP);
				sound_start (ST_EFFECT, ZAPP_3_MED, SL_2S, PRI_GAME_QUICK2);
				task_sleep (TIME_100MS);
			}

			task_sleep (TIME_500MS);
			break;

	//CAR CHASE
		case 8 :
			dmd_draw_thin_border (dmd_low_buffer);
			sprintf ("START");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Top, sprintf_buffer);
			sprintf ("CAR CHASE");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, sprintf_buffer);
			dmd_show_low ();
			task_sleep_sec (1);
			start_car_chase(); //at car_chase_mode.c
			break;

	//EXPLODE
		case 9 :
			dmd_draw_thin_border (dmd_low_buffer);
			sprintf ("START");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Top, sprintf_buffer);
			sprintf ("EXPLODE");
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, sprintf_buffer);
			dmd_show_low ();
			task_sleep_sec (1);
			start_explode();//start explode mode
			break;
	}//end of switch
	task_sleep(TIME_500MS);

	//////////////////////////////////////////////////////////////////////
	if (DM_IN_DMD_TEST || DM_IN_CAB_TEST) {
		if (++nextcomputerAwardsChooser > 9) 	nextcomputerAwardsChooser = 0;
	}
	else {
		if (system_config.tournament_mode == NO) {
			//	not tournament mode
			nextcomputerAwardsChooser = random_scaled(10);
			CAChooser = nextcomputerAwardsChooser;
		}
			//tournament mode
		else {
			if (++TM_nextcomputerAwardsChooser_PlayerPointer >= 10)  TM_nextcomputerAwardsChooser_PlayerPointer = 0;
			CAChooser = TM_nextcomputerAwardsChooser[TM_nextcomputerAwardsChooser_PlayerPointer];
		}
	}//end of else not in dmd test

	dmd_alloc_pair_clean ();// Clean both pages
	dmd_draw_thin_border (dmd_low_buffer);
	sprintf ("NEXT AWARD");
	font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Top, sprintf_buffer);

	switch (CAChooser) {
		case 0 : font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "BONUS"); break;
		case 1 : font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "3X CRASH"); break;
		case 2 : font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "STANDUPS"); break;
		case 3 : font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "ARROWS"); break;
		case 4 : font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "EXTRA BALL"); break;
		case 5 : font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "MAX FREEZES"); break;
		case 6 : font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "2X RETINA SCAN"); break;
		case 7 : font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "BIG POINTS"); break;
		case 8 : font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "CAR CHASE"); break;
		case 9 : font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "EXPLODE"); break;
	}//end of switch
	dmd_show_low ();
	task_sleep(TIME_1S);

	computer_light_off(); //turns off flag here also
	combo_rehit_check (); //check to see if enough combos for next computer award
	ball_search_monitor_start ();
	computer_award_just_awarded = TRUE;
	deff_exit ();
}//end of function





#define MAX_SQUARE 24
#define MAX_STATE_SQUARE 5

struct square_state {
	U8 state;
	U8 x;
	U8 y;
} square_states[MAX_SQUARE];



/*
 * The format of the image data is the same as for a font glyph:
the first byte is its bit-width, the second byte is its
bit-height, and the remaining bytes are the image data, going
from left to right, top to bottom.
 *font_byte_width = (font_width + 7) >> 3
 */
static const U8 open_square_bitmaps1[] = {//open, big hole in middle
		8, 8,
		0xFF, 0X81, 0X81, 0X81,
		0X81, 0X81, 0X81, 0xFF,

};

static const U8 open_square_bitmaps2[] = {//open, small hole in middle
		8, 8,
		0xFF, 0XFF, 0XC3, 0XC3,
		0XC3, 0XC3, 0XFF, 0xFF,
};

static const U8 closed_square_bitmaps[] = {//solid square
		8, 8,
		0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF,
};

static const U8 closed_square_bitmaps2[] = {//small solid square
		8, 8,
		0x00, 0x00, 0x3C, 0x3C,
		0x3C, 0x3C, 0x00, 0x00,
};

static const U8 closed_square_bitmaps3[] = {//tiny solid square
		8, 8,
		0x00, 0x00, 0x18, 0x18,
		0x18, 0x18, 0x00, 0x00,
};

void square_init (void) {
	U8 TEMPX = 6;
	U8 TEMPY = 0;
	U8 n;
	for (n = 0; n < 24; n++) {
		struct square_state *s = &square_states[n];
		if (n % 12 == 0) {
			TEMPX = 6;
			TEMPY += 9;
		}
		s->x = TEMPX; // from 14 to 114 --total size is 128
		s->y = TEMPY;
		TEMPX += 10;
		s->state = random_scaled (12); // 0 to n-1
	}
}//end of function



void square_draw (U8 sq) {
	struct square_state *s = &square_states[sq];
//	s->state = 1; // 0 to n-1
	s->state = random_scaled (12); // 0 to n-1
	switch (s->state) {
	case 0:
		bitmap_blit (open_square_bitmaps1, s->x, s->y); //open square - light
		break;
	case 1:
		bitmap_blit (open_square_bitmaps1, s->x, s->y); //open square - dark
		dmd_flip_low_high();
		bitmap_blit (open_square_bitmaps1, s->x, s->y);
		dmd_flip_low_high();
		break;
	case 2:
		bitmap_blit (open_square_bitmaps2, s->x, s->y); //open small square - light
		break;
	case 3:
		bitmap_blit (open_square_bitmaps2, s->x, s->y); //open small square - dark
		dmd_flip_low_high();
		bitmap_blit (open_square_bitmaps2, s->x, s->y);
		dmd_flip_low_high();
		break;
	case 4:
		bitmap_blit (closed_square_bitmaps, s->x, s->y); //closed square, light
		break;
	case 5:
		bitmap_blit (closed_square_bitmaps, s->x, s->y); //closed square, dark
		dmd_flip_low_high();
		bitmap_blit (closed_square_bitmaps, s->x, s->y);
		dmd_flip_low_high();
		break;
	case 6:
		bitmap_blit (closed_square_bitmaps2, s->x, s->y); //closed small square, light
		break;
	case 7:
		bitmap_blit (closed_square_bitmaps2, s->x, s->y); //closed small square, dark
		dmd_flip_low_high();
		bitmap_blit (closed_square_bitmaps2, s->x, s->y);
		dmd_flip_low_high();
		break;
	case 8:
		bitmap_blit (open_square_bitmaps1, s->x, s->y); //dark in middle, light outside
		dmd_flip_low_high();							//slightly tilted to left
		bitmap_blit (closed_square_bitmaps2, s->x, s->y);
		dmd_flip_low_high();
		break;
	case 9:
		bitmap_blit (closed_square_bitmaps2, s->x, s->y); //light in middle, dark outside
		dmd_flip_low_high();							//slightly tilted to left
		bitmap_blit (open_square_bitmaps1, s->x, s->y);
		dmd_flip_low_high();
		break;
	case 10:
		bitmap_blit (open_square_bitmaps1, s->x, s->y); //dark in middle, light outside
		dmd_flip_low_high();							//slightly tilted to left
		bitmap_blit (closed_square_bitmaps3, s->x, s->y);
		dmd_flip_low_high();
		break;
	case 11:
		bitmap_blit (closed_square_bitmaps3, s->x, s->y); //light in middle, dark outside
		dmd_flip_low_high();							//slightly tilted to left
		bitmap_blit (open_square_bitmaps1, s->x, s->y);
		dmd_flip_low_high();
		break;
	default:
		bitmap_blit (closed_square_bitmaps2, s->x, s->y);
		break;
	}
//	bitmap_blit2 (square_bitmaps + s->state * 5, s->x, s->y);//bitmap_erase_asm (...);
}//end of function



void show_text_on_squares (U8 times) {
	square_init();
	U8 n;
	U8 z;
	for (z = 0; z < times; z++) {
			dmd_dup_mapped ();//allocate new space but make it a copy of what is on DMD now
			dmd_overlay_onto_color ();//mono overlay onto current color page
			for (n = 0; n < 24; n++) {
				square_draw (n);
			}
		//	dmd_show_low();//shows a 2 color image
			dmd_show2 ();//shows a 4 color image
			task_sleep (TIME_200MS);
		//	dmd_map_overlay ();/** Map a consecutive display page pair into windows 0 & 1 */
			dmd_alloc_pair_clean ();
	}
}//END OF FUNCTION
