#include <freewpc.h>
#include <coin.h>
#include <highscore.h>
#include <replay.h>
#include "dm/global_constants.h"




//constants
const U8 	amode_flipper_sound_TotalNumOfSounds = 9; //num between 0 and N-1 == N total

															//huxley
const sound_code_t amode_flipper_sound_SoundsArray[] = { 	SPCH_WEEAHOO, 				SPCH_I_GOT_IT,		SPCH_WOAH,
															SPCH_WHAT_ARE_YOU_DOING, 	SPCH_EXCUSE_ME,
															//spartan
															SPCH_OHH_YEAH3, 			SPCH_STOP_THIS,		SPCH_LETS_GO1,
															SPCH_YEEAHHAA };


//local variables
U8 amode_page;
U8 amode_page_changed;
U8 amode_flipper_sound_counter;


//external variables


//internally called function prototypes  --external found at protos.h
void amode_page_change (S8 delta);




/****************************************************************************
 *
 * LIGHTS
 *
 ***************************************************************************/
void system_amode_leff (void) { for (;;) task_sleep_sec (1); }





/****************************************************************************
 *
 * SOUNDS
 *
 ***************************************************************************/
void amode_flipper_sound_debounce_timer (void) {
	task_sleep_sec (10);
	task_exit ();
}//end of function


//this is disabled because of the music
//clipping bug. in effect, if the music is not playing then the music server
//sends a code to the sound board to turn off sounds every so many millisecs
// unfortunately this also clips other sound calls so they only play for a little bit
//then are clipped.
void amode_flipper_sound (void) {
#ifdef MACHINE_AMODE_FLIPPER_SOUND_CODE
	if (!task_find_gid (GID_AMODE_FLIPPER_SOUND_DEBOUNCE)) {
		task_create_gid (GID_AMODE_FLIPPER_SOUND_DEBOUNCE, amode_flipper_sound_debounce_timer);
		if (++amode_flipper_sound_counter > amode_flipper_sound_TotalNumOfSounds) amode_flipper_sound_counter = 0;
		sound_start (ST_SPEECH, amode_flipper_sound_SoundsArray[amode_flipper_sound_counter], SL_4S, PRI_GAME_QUICK2);

//		sound_send (MACHINE_AMODE_FLIPPER_SOUND_CODE);
	}
#endif
}//end of function






/****************************************************************************
 *
 * DMD GRAPHICS
 *
 ***************************************************************************/
void amode_sleep_sec (U8 secs) {
	if (secs > 0) {
		amode_page_changed = 0;
		while (secs > 0) {
			task_sleep (TIME_250MS);
			if (amode_page_changed)
				return;
			task_sleep (TIME_250MS);
			if (amode_page_changed)
				return;
			task_sleep (TIME_250MS);
			if (amode_page_changed)
				return;
			task_sleep (TIME_250MS);
			if (amode_page_changed)
				return;
			secs--;
		}//end of while loop
	}//end of if
}//end of function






void amode_page_end (U8 secs) {
	amode_sleep_sec (secs);
	amode_page_change (1);
}//end of function






void amode_score_page (void) {
	dmd_alloc_low_clean ();
	scores_draw ();
	dmd_show_low ();

	// Hold the scores up for a while longer than usual in tournament mode.
	if (system_config.tournament_mode == YES)
		amode_page_end (20); //this was 120 - why so long?
	else
		amode_page_end (3);
}//end of function







void amode_logo_page (void) {
	U16 fno;
	amode_page_changed = 0;
	for (fno = IMG_FREEWPC_SMALL; fno <= IMG_FREEWPC; fno += 2) {
		dmd_alloc_pair ();
		frame_draw (fno);
		dmd_show2 ();
		if (amode_page_changed) fno = IMG_FREEWPC;
		else task_sleep (TIME_100MS);
	}

	if (amode_page_changed) amode_page_change (1);
	else {
		dmd_sched_transition (&trans_bitfade_slow);
		amode_page_end (1);
	}
}//end of function









void dm_amode_demolition_time_page (void) {
	dmd_clean_page_low ();
		font_render_string_center (&font_halobold12, 64, 7, "DEMOLITION");
		font_render_string_center (&font_halobold12, 64, 22, "TIME");
	dmd_show_low ();
	amode_page_end (4);
}//end of function






void dm_amode_show_huxley_info_page (void) {
	U16 fno;
	amode_page_changed = 0;
	for (fno = IMG_HUXLEY_B2_START; fno <= IMG_HUXLEY_B2_END; fno += 2) {
		dmd_alloc_pair ();
		frame_draw(fno);
		dmd_show2 ();
		if (amode_page_changed) fno = IMG_HUXLEY_B2_END;
		else task_sleep (TIME_100MS);
	}//end of inner loop

	if (!amode_page_changed) {
		dmd_sched_transition (&trans_scroll_down);
		dmd_clean_page_low ();
		font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, "START 4 NON-CLAW");
		font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_2, "MODES FOR");
			font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "HUXLEY");
		dmd_show_low();
		amode_page_end (3);
	}
	else amode_page_change (1);
}//end of function





void dm_amode_show_rollovers1_info_page (void) {
	U16 fno;
	amode_page_changed = 0;
	for (fno = IMG_CRYOCLAW_MARIO_START; fno <= IMG_CRYOCLAW_MARIO_END; fno += 2) {
		dmd_alloc_pair ();
		frame_draw(fno);
		dmd_show2 ();
		if (amode_page_changed) fno = IMG_CRYOCLAW_MARIO_END;
		else task_sleep (TIME_100MS);
	}//end of inner loop

	if (!amode_page_changed) {
		dmd_sched_transition (&trans_scroll_down);
		dmd_clean_page_low ();
		font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, "LIGHT ALL M T L");
		font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_2, "ROLLOVERS TO");
		font_render_string_center (&font_fixed6, DMD_MIDDLE_X, DMD_SMALL_CY_4, "LIGHT CLAW");
		dmd_show_low();
		amode_page_end (3);
	}
	else amode_page_change (1);
}//end of function




void dm_amode_show_john_spartan_animation_page (void) {
	U16 fno;
	amode_page_changed = 0;
	for (fno = IMG_FORTRESS_D1_START; fno <= IMG_FORTRESS_D1_END; fno += 2) {
		dmd_alloc_pair ();
		frame_draw(fno);
		dmd_show2 ();
		task_sleep (TIME_100MS);
	}//end of inner loop

		dmd_sched_transition (&trans_bitfade_fast);
		dmd_alloc_pair ();
		frame_draw(IMG_FORTRESS_D3_START);
		dmd_show2 ();
		task_sleep (TIME_100MS);

		for (fno = IMG_FORTRESS_D3_START; fno <= IMG_FORTRESS_D3_END; fno += 2) {
			dmd_alloc_pair ();
			frame_draw(fno);
			dmd_show2 ();
			task_sleep (TIME_100MS);
		}//end of inner loop

		if (!amode_page_changed) {
			dmd_alloc_pair_clean ();// Clean both pages
			dmd_map_overlay ();
			dmd_clean_page_low ();
				font_render_string_center (&font_halobold12, DMD_MIDDLE_X - 10, DMD_BIG_CY_Top, "JOHN");
				font_render_string_center (&font_halobold12, DMD_MIDDLE_X - 10, DMD_BIG_CY_Bot, "SPARTAN");
			dmd_text_outline ();
			dmd_alloc_pair ();
			frame_draw(IMG_FORTRESS_D3_END);
			dmd_overlay_outline ();
			dmd_show2 ();
			amode_page_end (2);
		}
		else amode_page_change (1);
}//end of mode_effect_deff






void dm_amode_show_john_spartan2_animation_page (void) {
	U16 fno;
	amode_page_changed = 0;
	for (fno = IMG_JOHN_SPARTAN_A_START; fno <= IMG_JOHN_SPARTAN_A_END; fno += 2) {
		dmd_alloc_pair ();
		frame_draw(fno);
		dmd_show2 ();
		task_sleep (TIME_100MS);
	}//end of inner loop

	for (fno = IMG_JOHN_SPARTAN_A_END-2; fno >= IMG_JOHN_SPARTAN_A_START; fno -= 2) {
		dmd_alloc_pair ();
		frame_draw(fno);
		dmd_show2 ();
		task_sleep (TIME_100MS);
	}//end of inner loop

	if (!amode_page_changed) {
		dmd_alloc_pair_clean ();// Clean both pages
		dmd_map_overlay ();
		dmd_clean_page_low ();
			font_render_string_center (&font_halobold12, DMD_MIDDLE_X - 10, DMD_BIG_CY_Top, "JOHN");
			font_render_string_center (&font_halobold12, DMD_MIDDLE_X - 10, DMD_BIG_CY_Bot, "SPARTAN");
		dmd_text_outline ();
		dmd_alloc_pair ();
		frame_draw(IMG_JOHN_SPARTAN_A_START);
		dmd_overlay_outline ();
		dmd_show2 ();
		amode_page_end (2);
	}
	else amode_page_change (1);
}//end of mode_effect_deff







void dm_amode_show_simon_phoenix_animation_page (void) {
	U16 fno;
	amode_page_changed = 0;
	for (fno = IMG_SIMON_C_START; fno <= IMG_SIMON_C_END; fno += 2) {
		dmd_alloc_pair ();
		frame_draw(fno);
		dmd_show2 ();
		if (amode_page_changed) fno = IMG_SIMON_C_END;
		else task_sleep (TIME_100MS);
	}//end of inner loop

	if (!amode_page_changed) {
		dmd_alloc_pair_clean ();// Clean both pages
		dmd_map_overlay ();
		dmd_clean_page_low ();
			font_render_string_center (&font_halobold12, DMD_MIDDLE_X - 10, DMD_BIG_CY_Top, "SIMON");
			font_render_string_center (&font_halobold12, DMD_MIDDLE_X - 10, DMD_BIG_CY_Bot, "PHOENIX");
		dmd_text_outline ();
		dmd_alloc_pair ();
		frame_draw(IMG_SIMON_C_END);
		dmd_overlay_outline ();
		dmd_show2 ();
		amode_page_end (2);
	}
	else amode_page_change (1);
}//end of mode_effect_deff







void dm_amode_show_simon_phoenix2_animation_page (void) {
	U8 i;
	U16 fno;
	amode_page_changed = 0;
	for (fno = IMG_MUSEUM_C2_START; fno <= IMG_MUSEUM_C2_END; fno += 2) {
		dmd_alloc_pair ();
		frame_draw(fno);
		dmd_show2 ();
		if (amode_page_changed) fno = IMG_MUSEUM_C2_END;
		else task_sleep (TIME_100MS);
	}//end of inner loop

	if (!amode_page_changed) {
		dmd_sched_transition (&trans_bitfade_fast);
		dmd_alloc_pair ();
		frame_draw(IMG_MUSEUM_D3_START);
		dmd_show2 ();
		task_sleep (TIME_100MS);
	}

	for (i = 0; i < 4; i++) {
		for (fno = IMG_MUSEUM_D3_START; fno <= IMG_MUSEUM_D3_END; fno += 2) {
			dmd_alloc_pair ();
			frame_draw(fno);
			dmd_show2 ();
			task_sleep (TIME_66MS);
		}//end of inner loop
	}//end of outer loop

	if (!amode_page_changed) {
		dmd_alloc_pair_clean ();// Clean both pages
		dmd_map_overlay ();
		dmd_clean_page_low ();
			font_render_string_center (&font_halobold12, DMD_MIDDLE_X - 10, DMD_BIG_CY_Top, "SIMON");
			font_render_string_center (&font_halobold12, DMD_MIDDLE_X - 10, DMD_BIG_CY_Bot, "PHOENIX");
		dmd_text_outline ();
		dmd_alloc_pair ();
		frame_draw(IMG_MUSEUM_D3_END);
		dmd_overlay_outline ();
		dmd_show2 ();
		amode_page_end (2);
	}
	else amode_page_change (1);
}//end of mode_effect_deff





void dm_amode_show_lenina_animation_page (void) {
	U16 fno;
	amode_page_changed = 0;
	for (fno = IMG_HUXLEY_A_START; fno <= IMG_HUXLEY_A_END; fno += 2) {
		dmd_alloc_pair ();
		frame_draw(fno);
		dmd_show2 ();
		if (amode_page_changed) fno = IMG_HUXLEY_A_END;
		else task_sleep (TIME_100MS);
	}//end of inner loop

	if (!amode_page_changed) {
		dmd_alloc_pair_clean ();// Clean both pages
		dmd_map_overlay ();
		dmd_clean_page_low ();
			font_render_string_center (&font_halobold12, DMD_MIDDLE_X - 10, DMD_BIG_CY_Top, "LENINA");
			font_render_string_center (&font_halobold12, DMD_MIDDLE_X - 10, DMD_BIG_CY_Bot, "HUXLEY");
		dmd_text_outline ();
		dmd_alloc_pair ();
		frame_draw(IMG_HUXLEY_A_END);
		dmd_overlay_outline ();
		dmd_show2 ();
		amode_page_end (2);
	}
	else amode_page_change (1);
}//end of mode_effect_deff





void dm_amode_show_standups_info_page (void) {
	U16 fno;
	amode_page_changed = 0;
	for (fno = IMG_COMBO3_MARIO_START; fno <= IMG_COMBO3_MARIO_END; fno += 2) {
		dmd_alloc_pair ();
		frame_draw(fno);
		dmd_show2 ();
		if (amode_page_changed) fno = IMG_COMBO3_MARIO_END;
		else task_sleep (TIME_100MS);
	}//end of inner loop

	if (!amode_page_changed) {
		dmd_sched_transition (&trans_scroll_down);
		dmd_clean_page_low ();
		font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, "HIT STANDUPS");
		font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_2, "TO LIGHT");
		font_render_string_center (&font_fixed6, DMD_MIDDLE_X, DMD_SMALL_CY_4, "QUICK FREEZE");
		dmd_show_low();
		amode_page_end (3);
	}
	else amode_page_change (1);
}//end of mode_effect_deff








void dm_amode_show_demotime_info_page (void) {
	U16 fno;
	amode_page_changed = 0;
	for (fno = IMG_MTL_COMPLETE_START; fno <= IMG_MTL_COMPLETE_END; fno += 2) {
		dmd_alloc_pair ();
		frame_draw(fno);
		dmd_show2 ();
		if (amode_page_changed) fno = IMG_MTL_COMPLETE_END;
		else task_sleep (TIME_133MS);
	}//end of inner loop

	dmd_sched_transition (&trans_bitfade_fast);
	dmd_alloc_pair ();
	frame_draw(IMG_MTL_START);
	dmd_show2 ();
	task_sleep (TIME_133MS);

	for (fno = IMG_MTL_START; fno <= IMG_MTL_END; fno += 2) {
		dmd_alloc_pair ();
		frame_draw(fno);
		dmd_show2 ();
		task_sleep (TIME_133MS);
	}//end of inner loop

	task_sleep (TIME_300MS);

	if (!amode_page_changed) {
		dmd_sched_transition (&trans_scroll_down);
		dmd_clean_page_low ();
		font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, "START 5");
		font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_2, "CLAW MODES FOR");
		font_render_string_center (&font_fixed6, DMD_MIDDLE_X, DMD_SMALL_CY_4, "DEMOLITION TIME");
		dmd_show_low();
		amode_page_end (3);
	}
	else amode_page_change (1);
}//end of mode_effect_deff






void amode_credits_page (void) {
	credits_draw ();
	dmd_show_low ();
	amode_page_end (2);
}//end of function






void amode_freeplay_page (void) {
	if (system_config.replay_award != FREE_AWARD_OFF) {
		replay_draw ();
		amode_page_end (3);
	}
	else amode_page_end (0);
}//end of function







void amode_game_rules_by_page (void) {
	dmd_sched_transition (&trans_bitfade_fast);
	dmd_clean_page_low ();
	font_render_string_center (&font_term6, 64, 7, "GAME RULES BY");
	font_render_string_center (&font_halobold14, 64, 20, "CARDONA");
	dmd_show_low ();
	amode_page_end (2);
}//end of function






void amode_dots_by_page (void) {
	dmd_sched_transition (&trans_scroll_up);
	dmd_clean_page_low ();
	font_render_string_center (&font_term6, 64, 7, "DOTS BY");
	font_render_string_center (&font_halobold14, 64, 20, "MARIO");
	dmd_show_low ();
	amode_page_end (3);
}//end of function





void amode_high_score_page_gc (void) {
	if (hstd_config.highest_scores == ON) {
		high_score_draw_gc ();
		amode_page_end (2);
	}
	else amode_page_end (0);
}






void amode_high_score_page_12 (void) {
	if (hstd_config.highest_scores == ON) {
		high_score_draw_12 ();
		amode_page_end (2);
	}
	else amode_page_end (0);
}




void amode_high_score_page_34 (void) {
	if (hstd_config.highest_scores == ON) {
		high_score_draw_34 ();
		amode_page_end (2);
	}
	else amode_page_end (0);
}







#ifdef CONFIG_RTC
void amode_date_time_page (void) {
	if (system_config.show_date_and_time == YES) {
		rtc_show_date_time (&current_date);
		amode_page_end (2);
	}
	else amode_page_end (0);
}//end of function
#endif







void amode_kill_music (void) {
	music_set (MUS_OFF);
	amode_page_end (0);
}//end of function





//try to limit to 32 pages or less
void (*amode_page_table[]) (void) = {
	amode_score_page,
	dm_amode_demolition_time_page,
	amode_logo_page, 							//FREEWPC LOGO
	amode_credits_page,
	dm_amode_show_john_spartan_animation_page,
	amode_game_rules_by_page,
	amode_dots_by_page,
	dm_amode_show_huxley_info_page,
	amode_high_score_page_gc,
	amode_high_score_page_12,
	amode_high_score_page_34,
	dm_amode_show_simon_phoenix_animation_page,
#ifdef CONFIG_RTC
	amode_date_time_page,
#endif
	dm_amode_show_lenina_animation_page,
	amode_freeplay_page, 						//EXTRA BALL AT: SCORE
	dm_amode_show_rollovers1_info_page,

	amode_score_page,
	dm_amode_demolition_time_page,
	amode_logo_page, 							//FREEWPC LOGO
	amode_credits_page,
	dm_amode_show_john_spartan2_animation_page,
	amode_game_rules_by_page,
	amode_dots_by_page,
	dm_amode_show_standups_info_page,
	amode_high_score_page_gc,
	amode_high_score_page_12,
	amode_high_score_page_34,
	dm_amode_show_simon_phoenix2_animation_page,
#ifdef CONFIG_RTC
	amode_date_time_page,
#endif
	dm_amode_show_demotime_info_page,
	amode_freeplay_page, 						//EXTRA BALL AT: SCORE
	amode_kill_music,
};








__attribute__((noinline)) void amode_page_change (S8 delta) {
	for (;;) {
		amode_page += delta;
		// Check for boundary cases // F0 = 240
		if (amode_page >= 0xF0) 													amode_page = (sizeof (amode_page_table) / sizeof (void *)) - 1;
		else if (amode_page >= sizeof (amode_page_table) / sizeof (void *)) 		amode_page = 0;
		// Check for pages that should be skipped

		// All done
		break;
	}

	// Reset any DMD transition in progress
#if (MACHINE_DMD == 1)
	dmd_in_transition = FALSE;
#endif

	amode_page_changed = 1;
}//end of function







//ALLSET_ENTRY (amode, sw_left_button, sw_upper_left_button) {
//	if (deff_get_active () == DEFF_AMODE) {
//		amode_flipper_sound ();
//		if (amode_page_changed == 0) amode_page_change (-2);//was -1 but that would restart at page already on
//	}
//}//end of function






//ALLSET_ENTRY (amode, sw_right_button, sw_upper_right_button) {
//	if (deff_get_active () == DEFF_AMODE) {
//		amode_flipper_sound ();
//		if (amode_page_changed == 0) amode_page_change (1);
//	}
//}//end of function







__attribute__((noreturn)) void system_amode_deff (void) {
	// When amode is started, diagnostic are also being re-run.  Give that
	//some time to finish, so that the score screen will show the credit
	//dot correctly.
	task_sleep (TIME_100MS);
	amode_page = 0;
	for (;;) {
		if (amode_page == 1) callset_invoke (amode_page);
		amode_page_table[amode_page] ();
	}
}//end of function



