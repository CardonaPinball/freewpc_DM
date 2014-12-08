/*************************************************************************************************
 *
 * PAGE 2
 *
 *************************************************************************************************/
/* CALLSET_SECTION (call_tester2,  __machin2__ ) */
#include <freewpc.h>

__local__ U8 		car_crash_shots_made;
U8 					car_chase_mode_shots_made;


/* car_chase_mode.c */
 void start_car_chase(void){ }
 void car_chase_ramp_made(void){ }
 __boolean is_carchase_mode_running (void){return FALSE; }
 void car_chase_start_effect_deff(void) {deff_exit ();}
 void car_chase_effect_deff(void) {deff_exit ();}
 void car_chase_hit_effect_deff(void) {deff_exit ();}


/* explode.c */
 void start_explode(void){ }
 void explode_made(void){ }
 __boolean is_explode_mode_running (void){return FALSE; }
 void explode_start_effect_deff(void) {deff_exit ();}
 void explode_effect_deff(void) {deff_exit ();}
 void explode_hit_effect_deff(void) {deff_exit ();}


/* car_crash.c */
 void comp_award_trip_car_crash(void){ }
 void restore_carcrash_lights_state(void){ }
 void carcrash_effect_deff(void) {deff_exit ();}


/* underground.c */
 void underground_jackpot_light_on(void){ }
 void underground_jackpot_light_off(void){ }
 void underground_arrow_light_on(void){ }
 void underground_arrow_light_off(void){ }
 void computer_light_on(void){ }
 void computer_light_off(void){ }
 void underground_effect_deff(void) {deff_exit ();}
 void computer_award_deff(void) {deff_exit ();}


 /*cryoclaw.c*/
  void disabled_claw_hit (void){ }
  void cryoclaw_effect_deff(void) {deff_exit ();}


/*bonus.c*/
 void bonus_runner (void){ }
 void bonus_runner1 (char * words, U8 scoreAmount, U8 multiplier){ }
 void bonus_button_monitor (void){ }
 void bonus_sched_transition (void){ }
 void bonus_pause (void){ }
 bool check_for_big_score (void){return FALSE; }
 bool check_for_puny_score (void){return FALSE; }
 void bonus_deff(void) {deff_exit ();}
