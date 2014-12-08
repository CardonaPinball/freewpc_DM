/*
 * bonus.c
 */
/* CALLSET_SECTION (bonus, __machine2__) */



#include <freewpc.h>
#include <eb.h>
#include <status.h>
#include "ngg/global_constants.h" 
#include "search.h"
#include <bcd_string.h>




//local variables
bool 	one_button_held;
bool 	both_buttons_held;
U16 	flipper_shots; 				//used to calculate bonus % for shots made using gun handles
U16 	gun_handle_trigger_shots; 	//used to calculate bonus % for shots made using gun handles
score_t total_bonus;				/* Total bonus score */
score_t bonus_scored;				/* Temp variable used to calculate bonus per item etc */

//external variables
extern __local__ U8 		car_crash_shots_made;
extern __local__ U8 		eyeball_shots_made;
extern __local__ U8 		combo_counter;
extern __local__ U8 		standupFrenzyNumHits;
extern __local__ U8 		standup_num_of_hits;

extern U8 		rollover_bonus_multiplier; //NOT LOCAL OKAY - RESET AT each new ball





/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
CALLSET_ENTRY (bonusNcomp_award, start_ball) {
	flipper_shots = 0;
	gun_handle_trigger_shots = 0;
}//end of function




/****************************************************************************
 *
 * body
 *
 ****************************************************************************/
void bonus_runner1 (char * words, U8 scoreAmount, U8 multiplier) {
	sound_start1 (ST_EFFECT, BONUS_SHORT);
	dmd_alloc_low_clean ();

	score_zero (bonus_scored);

	switch (scoreAmount) {
		case 1: 	score_add (bonus_scored, score_table[SC_25K]);	break;
		case 2: 	score_add (bonus_scored, score_table[SC_50K]); 	break;
		case 3: 	score_add (bonus_scored, score_table[SC_100K]); break;
		case 4: 	score_add (bonus_scored, score_table[SC_500K]); break;
		case 5: 	score_add (bonus_scored, score_table[SC_1M]);	break;
		case 6: 	score_add (bonus_scored, score_table[SC_3M]); 	break;
	}

	if (multiplier > 1) { //multiply bonus scored by multiplier
		score_t copy;
		score_copy (copy, bonus_scored);

		do {
			score_add (bonus_scored, copy);
		} while (--multiplier > 1);
	}

	score_add (total_bonus, bonus_scored);
	sprintf_score (bonus_scored);
	font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, sprintf_buffer);
	font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, words);
	bonus_sched_transition ();
	dmd_show_low ();
	bonus_pause ();
}//END OF FUNCTION






void bonus_runner (void) {
	in_bonus = TRUE;
	one_button_held = FALSE;
	both_buttons_held = FALSE;
	task_sleep (TIME_100MS);	/* Wait a bit so the previous music_stop doesn't kill the sounds */
	sound_start1 (ST_EFFECT, BONUS_SHORT);

	/* Start a task to monitor the buttons - if buttons are held bonus runs faster*/
	task_recreate_gid (GID_BONUS_BUTTON_MONITOR, bonus_button_monitor);

	/* Show Initial bonus screen */
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, "BONUS");
	dmd_sched_transition (&trans_scroll_down);
	dmd_show_low ();
	task_sleep (TIME_500MS);
	task_sleep (TIME_133MS);

	//minimum bonus score is 100k
	score_zero (total_bonus);
	score_zero (bonus_scored);
	score_add (total_bonus, score_table[SC_100K]);

	if (car_crash_shots_made > 0) 			bonus_runner1 ("CAR CRASH", 2,  car_crash_shots_made);
	if (eyeball_shots_made > 0) 			bonus_runner1 ("EYEBALLS", 3,  eyeball_shots_made);
	if (combo_counter > 0) 					bonus_runner1 ("COMBOS", 1,  combo_counter);
	if (get_dm_mode(CHASE_COMPLETED)) 		bonus_runner1 ("CAR CHASE", 5,  1);
	if (get_dm_mode(EXPLODE_COMPLETED)) 	bonus_runner1 ("EXPLODE", 5,  1);
	if (get_dm_mode(ACMAG_COMPLETED)) 		bonus_runner1 ("ACMAG", 6,  1);
	if (get_dm_mode(CAP_SIM_COMPLETED)) 	bonus_runner1 ("CAPTURE SIMON", 6,  1);
	if (get_dm_mode(BREAKOUT_COMPLETED)) 	bonus_runner1 ("BREAKOUT", 6,  1);
	if (get_dm_mode(SJETS_COMPLETED)) 		bonus_runner1 ("SUPER JETS", 6,  1);
	if (standupFrenzyNumHits > 0) 			bonus_runner1 ("FRENZY", 2,  standupFrenzyNumHits);
	if (get_dm_mode2(FORTRESS_COMPLETED)) 	bonus_runner1 ("FORTRESS", 5,  1);
	if (get_dm_mode2(MUSEUM_COMPLETED)) 	bonus_runner1 ("MUSEUM", 5,  2);
	if (get_dm_mode2(WASTELAND_COMPLETED)) 	bonus_runner1 ("WASTELAND", 5,  3);
	if (get_dm_mode2(CRYO_COMPLETED)) 		bonus_runner1 ("CRYOPRISON", 5,  4);
	if (get_dm_mode2(DTIME_COMPLETED)) 		bonus_runner1 ("DEMO TIME", 6,  5);
	if (get_dm_mode(HUXLEY_COMPLETED)) 		bonus_runner1 ("HUXLEY", 6,  3);
	if (get_dm_mode2(BITF_COMPLETED)) 		bonus_runner1 ("FRIDGE", 6,  5);

	/**
	 * *trigger shots scoring and display *
	 * **/
	S16 diff;
	diff = 0;
	if (flipper_shots || gun_handle_trigger_shots) //take divide by 0 into account
		diff = ( (gun_handle_trigger_shots * 10) / (flipper_shots + gun_handle_trigger_shots) );
	if (diff > 0) 		 bonus_runner1 ("GUN HANDLES", 3,  diff);

	/**
	 * *rollover_bonus_multiplier scoring and display *
	 * **/
	if (rollover_bonus_multiplier > 1) {
			sound_start1 (ST_EFFECT, BONUS_SHORT);
			dmd_alloc_low_clean ();
			score_zero (bonus_scored);
			score_add (bonus_scored, total_bonus);
			score_mul (bonus_scored, rollover_bonus_multiplier-1);
			score_add (total_bonus, bonus_scored);

			sprintf_score (bonus_scored);
			font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, sprintf_buffer);
			sprintf ("X ROLLOVER X");
			font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);
			bonus_sched_transition ();
			dmd_show_low ();
			bonus_pause ();
	}/***end of rollover_bonus_multiplier scoring and display ***/

	/* Show final score */
	sound_start1 (ST_EFFECT, BONUS_LONG);
	dmd_alloc_low_clean ();
	sprintf_score (total_bonus);
	font_render_string_center (&font_fixed10, DMD_MIDDLE_X, DMD_BIG_CY_Cent, sprintf_buffer);
	sprintf ("BONUS");
	font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);
	bonus_sched_transition ();
	dmd_show_low ();
	bonus_pause ();
    /***end of Show final scor ***/

	score_long (total_bonus); // Add to total bonus to player score
	dmd_alloc_low_clean ();
	scores_draw ();
	dmd_sched_transition (&trans_scroll_up);
	dmd_show_low ();

	task_kill_gid (GID_BONUS_BUTTON_MONITOR);
	task_sleep (TIME_500MS);
	task_sleep (TIME_133MS);
}//END OF FUNCTION






CALLSET_ENTRY (bonusNcomp_award, sw_upper_right_button, sw_upper_left_button) 	{
	if (in_game && !in_tilt && valid_playfield)	gun_handle_trigger_shots++;
}//end function




CALLSET_ENTRY (bonusNcomp_award, sw_right_button, sw_left_button) 	{
	if (in_game && !in_tilt && valid_playfield)	flipper_shots++;
}//end function



CALLSET_ENTRY (bonusNcomp_award, bonus){
	deff_start (DEFF_BONUS);
}//end of function




void bonus_deff (void) {
	bonus_runner ();

	//make verbal comments on final score
	U8 BSoundCounter;
	BSoundCounter = random_scaled(5);
	if (check_for_puny_score () ) {
			if (BSoundCounter == 0)	sound_start1 (ST_SPEECH, SPCH_PATHETIC);
			if (BSoundCounter == 1)	sound_start1 (ST_SPEECH, SPCH_SIMON_LAUGH_LONG);
			if (BSoundCounter == 2)	sound_start1 (ST_SPEECH, SPCH_SIMON_SNICKER);
			if (BSoundCounter == 3)	sound_start1 (ST_SPEECH, SPCH_SIMON_LAUGH_LONG);
			if (BSoundCounter == 4)	sound_start1 (ST_SPEECH, SPCH_HATE_WHEN_THAT_HAPPENS);
	}
	else if (check_for_big_score () ) {
			if (BSoundCounter == 0)	sound_start1 (ST_SPEECH, SPCH_BEST_DAY_OF_MY_LIFE);
			if (BSoundCounter == 1)	sound_start1 (ST_SPEECH, SPCH_HOW_NICE);
			if (BSoundCounter == 2)	sound_start1 (ST_SPEECH, SPCH_LOVE_THIS_GUY);
			if (BSoundCounter == 3)	sound_start1 (ST_SPEECH, SPCH_SOMETHING_RIGHT_PREV_LIFE);
			if (BSoundCounter == 4)	sound_start1 (ST_SPEECH, SPCH_OUTSTANDING);
	}

	task_sleep (TIME_500MS);
	task_sleep (TIME_133MS);
	in_bonus = FALSE;

	//this will start second half of end_ball routine in kernal/game.c
	//or if tilted will reset tilt at common/tilt.c
	callset_invoke (bonus_complete);
	deff_exit ();
}







/****************************************************************************
 *
 * bonus helper functions
 *
 ****************************************************************************/
/* Speed up the bonus if flipper buttons are pressed */
void bonus_button_monitor (void) {
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
void bonus_sched_transition (void) {
	if (both_buttons_held || one_button_held)
		dmd_sched_transition (&trans_scroll_down_fast);
	else
		dmd_sched_transition (&trans_scroll_down);
}//end of function




void bonus_pause (void) {
	if (both_buttons_held)		task_sleep (TIME_33MS);
	else if (one_button_held) 	task_sleep (TIME_100MS);
	else 					{ 	task_sleep (TIME_500MS); task_sleep (TIME_133MS); }
}//end of function





/* Used to announce if the player has played well */
bool check_for_big_score (void) {
	if (score_compare (total_bonus, score_table[SC_5M]) == 1) 	return TRUE;
			else 												return FALSE;
}//end of function





//returns 1 if s1 > s2
bool check_for_puny_score (void) {
	if (score_compare (score_table[SC_5M], total_bonus) == 1)  	return TRUE;
			else												return FALSE;
}//end of function

