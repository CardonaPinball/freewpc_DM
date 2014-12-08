 /*
 * demolition man
 * cryoclaw.c
 *
 * written by James Cardona
 *
 * Location Description:
 *
 *
 */
/* CALLSET_SECTION (cryoclaw, __machine2__) */



#include <freewpc.h>
#include "dm/global_constants.h"
#include "elevator.h"
#include "claw.h"
#include "clawmagnet.h"
#include "search.h"

#define FULLSWING_IFNOTHOME 1
#define PICKUPBALL 2
#define FULLSWING 3

//local variables
U8			cryoclaw_mode_timer;
__local__ U8 dc_next_award; //used for when cryoclaw is disabled and we must increment through claw modes using right ramp
__boolean is_claw_running;


//internally called function prototypes  --external found at protos.h
void cryoclaw_mode_init (void);
void cryoclaw_mode_expire (void);
void cryoclaw_mode_exit (void);

/****************************************************************************
 * mode definition structure
 ***************************************************************************/
struct timed_mode_ops cryoclaw_mode = {
	DEFAULT_MODE,
	.init = cryoclaw_mode_init,
	.exit = cryoclaw_mode_expire,
	.gid = GID_CRYOCLAW_MODE_RUNNING,
	.music = MUS_CLAW,
	.deff_running = DEFF_CRYOCLAW_EFFECT,
	.prio = PRI_GAME_MODE1,
	.init_timer = 10,
	.timer = &cryoclaw_mode_timer,
	.grace_timer = 0, //default is 2
};


/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
void MOVE_CLAW (U8 movetype) {
	//reset claw at start player or start ball or amode start
	if (movetype == FULLSWING_IFNOTHOME && !is_claw_running  && system_config.disable_claw == NO) {
			task_sleep(TIME_100MS);
			if (switch_poll_logical (SW_CLAW_POSITION_2) ) 	global_flag_on(GLOBAL_FLAG_IS_CLAW_HOME);
			task_sleep(TIME_100MS);

			if (!global_flag_test(GLOBAL_FLAG_IS_CLAW_HOME)) {
					is_claw_running = TRUE;
					claw_go_right();
					task_sleep(TIME_100MS);
					while (!switch_poll_logical (SW_CLAW_POSITION_1)) task_sleep(TIME_100MS);
					clawmagnet_on ();
					elevator_move_up();							//move up
					task_sleep(TIME_1S);						//then back down back to home
					elevator_move_down();
					task_sleep(TIME_1S);
					while (switch_poll_logical (SW_ELEVATOR_HOLD)) task_sleep(TIME_100MS);
					task_sleep(TIME_1S);
					claw_go_left();
					task_sleep(TIME_100MS);
					while (!switch_poll_logical (SW_CLAW_POSITION_2)) task_sleep(TIME_100MS);
					global_flag_on(GLOBAL_FLAG_IS_CLAW_HOME);
					clawmagnet_off (); 							//drop ball on acmag
					global_flag_off(GLOBAL_FLAG_IS_BALL_ON_CLAW);
					task_sleep(TIME_1S);
					is_claw_running = FALSE;
				}//end of if claw not home
	}//end of movetype 1, reset claw

	//claw initial ball pickup at mode start
	else if (movetype == PICKUPBALL && !is_claw_running && system_config.disable_claw == NO) {
			ball_search_monitor_stop ();
			is_claw_running = TRUE;
			sound_start (ST_SPEECH, SPCH_USE_TRIGGERS_TO_MOVE_CRYOCLAW, SL_4S, PRI_GAME_QUICK5);
			flipper_disable ();							//approximately 4 secs, the player cannot control anything
			leff_start (LEFF_CLAW);

			//routine which has claw starting from parked at left
			global_flag_off(GLOBAL_FLAG_IS_CLAW_HOME);
			claw_go_right();
			if (claw_get_speed() == CLAW_DUTY_100) 				task_sleep(TIME_2S);
			else if (claw_get_speed() == CLAW_DUTY_50) 			task_sleep(TIME_3S);
			else task_sleep(TIME_4S);
			while (!switch_poll_logical (SW_CLAW_POSITION_1)) 	task_sleep(TIME_100MS);
			clawmagnet_on ();
			elevator_move_up();							//move up
			task_sleep(TIME_100MS);						//then back down back to home
			elevator_move_down();
			task_sleep(TIME_100MS);
			while (switch_poll_logical (SW_ELEVATOR_HOLD)) 		task_sleep(TIME_100MS);
			task_sleep(TIME_1S);
			claw_go_left_to_center();

			sound_start (ST_SPEECH, SPCH_USE_BUTTONS_TO_RELEASE_BALL, SL_4S, PRI_GAME_QUICK5);

			task_sleep(TIME_1S);
			global_flag_on(GLOBAL_FLAG_IS_BALL_ON_CLAW);
			rramp_clawready_off();		//turn off diverter
			ball_search_monitor_start ();
	}//end of movetype 2, claw mode start

	//reset claw at ball search call or if ball dropped on elevator and not in game
	else if (movetype == FULLSWING  && system_config.disable_claw == NO) {
					is_claw_running = TRUE;
					global_flag_off(GLOBAL_FLAG_IS_CLAW_HOME);
					claw_go_right();
					task_sleep(TIME_100MS);
					while (!switch_poll_logical (SW_CLAW_POSITION_1)) task_sleep(TIME_100MS);
					clawmagnet_on ();
					elevator_move_up();							//move up
					task_sleep(TIME_1S);						//then back down back to home
					elevator_move_down();
					task_sleep(TIME_1S);
					while (switch_poll_logical (SW_ELEVATOR_HOLD)) task_sleep(TIME_100MS);
					task_sleep(TIME_1S);
					claw_go_left();
					task_sleep(TIME_100MS);
					while (!switch_poll_logical (SW_CLAW_POSITION_2)) task_sleep(TIME_100MS);
					global_flag_on(GLOBAL_FLAG_IS_CLAW_HOME);
					clawmagnet_off (); 							//drop ball on acmag
					global_flag_off(GLOBAL_FLAG_IS_BALL_ON_CLAW);
					task_sleep(TIME_1S);
					is_claw_running = FALSE;
	}//end of movetype 3
}//end of function




//ensure claw is all the way to the right this also takes care of situation where ball is left on elevator at bootup
CALLSET_ENTRY (cryoclaw, amode_start) {
	//wait here, in case game was tilted and in ball search this allows search a few seconds to put claw away
	task_sleep(TIME_4S);
	task_sleep(TIME_4S);
	global_flag_off(GLOBAL_FLAG_IS_BALL_ON_CLAW);
	clawmagnet_off (); 																				//drop ball on acmag
	is_claw_running = FALSE;
	MOVE_CLAW (FULLSWING_IFNOTHOME); //only moves if not home already
}//end of function



CALLSET_ENTRY (cryoclaw, start_ball) {
	global_flag_off(GLOBAL_FLAG_IS_BALL_ON_CLAW);
	clawmagnet_off (); 																				//drop ball on acmag
	is_claw_running = FALSE;
	MOVE_CLAW (FULLSWING_IFNOTHOME); //only moves if not home already
}//end of function



//The claw currently resets itself at every animation mode start
//if a game is started during the time when claw is moving, the claw might
//find itself not reset - in that case, reset it here
CALLSET_ENTRY (cryoclaw, start_player) {
	dc_next_award = 0;
	clawmagnet_off (); 																				//drop ball on acmag
	MOVE_CLAW (FULLSWING_IFNOTHOME); //only moves if not home already
}//end of function


//this calls mode expire below
CALLSET_ENTRY (cryoclaw, end_ball) {
	if (timed_mode_running_p(&cryoclaw_mode) ) timed_mode_end (&cryoclaw_mode);
}//end of function



//this is used at start of claw mode - when ball is dropped on elevator
//then this called by mode start
void cryoclaw_mode_init (void) {
	MOVE_CLAW (PICKUPBALL);
}//end of function



bool is_cryoclaw_mode_running (void) {
	if (is_claw_running) return TRUE;
	else return FALSE;
}//end of function



CALLSET_ENTRY (cryoclaw, ball_search_claw) {
	MOVE_CLAW (FULLSWING);
}//end of task




//after ball leaves claw - mode waits for time out then moves claw back to home
//this is also called if drain happens
//we may also get here if timer expires and mode not started - ball may have fallen on elevator
void cryoclaw_mode_expire (void) {
	if (!flag_test(FLAG_VIDEO_MODE_RUNNING) ) flipper_enable ();
 	clawmagnet_off ();
	global_flag_off(GLOBAL_FLAG_IS_BALL_ON_CLAW);
	task_sleep(TIME_1S);
	//move claw back to home position - this also takes care of the case where ball was dropped back on elevator
	MOVE_CLAW (FULLSWING); //only moves if not home already - which it won't be
	is_claw_running = FALSE;
	check_access_claw_relight();//if claw modes are stacked up then relight claw at inlanes.c
	if (!flag_test(FLAG_VIDEO_MODE_RUNNING) ) 	ball_search_monitor_start ();
	//else 										ball_search_monitor_stop ();
}//end of function



/****************************************************************************
 * external event listeners
 ****************************************************************************/
CALLSET_ENTRY (cryoclaw, music_refresh)  	{ if (in_game) timed_mode_music_refresh (&cryoclaw_mode); }
CALLSET_ENTRY (cryoclaw, display_update) 	{ timed_mode_display_update (&cryoclaw_mode); }





/****************************************************************************
 *
 * body
 *
 ****************************************************************************/
//if ball lands on top of elevator then switch will be made
CALLSET_ENTRY (cryoclaw, sw_elevator_hold) {
	task_sleep (TIME_2S);

	if (system_config.disable_claw == NO) {
			if (	in_game
				&& valid_playfield
				&& !is_claw_running ) {
						if (!timed_mode_running_p(&cryoclaw_mode) ) timed_mode_begin (&cryoclaw_mode);//start mode

						flasher_pulse (FLASH_ELEVATOR_1);
						flasher_pulse (FLASH_ELEVATOR_2);
						flasher_pulse (FLASH_CLAW_FLASHER);
						task_sleep (TIME_100MS);
						flasher_pulse (FLASH_ELEVATOR_1);
						flasher_pulse (FLASH_ELEVATOR_2);
						flasher_pulse (FLASH_CLAW_FLASHER);
						task_sleep (TIME_100MS);
						flasher_pulse (FLASH_ELEVATOR_1);
						flasher_pulse (FLASH_ELEVATOR_2);
						flasher_pulse (FLASH_CLAW_FLASHER);
			}//END OF INNER IF
			else
				//somehow we are not in a game, yet the ball is on the elevator? get rid of it
				if ( !in_game && !is_claw_running ) MOVE_CLAW (FULLSWING);
	}//end of if claw disabled
}//end of function





// this is how we handle activating claw modes when the claw is disabled
// this is called by right ramp hit at ramps.c
//
// claw can be disabled by player in options menu for the following reasons:
// 1) diverter, claw motor, elevator, or magnet broke
// 2) for tournaments because it makes game harder
void disabled_claw_hit (void) {
	if (++dc_next_award >= 5) dc_next_award = 0;
	switch (dc_next_award) {
		case 0: callset_invoke (sw_claw_capture_simon); break; //capture simon
		case 1: callset_invoke (sw_claw_acmag); 		break; //acmag
		case 2: callset_invoke (sw_claw_freeze); 		break; //frenzy
		case 3: callset_invoke (sw_claw_prison_break); 	break; //cryoprison breakout
		case 4: callset_invoke (sw_claw_super_jets); 	break; //super jets
	}// end of switch
	rramp_clawready_off (); //turn off claw enabled flag and light
}//end of function




//release ball
CALLSET_ENTRY (cryoclaw, sw_left_handle_button, sw_launch_button) {
	if (global_flag_test(GLOBAL_FLAG_IS_BALL_ON_CLAW)) clawmagnet_off ();
}//end of function



//end mode
CALLSET_ENTRY (cryoclaw, end_claw_mode) {
	 if (timed_mode_running_p(&cryoclaw_mode) ) timed_mode_end (&cryoclaw_mode);
}//end of function





//move claw left
CALLSET_ENTRY (cryoclaw, sw_left_button, sw_upper_left_button) {
	if (system_config.disable_claw == NO) {
		while (		global_flag_test(GLOBAL_FLAG_IS_BALL_ON_CLAW)
				&& claw_location != CLAW_LEFT
				&& (switch_poll_logical (SW_LEFT_BUTTON) || switch_poll_logical (SW_U_L_FLIPPER_BUTTON) )   ) {
			claw_bump_left ();
//			task_sleep (TIME_33MS);
			task_sleep (TIME_16MS);
		}// end of while loop
	}
}//end of function





//move claw right
CALLSET_ENTRY (cryoclaw, sw_right_button, sw_upper_right_button) {
	if (system_config.disable_claw == NO) {
		while (		global_flag_test(GLOBAL_FLAG_IS_BALL_ON_CLAW)
//				&& !switch_poll_logical (SW_CLAW_POSITION_1)
				&& claw_location != CLAW_RIGHT
				&& (switch_poll_logical (SW_RIGHT_BUTTON) || switch_poll_logical (SW_U_R_FLIPPER_BUTTON) )   ) {
			claw_bump_right ();
			//			task_sleep (TIME_33MS);
						task_sleep (TIME_16MS);
		}// end of while loop
	}
}//end of function










/****************************************************************************
 *
 * DMD display
 *
 ****************************************************************************/
void cryoclaw_effect_deff (void) {
	U16 i;
	bool direction;
	i = IMG_CRYOCLAW_MARIO_START;
	direction = TRUE;
	for (;;) {
			dmd_alloc_pair_clean ();// Clean both pages
					dmd_map_overlay ();
					dmd_clean_page_low ();
					dmd_draw_thin_border (dmd_low_buffer);
						sprintf ("%d", cryoclaw_mode_timer);
						font_render_string_center (&font_term6, 10, 27, sprintf_buffer);
						font_render_string_center (&font_var5, DMD_MIDDLE_X, 28, "CRYO CLAW");
					dmd_text_outline ();
					dmd_alloc_pair ();
					frame_draw(i);
					dmd_overlay_outline ();
					dmd_show2 ();
					if (i == IMG_CRYOCLAW_MARIO_END) direction = FALSE;
					if (i == IMG_CRYOCLAW_MARIO_START) direction = TRUE;
					if (direction) i += 2; else i -= 2;
				task_sleep (TIME_100MS);
	}//END OF LOOP
}//end of function
