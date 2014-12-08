#include <freewpc.h>
/*************************************************************************************************
 *
 * PAGE 5
 *
 *************************************************************************************************/
/* CALLSET_SECTION (call_tester5, __machine5__) */


__local__ U8 		combo_counter;
U8 		huxley_mode_shots_made;
U8		museum_jackpot_shots_made;
U8		cryoprison_jackpot_shots_made;
U8		demotime_jackpot_shots_made;
U8		back_in_the_fridge_shots_made;



void cryoprison_start(U8 num){}
void cryoprison_jackpot_made(void){}
void cryoprison_award_super_jackpot(void){}
__boolean get_cryoprison_running (void) {return FALSE;}
void cryoprison_start_effect_deff(void) {deff_exit ();}
void cryoprison_jackpot_effect_deff(void) {deff_exit ();}
void cryoprison_effect_deff(void) {deff_exit ();}
void cryoprison_super_jackpot_deff(void) {deff_exit ();}


void huxley_increment(void){}
void huxley_begin(void){}
void huxley_mode_shot_made(void){}
void huxley_made(void){}
void huxley_increment_all(void) {}
U8 get_huxley_timer (void) {return 0;}
bool is_huxley_running (void){return FALSE;}
void add_time_to_huxley_mode (U8 time) {}
U8 get_huxley_timer_total_time (void) {return 0;}
void huxley_info_effect_deff(void) {deff_exit ();}
void huxley_start_effect_deff(void) {deff_exit ();}
void huxley_effect_deff(void) {deff_exit ();}
void huxley_hit_effect_deff(void) {deff_exit ();}


void museum_start(U8 num) {}
void museum_jackpot_made(void) {}
void museum_award_super_jackpot(void) {}
__boolean get_museum_running (void) {return FALSE;}
void museum_start_effect_deff(void) {deff_exit ();}
void museum_jackpot_effect_deff(void) {deff_exit ();}
void museum_effect_deff(void) {deff_exit ();}
void museum_super_jackpot_deff(void) {deff_exit ();}


void demotime_increment (void){}
void demotime_increment_all (void) {}
void demotime_start(void) {}
void demotime_jackpot_made(void){}
__boolean get_demotime_running (void) {return FALSE;}
__boolean get_demotime_starting (void) {return FALSE;}
void demotime_start_effect_deff(void) {deff_exit ();}
void demotime_jackpot_effect_deff(void) {deff_exit ();}
void demotime_info_effect_deff(void) {deff_exit ();}
void demotime_effect_deff(void) {deff_exit ();}


void enable_back_in_the_fridge(void) {}
void start_back_in_the_fridge(void) {}
void back_in_the_fridge_shot_made(void) {}
__boolean get_back_in_the_fridge_running(void) {return FALSE;}
__boolean get_back_in_the_fridge_ending (void) {return FALSE;}
void bitf_start_effect_deff(void) {deff_exit ();}
void bitf_hit_effect_deff(void) {deff_exit ();}
void bitf_info_effect_deff(void) {deff_exit ();}
void bitf_effect_deff(void) {deff_exit ();}
void bitf_end_effect_deff(void) {deff_exit ();}




void set_dm_mode (U8 mode_flag){}
__boolean get_dm_mode (U8 mode_flag){return FALSE;}


/*jackpots.c*/
void jackpot_reset (void){ }
void choose_random_jackpot(void){ }
void choose_multiple_random_jackpot(U8 numOfJakpots){ }
void score_jackpot(void){ }
void set_all_jackpots (void){ }
void score_super_jackpot (void){ }
void set_jackpot_arrows (U8 arrow_flag){ }
void set_jackpot_arrows_all_off (void){ }
__boolean get_jackpot_arrows (U8 arrow_flag){return FALSE; }


/*dm_ball_search.c*/
