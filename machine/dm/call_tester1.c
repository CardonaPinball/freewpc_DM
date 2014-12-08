/*************************************************************************************************
 *
 * PAGE 1
 *
 *************************************************************************************************/
/* CALLSET_SECTION (call_tester1,  __machine1__ ) */
#include <freewpc.h>

U8 		rollover_bonus_multiplier;
__local__ U8 jet_shots_made;


/*standupfrenzy.c*/
bool is_frenzy_running (void) {return FALSE;}
void standupfrenzy_start_effect_deff(void) {deff_exit ();}
void standupfrenzy_effect_deff(void) {deff_exit ();}
void standup_effect_deff(void) {deff_exit ();}


/*jets.c*/
void jets_effect_deff(void) {deff_exit ();}
void jets_completed_effect_deff(void) {deff_exit ();}


/*rollovers.c*/
void rollovers_effect_deff(void) {deff_exit ();}
void all_rollovers_effect_deff(void) {deff_exit ();}

