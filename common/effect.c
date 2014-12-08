/*
 * Copyright 2007-2012 by Brian Dominy <brian@oddchange.com>
 *
 * This file is part of FreeWPC.
 *
 * FreeWPC is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * FreeWPC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FreeWPC; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <freewpc.h>
#include <highscore.h>
#include <replay.h>
#include <coin.h>
#include <diag.h>
#include "dm/global_constants.h"

extern U8 last_nonfatal_error_code;
extern task_gid_t last_nonfatal_error_gid;
extern __nvram__ U8 current_volume;



void shoot_again_deff (void) {
	U8 sa_rnd_sound;
	U16 fno;
	U8 i;
	dmd_alloc_pair_clean ();// Clean both pages
	sa_rnd_sound = random_scaled(2);
	sound_start (ST_EFFECT, EXTRA_BALL_SOUND, SL_2S, SP_NORMAL);

	for (i = 0; i < 2; i++) {
		for (fno = IMG_SHOOT_AGAIN_START; fno <= IMG_SHOOT_AGAIN_END; fno += 2) {
			dmd_alloc_pair ();
			frame_draw(fno);
			dmd_show2 ();
			sound_start (ST_EFFECT, GUNSHOT_MUFFLED, SL_100MS, PRI_GAME_QUICK2);
			task_sleep (TIME_133MS);
		}//end of inner loop
	}//end of outer loop
	sound_start (ST_EFFECT, GUNSHOT, SL_1S, PRI_GAME_QUICK2);

	if (sa_rnd_sound) 	sound_start (ST_SPEECH, SPCH_SHOOT_AGAIN, SL_2S, SP_NORMAL);
	else 				sound_start (ST_SPEECH, SPCH_SHOOT_AGAIN_SLY, SL_2S, SP_NORMAL);

	dmd_alloc_pair_clean ();// Clean both pages
	dmd_map_overlay ();
	dmd_clean_page_low ();
	font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "SHOOT");
	font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "AGAIN");
	dmd_text_outline ();
	dmd_alloc_pair ();
	frame_draw(IMG_SHOOT_AGAIN_END);
	dmd_overlay_outline ();
	dmd_show2 ();
	task_sleep (TIME_2S);
	deff_exit ();
}//end of function






void dm_game_over_deff (void) {
	U8 sa_rnd_sound;
	U16 fno;
	dmd_alloc_pair_clean ();// Clean both pages

	if (system_config.swear_sounds == YES) {
		//this doubles the chance that a swear would occur
		sa_rnd_sound = random_scaled(5);   //choose 0 - 4
		if (sa_rnd_sound > 3) sa_rnd_sound = 3;
	}
	else if (system_config.extra_sounds == YES) sa_rnd_sound = random_scaled(3);
	else 										sa_rnd_sound = random_scaled(2);

	for (fno = IMG_CAR_CRASH_START; fno <= IMG_CAR_CRASH_END; fno += 2) {
		dmd_alloc_pair ();
		frame_draw(fno);
		dmd_show2 ();
		task_sleep (TIME_100MS);
	}//end of inner loop

	switch (sa_rnd_sound) {
		case (0): sound_start (ST_SPEECH, SPCH_PLAY_ACCORDION_TOO, SL_2S, SP_NORMAL); break;
		case (1): sound_start (ST_SPEECH, SPCH_SIMON_LAUGH_LONG, SL_2S, SP_NORMAL);  break;
		case (2): sound_start (ST_SPEECH, SPCH_TRY_IT_AGAIN_SUCKER_SIMON, SL_2S, SP_NORMAL); break; //swear roms but doesn't curse
		case (3): sound_start (ST_SPEECH, SPCH_VLGR_REALLY_LICKED_AS_SNDRA, SL_2S, SP_NORMAL); break; //swear roms - curses
	}

	dmd_alloc_pair_clean ();// Clean both pages
	dmd_map_overlay ();
	dmd_clean_page_low ();
		font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "GAME OVER");
	dmd_text_outline ();
	dmd_alloc_pair ();
	frame_draw(IMG_CAR_CRASH_END);
	dmd_overlay_outline ();
	dmd_show2 ();
	task_sleep (TIME_2S);
	deff_exit ();
}//end of function






/*
 * every third ball save, show a display effect.  other 2 times, use only a voice call out
 */
const sound_code_t ball_save_SoundsArray[] = {	SPCH_AINT_OVER_YET,		SPCH_HEADS_UP,		SPCH_DONT_MOVE,
												SPCH_DONT_MOVE_PHOENIX, SPCH_SECOND_CHANCE,		SPCH_NEXT_SHOT };

__boolean ballSaveAlternator;
void ball_save_deff (void) {
	U16 fno;
	U8 ball_save_SoundCounter;
	ball_save_SoundCounter = random_scaled(3);//from kernal/random.c

	if (ballSaveAlternator) {
		ballSaveAlternator = FALSE;
		sound_start (ST_SPEECH, ball_save_SoundsArray[ball_save_SoundCounter], SL_4S, PRI_GAME_QUICK2);
		for (fno = IMG_BALL_SAVE_START; fno <= IMG_BALL_SAVE_END; fno += 2) {
			dmd_alloc_pair ();
			frame_draw(fno);
			dmd_show2 ();
			task_sleep (TIME_100MS);
		}//end of loop 1

		U8 i;
		for (i = 0; i <= 3; i++) {
				sound_start (ST_EFFECT, GUNSHOT_MUFFLED, SL_100MS, PRI_GAME_QUICK2);
				for (fno = IMG_BALL_SAVE_END - 2; fno <= IMG_BALL_SAVE_END; fno += 2) {
						dmd_alloc_pair ();
						frame_draw(fno);
						dmd_show2 ();
						task_sleep (TIME_100MS);
					}//end of inner loop 2
		}//end of loop outer loop 2

		sound_start (ST_EFFECT, GUNSHOT, SL_200MS, PRI_GAME_QUICK3);

		for (fno = IMG_BALL_SAVE_END - 2; fno >= IMG_BALL_SAVE_START; fno -= 2) {
			dmd_alloc_pair ();
			frame_draw(fno);
			dmd_show2 ();
			task_sleep (TIME_100MS);
		}//end of loop 3
	}//end of if (ballSaveAlternator)
	else {
		ballSaveAlternator = TRUE;
		sound_start (ST_SPEECH, ball_save_SoundsArray[ball_save_SoundCounter+3], SL_4S, PRI_GAME_QUICK2);
	}
	deff_exit ();
}







/** Display effect when locating missing balls prior to game start */
void locating_balls_deff (void) {
		dmd_clean_page_low ();
		//right side status display
				dmd_draw_vert_line (dmd_low_buffer, 100);
				if (flag_test (FLAG_IS_EXPLODE_MODE_ENABLED) ) { sprintf ("E"); font_render_string_right (&font_var5, 106, 0, sprintf_buffer); }
				if (flag_test (FLAG_IS_CARCHASE_MODE_ENABLED) ){ sprintf ("C"); font_render_string_right (&font_var5, 111, 0, sprintf_buffer); }
				if (flag_test (FLAG_VIDEO_MODE_ENABLED) ) {		 sprintf ("V"); font_render_string_right (&font_var5, 117, 0, sprintf_buffer); }
				if (flag_test (FLAG_BACK_IN_THE_FRIDGE_ACTIVATED) ) { sprintf ("F"); font_render_string_right (&font_var5, 122, 0, sprintf_buffer); }
				if (flag_test (FLAG_IS_HUXLEY_ENABLED) ) {		 sprintf ("H"); font_render_string_right (&font_var5, 128, 0, sprintf_buffer); }
				if (TROUGH_TEST) {								sprintf ("L%d", live_balls); font_render_string_right (&font_var5, 110, 6, sprintf_buffer);
				sprintf ("%d", missing_balls); font_render_string_right (&font_var5, 119, 6, sprintf_buffer);
				sprintf ("T%d", balls_in_trough); font_render_string_right (&font_var5, 128, 6, sprintf_buffer); }
				sprintf ("P%d", player_up); font_render_string_right (&font_fixed6, 126, 11, sprintf_buffer);
				sprintf ("BALL %1i", ball_up); font_render_string_right (&font_var5, 128, 21, sprintf_buffer);
				credits_render (); font_render_string_right (&font_var5, 128, 27, sprintf_buffer);

		//left side display
				font_render_string_center (&font_halobold12, 50, 20, "SEARCH");
				dmd_show_low();
				task_sleep (TIME_4S);
	deff_exit ();
}





void draw_volume_bar (U8 n)
{
#if (MACHINE_DMD == 1)
	U8 *base = dmd_low_buffer + 22 * DMD_BYTE_WIDTH + 4;
	U8 val = 0x55;
	U8 h;
	static const U8 volume_bar_data[] = { 0x0, 0x1, 0x5, 0x15, 0x55 };
	while (n >= 4)
	{
		for (h=0; h < 8; h++)
			base[h * DMD_BYTE_WIDTH] = val;
		base++;
		n -= 4;
	}
	val = volume_bar_data[n];
	for (h=0; h < 8; h++)
		base[h * DMD_BYTE_WIDTH] = val;
#endif
}




#if (MACHINE_DMD == 1)
/** Draw a thin border 2 pixels wide around the given display page. */
void dmd_draw_border (U8 *dbuf)
{
	const dmd_buffer_t dbuf_bot = (dmd_buffer_t)((char *)dbuf + 480);
	register U16 *dbuf16 = (U16 *)dbuf;
	register U16 *dbuf16_bot = (U16 *)dbuf_bot;
	U8 i;

	for (i=0; i < 16; i++)
		*dbuf16_bot++ = *dbuf16++ = 0xFFFFUL;
	dbuf += 32;
	for (i=0; i < 28; i++)
	{
		dbuf[0] = 0x03;
		dbuf[15] = 0xC0;
		dbuf += 16;
	}
}




void dmd_draw_thin_border (U8 *dbuf)
{
	const dmd_buffer_t dbuf_bot = (dmd_buffer_t)((char *)dbuf + 496);
	register U16 *dbuf16 = (U16 *)dbuf;
	register U16 *dbuf16_bot = (U16 *)dbuf_bot;
	U8 i;

	for (i=0; i < 8; i++)
		*dbuf16_bot++ = *dbuf16++ = 0xFFFFUL;
	dbuf += 16;

	for (i=0; i < 30; i++)
	{
		dbuf[0] = 0x01;
		dbuf[15] = 0x80;
		dbuf += 16;
	}
}




/**
 * Draw a horizontal line at the specified y-coordinate.
 */
void dmd_draw_horiz_line (U16 *dbuf, U8 y) {
	dbuf += y * (16 / 2);

	*dbuf++ = 0xffffUL;
	*dbuf++ = 0xffffUL;
	*dbuf++ = 0xffffUL;
	*dbuf++ = 0xffffUL;
	*dbuf++ = 0xffffUL;
	*dbuf++ = 0xffffUL;
	*dbuf++ = 0xffffUL;
	*dbuf++ = 0xffffUL;
}



//the DMD is composed of 128 pixels across
//which is divided into 8 16-bit numbers
//
// the x input is from 0 to 127
//the offset is the 8 numbers so is x/8
//then to find the position in reference to the offset
//we take remainder (modulus).  New position must be converted
//from a number to a positional representation so we use shift.
void dmd_draw_vert_line (U8 *dbuf, U8 x) {
	U8 i;
	U8 offset;
	U8 position;
	offset = x / 8;
	position = x % 8;
	for (i=0; i < 32; i++) {//there are 32 vertical lines
		dbuf[offset] = 0x01 << position;
		dbuf += 16;//this skips us down to the next line
	}
}



#endif /* MACHINE_DMD */






/** The display effect for a volume change */
void volume_change_deff (void)
{
	dmd_alloc_low_clean ();
	sprintf ("VOLUME %d", current_volume);
	font_render_string_center (&font_fixed6, 64, 9, sprintf_buffer);
	draw_volume_bar (current_volume);
	dmd_show_low ();
	if (in_live_game)
		task_sleep_sec (3);
	else
		task_sleep_sec (5);
	deff_exit ();
}





/** The display effect for a non-fatal error */
void nonfatal_error_deff (void)
{
#ifdef DEBUGGER
	dmd_alloc_low_clean ();
	sprintf ("NONFATAL %ld", system_audits.non_fatal_errors);
	font_render_string_center (&font_mono5, 64, 10, sprintf_buffer);
	sprintf ("ERRNO %i GID %i", last_nonfatal_error_code, last_nonfatal_error_gid);
	font_render_string_center (&font_mono5, 64, 20, sprintf_buffer);
	dmd_show_low ();
	sound_send (SND_TEST_ALERT);
	task_sleep (TIME_200MS);
	sound_send (SND_TEST_ALERT);
	task_sleep (TIME_200MS);
	sound_send (SND_TEST_ALERT);
	task_sleep_sec (4);
#endif
	deff_exit ();
}





/** The display effect for the final ball goal */
void score_goal_deff (void)
{
	/* Show the replay if it is enabled and hasn't been awarded yet. */
	if (replay_can_be_awarded ())
	{
		replay_draw ();
	}
	else
	{
		grand_champion_draw ();
	}
	task_sleep_sec (2);
	deff_exit ();
}






const U8 	shoot_reminder_TotalNumOfSounds = 10; //num between 0 and N-1 == N total
const sound_code_t shoot_reminder_SoundsArray[] = {	SPCH_COME_GET_ME, 		SPCH_LETS_GO2, 			SPCH_MOVE_IT_SLY,
													SPCH_DRIVE, 			SPCH_GO_SLY,
													SPCH_DO_SOMETHING, 		SPCH_MOVE, 				SPCH_MOVE_IT,
													SPCH_GO_WES, 			SPCH_NOW };


void plunge_ball_deff (void) {
	U16 fno;
	U8 shoot_reminder_SoundCounter;
	shoot_reminder_SoundCounter = random_scaled(shoot_reminder_TotalNumOfSounds);//from kernal/random.c

	dmd_alloc_pair_clean ();// Clean both pages

	sound_start (ST_SPEECH, shoot_reminder_SoundsArray[shoot_reminder_SoundCounter], SL_4S, PRI_GAME_QUICK2);

	for (fno = IMG_PLUNGE_BALL_START; fno <= IMG_PLUNGE_BALL_END; fno += 2) {
			dmd_alloc_pair ();
			frame_draw(fno);
			dmd_show2 ();
			task_sleep (TIME_100MS);

			if (fno == IMG_PLUNGE_BALL_FIRE) 	sound_start (ST_EFFECT, GUNSHOT, SL_200MS, PRI_GAME_QUICK3);
	}//end of for loop

	dmd_alloc_pair_clean ();// Clean both pages
	dmd_map_overlay ();
	dmd_clean_page_low ();
	font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Top, "PLUNGE");
	font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Bot, "BALL");
	dmd_text_outline ();
	dmd_alloc_pair ();
	frame_draw(IMG_PLUNGE_BALL_END);
	dmd_overlay_outline ();
	dmd_show2 ();
	task_sleep (TIME_1S);
	deff_exit ();
}




void coin_door_buttons_deff (void)
{
	dmd_alloc_low_clean ();
#if (MACHINE_DMD == 1)
	font_render_string_center (&font_var5, 64, 3, "COIN DOOR IS CLOSED");
#endif
	font_render_string_center (&font_var5, 64, 10, "OPEN COIN DOOR");
	font_render_string_center (&font_var5, 64, 17, "TO USE BUTTONS");
	dmd_show_low ();
	task_sleep_sec (3);
	deff_exit ();
}



void coin_door_power_deff (void)
{
	U8 n;
	for (n=0; n < 8; n++)
	{
		dmd_alloc_low_clean ();
		dmd_show_low ();
		task_sleep (TIME_200MS);

		dmd_alloc_low_clean ();
#if (MACHINE_DMD == 1)
		font_render_string_center (&font_fixed6, 64, 6, "COIN DOOR IS OPEN");
		font_render_string_center (&font_fixed6, 64, 16, "HIGH POWER");
		font_render_string_center (&font_fixed6, 64, 26, "IS DISABLED");
#else
		font_render_string_center (&font_fixed6, 64, 10, "HIGH POWER");
		font_render_string_center (&font_fixed6, 64, 21, "IS DISABLED");
#endif
		dmd_show_low ();
		sound_send (SND_TEST_ALERT);
		task_sleep (TIME_300MS);
	}
	task_sleep_sec (4);
	deff_exit ();
}


/** The tilt display effect runs until explicitly cancelled. */
void tilt_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed10, 64, 13, "TILT");
	dmd_show_low ();
	task_suspend ();
}


void tilt_warning_deff (void)
{
	extern U8 tilt_warnings;
	dmd_alloc_pair_clean ();
	if (tilt_warnings % 2)
	{
		font_render_string_center (&font_fixed10, 64, 16, "DANGER");
	}
	else
	{
		font_render_string_center (&font_fixed10, 64, 7, "DANGER");
		font_render_string_center (&font_fixed10, 64, 23, "DANGER");
	}
	deff_swap_low_high (24, TIME_66MS);
	deff_exit ();
}







void slam_tilt_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed10, 64, 13, "SLAM TILT");
	dmd_show_low ();
	task_suspend ();
}







/** Reduce a credit fraction to simplest terms. */
static inline void reduce_unit_fraction (U8 *units, U8 *units_per_credit)
{
	switch (*units_per_credit)
	{
		case 4:
			if (*units == 2)
			{
				*units = 1;
				*units_per_credit = 2;
			}
			break;

		case 6:
			switch (*units)
			{
				case 2:
					*units = 1;
					*units_per_credit = 3;
					break;
				case 4:
					*units = 2;
					*units_per_credit = 3;
					break;
			}
			break;
	}
}







/** Render the number of credits */
void credits_render (void) {
	if (price_config.free_play)
		sprintf ("FREE");
	else
	{
		if (get_units () != 0) {
			U8 units = get_units ();
			U8 units_per_credit = price_config.units_per_credit;

			/* There are fractional credits.  Reduce to the
			 * lowest common denominator before printing. */
			reduce_unit_fraction (&units, &units_per_credit);

			if (get_credits () == 0)
				sprintf ("%d/%d CR", units, units_per_credit);
			else
				sprintf ("%d %d/%d CR",
					get_credits (), units, units_per_credit);
		}
		else {
			if (get_credits () == 1)
				sprintf ("%d CR", get_credits ());
			else
				sprintf ("%d CR", get_credits ());
		}
	} //END OF NOT FREE PLAY
}//END OF FUNCTION







/** Draw the current credits full screen */
void credits_draw (void) {
	dmd_alloc_pair ();
	dmd_clean_page_low ();

	credits_render ();
	font_render_string_right (&font_var5, 128, 26, sprintf_buffer);
	dmd_copy_low_to_high ();

	if (!has_credits_p ()) {
		if (price_config.payment_method == PAY_COIN) 		sprintf ("INSERT COINS");
		else if (price_config.payment_method == PAY_TOKEN) 	sprintf ("INSERT TOKENS");
		else if (price_config.payment_method == PAY_CARD) 	sprintf ("SWIPE CARD");
		else if (price_config.payment_method == PAY_BILL) 	sprintf ("INSERT BILLS");
	}
	else
	{
		sprintf ("PRESS START");
	}
	font_render_string_center (&font_fixed6, 64, 18, sprintf_buffer); //Y was 22
}


void credits_deff (void)
{
	credits_draw ();
	deff_swap_low_high (in_live_game ? 12 : 20, 2 * TIME_100MS);
	deff_delay_and_exit (TIME_1S);
}



void player_tournament_ready_deff (void)
{
	U8 timer;

	dmd_alloc_low_clean ();
#if (MACHINE_DMD == 1)
	font_render_string_center (&font_fixed6, 64, 5, "TOURNAMENT");
	font_render_string_center (&font_fixed6, 64, 16, "MODE ENABLED");
#else
	font_render_string_center (&font_var5, 64, 5, "TOURNAMENT MODE");
#endif
	font_render_string_center (&font_var5, 64, 28, "PRESS START NOW");
	dmd_show_low ();

	timer = 7;
	do {
		task_sleep_sec (1);
	} while (--timer != 0);

	tournament_mode_enabled = OFF;
	deff_exit ();
}



