/*************************************************************************************************
 *
 * PAGE 4
 *
 *************************************************************************************************/
/* CALLSET_SECTION (call_tester4,  __machine4__) */
#include <freewpc.h>

__local__ U8 		eyeball_shots_made;


/* vm_handler.c */
 U8 get_next_video_mode (void){return 0;}


/* eject.c */
 void comp_award_doub_retina(void){}
 void set_normal_eject_killed_status (__boolean status){}
 __boolean get_normal_eject_killed_status (void){return FALSE;}
 void eject_effect_deff(void) {deff_exit ();}
 void eject_leff(void) {leff_exit ();}


/*kaboom.c*/
 void start_kaboom (void){}
 void kaboom_deff(void) {deff_exit ();}
 void kaboom_abort_deff(void) {deff_exit ();}
 void kaboom_intro_deff(void) {deff_exit ();}
 void kaboom_end_deff(void) {deff_exit ();}


/*ballshot_vm*/
 void start_shooter (void){}
 void shooter_deff(void) {deff_exit ();}
 void shooter_abort_deff(void) {deff_exit ();}
 void shooter_intro_deff(void) {deff_exit ();}
 void shooter_end_deff(void) {deff_exit ();}


/*simon says*/
 void start_simon_says (void){}
 void simon_says_deff(void) {deff_exit ();}
 void simon_says_intro_deff(void) {deff_exit ();}
 void simon_says_runner_deff(void) {deff_exit ();}
 void simon_says_ready_deff(void) {deff_exit ();}
 void simon_says_wrong_deff(void) {deff_exit ();}
 void simon_says_abort_deff(void) {deff_exit ();}
 void simon_says_watch_deff(void) {deff_exit ();}
 void simon_says_indy_deff(void) {deff_exit ();}
 void simon_says_end_deff(void) {deff_exit ();}


/* acmag.c */
 void acmag_made(void){}
 U8 get_acmag_timer (void){return 0;}
 bool is_acmag_running (void){return FALSE;}
 void add_time_to_acmag_mode (U8 time){}
 U8 get_acmag_timer_total_time (void){return 0;}
 void acmag_start_effect_deff(void) {deff_exit ();}
 void acmag_effect_deff(void) {deff_exit ();}
 void acmag_hit_effect_deff(void) {deff_exit ();}


/* top_popper.c */
 void top_popper_effect_deff(void) {deff_exit ();}
 void extra_ball_effect_deff(void) {deff_exit ();}
 void extraball_leff(void) {leff_exit ();}
 void top_popper_leff(void) {leff_exit ();}

 /* eyeball.c */
 void eyeball_effect_deff(void) {deff_exit ();}



 /* startup_shutdown.c */
 void startup_effect_deff(void) {deff_exit ();}


 /* leffs.c */
 void flash_all_leff(void) {leff_exit ();}
 void bot2top_leff(void) {leff_exit ();}
 void top2bot_leff(void) {leff_exit ();}
 void right2left_leff(void) {leff_exit ();}
 void left2right_leff(void) {leff_exit ();}
 void no_gi_onesec_leff(void) {leff_exit ();}
 void no_gi_twosec_leff(void) {leff_exit ();}
 void turn_off_gi_leff(void) {leff_exit ();}
 void turn_on_gi_leff(void) {leff_exit ();}
 void flash_gi_leff(void) {leff_exit ();}
 void left_ramp_leff(void) {leff_exit ();}
 void right_ramp_leff(void) {leff_exit ();}
 void center_ramp_leff(void) {leff_exit ();}
 void side_ramp_leff(void) {leff_exit ();}
 void ramp_quickfreeze_leff(void) {leff_exit ();}
 void ramp_clawready_leff(void) {leff_exit ();}
 void Amode_leff(void) {leff_exit ();}
 void lower_rebound_leff(void) {leff_exit ();}
 void upper_rebound_leff(void) {leff_exit ();}
 void orbits_runner_leff(void) {leff_exit ();}
 void freeze_leff(void) {leff_exit ();}
 void claw_leff(void) {leff_exit ();}
 void inlane_quick_freeze_leff(void) {leff_exit ();}
 void inlane_cryoclaw_leff(void) {leff_exit ();}
 void Underground_leff(void) {leff_exit ();}
 void computer_award_leff(void) {leff_exit ();}
 void eyeball_leff(void) {leff_exit ();}
 void skillshot_leff(void) {leff_exit ();}
 void car_crash_runner_leff(void) {leff_exit ();}


 // void troubleshooting_deff(void) {deff_exit ();}
