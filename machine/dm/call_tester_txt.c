/*************************************************************************************************
 *
 * PAGE txt
 *
 *************************************************************************************************/
#include <freewpc.h>



/* orbits.c */
void extraball_light_on(void){ }
void extraball_light_off(void){ }
void multiball_light_on(void){ }
void multiball_light_off(void){ }
void activate_explode_inserts_orbits(void){ }
void deactivate_explode_inserts_orbits(void){ }
void ll_jackpot_light_on(void){ }
void ll_jackpot_light_off(void){ }
void rl_jackpot_light_on(void){ }
void rl_jackpot_light_off(void){ }
void ll_arrow_light_on(void){ }
void ll_arrow_light_off(void){ }
void rl_arrow_light_on(void){ }
void rl_arrow_light_off(void){ }


/* ramps.c*/
void activate_explode_inserts_ramps(void){ }
void deactivate_explode_inserts_ramps(void){ }
void carchase_mode_on(void){ }
void carchase_mode_off(void){ }
void activate_left_ramp_quickfreeze(void){ }
void deactivate_left_ramp_quickfreeze(void){ }
void rramp_clawready_on(void){ }
void rramp_clawready_off(void){ }
void lramp_jackpot_light_on(void){ }
void lramp_jackpot_light_off(void){ }
void rramp_jackpot_light_on(void){ }
void rramp_jackpot_light_off(void){ }
void cramp_jackpot_light_on(void){ }
void cramp_jackpot_light_off(void){ }
void sramp_jackpot_light_on(void){ }
void sramp_jackpot_light_off(void){ }
void lramp_arrow_light_on(void){ }
void lramp_arrow_light_off(void){ }
void rramp_arrow_light_on(void){ }
void rramp_arrow_light_off(void){ }
void sramp_arrow_light_on(void){ }
void sramp_arrow_light_off(void){ }
void cramp_arrow_light_on(void){ }
void cramp_arrow_light_off(void){ }


/* arrow_handler.c*/
void center_ramp_arrow_update(void){ }
void all_arrow_update(void){ }


/*diverter_check.c*/
void diverter_check (void){ }


/*inlanes.c*/
void access_claw_light_on(void){ }
void light_quick_freeze_light_on (void){ }
void light_quick_freeze_light_off (void){ }
void increment_access_claw_light_on(void){ }
void check_access_claw_relight (void){ }
void increment_light_quick_freeze_light (void){ }
void clw_inlanes_effect_deff(void) {deff_exit ();}
void qf_inlanes_effect_deff(void) {deff_exit ();}




/*skillshot.c*/
void award_skill_shot (U8 type_skill_shot_made){ }
__boolean get_skill_shot_enabled (void){return FALSE;  }
void skillshot_deff(void) {deff_exit ();}


/*superjets.c*/
bool is_sjets_running (void){return FALSE;  }
void superjets_effect_deff(void) {deff_exit ();}
void superjets_hit_effect_deff(void) {deff_exit ();}

/*combos.c*/
void comp_award_light_arrows(void) {}
void combo_hit(void ) {}
void combo_init(void) {}
void kill_combos(void) {}
void combo_rehit_check(void ) {}
bool get_is_combos_restartable (void) {return FALSE;}
bool get_is_combos_killed (void) {return FALSE;}
void combo_effect_deff(void) {deff_exit ();}

/*simple_switches.c*/


