/* skillshot.c
 * written by James Cardona
 */
#include <freewpc.h>
#include "ngg/global_constants.h" 

//local variables
__boolean	skill_shot_made;
__boolean	is_skill_shot_enabled;
score_t 	skillshot_score;


//internally called function prototypes  --external found at protos.h
void start_skillshot_timer_task (void);
void skillshot_sounds_task (void);

/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
CALLSET_ENTRY (skillshot, start_ball) {
	is_skill_shot_enabled = TRUE;
	skill_shot_made = FALSE;
	score_zero (skillshot_score);
}//end of function


CALLSET_ENTRY (skillshot, end_game, end_ball) {
	is_skill_shot_enabled = FALSE;
	task_kill_gid (GID_SKILLSHOT_TIMER);
}//end of function


void start_skillshot_timer_task (void) {
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
		&&	is_skill_shot_enabled)
		task_create_gid1(GID_SKILLSHOT_TIMER, start_skillshot_timer_task);
}//end of function


__boolean get_skill_shot_enabled (void) {
	if (is_skill_shot_enabled) 	return TRUE;
	else 						return FALSE;
}//end of function


void award_skill_shot (void ) {
	is_skill_shot_enabled = FALSE;
	task_kill_gid(GID_SKILLSHOT_TIMER);
	type_skillshot_made = type_skill_shot_made;

	deff_start (DEFF_SKILLSHOT);
	leff_start (LEFF_SKILLSHOT);

	score (SKILLSHOT_SCORE);
	score_add (skillshot_score, score_table[SKILLSHOT_SCORE]);
}//end of function


CALLSET_ENTRY (skillshot, sw_top_skill_shot) {
	if ( in_game
		&& 	!in_tilt
		&&	is_skill_shot_enabled)
		award_skill_shot ();
}



CALLSET_ENTRY (skillshot, sw_middle_skill_shot) {
	if ( in_game
		&& 	!in_tilt
		&&	is_skill_shot_enabled)
		award_skill_shot ();
}


CALLSET_ENTRY (skillshot, sw_lower_skill_shot) {
	if ( in_game
		&& 	!in_tilt
		&&	is_skill_shot_enabled)
		award_skill_shot ();
}


/****************************************************************************
 *
 * sound effects
 *
 ****************************************************************************/
void skillshot_sounds_task (void) {
//	sound_start (ST_ANY, MACHINE11, SL_3S, PRI_GAME_QUICK6);
//	task_sleep (TIME_500MS);
//	sound_start (ST_SPEECH, SPCH_SKILLSHOT, SL_3S, PRI_GAME_QUICK6);
//	task_sleep (TIME_1S);
//	sound_start (ST_ANY, MACHINE11, SL_3S, PRI_GAME_QUICK6);
//	task_sleep (TIME_500MS);
//	sound_start (ST_ANY, MACHINE11, SL_3S, PRI_GAME_QUICK6);
	task_exit();
}//end of function



/****************************************************************************
 *
 * DISPLAY EFFECTS
 *
 ****************************************************************************/
void skillshot_deff(void) {
	dmd_alloc_pair_clean ();
	task_create_gid1(GID_SKILLSHOT_SOUNDS, skillshot_sounds_task);
	font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "SKILL SHOT");
	font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "1 MILLION");
	dmd_show)low ();
	task_sleep_sec (3);
	deff_exit ();
}//end of mode_effect_deff

