/*
 * demolition man
 * orbits.c
 *
 * written by James Cardona
 *
 * Location Description:
 * Also called loops.
 * Left Loop: This loop is just to the right of the upper flipper.
 * It feeds to a sinkhole when hit hard enough; otherwise, the ball passes
 * behind the top ramp into the MTL rollovers or can pass all the way to
 * the right loop -making a complete orbit.
 * This shot can be lit to start multiball and award extra balls, otherwise it
 * awards a mystery bonus.
 * Lights are, from bottom up, Extra Ball, Start Multi-Ball, Explode, Jackpot, Combo arrow.
 *
 * Right Loop: This shot feeds the ball past the MTL rollovers and all
 * the way around to the upper left flipper. If it doesn't make it
 * (ie: weak shot) the ball will fall into the MTL rollovers.
 * Lights are, from bottom up, Explode, Jackpot, Combo Arrow.
 *
 * Scoring Description: (original game)
 *
 * depending upon # of freeze required, shoot left loop will start MB with X num of balls,
 * ends when 1 ball left if shoot light freeze from claw will grant instant 5 ball MB
 * if at least 1 ball already frozen, else will light a ball
 * and shoot left loop to start MB
 *
 */

#include <freewpc.h>
#include "dm/global_constants.h"

//constants

//local variables
U8		orbits_SoundCounter;

//external variables

//prototypes
void left_orbit_task (void);
void right_orbit_task (void);
void left_orbit_shot_made(void);
void right_orbit_shot_made(void);
void eb_mb_lights_task (void);

/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
CALLSET_ENTRY (orbits, start_ball) {
	if (flag_test(FLAG_IS_EXTRABALL_LIT)) lamp_tristate_on (LM_EXTRA_BALL); else lamp_tristate_off (LM_EXTRA_BALL);
//	if (flag_test(FLAG_IS_MULTIBALL_ENABLED)) lamp_tristate_on (LM_START_MULTIBALL); //done at lock freeze

//	if (flag_test(FLAG_IS_EXTRABALL_LIT) || flag_test(FLAG_IS_MULTIBALL_ENABLED) )
//		leff_start (LEFF_ORBITS_RUNNER);

	lamp_tristate_off (LM_LEFT_LOOP_EXPLODE);
	lamp_tristate_off (LM_RIGHT_LOOP_EXPLODE);
	lamp_tristate_off (LM_LEFT_LOOP_JACKPOT);
	lamp_tristate_off (LM_RIGHT_LOOP_JACKPOT);
}//end of function



CALLSET_ENTRY (orbits, start_player) {
	orbits_SoundCounter = 0;
	flag_off(FLAG_IS_MULTIBALL_ENABLED);
	flag_off(FLAG_IS_EXTRABALL_LIT);
}//end of function






CALLSET_ENTRY (orbits, end_ball) {
	leff_stop (LEFF_ORBITS_RUNNER);
	lamp_tristate_off (LM_LEFT_LOOP_EXPLODE);
	lamp_tristate_off (LM_RIGHT_LOOP_EXPLODE);
	lamp_tristate_off (LM_LEFT_LOOP_JACKPOT);
	lamp_tristate_off (LM_RIGHT_LOOP_JACKPOT);
	lamp_tristate_off (LM_EXTRA_BALL);
	lamp_tristate_off (LM_START_MULTIBALL);
}






/****************************************************************************
 * playfield lights and flags
 ***************************************************************************/
void extraball_light_on(void) {
	lamp_tristate_on (LM_EXTRA_BALL);
//	leff_start (LEFF_ORBITS_RUNNER);
}//end of function

void extraball_light_off(void) {
	lamp_tristate_off (LM_EXTRA_BALL);
//	if (!flag_test(FLAG_IS_MULTIBALL_ENABLED) ) leff_stop (LEFF_ORBITS_RUNNER);
}//end of function

void multiball_light_on(void) {
	lamp_tristate_on (LM_START_MULTIBALL);
//	leff_start (LEFF_ORBITS_RUNNER);
}//end of function

void multiball_light_off(void) {
	flag_off(FLAG_IS_MULTIBALL_ENABLED);
	lamp_tristate_off (LM_START_MULTIBALL);
//	if (!flag_test(FLAG_IS_EXTRABALL_LIT) ) leff_stop (LEFF_ORBITS_RUNNER);
}//end of function

void activate_explode_inserts_orbits(void) {
	lamp_tristate_on (LM_LEFT_LOOP_EXPLODE);
	lamp_tristate_on (LM_RIGHT_LOOP_EXPLODE);
}//end of function

void deactivate_explode_inserts_orbits(void) {
	lamp_tristate_off (LM_LEFT_LOOP_EXPLODE);
	lamp_tristate_off (LM_RIGHT_LOOP_EXPLODE);
}//end of function

void ll_jackpot_light_on(void) {
	lamp_tristate_on (LM_LEFT_LOOP_JACKPOT);
}//end of function

void ll_jackpot_light_off(void) {
	lamp_tristate_off (LM_LEFT_LOOP_JACKPOT);
}//end of function

void rl_jackpot_light_on(void) {
	lamp_tristate_on (LM_RIGHT_LOOP_JACKPOT);
}//end of function

void rl_jackpot_light_off(void) {
	lamp_tristate_off (LM_RIGHT_LOOP_JACKPOT);
}//end of function

void ll_arrow_light_on(void) {
	flag_on (FLAG_IS_L_LOOP_ARROW_ACTIVATED);
	if (get_capture_simon_arrows (CAPSIM_LEFTORB)) 	lamp_tristate_flash (LM_LEFT_LOOP_ARROW);
	else 												lamp_tristate_on (LM_LEFT_LOOP_ARROW);
}//end of function

void ll_arrow_light_off(void) {
	flag_off (FLAG_IS_L_LOOP_ARROW_ACTIVATED);
	lamp_tristate_off (LM_LEFT_LOOP_ARROW);
}//end of function

void rl_arrow_light_on(void) {
	flag_on (FLAG_IS_R_LOOP_ARROW_ACTIVATED);
	if (get_capture_simon_arrows (CAPSIM_RIGHTORB)) 	lamp_tristate_flash (LM_RIGHT_LOOP_ARROW);
	else 												lamp_tristate_on (LM_RIGHT_LOOP_ARROW);
}//end of function

void rl_arrow_light_off(void) {
	flag_off (FLAG_IS_R_LOOP_ARROW_ACTIVATED);
	lamp_tristate_off (LM_RIGHT_LOOP_ARROW);
}//end of function


/****************************************************************************
 *
 * body
 *
 ****************************************************************************/
void left_orbit_task (void) { task_sleep_sec(2); task_exit(); }
void right_orbit_task (void) { task_sleep_sec(2); task_exit(); }



// full orbit right to left
// or start left to right check
CALLSET_ENTRY (orbits, sw_left_loop) {
	if (in_game && !in_tilt) {
			if (get_back_in_the_fridge_running ()  ) 				back_in_the_fridge_shot_made();
			if (get_jackpot_arrows(lloop_mask) ) 					score_jackpot();
			if (is_huxley_running ()  )								huxley_mode_shot_made();
			if (get_capture_simon_arrows (CAPSIM_LEFTORB) )  		capture_simon_made();
			if (is_prison_break_running () ) 						prison_break_made();

			if (flag_test(FLAG_IS_COMBO_LEFTORB_ACTIVATED) ) 		combo_hit();
			else if (get_is_combos_killed ()
				&&	 get_is_combos_restartable () ) 					combo_init();

			if (is_explode_mode_running()  ) 									explode_made();

			leff_start(LEFF_LEFT_RAMP);

			if ( task_kill_gid(GID_RIGHT_ORBIT_MADE) ) right_orbit_shot_made();
			else {
				task_create_gid1 (GID_LEFT_ORBIT_MADE, left_orbit_task);
				if (!is_prison_break_running () ) {
						if ( (orbits_SoundCounter++ % 2) == 0 )//check if even
							sound_start (ST_EFFECT, RACE_BY, SL_2S, PRI_GAME_QUICK2);
						else
							sound_start (ST_EFFECT, RACE_BY_2, SL_2S, PRI_GAME_QUICK2);
				}//end of if ! pbreak
			}//end of else
	}//end of 	if (in_game && !in_tilt)
}//end of function



// full orbit left to right
// or start right to left check
CALLSET_ENTRY (orbits, sw_right_freeway) {
	if (in_game && !in_tilt) {
			if (get_back_in_the_fridge_running()  ) 					back_in_the_fridge_shot_made();
			if (get_jackpot_arrows(rloop_mask) ) 					score_jackpot();
			if (is_huxley_running ()  )							huxley_mode_shot_made();
			if (get_capture_simon_arrows (CAPSIM_RIGHTORB) )  		capture_simon_made();
			if (is_prison_break_running () )   					prison_break_made();

			if (flag_test(FLAG_IS_COMBO_RIGHTORB_ACTIVATED) ) 		combo_hit();
			else if (get_is_combos_killed ()
				&&	 get_is_combos_restartable ()) 						combo_init();

			if (is_explode_mode_running() ) 									explode_made();

			leff_start(LEFF_RIGHT_RAMP);

			if ( task_kill_gid(GID_LEFT_ORBIT_MADE) ) left_orbit_shot_made();
			else {
				task_create_gid1 (GID_RIGHT_ORBIT_MADE, right_orbit_task);
				if (!is_prison_break_running () ) {
						if ( (orbits_SoundCounter++ % 2) == 0 )//check if even
							sound_start (ST_EFFECT, RACE_BY, SL_2S, PRI_GAME_QUICK2);
						else
							sound_start (ST_EFFECT, RACE_BY_2, SL_2S, PRI_GAME_QUICK2);
				}//end of if ! pbreak
			}//end of else
	}//end of 	if (in_game && !in_tilt)
}//end of function



void left_orbit_shot_made(void) {
	score (ORBIT_SCORE);//located in kernal/score.c
	if (!is_prison_break_running () ) sound_start (ST_SAMPLE, MACHINE12, SL_2S, PRI_GAME_QUICK1);
}//end of function



void right_orbit_shot_made(void) {
	score (ORBIT_SCORE);//located in kernal/score.c
	if (!is_prison_break_running () ) sound_start (ST_SAMPLE, MACHINE12, SL_2S, PRI_GAME_QUICK1);
}//end of function



