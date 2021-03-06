/*
 * demolition man
 * huxley.c
 *
 * written by James Cardona
 *
 * Description:
 * wizrd mode started by completing at least 4 non-claw modes
 *
 * Scoring Description: (my rules)
 * scores 1 million per shot - everything scores
 *
 */
/* CALLSET_SECTION (huxley, __machine5__) */

#include <freewpc.h>
#include "dm/global_constants.h"
#include <diverter.h> //autogenerated by divhold.ct
#include "search.h"
#include "ballsave.h"
#include <coin.h>


//constants
#define	HUXLEY_EASY_GOAL  3


//constants
const U8 	huxley_TotalNumOfSounds = 8; //num between 0 and N-1 == N total
const sound_code_t huxley_SoundsArray[] = { SPCH_WEEAHOO, 				SPCH_I_GOT_IT,							SPCH_WOAH,
											SPCH_WHAT_ARE_YOU_DOING, 	SPCH_DONT_YOU_WANT_SOMETHING_HAPPEN,	SPCH_COMPETITION,
											SPCH_EXCUSE_ME,				SPCH_SOME_ACTION};


//local variables
U8 			huxley_mode_shots_made;
U8			huxley_mode_timer;
score_t 	huxley_mode_score;
score_t 	huxley_mode_last_score;
score_t 	huxley_mode_next_score;
score_t 	huxley_mode_score_total_score;
__local__ U8 			huxley_counter;
U8			huxley_goal;
bool		huxley_suspend;


//external variables


//internally called function prototypes  --external found at protos.h
void huxley_mode_init (void);
void huxley_mode_expire (void);
void huxley_mode_exit (void);
void play_huxley_sounds(void);

/****************************************************************************
 * mode definition structure
 ***************************************************************************/
struct timed_mode_ops huxley_mode = {
	DEFAULT_MODE,
	.init = huxley_mode_init,
	.exit = huxley_mode_exit,
	.gid = GID_HUXLEY_MODE_RUNNING,
	.music = MUS_MB_B,//MUS_MB_A,
//	.deff_starting = DEFF_HUXLEY_START_EFFECT, //- started at init
	.deff_running = DEFF_HUXLEY_EFFECT,
//	.deff_ending = DEFF_HUXLEY_END_EFFECT,
	.prio = PRI_GAME_MODE3,
	.init_timer = 63,
	.timer = &huxley_mode_timer,
	.grace_timer = 2, //default is 2
	.pause = suspend_huxley,
};


/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
CALLSET_ENTRY (huxley, start_player) 	{
	if (DM_IN_CAB_TEST) huxley_goal = 1;
	else		 huxley_goal = HUXLEY_EASY_GOAL;

	huxley_counter = 0;
	huxley_mode_shots_made = 0;
	score_zero(huxley_mode_score_total_score);
	task_kill_gid(GID_HUXLEY_REMINDER);

#ifdef CONFIG_DIFFICULTY_LEVEL
	huxley_goal = system_config.num2huxley;
#endif

	if (huxley_goal == 0) flag_on(FLAG_IS_HUXLEY_ENABLED);
	else flag_off(FLAG_IS_HUXLEY_ENABLED);

	//for testing
//	huxley_increment();
	huxley_suspend = FALSE;
}//end of function




void huxley_mode_init (void) {
	huxley_suspend = FALSE;
	ball_search_monitor_stop ();
	flag_off (FLAG_IS_HUXLEY_ENABLED);
	task_kill_gid(GID_HUXLEY_REMINDER);
	huxley_mode_shots_made = 0;

	score_zero(huxley_mode_score);
	score_zero(huxley_mode_last_score);
	score_zero(huxley_mode_next_score);

	score(HUXLEY_START_SCORE);
	score_add(huxley_mode_score, score_table[HUXLEY_START_SCORE]);
	score_add(huxley_mode_next_score, score_table[HUXLEY_MODE_HIT_SCORE]);

	huxley_counter = 0; //reset for next time

	deff_start_sync (DEFF_HUXLEY_START_EFFECT);//under /kernel/deff.c
	ballsave_add_time (system_config.mode_ballsave);

	leff_start(LEFF_EYEBALL);

	sol_request_async (SOL_EJECT); //request to fire the eject sol
	task_sleep (TIME_300MS);
	set_normal_eject_killed_status (FALSE);
	ball_search_monitor_start ();

	set_dm_mode(HUXLEY_COMPLETED); //for BONUS
}//end of function



void huxley_mode_expire (void) {
	diverter_check();
}//end of function


void huxley_mode_exit (void) { huxley_mode_expire();}


/****************************************************************************
 * external event listeners
 ****************************************************************************/
CALLSET_ENTRY (huxley, music_refresh)  	{ if (in_game) timed_mode_music_refresh (&huxley_mode); }
CALLSET_ENTRY (huxley, display_update) 	{ timed_mode_display_update (&huxley_mode); }


CALLSET_ENTRY (huxley, end_ball, tilt) 	{
	if (timed_mode_running_p(&huxley_mode) ) timed_mode_end (&huxley_mode);
	task_kill_gid (GID_HUXLEY_REMINDER);
}



/****************************************************************************
 *
 * body
 *
 ***************************************************************************/
U8 get_huxley_timer (void) {
	if (timed_mode_running_p (&huxley_mode) ) 	return timed_mode_get_timer (&huxley_mode);
	else 										return (0);
}//end of function



U8 get_huxley_timer_total_time (void) {
	return timed_mode_get_timer_total (&huxley_mode);
}//end of function



bool is_huxley_running (void) {
	return timed_mode_running_p (&huxley_mode);
}//end of function


//this is used for when a video mode is started while mode is running
bool suspend_huxley (void) {
	if (huxley_suspend) return TRUE;
	else return FALSE;
}//end of function


void pause_huxley (bool state) {
	if (state) huxley_suspend = TRUE;
	else {
		//unpause and add a few seconds for lost delay time
		huxley_suspend = FALSE;
		timed_mode_add (&huxley_mode, 3);
	}
}//end of function

void add_time_to_huxley_mode (U8 time){
	timed_mode_add (&huxley_mode, time);
}//end of function




void huxley_increment (void) {
	if (++huxley_counter >= huxley_goal) {
		flag_on(FLAG_IS_HUXLEY_ENABLED);
	}
}//end of function



void huxley_increment_all (void) {
		flag_on(FLAG_IS_HUXLEY_ENABLED);
}//end of function



//Once huxley mode is enabled it is started by a huxley shot (backwards to retina scan)
void huxley_made(void){
	play_huxley_sounds();
	if (flag_test(FLAG_IS_HUXLEY_ENABLED) )		timed_mode_begin (&huxley_mode);//start mode
	else {
		score (HUXLEY_SCORE);

//		deff_start_sync (DEFF_HUXLEY_INFO_EFFECT);
		deff_start (DEFF_HUXLEY_INFO_EFFECT);
		task_sleep (TIME_300MS);

		sol_request_async (SOL_EJECT); //request to fire the eject sol
		task_sleep (TIME_300MS);
		set_normal_eject_killed_status (FALSE);
	}//end of else
}//end of function



 //shot made during huxley mode
void huxley_mode_shot_made(void) {
	deff_start (DEFF_HUXLEY_HIT_EFFECT);//under /kernel/deff.c
	++huxley_mode_shots_made;
	score (HUXLEY_MODE_HIT_SCORE);
	score_add (huxley_mode_score, score_table[HUXLEY_MODE_HIT_SCORE]);
	score_add (huxley_mode_score_total_score, score_table[HUXLEY_MODE_HIT_SCORE]);
}//end of function



/****************************************************************************
 *
 * sound effects
 *
 ****************************************************************************/
void play_huxley_sounds(void){
	U8 huxley_SoundCounter;
	huxley_SoundCounter = random_scaled(huxley_TotalNumOfSounds);//from kernal/random.c
	sound_start (ST_SPEECH, huxley_SoundsArray[huxley_SoundCounter], SL_4S, PRI_GAME_QUICK3);
}//end of function





/****************************************************************************
 *
 * DMD display
 *
 ****************************************************************************/
void huxley_animation_display_effect (U16 start_frame, U16 end_frame){
	U16 fno;
	for (fno = start_frame; fno <= end_frame; fno += 2) {
		dmd_alloc_pair ();
		frame_draw(fno);
		dmd_show2 ();
		task_sleep (TIME_100MS);
	}//end of inner loop
}




void huxley_frame_bitfade_fast (U16 frame){
	dmd_sched_transition (&trans_bitfade_fast);
	dmd_alloc_pair ();
	frame_draw(frame);
	dmd_show2 ();
	task_sleep (TIME_100MS);
}




void huxley_frame_with_words_display_fipps_effect (U16 frame, U8 x, U8 y, char *words){
	dmd_alloc_pair_clean ();// Clean both pages
	dmd_map_overlay ();
	dmd_clean_page_low ();
		font_render_string_center (&font_halobold12, x, y, words);
	dmd_text_outline ();
	dmd_alloc_pair ();
	frame_draw(frame);
	dmd_overlay_outline ();
	dmd_show2 ();
	task_sleep (TIME_100MS);
}




void huxley_start_effect_deff(void) {
	dmd_alloc_pair_clean ();
	sound_start (ST_SAMPLE, EXPLOSION, SL_2S, PRI_GAME_QUICK3);
		font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "LENINA");
		font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "HUXLEY");
	dmd_show_low();
	task_sleep (TIME_1S);

	U8 i;
	for (i = 0; i < 5; i++) {
			if (i == 0) sound_start (ST_SPEECH, SPCH_SOME_ACTION, SL_4S, PRI_GAME_QUICK3);
			if (i == 1) sound_start (ST_SPEECH, SPCH_WEEAHOO, SL_4S, PRI_GAME_QUICK3);
			if (i == 2)	sound_start (ST_SPEECH, SPCH_EXCUSE_ME, SL_4S, PRI_GAME_QUICK3);
			if (i == 3) sound_start (ST_SPEECH, SPCH_WHAT_ARE_YOU_DOING, SL_4S, PRI_GAME_QUICK3);
			if (i == 4) sound_start (ST_SPEECH, SPCH_I_GOT_IT, SL_4S, PRI_GAME_QUICK3);
			dmd_sched_transition (&trans_scroll_down);
			dmd_alloc_pair_clean ();
			if (i == 0) huxley_animation_display_effect (IMG_HUXLEY_A_START, IMG_HUXLEY_A_END);
			if (i == 1) huxley_animation_display_effect (IMG_HUXLEY_B1_START, IMG_HUXLEY_B1_END);
			if (i == 2) huxley_animation_display_effect (IMG_HUXLEY_B2_START, IMG_HUXLEY_B2_END);
			if (i == 3) huxley_animation_display_effect (IMG_HUXLEY_D_START, IMG_HUXLEY_D_END);
			if (i == 4) huxley_animation_display_effect (IMG_HUXLEY_A_START, IMG_HUXLEY_A_END);
			sound_start (ST_SAMPLE, EXPLOSION, SL_2S, PRI_GAME_QUICK3);
			dmd_sched_transition (&trans_scroll_down);
			dmd_alloc_pair_clean ();
			if (i == 0) font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "STANDUPS");
			if (i == 1) font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "REBOUNDS");
			if (i == 2) font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "ORBITS");
			if (i == 3) font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "RAMPS");
			if (i == 4) font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "SUBWAY");
			font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "1 MILLION");
			dmd_show_low();
			task_sleep (TIME_1S);
	}
	deff_exit ();
}//end of mode_effect_deff






void huxley_hit_sounds_task(void) {
	U8 i;
	for (i = 0; i < 3; i++) {
		sound_send (EXPLOSION1_SHORT);
		task_sleep (TIME_100MS);
	}
	sound_send (EXPLOSION1_MED);
	task_sleep (TIME_100MS);
	for (i = 0; i < 3; i++) {
		sound_send (EXPLOSION1_LONG);
		task_sleep (TIME_500MS);
	}
	play_huxley_sounds();

	task_exit();
}//end of mode_effect_deff






U8 			huxley_MessageCounter;
void huxley_hit_effect_deff(void) {
	if (DM_IN_DMD_TEST) {	if (++huxley_MessageCounter > 3) huxley_MessageCounter = 0; }
	else huxley_MessageCounter = random_scaled(4);

	dmd_clean_page_high ();//
	dmd_clean_page_low ();//

	task_create_gid1 (GID_HUXLEY_HIT_SOUND, huxley_hit_sounds_task);

	switch (huxley_MessageCounter) {
		default:
		case 0:
//			huxley_animation_display_effect (IMG_HUXLEY_A_START, IMG_HUXLEY_A_END);
			huxley_frame_with_words_display_fipps_effect (IMG_HUXLEY_A_END, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "1 MILLION");
			break;
		case 1:
//			huxley_animation_display_effect (IMG_HUXLEY_B1_START, IMG_HUXLEY_B1_END);
			huxley_frame_with_words_display_fipps_effect (IMG_HUXLEY_B1_END, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "HUXLEY");
			break;
		case 2:
//			huxley_animation_display_effect (IMG_HUXLEY_B2_START, IMG_HUXLEY_B2_END);
			huxley_frame_with_words_display_fipps_effect (IMG_HUXLEY_B2_END, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "1 MILLION");
			break;
		case 3:
//			huxley_animation_display_effect (IMG_HUXLEY_D_START, IMG_HUXLEY_D_END);
			huxley_frame_with_words_display_fipps_effect (IMG_HUXLEY_D_END, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "HUXLEY");
			break;
		}//end of switch
	task_sleep (TIME_500MS);
	deff_exit ();
}//end of mode_effect_deff







void huxley_effect_deff(void) {
	for (;;) {
		dmd_clean_page_low ();
		//right side status display
		ll_score_draw_ball ();

		//left side display
				sprintf_score(current_score);
				font_render_string_right (&font_var5, 98, 26, sprintf_buffer);
				font_render_string_center (&font_halobold12, 50, 5, "HUXLEY");
				if (ballsave_test_active()) {
					sprintf ("%d BALL SAVE", ballsave_get_timer());
					font_render_string_right (&font_var5, 88, 27, sprintf_buffer);
				}
				else
					font_render_string_right (&font_term6, 98, 14, "1 MILLION");

				sprintf ("%d", huxley_mode_timer);
				font_render_string_left (&font_halobold12, 1, 14, sprintf_buffer);
				dmd_show_low();
				task_sleep (TIME_1S);
	}//END OF ENDLESS LOOP
	deff_exit ();
}//end of mode_effect_deff








void huxley_info_effect_deff(void) {
	U16 fno;
	dmd_alloc_pair_clean ();
	for (fno = IMG_HUXLEY_E_START; fno <= IMG_HUXLEY_E_END; fno += 2) {
				dmd_alloc_pair ();
				frame_draw(fno);
				dmd_show2 ();
				task_sleep (TIME_100MS);
	}//end of for loop

			dmd_map_overlay ();
			dmd_clean_page_low ();
				font_render_string_center (&font_halobold12, DMD_MIDDLE_X - 20, DMD_BIG_CY_Top, "HUXLEY");
				if (flag_test (FLAG_IS_HUXLEY_ENABLED) )
					font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "READY");
				else
					font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "1 MILLION");
				dmd_text_outline ();
				dmd_alloc_pair ();
				frame_draw(IMG_HUXLEY_E_END);
				dmd_overlay_outline ();
				dmd_show2 ();
				task_sleep (TIME_1S);
	deff_exit ();
}//end of mode_effect_deff
