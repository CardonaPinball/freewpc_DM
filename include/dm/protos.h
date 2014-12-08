/*******************************************************************
 * common page
 ********************************************************************/



/*******************************************************************
 * .text page == GAME_OBJS
 ********************************************************************/
/* orbits.c */
void extraball_light_on(void);
void extraball_light_off(void);
void multiball_light_on(void);
void multiball_light_off(void);
void activate_explode_inserts_orbits(void);
void deactivate_explode_inserts_orbits(void);
void ll_jackpot_light_on(void);
void ll_jackpot_light_off(void);
void rl_jackpot_light_on(void);
void rl_jackpot_light_off(void);
void ll_arrow_light_on(void);
void ll_arrow_light_off(void);
void rl_arrow_light_on(void);
void rl_arrow_light_off(void);


/* ramps.c*/
void activate_explode_inserts_ramps(void);
void deactivate_explode_inserts_ramps(void);
void carchase_mode_on(void);
void carchase_mode_off(void);
void activate_left_ramp_quickfreeze(void);
void deactivate_left_ramp_quickfreeze(void);
void rramp_clawready_on(void);
void rramp_clawready_off(void);
void lramp_jackpot_light_on(void);
void lramp_jackpot_light_off(void);
void rramp_jackpot_light_on(void);
void rramp_jackpot_light_off(void);
void cramp_jackpot_light_on(void);
void cramp_jackpot_light_off(void);
void sramp_jackpot_light_on(void);
void sramp_jackpot_light_off(void);
void lramp_arrow_light_on(void);
void lramp_arrow_light_off(void);
void rramp_arrow_light_on(void);
void rramp_arrow_light_off(void);
void sramp_arrow_light_on(void);
void sramp_arrow_light_off(void);
void cramp_arrow_light_on(void);
void cramp_arrow_light_off(void);


/* arrow_handler.c*/
void center_ramp_arrow_update(void);
void all_arrow_update(void);


/*diverter_check.c*/
void diverter_check (void);


/*inlanes.c*/
void access_claw_light_on(void);
void light_quick_freeze_light_on (void);
void light_quick_freeze_light_off (void);
void increment_access_claw_light_on(void);
void check_access_claw_relight (void);
void increment_light_quick_freeze_light (void);


/*skillshot.c*/
void award_skill_shot (U8 type_skill_shot_made);
__boolean get_skill_shot_enabled (void);

/* combos.c */
void comp_award_light_arrows(void);
void combo_hit(void );
void combo_init(void);
void kill_combos(void);
void combo_rehit_check(void );
bool get_is_combos_restartable (void);
bool get_is_combos_killed (void);




/*simple_switches.c*/


/*******************************************************************
 * machine page 1
 ********************************************************************/
/*standupfrenzy.c*/
__machine__ bool is_frenzy_running (void);


/*jets.c*/
/*rollovers.c*/


/*******************************************************************
 * machine page 2
 ********************************************************************/
/* car_chase_mode.c */
__machine2__ void start_car_chase(void);
__machine2__ void car_chase_ramp_made(void);
__machine2__ __boolean is_carchase_mode_running (void);


/* explode.c */
__machine2__ void start_explode(void);
__machine2__ void explode_made(void);
__machine2__ __boolean is_explode_mode_running (void);


/* car_crash.c */
__machine2__ void comp_award_trip_car_crash(void);
__machine2__ void restore_carcrash_lights_state(void);


/* underground.c */
__machine2__ void underground_jackpot_light_on(void);
__machine2__ void underground_jackpot_light_off(void);
__machine2__ void underground_arrow_light_on(void);
__machine2__ void underground_arrow_light_off(void);
__machine2__ void computer_light_on(void);
__machine2__ void computer_light_off(void);
__machine2__ void computer_light_temp_off(void);
__machine2__ void computer_award_light_recheck(void);


/*bonus.c*/
__machine2__ void bonus_runner (void);
__machine2__ void bonus_runner1 (char * words, U8 scoreAmount, U8 multiplier);
__machine2__ void bonus_button_monitor (void);
__machine2__ void bonus_sched_transition (void);
__machine2__ void bonus_pause (void);
__machine2__ bool check_for_big_score (void);
__machine2__ bool check_for_puny_score (void);

/*cryoclaw.c*/
__machine2__ void disabled_claw_hit (void);
__machine2__ bool is_cryoclaw_mode_running (void);





/*******************************************************************
 * machine page 3
 ********************************************************************/
/* capture_simon.c */
__machine3__ void capture_simon_made(void);
__machine3__ U8 get_capture_simon_timer (void);
__machine3__ bool is_capture_simon_running (void);
__machine3__ void add_time_to_capture_simon_mode (U8 time);
__machine3__ U8 get_capture_simon_timer_total_time (void);
__machine3__ __boolean get_capture_simon_arrows (U8 arrow_flag);
__machine3__ void set_capture_simon_arrows (U8 arrow_flag);
__machine3__ __boolean is_capture_simon_running (void);
__machine3__ void set_capture_simon_arrows_all_off (void);
__machine3__ bool get_is_capture_simon_initial_start (void);
__machine3__ bool suspend_capture_simon (void);
__machine3__ void pause_capture_simon (bool state);


/* lock_freeze_mbstart.c */
__machine3__ void maximize_freeze(void);
__machine3__ void increment_freeze(void);
__machine3__ void multiball_start (void);
__machine3__ void multiball_started (void);


/* prison_break.c */
__machine3__ void prison_break_made (void);
__machine3__ U8 get_prison_break_timer (void);
__machine3__ bool is_prison_break_running (void);
__machine3__ void add_time_to_prison_break_mode (U8 time);
__machine3__ U8 get_prison_break_timer_total_time (void);
__machine3__ bool suspend_prison_break (void);
__machine3__ void pause_prison_break (bool state);


/* fortress.c */
__machine3__ void fortress_start(U8 num);
__machine3__ void fortress_jackpot_made(void);
__machine3__ void fortress_award_super_jackpot(void);
__machine3__ __boolean get_fortress_running (void);


/* wasteland.c */
__machine3__ void wasteland_start(U8 num);
__machine3__ void wasteland_jackpot_made(void);
__machine3__ void wasteland_award_super_jackpot(void);
__machine3__ __boolean get_wasteland_running (void);


/*super_jackpot_reminder.c*/
__machine3__ void start_super_jackpot_reminder (void);
__machine3__ void end_super_jackpot_reminder (void);
__machine3__ __boolean get_is_super_jackpot_lit(void);


/*extra_ball.c*/
__machine3__ void start_extraball(void);
__machine3__ void end_extraball(void);
__machine3__ void score_extraball(void);

/* special_shots.c */
__machine3__ void laser_shot_made(void);


/*superjets.c*/
__machine3__ bool is_sjets_running (void);


/* acmag.c */
__machine3__ void acmag_made(void);
__machine3__ U8 get_acmag_timer (void);
__machine3__ bool is_acmag_running (void);
__machine3__ void add_time_to_acmag_mode (U8 time);
__machine3__ U8 get_acmag_timer_total_time (void);
__machine3__ bool suspend_acmag (void);
__machine3__ void pause_acmag (bool state);





/*******************************************************************
 * machine page 4
 ********************************************************************/
/* eject.c */
__machine4__ void comp_award_doub_retina(void);
__machine4__ void set_normal_eject_killed_status (__boolean status);
__machine4__ __boolean get_normal_eject_killed_status (void);


/* vm_handler.c */
__machine4__ U8 get_next_video_mode (void);


/*kaboom.c*/
__machine4__ void start_kaboom (void);


/*ballshot_vm*/
__machine4__ void start_shooter (void);


/*simon says*/
__machine4__ void start_simon_says (void);


/* leffs.c */
__machine4__ void turn_off_gi (void);
__machine4__ void turn_on_gi  (void);



/* top_popper.c */
/* eyeball.c */
/* startup_shutdown.c */





/*******************************************************************
 * machine page 5
 ********************************************************************/
/* museum.c */
__machine5__ void museum_start(U8 num);
__machine5__ void museum_jackpot_made(void);
__machine5__ void museum_award_super_jackpot(void);
__machine5__ __boolean get_museum_running (void);


/* cryoprison.c */
__machine5__ void cryoprison_start(U8 num);
__machine5__ void cryoprison_jackpot_made(void);
__machine5__ void cryoprison_award_super_jackpot(void);
__machine5__ __boolean get_cryoprison_running (void);


/* demotime.c */
__machine5__ void demotime_increment (void);
__machine5__ void demotime_increment_all (void);
__machine5__ void demotime_start(void);
__machine5__ void demotime_jackpot_made(void);
__machine5__ __boolean get_demotime_running (void);
__machine5__ __boolean get_demotime_starting (void);


/* huxley.c*/
__machine5__ void huxley_increment(void);
__machine5__ void huxley_increment_all(void);
__machine5__ void huxley_begin(void);
__machine5__ void huxley_mode_shot_made(void);
__machine5__ void huxley_made(void);
__machine5__ U8 get_huxley_timer (void);
__machine5__ bool is_huxley_running (void);
__machine5__ void add_time_to_huxley_mode (U8 time);
__machine5__ U8 get_huxley_timer_total_time (void);
__machine5__ bool suspend_huxley (void);
__machine5__ void pause_huxley (bool state);


/*back_in_the_fridge.c*/
__machine5__ void enable_back_in_the_fridge(void);
__machine5__ void start_back_in_the_fridge(void);
__machine5__ void back_in_the_fridge_shot_made(void);
__machine5__ __boolean get_back_in_the_fridge_running(void);
__machine5__ __boolean get_back_in_the_fridge_ending (void);
__machine5__ __boolean get_is_back_in_the_fridge_in_ball_save (void);
__machine5__ void kill_back_in_the_fridge (void);



/*dm_modes_locals*/
__machine5__ void set_dm_mode (U8 mode_flag);
__machine5__ void reset_dm_mode (void);
__machine5__ __boolean get_dm_mode (U8 mode_flag);
__machine5__ void set_dm_mode2 (U8 mode_flag);
__machine5__ __boolean get_dm_mode2 (U8 mode_flag);


/*jackpots.c*/
__machine5__ void jackpot_reset (void);
__machine5__ void choose_random_jackpot(void);
__machine5__ void choose_multiple_random_jackpot(U8 numOfJakpots);
__machine5__ void score_jackpot(void);
__machine5__ void set_all_jackpots (void);
__machine5__ void score_super_jackpot (void);
__machine5__ void set_jackpot_arrows (U8 arrow_flag);
__machine5__ void set_jackpot_arrows_all_off (void);
__machine5__ __boolean get_jackpot_arrows (U8 arrow_flag);

/*dm_ball_search.c*/
