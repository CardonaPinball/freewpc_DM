/*
 * demolition man
 * jets.c
 *
 * written by James Cardona
 *
 * Location Description:
 * Jet Bumpers: There are two regular jet bumpers and a top slingshot
 * which scores the same as a jet bumper. They advance the
 * Retina Scan value. The left jet bumper can also be hit from
 * the center ramp -- it acts as the right wall of the center ramp.
 *
 * Scoring Description: (original game)
 * The Jet Bumpers increase the Retina Value.(eyeball)
 * It starts at 5M and goes up 100K per jet.
 * There are two Jet Bumpers and one slingshot ... the slingshot counts as a jet bumper.
 * Jet Bumpers award 250k a Pop.
 * superjets mode award 1 million each
 *
 * Scoring Description: (my rules)
 * same as above except
 * superjets mode award 2 million each
 * successive modes award more
 *
 * estimate of average superjets mode score: 20 million to 80 million
 * estimate of average jets score: 2.5 million
 *
 */
//this is an old note
/*this is not needed ---> ALLSET_SECTION (jets, __common__) */
//this file is currently being compiled into the common page since we have ran out of
//room on the other 5 pages.  check common/makefile and platform/generic.md


/* CALLSET_SECTION (jets, __machine__) */



#include <freewpc.h>
#include "dm/global_constants.h"


//constants
#define JETS_EASY_GOAL  25
#define JETS_HARD_GOAL  50
#define JETS_GOAL_STEP  15
#define JETS_GOAL_MAX  150

//local variables
U8 			jet_goal;
U8 			mode_jet_shots_made;
U8			jets_modes_achieved;
__boolean 	jets_inBall_search;
score_t 	jets_temp_score;
__local__ U8 			jet_shots_made;//external ref to eject.c

//external variables

//internally called function prototypes  --external found at protos.h
void jet_flasher(void);
void jets_effect_deff(void);
void jet_goal_award(void);
void player_jet_goal_reset(void);


/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
void player_jet_goal_reset  (void) {
	mode_jet_shots_made = 0;
	jet_shots_made = 0;
	jets_modes_achieved = 0;
	jet_goal = JETS_EASY_GOAL;
	jets_inBall_search = FALSE;

#ifdef CONFIG_DIFFICULTY_LEVEL
	jet_goal = system_config.jets_goal;
#endif
}//end of function

CALLSET_ENTRY (jets, start_player) 	{  player_jet_goal_reset (); }
CALLSET_ENTRY (jets, ball_search) { jets_inBall_search = TRUE; }
CALLSET_ENTRY (jets, ball_search_end, end_ball, start_ball) { jets_inBall_search = FALSE; }


/****************************************************************************
 *
 * body
 *
 ***************************************************************************/
void jet_goal_award (void) {
	mode_jet_shots_made = 0;
	switch (++jets_modes_achieved) {  //score higher if mode done more than once
		case 0: 	break; //never entered mode
		case 1:  score (JETS_GOAL_SCORE1);  break;
		case 2:  score (JETS_GOAL_SCORE2);  break;
		case 3:  score (JETS_GOAL_SCORE3);  break;
		case 4:	 score (JETS_GOAL_SCORE4);  break;
		default: score (JETS_GOAL_SCORE5);  break;
		}//end of switch
	sound_start (ST_SAMPLE, EXPLOSION, SL_2S, PRI_GAME_QUICK2);
	deff_start (DEFF_JETS_COMPLETED_EFFECT);
	if (jet_goal < JETS_GOAL_MAX)  jet_goal += JETS_GOAL_STEP;
	//light access claw
	increment_access_claw_light_on();//at inlanes.c
}//END OF FUNCTION



CALLSET_ENTRY (jets, sw_jet) {
	if (in_game && !in_tilt && !jets_inBall_search) {
			if (is_prison_break_running () ) { prison_break_made(); }
			else if (!is_sjets_running () ) {//not in super jets mode
				++jet_shots_made;
				++mode_jet_shots_made;
				score(JETS_HIT_SCORE);
				if (mode_jet_shots_made >= jet_goal)  jet_goal_award ();//sound played in call
				else deff_start (DEFF_JETS_EFFECT);//under /kernel/deff.c
				}//end of not in superjets mode
			sound_start (ST_EFFECT, MACHINE3, SL_1S, PRI_GAME_QUICK2);
			flasher_pulse (FLASH_JETS_FLASHER);
	}
}//end of function




/****************************************************************************
 *
 * DMD display effects
 *
 ****************************************************************************/
void jets_effect_deff(void) {
	if (DM_IN_DMD_TEST) {
		jet_shots_made += 4;
		jet_goal = 20;
		jets_modes_achieved++;
	}
	score_zero (jets_temp_score);						//zero out temp score

	dmd_alloc_pair ();
	dmd_map_overlay ();
	dmd_clean_page_low ();
		if (jets_modes_achieved % 2 == 0) { //DISPLAY THIS ON EVEN NUMBERED JETS MODES
			switch (jets_modes_achieved) {  //score higher if mode done more than once
				case 0:  score_add (jets_temp_score, score_table[JETS_GOAL_SCORE1]); break;
				case 1:  score_add (jets_temp_score, score_table[JETS_GOAL_SCORE2]); break;
				case 2:  score_add (jets_temp_score, score_table[JETS_GOAL_SCORE3]); break;
				case 3:  score_add (jets_temp_score, score_table[JETS_GOAL_SCORE4]); break;
				default: score_add (jets_temp_score, score_table[JETS_GOAL_SCORE5]); break;
			}//end of switch
			psprintf ("1 JET", "%d JETS", mode_jet_shots_made);
			font_render_string_center (&font_term6, DMD_MIDDLE_X, DMD_MED_CY_1, sprintf_buffer);
			sprintf ("%d FOR BONUS", jet_goal-mode_jet_shots_made);
			font_render_string_center (&font_fixed6, DMD_MIDDLE_X, DMD_MED_CY_2, sprintf_buffer);
			sprintf_score (jets_temp_score);
			font_render_string_center (&font_fixed6, DMD_MIDDLE_X, DMD_MED_CY_BOTTOM_LINE, sprintf_buffer);
		}//end of if
		else { // DISPLAY THIS ON ODD NUMBERED JETS MODES
			score_add (jets_temp_score, score_table[SC_100K]);
			score_mul (jets_temp_score, jet_shots_made);		//multiply 100K by jet count
			score_add (jets_temp_score, score_table[EJECT_SCORE]);			//add in normal retina scan score
			font_render_string_center (&font_fixed6, DMD_MIDDLE_X - 15, DMD_MED_CY_1, "JETS");
			font_render_string_center (&font_var5, DMD_MIDDLE_X + 29, DMD_MED_CY_1, "INCREASE");
			font_render_string_center (&font_fixed6, DMD_MIDDLE_X, DMD_MED_CY_2 + 1, "RETINA SCAN");
			sprintf_score (jets_temp_score);
			font_render_string_center (&font_term6, DMD_MIDDLE_X, DMD_MED_CY_BOTTOM_LINE, sprintf_buffer);
		}//end of else
	dmd_text_outline ();
	dmd_alloc_pair ();
	frame_draw (IMG_JETS_MARIO_0); //BRIGHT
	dmd_overlay_outline ();
	dmd_show2 ();
	task_sleep (TIME_300MS);


	dmd_alloc_pair ();
	dmd_map_overlay ();
	dmd_clean_page_low ();
		if (jets_modes_achieved % 2 == 0) { //DISPLAY THIS ON EVEN NUMBERED JETS MODES
			switch (jets_modes_achieved) {  //score higher if mode done more than once
				case 0:  score_add (jets_temp_score, score_table[JETS_GOAL_SCORE1]); break;
				case 1:  score_add (jets_temp_score, score_table[JETS_GOAL_SCORE2]); break;
				case 2:  score_add (jets_temp_score, score_table[JETS_GOAL_SCORE3]); break;
				case 3:  score_add (jets_temp_score, score_table[JETS_GOAL_SCORE4]); break;
				default: score_add (jets_temp_score, score_table[JETS_GOAL_SCORE5]); break;
			}//end of switch
			psprintf ("1 JET", "%d JETS", mode_jet_shots_made);
			font_render_string_center (&font_term6, DMD_MIDDLE_X, DMD_MED_CY_1, sprintf_buffer);
			sprintf ("%d FOR BONUS", jet_goal-mode_jet_shots_made);
			font_render_string_center (&font_fixed6, DMD_MIDDLE_X, DMD_MED_CY_2, sprintf_buffer);
			sprintf_score (jets_temp_score);
			font_render_string_center (&font_fixed6, DMD_MIDDLE_X, DMD_MED_CY_BOTTOM_LINE, sprintf_buffer);
		}//end of if
		else { // DISPLAY THIS ON ODD NUMBERED JETS MODES
			score_add (jets_temp_score, score_table[SC_100K]);
			score_mul (jets_temp_score, jet_shots_made);		//multiply 100K by jet count
			score_add (jets_temp_score, score_table[EJECT_SCORE]);			//add in normal retina scan score
			font_render_string_center (&font_fixed6, DMD_MIDDLE_X - 15, DMD_MED_CY_1, "JETS");
			font_render_string_center (&font_var5, DMD_MIDDLE_X + 29, DMD_MED_CY_1, "INCREASE");
			font_render_string_center (&font_fixed6, DMD_MIDDLE_X, DMD_MED_CY_2 + 1, "RETINA SCAN");
			sprintf_score (jets_temp_score);
			font_render_string_center (&font_term6, DMD_MIDDLE_X, DMD_MED_CY_BOTTOM_LINE, sprintf_buffer);
		}//end of else
	dmd_text_outline ();
	dmd_alloc_pair ();
	frame_draw (IMG_JETS_MARIO_1); //DULL
	dmd_overlay_outline ();
	dmd_show2 ();
	task_sleep (TIME_500MS);
	deff_exit ();
}//end of jets_effect_deff






void jets_completed_effect_deff(void) {
	U16 fno;
	score_zero (jets_temp_score);						//zero out temp score
	switch (jets_modes_achieved) {  //score higher if mode done more than once
		case 1:  score_add (jets_temp_score, score_table[JETS_GOAL_SCORE1]); break;
		case 2:  score_add (jets_temp_score, score_table[JETS_GOAL_SCORE2]); break;
		case 3:  score_add (jets_temp_score, score_table[JETS_GOAL_SCORE3]); break;
		case 4:  score_add (jets_temp_score, score_table[JETS_GOAL_SCORE4]); break;
		default: score_add (jets_temp_score, score_table[JETS_GOAL_SCORE5]); break;
	}//end of switch

	for (fno = IMG_JETS_COMP_MARIO_START; fno <= IMG_JETS_COMP_MARIO_END; fno += 2) {
		dmd_alloc_pair ();
		frame_draw(fno);
		dmd_show2 ();
		task_sleep (TIME_100MS);
	}//end of inner loop

	dmd_alloc_pair_clean ();// Clean both pages
	dmd_map_overlay ();
	dmd_clean_page_low ();
	font_render_string_center (&font_fixed6, DMD_MIDDLE_X, DMD_MED_CY_1, "JETS");
	font_render_string_center (&font_term6, DMD_MIDDLE_X, DMD_MED_CY_2, "COMPLETED");
	sprintf_score (jets_temp_score);
	font_render_string_center (&font_fixed6, DMD_MIDDLE_X, DMD_MED_CY_BOTTOM_LINE, sprintf_buffer);
	dmd_text_outline ();
	dmd_alloc_pair ();
	frame_draw(IMG_JETS_COMP_MARIO_END);
	dmd_overlay_outline ();
	dmd_show2 ();
	task_sleep (TIME_2S);
	deff_exit ();
}//end of mode_effect_deff


