/*
 * Copyright 2006-2011 by Brian Dominy <brian@oddchange.com>
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

#ifndef _STDADJ_H
#define _STDADJ_H

typedef U8 adjval_t;

#define MAX_REPLAY_LEVELS 4
#define MAX_COIN_SLOTS 4

/* Yes/No value defines */
enum { NO, YES };

/* Off/On value defines */
enum { OFF, ON };

/* Date/Time styles */
enum {
	CLOCK_STYLE_AMPM,
	CLOCK_STYLE_24HOUR
};

enum {
	DATE_STYLE_US,
	DATE_STYLE_EURO
};

/* Game restart setting */
enum {
	GAME_RESTART_NEVER,
	GAME_RESTART_SLOW,
	GAME_RESTART_ALWAYS
};

/* Free awards */
enum {
	FREE_AWARD_OFF,
	FREE_AWARD_CREDIT,
	FREE_AWARD_EB,
	FREE_AWARD_TICKET,
	FREE_AWARD_POINTS
};

/* Replay systems */
enum {
	REPLAY_FIXED,
	REPLAY_AUTO
};

/* Currency types */
enum {
	CUR_DOLLAR,
	CUR_FRANC,
	CUR_LIRA,
	CUR_PESETA,
	CUR_YEN,
	CUR_DM,
	CUR_GBP,
	CUR_EURO,
	CUR_TOKEN,
	NUM_CURRENCY_TYPES
};

/* Pricing modes */
enum {
	PRICE_CUSTOM,
	PRICE_USA_25CENT,
	PRICE_USA_50CENT,
	PRICE_USA_50_75_100,
	PRICE_USA_3_FOR_1,
	PRICE_USA_5_FOR_2,
	PRICE_USA_75CENT,
	PRICE_USA_DOLLAR,
	PRICE_UK,
	PRICE_EURO,
	NUM_PRICING_MODES,
};

/* Coin door types */
enum {
	COIN_DOOR_CUSTOM,
	COIN_DOOR_25_25_25,
	COIN_DOOR_25_100_25,
	COIN_DOOR_UK,
	COIN_DOOR_EURO,
	NUM_COIN_DOOR_TYPES
};

/* Languages */
enum {
	LANG_US_ENGLISH,
	LANG_GERMAN,
	LANG_FRENCH,
	LANG_SPANISH,
	LANG_UK_ENGLISH,
	NUM_LANGUAGES
};

/* Payment Method */
enum {
	PAY_COIN,
	PAY_TOKEN,
	PAY_CARD,
	PAY_BILL,
	MAX_PAY_METHODS
};

/* Difficulty Settings */
enum {
	EXTRA_EASY,
	EASY,
	MEDIUM,
	HARD,
	EXTRA_HARD,
};

typedef struct
{
	adjval_t balls_per_game; /* done */
	adjval_t max_players; /* done */
	adjval_t tilt_warnings; /* done */
	adjval_t max_ebs; /* done */
	adjval_t max_ebs_per_bip; /* done */
		/* Auto or fixed */
	adjval_t replay_system;
		/* Percentage of replays when Auto Replay in effect.  Range 5-50% */
	adjval_t replay_percent;
		/* First replay level when Auto Replay in effect.  Up to 60 different
		levels can be configured. */
	adjval_t replay_start;
		/* The number of replay levels used by Auto Replay.  Range is 1-4.
		Levels 2-4 are automatically set to 2x-4x the base value */
	adjval_t replay_levels;
		/* Only used when Fixed Replay is enabled.  This replaces Replay Start
		and Replay Levels.  Each level could also be set to OFF. */
	adjval_t replay_level[MAX_REPLAY_LEVELS];
		/* OFF, or amount to temporarily boost the replay */
	adjval_t replay_boost;
	adjval_t replay_award; /* done */
	adjval_t special_award; /* done */
//	adjval_t match_award;
//	adjval_t extra_ball_ticket;
//	adjval_t max_tickets_per_player; /* done */
//	adjval_t match_feature; /* done */
	adjval_t custom_message;
	adjval_t language;
	adjval_t clock_style; /* done */
	adjval_t date_style; /* done */
	adjval_t show_date_and_time; /* done */
	adjval_t allow_dim_illum; /* done */
	adjval_t tournament_mode; /* done */
	adjval_t euro_digit_sep; /* done */
	adjval_t min_volume_control; /* done */
	adjval_t gi_power_saver; /* done */
	adjval_t power_saver_level; /* done */
	/* The ticket_board adjustment says if a ticket dispenser
	is connected, or if a coin meter is attached. */
//	adjval_t ticket_board;
	adjval_t no_bonus_flips; /* done */
	adjval_t game_restart; /* done */
	adjval_t allow_chase_ball; /* done */

	adjval_t flipper_plunger;
	adjval_t timed_plunger;
	adjval_t game_music;


	adjval_t coin_door_ball_save;

	adjval_t eyeball_eb;	//done
	adjval_t num2explode;	//done
	adjval_t num2freeze;	//done - num standups to hit to light freeze
	adjval_t jets_goal;		//done
	adjval_t num2chase;		//done
	adjval_t num2comp_award; //done
	adjval_t num2video;		//done
	adjval_t num2huxley;	//done
	adjval_t num2demotime; 	//done
	adjval_t mb_ballsave;	//done
	adjval_t mode_ballsave; //done
	adjval_t vm_level;		//done


	adjval_t 	extra_sounds;
	adjval_t 	swear_sounds;
	adjval_t 	disable_kaboom;
	adjval_t 	disable_simon_says;
	adjval_t 	disable_shooter;
	adjval_t disable_claw;
	adjval_t disable_shaker;
	adjval_t extra_shaker;
	adjval_t disable_knocker;
} std_adj_t;

extern __nvram__ std_adj_t system_config;

#define config_timed_game OFF

#ifdef MACHINE_LAUNCH_SWITCH
#define config_flipper_plunger (system_config.flipper_plunger)
#define config_timed_plunger (system_config.timed_plunger)
#else
#define config_flipper_plunger OFF
#define config_timed_plunger ON
#endif

typedef struct
{
	adjval_t pricing_mode; /* done */
	adjval_t coin_units[MAX_COIN_SLOTS]; /* done */
	adjval_t units_per_credit; /* done */
	adjval_t units_per_bonus; /* done */
	adjval_t bonus_credits; /* done */
	adjval_t min_units;
	adjval_t coin_door_type; /* done */
	adjval_t collection_text; /* done */
	adjval_t slot_values[MAX_COIN_SLOTS];
	adjval_t max_credits; /* done */
	adjval_t free_play; /* done */
	adjval_t hide_coin_audits;
	adjval_t payment_method; /*( done */
	adjval_t base_coin_size;
	adjval_t coin_meter_units;
	adjval_t fast_bill_slot;
	adjval_t min_coin_msec;
	adjval_t slamtilt_penalty; /* done */
	adjval_t allow_hundredths;
	adjval_t credit_fraction;
} pricing_adj_t;

extern __nvram__ pricing_adj_t price_config;


typedef struct
{
	adjval_t highest_scores;
	adjval_t hstd_award;
	adjval_t champion_hstd;
	adjval_t champion_credits; /* done */
	adjval_t hstd_credits[4]; /* done */
	adjval_t hs_reset_every; /* done */
} hstd_adj_t;

extern __nvram__ hstd_adj_t hstd_config;


#ifdef MACHINE_FEATURE_ADJUSTMENTS
extern __nvram__ feature_adj_t feature_config;
#endif

extern adjval_t *last_adjustment_changed;

void adj_modified (adjval_t *adjp);
void adj_init (void);

#endif /* _STDADJ_H */
