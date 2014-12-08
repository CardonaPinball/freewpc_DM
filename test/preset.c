
#include <freewpc.h>
#include <window.h>
#include <preset.h>

#define PRESET_BEGIN(name) \
struct preset_component preset_ ## name ## _comps[] = {

#define PRESET_END(N, string) \
	{ NULL, 0 }, \
}; \
struct preset preset_ ## N = {  \
	.name = string,  \
	.comps = preset_ ## N ## _comps \
};

#ifndef FREE_ONLY
#define PRESET_FREE_PLAY \
	{ pricing_adjustments, &price_config.free_play, YES },
#else
#define PRESET_FREE_PLAY
#endif

extern struct adjustment standard_adjustments[];
extern struct adjustment feature_adjustments[];
extern struct adjustment pricing_adjustments[];

struct preset_component *preset_component_ptr;


PRESET_BEGIN (easy)
	{ feature_adjustments, &system_config.eyeball_eb, 10 },
	{ feature_adjustments, &system_config.num2explode, 2 },
	{ feature_adjustments, &system_config.num2freeze, 4 },
	{ feature_adjustments, &system_config.jets_goal, 25 },
	{ feature_adjustments, &system_config.num2chase, 2 },
	{ feature_adjustments, &system_config.num2comp_award, 10 },
	{ feature_adjustments, &system_config.num2video, 10 },
	{ feature_adjustments, &system_config.num2huxley, 2 },
	{ feature_adjustments, &system_config.num2demotime, 4 },
	{ feature_adjustments, &system_config.mb_ballsave, 10 },
	{ feature_adjustments, &system_config.mode_ballsave, 10 },
	{ feature_adjustments, &system_config.vm_level, 1 },
PRESET_END (easy, "EASY")



PRESET_BEGIN (hard)
	{ feature_adjustments, &system_config.eyeball_eb, 22 },
	{ feature_adjustments, &system_config.num2explode, 5 },
	{ feature_adjustments, &system_config.num2freeze, 7 },
	{ feature_adjustments, &system_config.jets_goal, 50 },
	{ feature_adjustments, &system_config.num2chase, 5 },
	{ feature_adjustments, &system_config.num2comp_award, 20 },
	{ feature_adjustments, &system_config.num2video, 20 },
	{ feature_adjustments, &system_config.num2huxley, 7 },
	{ feature_adjustments, &system_config.num2demotime, 8 },
	{ feature_adjustments, &system_config.mb_ballsave, 5 },
	{ feature_adjustments, &system_config.mode_ballsave, 5 },
	{ feature_adjustments, &system_config.vm_level, 3 },
PRESET_END (hard, "HARD")



PRESET_BEGIN (3ball)
	{ standard_adjustments, &system_config.balls_per_game, 3 },
PRESET_END (3ball, "3-BALL")


PRESET_BEGIN (5ball)
	{ standard_adjustments, &system_config.balls_per_game, 5 },
PRESET_END (5ball, "5-BALL")


PRESET_BEGIN (tournament)
	PRESET_FREE_PLAY
	{ standard_adjustments, &system_config.balls_per_game, 3 },
	{ standard_adjustments, &system_config.replay_award, FREE_AWARD_EB },
	{ standard_adjustments, &system_config.game_restart, GAME_RESTART_NEVER },
	{ standard_adjustments, &system_config.max_ebs, 0 },
	{ standard_adjustments, &system_config.tournament_mode, ON },
	{ standard_adjustments, &system_config.no_bonus_flips, NO },
PRESET_END (tournament, "TOURNAMENT")


PRESET_BEGIN (timed_game)
	{ standard_adjustments, &system_config.max_players, 1 },
PRESET_END (timed_game, "TIMED GAME")

/**
 * Regional presets
 *
 * The DIP switches on the CPU board can be used to select the current locale.
 * Each locale has a preset which contains defaults *which are different from
 * the ordinary, global defaults*.  These are installed automatically at
 * startup when a new setting is detected.
 */
PRESET_BEGIN (usa_canada)
//	{ standard_adjustments, &system_config.language, LANG_US_ENGLISH },
	{ standard_adjustments, &system_config.euro_digit_sep, NO },
	{ standard_adjustments, &system_config.clock_style, CLOCK_STYLE_AMPM },
	{ standard_adjustments, &system_config.date_style, DATE_STYLE_US },
PRESET_END (usa_canada, "USA/CANADA")


PRESET_BEGIN (eu)
	{ standard_adjustments, &system_config.euro_digit_sep, YES }, \
	{ standard_adjustments, &system_config.clock_style, CLOCK_STYLE_24HOUR }, \
	{ standard_adjustments, &system_config.date_style, DATE_STYLE_EURO },
	{ pricing_adjustments, &price_config.pricing_mode, PRICE_EURO },
PRESET_END (eu, "E.U.")

struct preset *preset_table[] = {
	&preset_easy,
	&preset_hard,
	&preset_3ball,
	&preset_5ball,
	&preset_eu,
	&preset_usa_canada,
	&preset_tournament,
//	&preset_timed_game,
};


U8 preset_count (void)
{
	return sizeof (preset_table) / sizeof (struct preset *);
}

void preset_install (struct preset_component *comps)
{
	/* Modify all of the adjustments affected by the preset */
	pinio_nvram_unlock ();
	while (comps->nvram != NULL)
	{
		*(comps->nvram) = comps->value;
		comps++;
	}
	pinio_nvram_lock ();

	/* Update the checksums to match the new values */
	adj_modified (NULL);
}


void preset_install_from_test (void)
{
	struct preset *pre = preset_table[menu_selection];
	preset_install (pre->comps);
}


/** Install the presets for a particular country.
 * The code is determined from the DIP switches. */
void preset_install_country_code (U8 code)
{
	dbprintf ("Installing preset for country code %d\n", code);
	switch (code)
	{
		case LC_USA_CANADA:
		case LC_USA_CANADA2:
			preset_install (preset_usa_canada_comps);
			break;

		case LC_FRANCE:
		case LC_FRANCE2:
		case LC_FRANCE3:
		case LC_FRANCE4:
			break;

		case LC_GERMANY:
			break;

		case LC_EXPORT_ENGLISH:
		case LC_EXPORT:
		case LC_UK:
		case LC_EUROPE:
			break;

		case LC_SPAIN:
			break;
	}
}


void preset_render_name (U8 index)
{
	sprintf ("%s", preset_table[index]->name);
}


/**
 * Returns true if a given preset is already installed.
 * This means that ALL of the items within the preset
 * are equal to their present values.
 */
bool preset_installed_p (U8 index)
{
	struct preset *pre = preset_table[index];
	struct preset_component *comps = pre->comps;

	while (comps->nvram != NULL)
	{
		if (*(comps->nvram) != comps->value)
			return FALSE;
		comps++;
	}
	return TRUE;
}


void preset_select (void)
{
	struct preset *pre = preset_table[menu_selection];
	preset_component_ptr = pre->comps;
}


#if (MACHINE_DMD == 1)
void preset_draw_component (void)
{
	struct adjustment *info;

	if (!preset_component_ptr || !preset_component_ptr->nvram)
		return;

	info = preset_component_ptr->info;
	if (!info)
		return;

	/* WARNING - you cannot make a farcall when some of the args
	 * are on the stack!  The called function sees the saved
	 * value of the page instead of the args.  This has to be
	 * fixed in the compiler itself.
	 * So for now, we split into two function calls... */
	adj_prepare_lookup (info);
	adj_name_for_preset (preset_component_ptr->nvram, preset_component_ptr->value);

	if (*preset_component_ptr->nvram == preset_component_ptr->value)
	{
		dmd_rough_invert (0, 18, 128, 5);
	}

	preset_component_ptr++;
	if (preset_component_ptr->nvram == NULL)
		preset_select ();
}
#endif

