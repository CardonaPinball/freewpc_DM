/*
 * demolition man
 * standupfrenzy.c
 * 
 * written by James Cardona - based loosely on greed mode from TZ code
 *
 * Location Description:
 * Standups: There are 5 yellow standup targets scattered about the playfield,
 * like those in TZ. However, these targets are very important to game play.
 * One is located directly below the upper left flipper; another is to the
 * right of the left ramp; two more are angled to the left of the right ramp;
 * and one is to the right of the right ramp.
 *
 * Scoring Description: (original game)
 * These are similar to Twilight Zone's Greed targets.
 * They are worth 1 million plus 1 million per number of hits
 * (resets on each ball). Maximum of 20 hits.
 *
 * Depending on machine settings, One, Two, or Three sets of
 * targets must be completed to light Quick Freeze, depending on
 * whether Quick Freeze is set to easy, medium, or hard.
 *
 * an unlit target scores nothing
 * once all 5 hit - they extinguish and all 5 relight
 *
 * Scoring Description: (my rules)
 * same as above except
 * in frenzy mode worth 5 million plus 1 million per number of hits
 * no max number of hits - 20 second timer
 * outside frenzy worth 500k points
 *
 *
 * estimate of average standupfrenzy mode score: 21 million to 56 million
 * estimate of average standup score: 2.5 million
 *
 *
 * */
/* CALLSET_SECTION (standupfrenzy, __machine__) */

#include <freewpc.h>
#include "dm/global_constants.h"
#include "clawmagnet.h"
#include "standupfrenzy.h"
#include "shaker.h"
#include "ballsave.h"


//constants
#define 	NO_TARGETS 	0x0/** Bitmask referring to all 5 standup targets */
#define 	ALL_TARGETS 0x1F/** Bitmask referring to all 5 standup targets */
#define			STANDUP_EASY_GOAL 	 1
#define 		STANDUP_HARD_GOAL 	 7
#define			STANDUP_GOAL_INCREMENT  5
#define			STANDUP_HARD_GOAL_INCREMENT  10
#define			STANDUP_GOAL_MAX 	 100


//local variables
U8			standup_MessageCounter;
U8			standupFrenzy_temp_counter;//generic counter
U8			standupFrenzy_SoundCounter = 0;//used for randomizing sound calls
U8			standup_SoundCounter = 0;//used for randomizing sound calls
U8 			standupFrenzyTimer;
U8 			standupFrenzyLightsLit; //tracks which LIGHTS ARE LIT
U8 			standupLightsLit; 		//tracks which LIGHTS ARE LIT
score_t 	standupFrenzy_temp_score;//generic score for calculations
score_t 			standupFrenzyTotalScore;
score_t 			standupFrenzyLastScore;
score_t 			standupFrenzyNextScore;
__boolean	rumbler;
__local__ 	U8 		standupFrenzyNumHits; //needed for bonus - kept for game - not reset each mode restart
__local__ 	U8 		standup_num_of_hits; //needed for tracking of relight freeze
__local__ 	U8 		standup_goal;		//needed for tracking of relight freeze
U8			exploded[5];

//external variables

//internally called function prototypes  --external found at protos.h
void standupFrenzy_mode_init (void);
void standupFrenzy_mode_exit (void);
void standupHandler (U8 target);
void standupHandler1 (U8 target);
void frenzyHandler (U8 target);
void standup_lamp_update1 (U8 mask);
void standupFrenzy_sounds (void);
void standup_sounds (void);
void lamp_update (void);
void start_rumbler(void);


/****************************************************************************
 * mode definition structure
 ***************************************************************************/
struct timed_mode_ops standupFrenzy_mode = {
	DEFAULT_MODE,
	.init = standupFrenzy_mode_init,
	.exit = standupFrenzy_mode_exit,
	.gid = GID_STANDUPFRENZY_MODE_RUNNING,
	.music = MUS_MD_STANDUP_FRENZY,
	.deff_starting = DEFF_STANDUPFRENZY_START_EFFECT,
	.deff_running = DEFF_STANDUPFRENZY_EFFECT,
//	.deff_ending = DEFF_STANDUPFRENZY_END_EFFECT,
	.prio = PRI_GAME_MODE5,
	.init_timer = 48, //time displayed plus length of starting deff
	.timer = &standupFrenzyTimer,
	.grace_timer = 3, //default is 2
	//.pause = , // default is null_false_function - other is system_timer_pause,
};


/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
void standupFrenzy_mode_init (void) {
		//the claw mode can expire on its own and since it is a lower priority it will not display
		//callset_invoke (end_claw_mode); // this seemed to cause occasional crashes
		clawmagnet_off ();
		global_flag_off(GLOBAL_FLAG_IS_BALL_ON_CLAW);
		flipper_enable ();
		ballsave_add_time (system_config.mode_ballsave);
		lamp_tristate_flash(LM_CLAW_FREEZE);
		task_sleep(TIME_500MS);
		lamp_tristate_on(LM_CLAW_FREEZE);
	standupFrenzyLightsLit = ALL_TARGETS;
	lamp_update ();
	//reset counter if first time run, otherwise do not - player may restart acmag while currently running
	if (! get_dm_mode(FRENZY_COMPLETED) ) {
		score_zero (standupFrenzyTotalScore);
		score_zero (standupFrenzyLastScore);
		score_zero (standupFrenzyNextScore);
	}
	score_add (standupFrenzyNextScore, score_table[FRENZY_HIT_SCORE]);
	score_add (standupFrenzyTotalScore, score_table[FRENZY_START_SCORE]);
	score (FRENZY_START_SCORE);

	set_dm_mode(FRENZY_COMPLETED); //for next time
	U8 i;
	for (i = 0; i < 5; i++) exploded[i] = 0;
	if(!rumbler) start_rumbler();
}//end of standupFrenzy_mode_init 



void standupFrenzy_mode_exit (void) {
	/* Light all 'default' lamps */
	task_sleep (TIME_100MS);
	standupLightsLit  = ALL_TARGETS;
	lamp_update ();
	rumbler = FALSE;
}//end of standupFrenzy_mode_exit 



CALLSET_ENTRY (standupFrenzy, start_ball) {
	/* Light all 'default' lamps */
	standupFrenzyLightsLit = NO_TARGETS;
	standupLightsLit  = ALL_TARGETS;
	lamp_update ();

	if (get_dm_mode(FRENZY_COMPLETED) ) 	lamp_tristate_on (LM_CLAW_FREEZE);
	else 									lamp_tristate_off (LM_CLAW_FREEZE);
	rumbler = FALSE;
}//end of function




CALLSET_ENTRY (standupFrenzy, start_player) {
	standup_MessageCounter = 0;
	standupFrenzyNumHits = 0;
	standup_num_of_hits = 0;

#ifdef CONFIG_DIFFICULTY_LEVEL
	standup_goal = system_config.num2freeze;
#elif
	standup_goal = STANDUP_EASY_GOAL;
#endif
}//end of function


/****************************************************************************
 * external event listeners
 ****************************************************************************/
CALLSET_ENTRY (standupFrenzy, music_refresh)  	{ if (in_game) timed_mode_music_refresh (&standupFrenzy_mode); }
CALLSET_ENTRY (standupFrenzy, end_ball, tilt) 	{ if (timed_mode_running_p(&standupFrenzy_mode) ) timed_mode_end (&standupFrenzy_mode); }
CALLSET_ENTRY (standupFrenzy, display_update) 	{ if (in_game && !flag_test(FLAG_VIDEO_MODE_RUNNING) )	 timed_mode_display_update (&standupFrenzy_mode); }




/****************************************************************************
 * standup target hit
 ****************************************************************************/
bool is_frenzy_running (void) {
	return timed_mode_running_p (&standupFrenzy_mode);
}//end of function




/* declare event listeners for standup target hits*/
/* target is given as a bitmask to cover all the switches*/
CALLSET_ENTRY (standupFrenzy, sw_standup_1) { standupHandler(0x1); }
CALLSET_ENTRY (standupFrenzy, sw_standup_2) { standupHandler(0x2); }
CALLSET_ENTRY (standupFrenzy, sw_standup_3) { standupHandler(0x4); }
CALLSET_ENTRY (standupFrenzy, sw_standup_4) { standupHandler(0x8); }
CALLSET_ENTRY (standupFrenzy, sw_standup_5) { standupHandler(0x10); }







void standupHandler (U8 target) {
	if (in_game && !in_tilt) {
			//verify target hit was a lit target and verify mode is running
			if ((standupFrenzyLightsLit & target) && timed_mode_running_p(&standupFrenzy_mode)) frenzyHandler (target);

			//else SF not running ---verify target hit was a lit target
			else if ((standupLightsLit & target) && !timed_mode_running_p(&standupFrenzy_mode)) standupHandler1 (target);
			//otherwise - do nothing since an unlit target was hit

			//check for other modes
			if (is_huxley_running () )					huxley_mode_shot_made();
			if (is_prison_break_running () ) 	prison_break_made();
	}//end of 	if (in_game && !in_tilt)
}//end of standupHandler



void update_exploded (U8 target){
	switch (target) {
			case 0x1:  exploded[0]++; break;
			case 0x2:  exploded[1]++; break;
			case 0x4:  exploded[2]++; break;
			case 0x8:  exploded[3]++; break;
			case 0x10: exploded[4]++; break;
	}//end of switch
}//end of function







//if we are here then a lit target was just hit and we are in frenzy mode
void frenzyHandler (U8 target) {
		++standupFrenzyNumHits;
		sound_send (EXPLOSION1_LONG);
		//lighting effects for appripriate standup hit
		switch (target) { //these cases are in decimal equivalent to hex/binary
			case 1:	leff_start (LEFF_FRENZY1); break;
			case 2:	leff_start (LEFF_FRENZY2); break;
			case 4:	leff_start (LEFF_FRENZY3); break;
			case 8:	leff_start (LEFF_FRENZY4); break;
			default:
			case 16: leff_start (LEFF_FRENZY5); break;
		}

		update_exploded(target); //this triggers explosion in display
		standupFrenzyLightsLit &= ~target;  // flag that target as hit
		standup_lamp_update1 (target);//turn that lamp off
		standupFrenzy_sounds();

		//score 5 million plus 1 million times number of hits
		score_zero (standupFrenzy_temp_score);//zero out temp score
		score_add (standupFrenzy_temp_score, score_table[FRENZY_ADD_SCORE]);//multiply 1M by num hits
		score_mul (standupFrenzy_temp_score, standupFrenzyNumHits);
		score (FRENZY_HIT_SCORE);
		score_long_unmultiplied (standupFrenzy_temp_score); //add temp score to player's score

		//do same for mode score
		score_add (standupFrenzyTotalScore, score_table[FRENZY_HIT_SCORE]);
		score_add (standupFrenzyTotalScore, standupFrenzy_temp_score);

		//do same for last score-this is the one we display
			score_zero (standupFrenzyLastScore);
			score_add (standupFrenzyLastScore, score_table[FRENZY_HIT_SCORE]);
			score_add (standupFrenzyLastScore, standupFrenzy_temp_score);

		//do same for next score-this is the one we display
		score_zero (standupFrenzyNextScore);
		score_add (standupFrenzyNextScore, score_table[FRENZY_HIT_SCORE]);
		score_add (standupFrenzyNextScore, standupFrenzy_temp_score);
		score_add (standupFrenzyNextScore, score_table[FRENZY_ADD_SCORE]);//next score will be 1 million more

		//if 5th light out then reset all lights back on
		if (standupFrenzyNumHits % 5 == 0) 	{
			standupFrenzyLightsLit = ALL_TARGETS;
			lamp_update ();
			U8 i;
			for (i = 0; i < 5; i++) exploded[i] = 0; //RESET DEFF DISPLAY
		}
}//end of function







//if we are here then a lit target was just hit and we are not in frenzy mode
void standupHandler1 (U8 target) {
		++standup_num_of_hits;
		standupLightsLit &= ~target;  /* flag that target as hit */
		standup_lamp_update1 (target);

		if (is_prison_break_running () ) 		prison_break_made();
		else 											standup_sounds();

		score (STANDUP_SCORE);
		//if we reached our quick freeze goal and quick freeze is not already set
		if (standup_num_of_hits >= standup_goal) {
				increment_light_quick_freeze_light();//sent to inlanes.c
				#ifdef CONFIG_DIFFICULTY_LEVEL
					standup_goal += system_config.num2freeze;
;
				#elif
					standup_goal += STANDUP_GOAL_INCREMENT;
				#endif
			}
		deff_start (DEFF_STANDUP_EFFECT);
		//if 5th light out then reset all lights back on
		if (standup_num_of_hits % 5 == 0) 	{
			standupLightsLit = ALL_TARGETS;
			lamp_update ();
		}
}//end of function




/****************************************************************************
 * stand up lamps update
 ****************************************************************************/
void standup_lamp_update1 (U8 mask) {
	if (is_frenzy_running () )	{
			//target was not hit yet, flash it
			if (standupFrenzyLightsLit & mask)
				switch (mask) {
					case 1 : lamp_tristate_flash (LM_STANDUP_1); break;
					case 2 : lamp_tristate_flash (LM_STANDUP_2); break;
					case 4 : lamp_tristate_flash (LM_STANDUP_3); break;
					case 8 : lamp_tristate_flash (LM_STANDUP_4); break;
					case 16 : lamp_tristate_flash (LM_STANDUP_5); break;
				}//end of switch
			else
				switch (mask) {
					case 1 : lamp_tristate_off (LM_STANDUP_1); break;
					case 2 : lamp_tristate_off (LM_STANDUP_2); break;
					case 4 : lamp_tristate_off (LM_STANDUP_3); break;
					case 8 : lamp_tristate_off (LM_STANDUP_4); break;
					case 16 : lamp_tristate_off (LM_STANDUP_5); break;
				}//end of switch
	}//end of if
	else { //mode not running
		//target was not hit yet so it is on
		if (standupLightsLit & mask)
			switch (mask) {
				case 1 : lamp_tristate_on (LM_STANDUP_1); break;
				case 2 : lamp_tristate_on (LM_STANDUP_2); break;
				case 4 : lamp_tristate_on (LM_STANDUP_3); break;
				case 8 : lamp_tristate_on (LM_STANDUP_4); break;
				case 16 : lamp_tristate_on (LM_STANDUP_5); break;
			}//end of switch
	else
			switch (mask) {
				case 1 : lamp_tristate_off (LM_STANDUP_1); break;
				case 2 : lamp_tristate_off (LM_STANDUP_2); break;
				case 4 : lamp_tristate_off (LM_STANDUP_3); break;
				case 8 : lamp_tristate_off (LM_STANDUP_4); break;
				case 16 : lamp_tristate_off (LM_STANDUP_5); break;
			}//end of switch

	}//end of else
}//end of standup_lamp_update1


//this mainly called to reset all the lights to on during startup, mode change or hitting the 5th target
void lamp_update (void) {
	standup_lamp_update1 (0x1);
	standup_lamp_update1 (0x2);
	standup_lamp_update1 (0x4);
	standup_lamp_update1 (0x8);
	standup_lamp_update1 (0x10);//16 in hex
}//end of lamp_update 


//claw freeze starts standup frenzy instead of locking a ball
CALLSET_ENTRY (standupFrenzy, sw_claw_freeze) {
	if (in_game && !in_tilt) {
			demotime_increment();
			timed_mode_begin (&standupFrenzy_mode);

	}//end of 	if (in_game && !in_tilt)
}//end of function





/****************************************************************************
 *
 * sound effects
 *
 ****************************************************************************/
void standup_sounds (void) {
	standup_SoundCounter = random_scaled(3);//from kernal/random.c
	if ( standup_SoundCounter  == 0 )
			sound_start (ST_EFFECT, ZAPP_3_SHORT, SL_2S, PRI_GAME_QUICK2);
	else if ( standup_SoundCounter  == 1 )
			sound_start (ST_EFFECT, ZAPP_3_MED, SL_2S, PRI_GAME_QUICK2);
	else if ( standup_SoundCounter  == 2 )
			sound_start (ST_EFFECT, ZAPP_3_LONG, SL_2S, PRI_GAME_QUICK2);
}//end of function



void standupFrenzy_sounds (void) {
	standupFrenzy_SoundCounter = random_scaled(3);//from kernal/random.c
	if ( standupFrenzy_SoundCounter  == 0 )
			sound_start (ST_EFFECT, CHORD1, SL_2S, PRI_GAME_QUICK2);
	else if ( standupFrenzy_SoundCounter  == 1 )
			sound_start (ST_EFFECT, CHORD2, SL_2S, PRI_GAME_QUICK2);
	else if ( standupFrenzy_SoundCounter  == 2 )
			sound_start (ST_EFFECT, CHORD3, SL_2S, PRI_GAME_QUICK2);
}//end of function






/****************************************************************************
 *
 * display effects -- frenzy mode only
 *
 ****************************************************************************/
void standupfrenzy_start_effect_deff (void) {
	U8 x;
	U8 y;
	U8 i = 0;
	sound_send (EXPLOSION1_SHORT);
	do { // Shake the text
			dmd_alloc_pair_clean ();
			dmd_draw_thin_border (dmd_low_buffer);
			if 		(i < 5) { 	 x = random_scaled (1); y = random_scaled (2);}
			else if (i < 10) {   x = random_scaled (2); y = random_scaled (3);}
			else if (i < 15) {   x = random_scaled (5); y = random_scaled (5);}
			else 			 {  x = random_scaled (10); y = random_scaled (5);}
					if 		(i % 4 == 0)  	font_render_string_center (&font_halobold14, DMD_MIDDLE_X + x, DMD_BIG_CY_Cent + y, "FRENZY");
					else if (i % 4 == 1)  	font_render_string_center (&font_halobold14, DMD_MIDDLE_X - x, DMD_BIG_CY_Cent - y, "FRENZY");
					else if (i % 4 == 2)	font_render_string_center (&font_halobold14, DMD_MIDDLE_X - x, DMD_BIG_CY_Cent + y, "FRENZY");
					else if (i % 4 == 3)	font_render_string_center (&font_halobold14, DMD_MIDDLE_X + x, DMD_BIG_CY_Cent - y, "FRENZY");
			dmd_show_low ();
			if (i == 0) sound_send (EXPLOSION1_SHORT);
			if (i == 10) sound_send (EXPLOSION1_SHORT);
			if (i == 18) sound_send (EXPLOSION1_SHORT);
			if (i == 24) sound_send (EXPLOSION1_SHORT);
			if (i == 28) sound_send (EXPLOSION1_MED);

			if (system_config.disable_shaker == NO  && i % 12 == 0) {
				if (system_config.extra_shaker == YES) 	shaker_start (SHAKER_HALF_ON, 2);
				else									shaker_start (SHAKER_ONE_QUARTER_ON, 2);
			}//end of shaker call

			task_sleep (TIME_66MS);
	} while (i++ < 30); //APPROX 2 SEC
	//pulsate words in middle
	sound_send (EXPLOSION1_LONG);
	i = 4;
	dmd_alloc_pair_clean ();
	dmd_draw_thin_border (dmd_low_buffer);
		font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_BIG_CY_Cent, "FRENZY");
	// low = text, high = blank
	while (--i > 0){
		dmd_show2 ();
		task_sleep (TIME_66MS);

		dmd_flip_low_high ();
		dmd_show2 ();
		task_sleep (TIME_66MS);

		dmd_show_high ();
		task_sleep (TIME_66MS);

		dmd_show2 ();
		task_sleep (TIME_66MS);
		dmd_flip_low_high ();

		if (system_config.disable_shaker == NO) {
			if (system_config.extra_shaker == YES) 	shaker_start (SHAKER_HALF_ON, 2);
			else									shaker_start (SHAKER_ONE_QUARTER_ON, 2);
		}//end of shaker call

	}//end of loop - APPROX 1 SEC
	deff_exit (); //TOTAL OF 3 SEC
} // standupFrenzyTotalScore_deff



void standupfrenzy_show_circle_1_rotate_cw (U8 step, U8 x, U8 y) {
	switch (step) {
	case 0:	bitmap_blit (circle1_1_low_bits, x, y);	break;
	case 1:	bitmap_blit (circle1_2_low_bits, x, y);	break;
	case 2:	bitmap_blit (circle1_3_low_bits, x, y);	break;
	case 3:	bitmap_blit (circle1_4_low_bits, x, y);	break;
	case 4:	bitmap_blit (circle1_5_low_bits, x, y);	break;
	case 5:	bitmap_blit (circle1_6_low_bits, x, y);	break;
	case 6:	bitmap_blit (circle1_7_low_bits, x, y);	break;
	case 7:	bitmap_blit (circle1_8_low_bits, x, y);	break;
	}//end of switch
}//end of function

void standupfrenzy_show_circle_1_rotate_ccw (U8 step, U8 x, U8 y) {
	switch (step) {
	case 0:	bitmap_blit (circle1_8_low_bits, x, y);	break;
	case 1:	bitmap_blit (circle1_7_low_bits, x, y);	break;
	case 2:	bitmap_blit (circle1_6_low_bits, x, y);	break;
	case 3:	bitmap_blit (circle1_5_low_bits, x, y);	break;
	case 4:	bitmap_blit (circle1_4_low_bits, x, y);	break;
	case 5:	bitmap_blit (circle1_3_low_bits, x, y);	break;
	case 6:	bitmap_blit (circle1_2_low_bits, x, y);	break;
	case 7:	bitmap_blit (circle1_1_low_bits, x, y);	break;
	}//end of switch
}//end of function

void standupfrenzy_show_circle_2_rotate_cw (U8 step, U8 x, U8 y) {
	switch (step) {
	case 0:	bitmap_blit (circle2_1_low_bits, x, y);	break;
	case 1:	bitmap_blit (circle2_2_low_bits, x, y);	break;
	case 2:	bitmap_blit (circle2_3_low_bits, x, y);	break;
	case 3:	bitmap_blit (circle2_4_low_bits, x, y);	break;
	case 4:	bitmap_blit (circle2_5_low_bits, x, y);	break;
	case 5:	bitmap_blit (circle2_6_low_bits, x, y);	break;
	case 6:	bitmap_blit (circle2_7_low_bits, x, y);	break;
	case 7:	bitmap_blit (circle2_8_low_bits, x, y);	break;
	}//end of switch
}//end of function

void standupfrenzy_show_circle_2_rotate_ccw (U8 step, U8 x, U8 y) {
	switch (step) {
	case 0:	bitmap_blit (circle2_8_low_bits, x, y);	break;
	case 1:	bitmap_blit (circle2_7_low_bits, x, y);	break;
	case 2:	bitmap_blit (circle2_6_low_bits, x, y);	break;
	case 3:	bitmap_blit (circle2_5_low_bits, x, y);	break;
	case 4:	bitmap_blit (circle2_4_low_bits, x, y);	break;
	case 5:	bitmap_blit (circle2_3_low_bits, x, y);	break;
	case 6:	bitmap_blit (circle2_2_low_bits, x, y);	break;
	case 7:	bitmap_blit (circle2_1_low_bits, x, y);	break;
	}//end of switch
}//end of function

void standupfrenzy_show_rotate_exploded (U8 step, U8 x, U8 y) {
	switch (step) {
	case 0:	bitmap_blit (explos1_1_low_bits, x, y);	break;
	case 1:	bitmap_blit (explos1_2_low_bits, x, y);	break;
	case 2:	bitmap_blit (explos1_3_low_bits, x, y);	break;
	case 3:	bitmap_blit (explos1_4_low_bits, x, y);	break;
	case 4:	bitmap_blit (explos1_5_low_bits, x, y);	break;
	case 5:	bitmap_blit (explos1_6_low_bits, x, y);	break;
	case 6:	bitmap_blit (explos1_7_low_bits, x, y);	break;
	case 7:	break;
	}//end of switch
}//end of function





//shake table for duration of mode regardless if frenzy DMD display is on screen
void start_rumbler(void){
	rumbler = TRUE;

	while (rumbler) {
		task_sleep (TIME_2S);

		if (system_config.disable_shaker == NO) {
			if (system_config.extra_shaker == YES) 	shaker_start (SHAKER_HALF_ON, 2);
			else									shaker_start (SHAKER_ONE_QUARTER_ON, 2);
		}//end of shaker call
	}
}//end of function





void standupfrenzy_effect_deff (void) {
	U8 i = 0;
	U8 toggle = 0;
	for (;;) {
		i++;
		//for testing only
		if (DM_IN_DMD_TEST) {
			if (i == 30) {exploded[0]++;}
			if (i == 50) {exploded[1]++;}
			if (i == 70) {exploded[2]++;}
			if (i == 90) {exploded[3]++;}
			if (i == 110) {exploded[4]++;}
		}
		//end of testing only

		dmd_alloc_low_clean ();
		dmd_draw_thin_border (dmd_low_buffer);

		if (ballsave_test_active()) {
			sprintf ("%d BALL SAVE", ballsave_get_timer());
		}
		else {
			if (i % 40 == 0) {
				if (++toggle >= 2) toggle = 0;//change TOGGLE once per (i % 40 x sleep_time) seconds, if sleep_time = 100ms then it is 4 secs
			}
			if (toggle == 1) 		sprintf ("%d SEC LEFT", standupFrenzyTimer);
			else 					sprintf ("SHOOT STANDUP TARGETS");
			//			else if (toggle == 2)	sprintf ("%d HIT", standupFrenzyNumHits);
		}
		font_render_string_center (&font_var5, DMD_MIDDLE_X, DMD_SMALL_CY_1, sprintf_buffer);

		//if the standup target has been hit then display the exploded target
		if (exploded[0] && exploded[0] < 10) 	standupfrenzy_show_rotate_exploded( exploded[0]++, 2, 8);
		//if the standup target has NOT been hit then display the rotating target
		else if (!exploded[0] )					standupfrenzy_show_circle_2_rotate_ccw 	( (i)%8, 	2, 8);

		if (exploded[1] && exploded[1] < 10) 	standupfrenzy_show_rotate_exploded( exploded[1]++, 27, 8);
		else  if (!exploded[1] )				standupfrenzy_show_circle_1_rotate_cw 	( (i+3)%8, 27, 8); //increment i in a different manner so all circles look different

		if (exploded[2] && exploded[2] < 10) 	standupfrenzy_show_rotate_exploded( exploded[2]++, 52, 8);
		else  if (!exploded[2] )				standupfrenzy_show_circle_1_rotate_ccw 	( (i+1)%8, 52, 8);

		if (exploded[3] && exploded[3] < 10) 	standupfrenzy_show_rotate_exploded( exploded[3]++, 77, 8);
		else  if (!exploded[3] )				standupfrenzy_show_circle_2_rotate_cw 	( (i+5)%8, 77, 8);

		if (exploded[4] && exploded[4] < 10) 	standupfrenzy_show_rotate_exploded( exploded[4]++, 102, 8);
		else  if (!exploded[4] )				standupfrenzy_show_circle_1_rotate_ccw 	( (i+1)%8,102, 8);
		dmd_show_low ();
		task_sleep (TIME_100MS);
	}//END OF ENDLESS LOOP
}//end of standupFrenzy_mode_deff






/****************************************************************************
 *
 * DMD display - non-frenzy
 *
 ****************************************************************************/
void standup_effect_deff (void) {
	if (DM_IN_DMD_TEST) {	if (++standup_MessageCounter > 2) standup_MessageCounter = 0; standup_num_of_hits+=3; }
	else			standup_MessageCounter = random_scaled(3);

	dmd_map_overlay ();
	dmd_clean_page_low ();
	switch (standup_MessageCounter) {
		default:
		case 0:
			sprintf ("%d ", standup_num_of_hits);
				font_render_string_left (&font_halobold12, 15, DMD_BIG_CY_Top - 5, sprintf_buffer);
				font_render_string_left (&font_halobold12, 7, DMD_BIG_CY_Bot - 4, "TARGETS");
			break;
		case 1:
			if (!flag_test(FLAG_IS_LRAMP_QUICKFREEZE_ACTIVATED)) {
				sprintf ("HIT %d MORE", standup_goal - standup_num_of_hits);
				font_render_string_right (&font_term6, 95, DMD_MED_CY_1 - 4, sprintf_buffer);
				font_render_string_right (&font_var5, 102, DMD_SMALL_CY_3 - 4, "TO LIGHT");
					font_render_string_right (&font_halobold12, 80, DMD_MED_CY_BOTTOM_LINE - 4, "FREEZE");
			}
			else {
					font_render_string_right (&font_halobold14, 95, DMD_BIG_CY_Top - 7, "FREEZE");
					font_render_string_right (&font_halobold12, 99, DMD_BIG_CY_Bot - 7, "ACTIVE");
			}
			break;
		case 2:
			font_render_string_right (&font_term6, 95, DMD_MED_CY_1 - 4, "CLAW FREEZE");
			font_render_string_right (&font_var5, 102, DMD_SMALL_CY_3 - 4, "STARTS");
				font_render_string_right (&font_halobold12, 95, DMD_MED_CY_BOTTOM_LINE - 4, "FRENZY");
			break;
		}//end of switch
	dmd_text_outline ();
	dmd_alloc_pair ();
	switch (random_scaled (4) ) {
		default:
		case 0:
			frame_draw(IMG_STANDUPS_0);
			break;
		case 1:
			frame_draw(IMG_STANDUPS_1);
			break;
		case 2:
			frame_draw(IMG_STANDUPS_2);
			break;
		case 3:
			frame_draw(IMG_STANDUPS_3);
			break;
		}//end of switch
	dmd_overlay_outline ();
	dmd_show2 ();
	task_sleep (TIME_2S);
	deff_exit ();
}//end of standupFrenzy_mode_deff



