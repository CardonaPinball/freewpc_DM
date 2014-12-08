/*
 * demolition man
 * special_shots.c
 *
 * written by James Cardona
 *
 *
 */
/* CALLSET_SECTION (special_shots, __machine3__) */

#include <freewpc.h>
#include "dm/global_constants.h"


//local variables


CALLSET_ENTRY (special_shots, start_player) {
	flag_off (FLAG_LASER_SHOT_ENABLED);
}//end of function






void laser_shot_made(void) {
	flag_off (FLAG_LASER_SHOT_ENABLED);
	score (LASER_SHOT_SCORE);
	deff_start (DEFF_LASER_SHOT);
}//end of function




void laser_shot_sounds_task(void) {
	sound_start (ST_EFFECT, MACHINE14_SHORT, SL_1S, PRI_GAME_QUICK2);
	task_sleep (TIME_100MS);
	sound_start (ST_EFFECT, MACHINE14_SHORT, SL_1S, PRI_GAME_QUICK2);
	task_sleep (TIME_100MS);
	sound_start (ST_EFFECT, MACHINE14_SHORT, SL_1S, PRI_GAME_QUICK2);
	task_sleep (TIME_100MS);
	sound_start (ST_EFFECT, MACHINE14_SHORT, SL_1S, PRI_GAME_QUICK2);
	task_sleep (TIME_200MS);
	sound_start (ST_EFFECT, MACHINE14_SHORT, SL_1S, PRI_GAME_QUICK2);
	task_sleep (TIME_200MS);
	sound_start (ST_EFFECT, MACHINE14_LONG, SL_2S, PRI_GAME_QUICK2);
	task_sleep (TIME_500MS);
	sound_start (ST_SPEECH, SPCH_LOVE_THIS_GUY, SL_2S, PRI_GAME_QUICK2);
	task_exit();
}//end of mode_effect_deff





void laser_shot_deff(void) {
	U16 fno;
	dmd_alloc_pair_clean ();// Clean both pages
	task_create_gid1 (GID_laser_shot_SOUND, laser_shot_sounds_task);

	for (fno = IMG_LASER_SHOT1; fno <= IMG_LASER_SHOT6; fno += 2) {
				dmd_alloc_pair ();
				frame_draw(fno);
				dmd_show2 ();
				task_sleep (TIME_100MS);
	}//end of for loop

	for (fno = IMG_LASER_SHOT4; fno <= IMG_LASER_SHOT6; fno += 2) {
				dmd_alloc_pair ();
				frame_draw(fno);
				dmd_show2 ();
				task_sleep (TIME_100MS);
	}//end of for loop

	dmd_map_overlay ();
	dmd_clean_page_low ();
	font_render_string_center (&font_fixed6, DMD_MIDDLE_X, DMD_BIG_CY_Top, "LASER");
	font_render_string_center (&font_fixed6, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "SHOT");
		dmd_text_outline ();
		dmd_alloc_pair ();
		frame_draw(IMG_LASER_SHOT6);
		dmd_overlay_outline ();
		dmd_show2 ();

		task_sleep (TIME_500MS);
	deff_exit ();
}//end of deff



