/*
 * demolition man
 * simple_swithces.c
 *
 * written by James Cardona
 * 
 * Location Description:
 * Upper Rebound : This is a three inch piece of rubber forming the left wall of
 * the Center Ramp that is stretched across a switch ... hitting the rubber
 * activates the switch, just like the left and right 110 switches on Whirlwind.
 *
 * Right Rebound : This is a three inch piece of rubber on the right side
 * of the playfield, just above the right outlane. Just like the Upper Rebound,
 * it is rubber stretched across a switch.
 *
 *
 * Scoring Description: (original game)
 * rebounds score 1010
 * slings score 1000
 *
 * Scoring Description: (my rules)
 * same as original
 *
 * */

#include <freewpc.h>
#include "ngg/global_constants.h" 
#include "search.h"


//constants
const sound_code_t outlaneSoundArray[] = {	SPCH_TOO_BAD, 				SPCH_PATHETIC,			SPCH_HATE_WHEN_THAT_HAPPENS,
											SPCH_OHH_NO,				SPCH_BAD_AIM,			SPCH_DULCH,
											SPCH_WES_LAUGH_SHORT1, 		SPCH_SIMON_SNICKER, 	SPCH_WES_LAUGH_SHORT2,
											SPCH_WES_LAUGH_SHORT3,		SPCH_JUST_LOVELY,
											//extra sounds
											SPCH_CHOW_SLY,
											SPCH_ISNT_PINBALL_DRAINING_SIMON,
											SPCH_TAKE_THIS_JOB_N_SHOVE_IT_SNDRA,
											SPCH_AT_LEAST_THERES_PINBALL_SLY,
											SPCH_EHH_DISGUSTING_SNDRA,
											SPCH_DONT_BE_A_WIMP_SLY,
											SPCH_THIS_IS_TOO_LONG_SIMON,
											//swear roms
											SPCH_PLAY_AGAIN_GIRL,
											SPCH_PLAY_W_ME_AGAIN_GIRL,
											SPCH_VLGR_OH_SHT_NO_SIMON,
											SPCH_VLGR_OHH_HELL_SLY,
											SPCH_VLGR_SHT_SIMON,
											SPCH_VLGR_AHH_SHT_SIMON
};

//local variables

//external variables

//prototypes
void simple_sounds(void);

/****************************************************************************
 * body
 *
 ****************************************************************************/
CALLSET_ENTRY (simple_switches, sw_right_outlane, sw_left_outlane) {
	if (in_game && !in_tilt) {
			score(OUTLANE_SCORE);
			U8		SoundChooser;

			if (system_config.swear_sounds == YES) {
				//this doubles the chance that a swear would occur
				SoundChooser = random_scaled(32);
				if (SoundChooser >= 25) SoundChooser -= 7;
			}
			else if (system_config.extra_sounds == YES) SoundChooser = random_scaled(18);
			else 										SoundChooser = random_scaled(11);

			sound_start (ST_SPEECH, outlaneSoundArray[SoundChooser], SL_4S, PRI_GAME_QUICK5);
	}//end of 	if (in_game && !in_tilt)
}//end of function






CALLSET_ENTRY (simple_switches, sw_upper_left_flipper_gate, sw_upper_rebound) {
	if (in_game && !in_tilt) {
			if (is_huxley_running ()  )					huxley_mode_shot_made();
			if (is_prison_break_running () )  			prison_break_made();
			else {
				score(SIMPLE_SWITCH);
				simple_sounds();
			}
	}//end of 	if (in_game && !in_tilt)
}//end of function






CALLSET_ENTRY (simple_switches, sw_lower_rebound) {
	if (in_game && !in_tilt) {
			leff_start (LEFF_LOWER_REBOUND);
			if (is_huxley_running ()  )		huxley_mode_shot_made();

			if (is_prison_break_running () ) prison_break_made();
			else {
					simple_sounds();
					score(SIMPLE_SWITCH);
				}//end of else

	}//end of 	if (in_game && !in_tilt)
}//end of function



CALLSET_ENTRY (simple_switches, sw_sling) {
	if (in_game && !in_tilt) {
		score(SLING_SCORE);
		simple_sounds();
	}
}//end of function






/****************************************************************************
 * sound effects
 ****************************************************************************/
void simple_sounds (void) {
	U8		simple_SoundCounter;
	simple_SoundCounter = random_scaled(4);//from kernal/random.c
	if ( simple_SoundCounter == 0 )			sound_start (ST_EFFECT, ZAPP_1, SL_2S, PRI_GAME_QUICK5);
	else if ( simple_SoundCounter == 1 )	sound_start (ST_EFFECT, JOINK, SL_2S, PRI_GAME_QUICK5);
	else if ( simple_SoundCounter == 2 )	sound_start (ST_EFFECT, JOINK_2, SL_2S, PRI_GAME_QUICK5);
	else if ( simple_SoundCounter == 3 )	sound_start (ST_EFFECT, ZAPP_2, SL_2S, PRI_GAME_QUICK5);
}//end of function

