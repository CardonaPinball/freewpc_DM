#include <freewpc.h>
#include <coin.h>

#define CONFIG_SCORE_SWEEP
#define CONFIG_SCORES_COLOR

/* The starting row for the status bar */
#define DMD_STATUS_ROW 29

/* How often the display is updated when sweeping the score.  We run about as fast
   as the human eye can perceive. */
#define LL_SWEEP_RATE TIME_33MS

/* The rate at which the score overlay is redrawn */
#define SCORE_OVERLAY_RATE TIME_166MS

/* How long we delay after a score change, before it begins to sweep */
#define LL_SWEEP_INIT_DELAY (TIME_2S / SCORE_OVERLAY_RATE)

/* How long we delay between one sweep and the next */
#define LL_SWEEP_REFRESH_DELAY (TIME_1S / SCORE_OVERLAY_RATE)

/* The number of iterations between overlay updates */
#define LL_STROBE_OVERLAY_RATE (SCORE_OVERLAY_RATE / LL_SWEEP_RATE)


/* A list of score font keys.  Each of these is an index into the
 * table below.  A key identifies a location on the DMD where
 * a score can be placed, and its font size there. */
enum score_font_key
{
	SCORE_POS_CENTER_LARGE,
	SCORE_POS_CENTER_MEDIUM,

	SCORE_POS_P2_1_LARGE,
	SCORE_POS_P2_2_LARGE,
	SCORE_POS_P2_1_MED,
	SCORE_POS_P2_2_MED,
	SCORE_POS_P2_1_SMALL,
	SCORE_POS_P2_2_SMALL,

	SCORE_POS_P3_2_MED,
	SCORE_POS_P3_3_MED,
	SCORE_POS_P3_2_SMALL,
	SCORE_POS_P3_3_SMALL,

	SCORE_POS_P4_2_MED,
	SCORE_POS_P4_3_MED,
	SCORE_POS_P4_4_MED,
	SCORE_POS_P4_2_SMALL,
	SCORE_POS_P4_3_SMALL,
	SCORE_POS_P4_4_SMALL,

	SCORE_POS_P4_2_SMALL_ALT,
	SCORE_POS_P4_3_SMALL_ALT,

};


/** A lookup table for mapping a 'score font key' into a font and
 * location on the DMD. */
const struct score_font_info
{
	/* The function to call to draw the string.  This determines
	the justification */
	void (*render) (const char *);

	/* The font to be used */
	const font_t *font;

	/* The location where the score should be drawn, subject to
	justification */
	U8 x;
	U8 y;

	/* The base pointer of the bounding box */
	U16 bb_base;

	/* The width of the bounding box in bytes */
	U8 bb_width;

	/* The height of the bounding box in rows (equal to font height) */
}
#define LROW(fontsize) (DMD_STATUS_ROW - 3 - (fontsize))

score_font_info_table[] = {
	[SCORE_POS_CENTER_LARGE] = { fontargs_render_string_center, &font_lucida9, 64, 10, 3*DMD_BYTE_WIDTH, DMD_BYTE_WIDTH },
	[SCORE_POS_CENTER_MEDIUM] = { fontargs_render_string_right, &font_mono9, 96, 10 },

	[SCORE_POS_P2_1_LARGE] = { fontargs_render_string_right, &font_lucida9, 96, 1 },
	[SCORE_POS_P2_2_LARGE] = { fontargs_render_string_right, &font_lucida9, 96, 18},
	[SCORE_POS_P2_1_MED] = { fontargs_render_string_right, &font_mono9, 96, 1 },
	[SCORE_POS_P2_2_MED] = { fontargs_render_string_right, &font_mono9, 96, 18 },
	[SCORE_POS_P2_1_SMALL] = { fontargs_render_string_right, &font_mono5, 96, 1 },
	[SCORE_POS_P2_2_SMALL] = { fontargs_render_string_right, &font_mono5, 96, 18 },

	[SCORE_POS_P3_2_MED] = { fontargs_render_string_right, &font_mono9, 96, 11 },
	[SCORE_POS_P3_3_MED] = { fontargs_render_string_right, &font_mono9, 96, 22 },
	[SCORE_POS_P3_2_SMALL] = { fontargs_render_string_right, &font_mono5, 96, 11 },
	[SCORE_POS_P3_3_SMALL] = { fontargs_render_string_right, &font_mono5, 96, 22 },

	[SCORE_POS_P4_2_MED] = { fontargs_render_string_right, &font_mono9, 96, 7 },
	[SCORE_POS_P4_3_MED] = { fontargs_render_string_right, &font_mono9, 96, 15 },
	[SCORE_POS_P4_4_MED] = { fontargs_render_string_right, &font_mono9, 96, 23 },
	[SCORE_POS_P4_2_SMALL] = { fontargs_render_string_right, &font_mono5, 96, 11 },
	[SCORE_POS_P4_3_SMALL] = { fontargs_render_string_right, &font_mono5, 96, 18 },
	[SCORE_POS_P4_4_SMALL] = { fontargs_render_string_right, &font_mono5, 96, 26 },

	[SCORE_POS_P4_2_SMALL_ALT] = { fontargs_render_string_right, &font_mono5, 96, 9 },
	[SCORE_POS_P4_3_SMALL_ALT] = { fontargs_render_string_right, &font_mono5, 96, 16 },

};



/* The lookup is [num_players-1][player_up][score_to_draw-1].
 *
 * The first index says how many players there are total.  Zero players
 * is not an option; num_players must always be at least 1.
 *
 * The second index says which player is up.  If zero, it means no
 * player is up, as during attract mode.  This will be nonzero during
 * a game.
 *
 * The third index says which player's score is being drawn.
 */
const enum score_font_key score_font_info_key[MAX_PLAYERS][MAX_PLAYERS+1][MAX_PLAYERS] = {
	/* 1 player */  {
		{SCORE_POS_CENTER_MEDIUM},
		{SCORE_POS_CENTER_MEDIUM},

	},
	/* 2 players */ {
		{SCORE_POS_P2_1_SMALL, SCORE_POS_P2_2_SMALL },
		{SCORE_POS_P2_1_MED, SCORE_POS_P2_2_SMALL },
		{SCORE_POS_P2_1_SMALL,   SCORE_POS_P2_2_MED }
	},
	/* 3 players */ {
		{SCORE_POS_P2_1_SMALL, SCORE_POS_P3_2_SMALL, SCORE_POS_P3_3_SMALL },
		{SCORE_POS_P2_1_MED, SCORE_POS_P3_2_SMALL, SCORE_POS_P3_3_SMALL },
		{SCORE_POS_P2_1_SMALL, SCORE_POS_P3_2_MED, SCORE_POS_P3_3_SMALL },
		{SCORE_POS_P2_1_SMALL, SCORE_POS_P3_2_SMALL, SCORE_POS_P3_3_MED },
	},
	/* 4 players */ {
		{SCORE_POS_P2_1_SMALL, SCORE_POS_P4_2_SMALL, SCORE_POS_P4_3_SMALL, SCORE_POS_P4_4_SMALL },
		{SCORE_POS_P2_1_MED, SCORE_POS_P4_2_SMALL, SCORE_POS_P4_3_SMALL, SCORE_POS_P4_4_SMALL, },
		{SCORE_POS_P2_1_SMALL, SCORE_POS_P4_2_MED, SCORE_POS_P4_3_SMALL, SCORE_POS_P4_4_SMALL, },
		{SCORE_POS_P2_1_SMALL, SCORE_POS_P4_2_SMALL_ALT, SCORE_POS_P4_3_MED, SCORE_POS_P4_4_SMALL, },
		{SCORE_POS_P2_1_SMALL, SCORE_POS_P4_2_SMALL_ALT, SCORE_POS_P4_3_SMALL_ALT, SCORE_POS_P4_4_MED, },
	},
};


const enum score_font_key *dmd_score_info_base;

U16 ll_dmd_sweep_addr;

U8 ll_sweep_row;

U8 ll_sweep_off;

U8 ll_sweep_width;

U8 ll_sweep_overlay_needed;

U8 ll_dmd_sweep_counter;


__attribute__((noinline)) void ll_score_change_player (void)
{
	/* Take a pointer to the score key for index 0 (not in game).
	 * This calculation only needs to happen when num_players or
	 * player_up changes. */
	dmd_score_info_base = &score_font_info_key[num_players-1][player_up][0];
}


void ll_scores_draw_current (U8 player)
{
	const struct score_font_info *info;

	/* Get score info for the desired player */
	info = score_font_info_table + dmd_score_info_base[player];

	/* Load the font info into the appropriate registers. */
	DECL_FONTARGS (info->font, info->x, info->y, sprintf_buffer);

	/* Start printing to the display */
	info->render (sprintf_buffer);
}





void ll_score_draw_ball (void) {
		dmd_draw_vert_line (dmd_low_buffer, 100);
		if (flag_test (FLAG_IS_EXPLODE_MODE_ENABLED) ) { sprintf ("E"); font_render_string_right (&font_var5, 106, 0, sprintf_buffer); }
		if (flag_test (FLAG_IS_CARCHASE_MODE_ENABLED) ){ sprintf ("C"); font_render_string_right (&font_var5, 111, 0, sprintf_buffer); }
		if (flag_test (FLAG_VIDEO_MODE_ENABLED) ) {		 sprintf ("V"); font_render_string_right (&font_var5, 117, 0, sprintf_buffer); }
		if (flag_test (FLAG_BACK_IN_THE_FRIDGE_ACTIVATED) ) { sprintf ("F"); font_render_string_right (&font_var5, 122, 0, sprintf_buffer); }
		if (flag_test (FLAG_IS_HUXLEY_ENABLED) ) {		 sprintf ("H"); font_render_string_right (&font_var5, 128, 0, sprintf_buffer); }
		if (TROUGH_TEST) {								sprintf ("L%d", live_balls); font_render_string_right (&font_var5, 110, 6, sprintf_buffer);
														sprintf ("%d", missing_balls); font_render_string_right (&font_var5, 119, 6, sprintf_buffer);
														sprintf ("T%d", balls_in_trough); font_render_string_right (&font_var5, 128, 6, sprintf_buffer); }
		if (TROUGH_TEST) {
				sprintf ("L%d", live_balls); font_render_string_right (&font_var5, 110, 6, sprintf_buffer);
				sprintf ("%d", missing_balls); font_render_string_right (&font_var5, 119, 6, sprintf_buffer);
				sprintf ("T%d", balls_in_trough); font_render_string_right (&font_var5, 128, 6, sprintf_buffer);
		}
		sprintf ("P%d", player_up); font_render_string_right (&font_fixed6, 126, 11, sprintf_buffer);
		sprintf ("BALL %1i", ball_up); font_render_string_right (&font_var5, 128, 21, sprintf_buffer);
		credits_render (); font_render_string_right (&font_var5, 128, 27, sprintf_buffer);
}


/* Reinitialize the score sweep after a full cycle */
static void ll_score_sweep_rescan (void)
{
	const struct score_font_info *info;
	info = score_font_info_table + dmd_score_info_base[player_up-1];
	ll_dmd_sweep_addr = info->bb_base;
	ll_sweep_row = far_read8 ((U8 *)info->font + 1, FON_PAGE) + 1;
	ll_sweep_width = info->bb_width;
}


/* Initialize the score sweep after a score change */
static void ll_score_sweep_init (void)
{
	ll_dmd_sweep_counter = LL_SWEEP_INIT_DELAY;
	ll_sweep_overlay_needed = LL_STROBE_OVERLAY_RATE;
	ll_sweep_off = TRUE;
	ll_score_sweep_rescan ();
}


/* Redraw the active score screen.
 * This function does not actually show the scores, but renders them
 * to the overlay buffer for showing later.
 * Before valid playfield, we also render a second screen without the
 * current player's score; this allows it to be flashed.
 */
void ll_score_redraw (void)
{
	if (valid_playfield)
	{
		dmd_map_overlay ();
		dmd_clean_page_low ();
		scores_draw_status_bar ();
		scores_draw_current (SCORE_DRAW_ALL);
		dmd_copy_low_to_high ();
		/* Take care that player_up != 0 */
		ll_score_sweep_init ();
	}
	else
	{
		dmd_alloc_pair ();
		dmd_clean_page_low ();
		scores_draw_status_bar ();
		dmd_copy_low_to_high ();
		scores_draw_current (player_up);
		dmd_flip_low_high ();
		scores_draw_current (SCORE_DRAW_ALL);
		dmd_show_low ();
	}
}



/* Strobe the display during the score deff, prior to valid playfield. */
void ll_score_strobe_novalid (void)
{
	dmd_show_other ();
	score_deff_sleep (TIME_133MS);
}


/* Strobe the display during the score deff, after valid playfield. */
void ll_score_strobe_valid (void)
{
#ifdef CONFIG_SCORE_SWEEP
	if (ll_dmd_sweep_counter == 0)
	{
		/* Copy the previous page - scores and overlay */
		dmd_dup_mapped ();

		/* Modify the current score area - either erase a line, or add back a line
		that was erased earlier. */
		if (ll_sweep_off)
		{
			memset (dmd_low_buffer + ll_dmd_sweep_addr, 0, ll_sweep_width);
		}
		else
		{
			pinio_dmd_window_set (PINIO_DMD_WINDOW_1, DMD_OVERLAY_PAGE);
			memcpy (dmd_low_buffer + ll_dmd_sweep_addr,
				dmd_high_buffer + ll_dmd_sweep_addr, ll_sweep_width);
			pinio_dmd_window_set (PINIO_DMD_WINDOW_1,
				pinio_dmd_window_get (PINIO_DMD_WINDOW_0) + 1);
		}

#ifdef CONFIG_SCORES_COLOR
		dmd_copy_low_to_high ();
#endif

		/* Draw the overlay periodically */
		if (--ll_sweep_overlay_needed == 0)
		{
			ll_sweep_overlay_needed = LL_STROBE_OVERLAY_RATE;
			callset_invoke (score_overlay);
		}

		/* Show the new frame */
#ifdef CONFIG_SCORES_COLOR
		dmd_show2 ();
#else
		dmd_show_low ();
#endif

		/* Advance to the next row */
		ll_dmd_sweep_addr += DMD_BYTE_WIDTH;
		if (--ll_sweep_row == 0)
		{
			ll_score_sweep_rescan ();
			ll_sweep_off = !ll_sweep_off;
			if (ll_sweep_off == TRUE)
			{
				ll_dmd_sweep_counter = LL_SWEEP_REFRESH_DELAY;
				score_deff_sleep (TIME_100MS);
				return;
			}
		}

		score_deff_sleep (LL_SWEEP_RATE);
		return;
	}

	ll_dmd_sweep_counter--;
#endif

#ifdef CONFIG_SCORES_COLOR
	//dmd_map_overlay ();
	dmd_dup_mapped ();
	dmd_overlay_onto_color ();
	callset_invoke (score_overlay);
	dmd_show2 ();
#else
	dmd_map_overlay ();
	dmd_dup_mapped ();
	dmd_overlay ();
	callset_invoke (score_overlay);
	dmd_show_low ();
#endif
	score_deff_sleep (TIME_133MS);
}


/**
 * Update the score screen font information when necessary.
 * If player_up or num_players changes, we need to do this.
 */
CALLSET_ENTRY (dmd_score, init_complete, start_game, start_ball, add_player, amode_start, stop_game)
{
	ll_score_change_player ();
}

