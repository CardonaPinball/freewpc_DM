/*
 * demolition man
 * skillshot.c
 *
 * written by James Cardona
 *
 *
 *
 */

#include <freewpc.h>
#include "dm/global_constants.h"

//local variables
__boolean	skill_shot_made;
__boolean	is_skill_shot_enabled;
__boolean	is_skill_shot_ball_start;
score_t 	skillshot_score;
U8			type_skillshot_made;

//internally called function prototypes  --external found at protos.h
void start_skillshot_timer_task (void);
void skillshot_sounds_task (void);


/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
CALLSET_ENTRY (skillshot, start_ball) {
	is_skill_shot_enabled = FALSE;
	is_skill_shot_ball_start = TRUE; //PREVENT MULTIFIRES FROM MESSING STUFF UP
	skill_shot_made = FALSE;
	score_zero (skillshot_score);
}//end of function



CALLSET_ENTRY (skillshot, end_game, end_ball) {
	is_skill_shot_enabled = FALSE;
	is_skill_shot_ball_start = FALSE;
	task_kill_gid (GID_SKILLSHOT_TIMER);
}//end of function



void start_skillshot_timer_task (void) {
	is_skill_shot_enabled = TRUE;
	task_sleep_sec(4);
	task_sleep(TIME_500MS);
	is_skill_shot_enabled = FALSE;
	task_exit();
}//end of function



//switch to launch ball
CALLSET_ENTRY (skillshot, sw_launch_button) {
	if ( in_game
		&& 	!in_tilt
		&&	!valid_playfield
		&&	is_skill_shot_ball_start) {
				is_skill_shot_ball_start = FALSE;
				task_create_gid1(GID_SKILLSHOT_TIMER, start_skillshot_timer_task);
	}
}//end of function




/****************************************************************************
 * body
 ****************************************************************************/
__boolean get_skill_shot_enabled (void) {
	if (is_skill_shot_enabled) 	return TRUE;
	else 						return FALSE;
}//end of function




void award_skill_shot (U8 type_skill_shot_made) {
	is_skill_shot_enabled = FALSE;
	task_kill_gid(GID_SKILLSHOT_TIMER);
	type_skillshot_made = type_skill_shot_made;

	deff_start (DEFF_SKILLSHOT);
	leff_start (LEFF_SKILLSHOT);

	switch (type_skill_shot_made) {
		case 1:  //underground shot
			score (SKILLSHOT_UGRND_SCORE);
			score_add (skillshot_score, score_table[SKILLSHOT_UGRND_SCORE]);
			break;
		case 2: //side ramp shot
			score (SKILLSHOT_SRAMP_SCORE);
			score_add (skillshot_score, score_table[SKILLSHOT_SRAMP_SCORE]);
			break;
		case 3: //side ramp shot
			score (SKILLSHOT_LRAMP_SCORE);
			score_add (skillshot_score, score_table[SKILLSHOT_LRAMP_SCORE]);
	}//end of switch
}//end of function


/****************************************************************************
 *
 * sound effects
 *
 ****************************************************************************/
void skillshot_sounds_task (void) {
	sound_start (ST_ANY, MACHINE11, SL_3S, PRI_GAME_QUICK6);
	task_sleep (TIME_500MS);
	sound_start (ST_SPEECH, SPCH_SKILLSHOT, SL_3S, PRI_GAME_QUICK6);
	task_sleep (TIME_1S);
	sound_start (ST_ANY, MACHINE11, SL_3S, PRI_GAME_QUICK6);
	task_sleep (TIME_500MS);
	sound_start (ST_ANY, MACHINE11, SL_3S, PRI_GAME_QUICK6);
	task_exit();
}//end of function



/****************************************************************************
 *
 * DISPLAY EFFECTS
 *
 ****************************************************************************/
void skillshot_deff(void) {
	U16 fno;
	U8 skillshot_Counter;
	skillshot_Counter = random_scaled(3);//from kernal/random.c

	dmd_alloc_pair_clean ();
	if (DM_IN_DMD_TEST) {	if (++type_skillshot_made > 3) type_skillshot_made = 1; }

	task_create_gid1(GID_SKILLSHOT_SOUNDS, skillshot_sounds_task);
	if (skillshot_Counter) {
			for (fno = IMG_PLUNGE_BALL_START; fno <= IMG_PLUNGE_BALL_END2; fno += 2) {
			dmd_alloc_pair ();
				frame_draw(fno);
				dmd_show2 ();
				task_sleep (TIME_100MS);
				if (fno == IMG_PLUNGE_BALL_FIRE) sound_start (ST_ANY, GUNSHOT, SL_200MS, PRI_GAME_QUICK7);
			}//end of loop

			for (fno = IMG_SKILL_SHOT_START; fno <= IMG_SKILL_SHOT_END; fno += 2) {
			dmd_alloc_pair ();
				frame_draw(fno);
				dmd_show2 ();
				task_sleep (TIME_100MS);
			}//end of loop
	}//end of 	if (skillshot_Counter)

	else { //skillshot_Counter == 0
			for (fno = IMG_FLYKICK_A_START; fno <= IMG_FLYKICK_A_END; fno += 2) {
			dmd_alloc_pair ();
				frame_draw(fno);
				dmd_show2 ();
				task_sleep (TIME_100MS);
			}//end of loop
	}//end of 	else

			dmd_map_overlay ();
			dmd_clean_page_low ();
				font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "SKILL SHOT");
				switch (type_skillshot_made) {
					case 1:  //underground shot
						font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "1 MILLION");
						break;
					case 2: //side ramp shot
						font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "3 MILLION");
						break;
					case 3: //side ramp shot
						font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "10 MILLION");
				}//end of switch
			dmd_text_outline ();
			dmd_alloc_pair ();
			if (skillshot_Counter) {
				frame_draw(IMG_SKILL_SHOT_END);
			}
			else {
				frame_draw(IMG_FLYKICK_A_END);
			}
			dmd_overlay_outline ();
			dmd_show2 ();
			task_sleep_sec (1);
			task_sleep (TIME_500MS);
	deff_exit ();
}//end of mode_effect_deff

