
/* CALLSET_SECTION (extra_ball, __machine3__) */

#include <freewpc.h>
#include "dm/global_constants.h"
#include "search.h"
#include <eb.h>


U8 	extraball_SoundCounter;

void extraball_reminder_task (void) {
	for (;;) {
		if ( (extraball_SoundCounter++ % 2) == 0 ) 	sound_start (ST_SPEECH, SPCH_GET_THE_EXTRABALL, SL_4S, PRI_GAME_QUICK5);
		else										sound_start (ST_SPEECH, SPCH_NEED_EXTRABALL, SL_4S, PRI_GAME_QUICK5);
		task_sleep_sec(14);
	}//end of loop
	task_exit();
}//end of function



void start_extraball(void) {
	if (in_game) { //do this since this can be called from computer award test in test menu
		flag_on(FLAG_IS_EXTRABALL_LIT);
		extraball_light_on ();
		task_create_gid1 (GID_EXTRA_BALL_REMINDER, extraball_reminder_task);
	}//end of if
}//end of function


//called from top popper when eb awarded
void end_extraball(void) {
	flag_off(FLAG_IS_EXTRABALL_LIT);
	extraball_light_off ();
	task_kill_gid(GID_EXTRA_BALL_REMINDER);
}//end of function



CALLSET_ENTRY (extraball, end_ball, start_player) {
	task_kill_gid(GID_EXTRA_BALL_REMINDER);
}//end of function


void score_extraball(void) {
	ball_search_monitor_stop ();
	flag_off(FLAG_IS_EXTRABALL_LIT);
	extraball_light_off ();
	task_kill_gid(GID_EXTRA_BALL_REMINDER);
	increment_extra_balls();
	leff_start (LEFF_EXTRABALL);
	deff_start (DEFF_EXTRA_BALL_EFFECT);
	ball_search_monitor_start ();
}//end of function




/****************************************************************************
 *
 * lighting effects
 *
 ****************************************************************************/
void extraball_leff(void) {
	gi_leff_disable (PINIO_GI_STRINGS); //turn off gi
	leff_start(LEFF_BOT2TOP);
	leff_start(LEFF_TOP2BOT);
	gi_leff_enable (PINIO_GI_STRINGS); //turn on gi
	task_sleep_sec (TIME_1S);
	leff_exit();
}//end of function








/****************************************************************************
 *
 * display effects
 *
 ****************************************************************************/
void extra_ball_effect_deff(void) {
	U8 eb_rnd_sound;
	U16 fno;
	dmd_alloc_pair_clean ();// Clean both pages

	if (system_config.swear_sounds == YES) {
		//this doubles the chance that a swear would occur
		eb_rnd_sound = random_scaled(5);
		if (eb_rnd_sound == 4) eb_rnd_sound = 3;
	}
	else if (system_config.extra_sounds == YES) 	eb_rnd_sound = random_scaled(3);
	else 											eb_rnd_sound = random_scaled(2);

	sound_start (ST_EFFECT, EXTRA_BALL_SOUND, SL_2S, SP_NORMAL);

	for (fno = IMG_FREEZER1_START; fno <= IMG_FREEZER1_END; fno += 2) {
				dmd_alloc_pair ();
				frame_draw(fno);
				dmd_show2 ();
				task_sleep (TIME_66MS);
	}//end of for loop

	for (fno = IMG_FREEZER2_START; fno <= IMG_FREEZER2_END; fno += 2) {
				dmd_alloc_pair ();
				frame_draw(fno);
				dmd_show2 ();
				task_sleep (TIME_66MS);
	}//end of for loop

	switch (eb_rnd_sound) {
		case 0: 	sound_start (ST_SPEECH, SPCH_EXTRABALL_WES, SL_4S, 3); break;
		case 1: 	sound_start (ST_SPEECH, SPCH_EXTRABALL_SLY, SL_4S, PRI_GAME_QUICK3); break;
		case 2: 	sound_start (ST_SPEECH, SPCH_LOVE_THOSE_EXTRA_BALLS_GIRL, SL_4S, PRI_GAME_QUICK3); break;
		case 3: 	sound_start (ST_SPEECH, SPCH_VLGR_REALLY_LICKED_AS_SNDRA, SL_4S, PRI_GAME_QUICK3); break;
}//end of switch

	for (fno = IMG_FREEZER3_START; fno <= IMG_FREEZER3_END; fno += 2) {
					dmd_map_overlay ();
					dmd_clean_page_low ();
						font_render_string_center (&font_halobold12, DMD_MIDDLE_X - 15, DMD_BIG_CY_Top, "EXTRA");
						font_render_string_center (&font_halobold12, DMD_MIDDLE_X - 15, DMD_BIG_CY_Bot, "BALL");
						dmd_text_outline ();
						dmd_alloc_pair ();
						frame_draw(fno);
						dmd_overlay_outline ();
						dmd_show2 ();
						task_sleep (TIME_66MS);
			}//end of for loop

	deff_exit ();
}//end of mode_effect_deff
