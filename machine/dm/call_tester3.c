/*************************************************************************************************
 *
 * PAGE 3
 *
 *************************************************************************************************/
/* CALLSET_SECTION (call_tester3,  __machine3__ ) */
#include <freewpc.h>


U8 		capture_simon_mode_shots_made;
U8 		prison_break_mode_shots_made;
U8		fortress_jackpot_shots_made;
U8		wasteland_jackpot_shots_made;


/* capture_simon.c */
 void capture_simon_made(void){ }
 U8 get_capture_simon_timer (void){return 0;}
 U8 get_capture_simon_timer_total_time (void){return 0; }
 void add_time_to_capture_simon_mode (U8 time){ }
 void set_capture_simon_arrows (U8 arrow_flag){ }
 __boolean get_capture_simon_arrows (U8 arrow_flag){return FALSE; }
 __boolean is_capture_simon_running (void){ return FALSE;}
 bool get_is_capture_simon_initial_start (void){ return FALSE;}
 void set_capture_simon_arrows_all_off (void){ }
 void capture_simon_start_effect_deff(void) {deff_exit ();}
 void capture_simon_effect_deff(void) {deff_exit ();}
 void capture_simon_hit_effect_deff(void) {deff_exit ();}
 void capture_simon_end_effect_deff(void) {deff_exit ();}


/* lock_freeze_mbstart.c */
 void maximize_freeze(void){ }
 void increment_freeze(void){ }
 void multiball_start (void){ }
 void multiball_started (void){ }
 void freeze_effect_deff(void) {deff_exit ();}


/* prison_break.c */
 void prison_break_made (void){ }
 U8 get_prison_break_timer (void){return 0;}
 bool is_prison_break_running (void){return FALSE; }
 void add_time_to_prison_break_mode (U8 time){ }
 U8 get_prison_break_timer_total_time (void){return 0; }
 void prison_break_start_effect_deff(void) {deff_exit ();}
 void prison_break_effect_deff(void) {deff_exit ();}
 void prison_break_hit_effect_deff(void) {deff_exit ();}


/* fortress.c */
 void fortress_start(U8 num){ }
 void fortress_jackpot_made(void){ }
 void fortress_award_super_jackpot(void){ }
 __boolean get_fortress_running (void){return FALSE; }
 void fortress_start_effect_deff(void) {deff_exit ();}
 void fortress_jackpot_effect_deff(void) {deff_exit ();}
 void fortress_effect_deff(void) {deff_exit ();}
 void fortress_super_jackpot_deff(void) {deff_exit ();}


/* wasteland.c */
 void wasteland_start(U8 num){ }
 void wasteland_jackpot_made(void){ }
 void wasteland_award_super_jackpot(void){ }
 __boolean get_wasteland_running (void){return FALSE; }
 void wasteland_start_effect_deff(void) {deff_exit ();}
 void wasteland_jackpot_effect_deff(void) {deff_exit ();}
 void wasteland_effect_deff(void) {deff_exit ();}
 void wasteland_super_jackpot_deff(void) {deff_exit ();}


/*super_jackpot_reminder.c*/
 void start_super_jackpot_reminder (void){ }
 void end_super_jackpot_reminder (void){ }
 __boolean get_is_super_jackpot_lit(void){return FALSE; }


/*extra_ball.c*/
 void start_extraball(void){ }
 void end_extraball(void){ }


/* special_shots.c */
 void laser_shot_made(void){ }
 void laser_shot_deff(void) {deff_exit ();}




/*override deffs.c*/
 void shoot_again_deff(void) {deff_exit ();}
 void dm_game_over_deff(void) {deff_exit ();}

