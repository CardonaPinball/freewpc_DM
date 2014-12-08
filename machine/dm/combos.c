/*
 * demolition man
 * combos.c
 *
 * written by James Cardona
 *
 *
 * Scoring Description: (original game)
 * a combo is obviously making more than one shot in a row
 * we detect this using a task timer and change the arrows that are lit after
 * each shot.  if the player makes the next lit arrow then they are
 * awarded a combo and so on.  if N number of combos are reached then computer award is lit.
 * computer award can be gotten at underground shot.
 *
 */



#include <freewpc.h>
#include "dm/global_constants.h"

//constants
#define COMBO_WAIT_TIME  12
#define COMBO_HURRY_TIME  5
#define COMBO_EASY_GOAL  10
#define COMBO_EASY_GOAL_STEP  10
#define COMBO_VM_EASY_GOAL  5
#define COMBO_VM_EASY_GOAL_STEP  10

//local variables
__local__ U8 	combo_counter;
__local__ U8 	combo_goal;
__local__ U8 	combo_vm_goal;
__local__ U8 	combo_ls_goal;
__boolean	is_combos_killed;
__boolean	is_combos_restartable;


//external variables


//internally called function prototypes  --external found at protos.h
void combo_reset (void);
void flash_combos(void);
void choose_random_flag_set(void);
void combo_task (void);

/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
//we always start with these 3 lights on because those are the skillshots
void combo_reset (void) {
	flag_on (FLAG_IS_COMBO_SIDERAMP_ACTIVATED);
	flag_on (FLAG_IS_COMBO_LEFTRAMP_ACTIVATED);
	flag_off (FLAG_IS_COMBO_RIGHTRAMP_ACTIVATED);
	flag_on (FLAG_IS_COMBO_UNDER_ACTIVATED);
	flag_off (FLAG_IS_COMBO_CENTERRAMP_ACTIVATED);
	flag_off (FLAG_IS_COMBO_LEFTORB_ACTIVATED);
	flag_off (FLAG_IS_COMBO_RIGHTORB_ACTIVATED);
	is_combos_restartable = TRUE;

	if (flag_test (FLAG_IS_COMPUTER_ACTIVATED) ) 	lamp_tristate_flash (LM_COMPUTER);
	else 											lamp_tristate_off (LM_COMPUTER);

	all_arrow_update(); // at arrow_handler.c
}//end of function



CALLSET_ENTRY (combo, start_player) 	{
	combo_counter = 0;
	flag_off (FLAG_IS_COMPUTER_ACTIVATED);

	if (DM_IN_CAB_TEST) 	{
		combo_goal = 2;
		combo_vm_goal = 2;
		combo_ls_goal = 2;
	}
	else {
		combo_goal = COMBO_EASY_GOAL;
		combo_vm_goal = COMBO_VM_EASY_GOAL;
		combo_ls_goal = random_scaled (10) + 1;
	}

#ifdef CONFIG_DIFFICULTY_LEVEL
		combo_goal = system_config.num2comp_award;
		if (system_config.num2video < 5) combo_vm_goal = system_config.num2video; // o/w starts at easy goal as set above
#endif
}//end of function



CALLSET_ENTRY (combo, start_ball) 		{ combo_reset(); }
CALLSET_ENTRY (combo, valid_playfield) 	{ combo_init(); }


CALLSET_ENTRY (combo, end_ball) 		{
	task_kill_gid (GID_COMBO);
	kill_combos();
}



/****************************************************************************
 *
 * body
 *
 ****************************************************************************/
bool get_is_combos_killed(void) {
	return is_combos_killed;
}//end of function




bool get_is_combos_restartable (void) {
	return is_combos_restartable;
}//end of function




void combo_init(void) {
	is_combos_killed = FALSE;
	is_combos_restartable = TRUE;
	choose_random_flag_set();
	all_arrow_update(); // at arrow_handler.c
	task_create_gid1 (GID_COMBO, combo_task);
}//end of function





//this is a hard kill that prevents combos from restarting
//we only use this during certain modes
void kill_combos(void) {
	flag_off (FLAG_IS_COMBO_SIDERAMP_ACTIVATED);
	flag_off (FLAG_IS_COMBO_LEFTRAMP_ACTIVATED);
	flag_off (FLAG_IS_COMBO_RIGHTRAMP_ACTIVATED);
	flag_off (FLAG_IS_COMBO_UNDER_ACTIVATED);
	flag_off (FLAG_IS_COMBO_CENTERRAMP_ACTIVATED);
	flag_off (FLAG_IS_COMBO_LEFTORB_ACTIVATED);
	flag_off (FLAG_IS_COMBO_RIGHTORB_ACTIVATED);

	is_combos_killed = TRUE;
	is_combos_restartable = FALSE;
	all_arrow_update();
}//end of function






void combo_task (void) {
	task_sleep_sec(COMBO_WAIT_TIME);
	//no combo made yet so flash active lamps
	flash_combos();
	task_sleep_sec(COMBO_HURRY_TIME);
	//still no hits so turn off flags and lamps until something is hit
	flag_off (FLAG_IS_COMBO_SIDERAMP_ACTIVATED);
	flag_off (FLAG_IS_COMBO_LEFTRAMP_ACTIVATED);
	flag_off (FLAG_IS_COMBO_RIGHTRAMP_ACTIVATED);
	flag_off (FLAG_IS_COMBO_UNDER_ACTIVATED);
	flag_off (FLAG_IS_COMBO_CENTERRAMP_ACTIVATED);
	flag_off (FLAG_IS_COMBO_LEFTORB_ACTIVATED);
	flag_off (FLAG_IS_COMBO_RIGHTORB_ACTIVATED);
	is_combos_killed = TRUE;
	is_combos_restartable = TRUE;
	all_arrow_update();
	task_exit();
}//end of function







//flashing overides being on solid, so if multiple modes
//are running, lamp will flash, but when timer ends, will go back to solid
void flash_combos(void){
	if (flag_test (FLAG_IS_COMBO_SIDERAMP_ACTIVATED) ) 		lamp_tristate_flash (LM_SIDE_RAMP_ARROW);
	if (flag_test (FLAG_IS_COMBO_LEFTRAMP_ACTIVATED) ) 		lamp_tristate_flash (LM_LEFT_RAMP_ARROW);
	if (flag_test (FLAG_IS_COMBO_RIGHTRAMP_ACTIVATED) ) 	lamp_tristate_flash (LM_RIGHT_RAMP_ARROW);
	if (flag_test (FLAG_IS_COMBO_UNDER_ACTIVATED) ) 		lamp_tristate_flash (LM_UNDERGROUND_ARROW);
	if (flag_test (FLAG_IS_COMBO_CENTERRAMP_ACTIVATED) ) 	lamp_tristate_flash (LM_CENTER_RAMP_ARROW);
	if (flag_test (FLAG_IS_COMBO_LEFTORB_ACTIVATED) ) 		lamp_tristate_flash (LM_LEFT_LOOP_ARROW);
	if (flag_test (FLAG_IS_COMBO_RIGHTORB_ACTIVATED) ) 		lamp_tristate_flash (LM_RIGHT_LOOP_ARROW);
}//end of function






void combo_hit(void ) {
	__boolean is_goal_yet;
	is_goal_yet = FALSE;
	//see if video mode goal made
	if (++combo_counter >= combo_vm_goal  && !flag_test (FLAG_VIDEO_MODE_ENABLED) ) {
		if (DM_IN_CAB_TEST) 	combo_vm_goal += 2;
		else {
			combo_vm_goal += system_config.num2video;
		}//end of else

		is_goal_yet = TRUE;
		flag_on (FLAG_VIDEO_MODE_ENABLED);
		deff_start (DEFF_COMBO_EFFECT);
	}//END OF VIDEO MODE GOAL

	//see if computer award goal made
	if (combo_counter >= combo_goal  && !flag_test (FLAG_IS_COMPUTER_ACTIVATED) ) {
		if (DM_IN_CAB_TEST) 	combo_goal += 2;
		else {
			combo_goal += system_config.num2comp_award;
		}//end of else

		is_goal_yet = TRUE;
		computer_light_on(); 	//at underground.c
		if (!flag_test (FLAG_VIDEO_MODE_ENABLED) ) deff_start (DEFF_COMBO_EFFECT);
	}//END OF COMPUTER MODE GOAL

	//not at a goal yet
	if (!is_goal_yet) deff_start (DEFF_COMBO_EFFECT);

	// reset the task timer
	choose_random_flag_set();
	all_arrow_update();
	task_recreate_gid (GID_COMBO, combo_task);

	if (combo_counter >= combo_ls_goal && !flag_test (FLAG_LASER_SHOT_ENABLED) ) {
		flag_on (FLAG_LASER_SHOT_ENABLED);
		combo_ls_goal += 12;
	}
}//end of function






//this is for stacking
void combo_rehit_check(void ) {
	//video mode
	if (combo_counter >= combo_vm_goal  && !flag_test (FLAG_VIDEO_MODE_ENABLED) ) {
		combo_vm_goal += COMBO_EASY_GOAL_STEP;
		flag_on (FLAG_VIDEO_MODE_ENABLED);
	}
	//computer award
	else if (combo_counter >= combo_goal  && !flag_test (FLAG_IS_COMPUTER_ACTIVATED) ) {
		combo_goal += COMBO_EASY_GOAL_STEP;
		computer_light_on(); 	//at underground.c
	}
}//end of function




//called from computer award in underground.c
void comp_award_light_arrows(void) {
	is_combos_killed = FALSE;
	flag_on 	(FLAG_IS_COMBO_SIDERAMP_ACTIVATED);
	flag_on 	(FLAG_IS_COMBO_LEFTRAMP_ACTIVATED);
	flag_on 	(FLAG_IS_COMBO_RIGHTRAMP_ACTIVATED);
	flag_on 	(FLAG_IS_COMBO_UNDER_ACTIVATED);
	flag_on 	(FLAG_IS_COMBO_CENTERRAMP_ACTIVATED);
	flag_on 	(FLAG_IS_COMBO_LEFTORB_ACTIVATED);
	flag_on 	(FLAG_IS_COMBO_RIGHTORB_ACTIVATED);
	all_arrow_update();
	task_recreate_gid (GID_COMBO, combo_task);
}//end of function





/****************************************************************************
 *
 * randomize flag chosen
 *
 * we are using a very stupid and in-elegant
 * way of randomness - basically, we have a number
 * of predefined sets of flags and we randomly
 * pick one of those sets
 ****************************************************************************/
void choose_random_flag_set(void) {
	U8 random_chooser;
	random_chooser = random_scaled(5);
	switch (random_chooser) {
	case 0:
		flag_on 	(FLAG_IS_COMBO_SIDERAMP_ACTIVATED);
		flag_on 	(FLAG_IS_COMBO_LEFTRAMP_ACTIVATED);
		flag_off 	(FLAG_IS_COMBO_RIGHTRAMP_ACTIVATED);
		flag_off 	(FLAG_IS_COMBO_UNDER_ACTIVATED);
		flag_on 	(FLAG_IS_COMBO_CENTERRAMP_ACTIVATED);
		flag_off 	(FLAG_IS_COMBO_LEFTORB_ACTIVATED);
		flag_on 	(FLAG_IS_COMBO_RIGHTORB_ACTIVATED);
		break;
	case 1:
		flag_on 	(FLAG_IS_COMBO_SIDERAMP_ACTIVATED);
		flag_on 	(FLAG_IS_COMBO_LEFTRAMP_ACTIVATED);
		flag_off 	(FLAG_IS_COMBO_RIGHTRAMP_ACTIVATED);
		flag_off 	(FLAG_IS_COMBO_UNDER_ACTIVATED);
		flag_off 	(FLAG_IS_COMBO_CENTERRAMP_ACTIVATED);
		flag_on 	(FLAG_IS_COMBO_LEFTORB_ACTIVATED);
		flag_off 	(FLAG_IS_COMBO_RIGHTORB_ACTIVATED);
		break;
	case 2:
		flag_off 	(FLAG_IS_COMBO_SIDERAMP_ACTIVATED);
		flag_off 	(FLAG_IS_COMBO_LEFTRAMP_ACTIVATED);
		flag_on 	(FLAG_IS_COMBO_RIGHTRAMP_ACTIVATED);
		flag_on 	(FLAG_IS_COMBO_UNDER_ACTIVATED);
		flag_on 	(FLAG_IS_COMBO_CENTERRAMP_ACTIVATED);
		flag_off 	(FLAG_IS_COMBO_LEFTORB_ACTIVATED);
		flag_on 	(FLAG_IS_COMBO_RIGHTORB_ACTIVATED);
		break;
	case 3:
		flag_off 	(FLAG_IS_COMBO_SIDERAMP_ACTIVATED);
		flag_off 	(FLAG_IS_COMBO_LEFTRAMP_ACTIVATED);
		flag_on 	(FLAG_IS_COMBO_RIGHTRAMP_ACTIVATED);
		flag_on 	(FLAG_IS_COMBO_UNDER_ACTIVATED);
		flag_off 	(FLAG_IS_COMBO_CENTERRAMP_ACTIVATED);
		flag_on 	(FLAG_IS_COMBO_LEFTORB_ACTIVATED);
		flag_off 	(FLAG_IS_COMBO_RIGHTORB_ACTIVATED);
		break;
	case 4:
		flag_on 	(FLAG_IS_COMBO_SIDERAMP_ACTIVATED);
		flag_off 	(FLAG_IS_COMBO_LEFTRAMP_ACTIVATED);
		flag_on 	(FLAG_IS_COMBO_RIGHTRAMP_ACTIVATED);
		flag_off 	(FLAG_IS_COMBO_UNDER_ACTIVATED);
		flag_off 	(FLAG_IS_COMBO_CENTERRAMP_ACTIVATED);
		flag_off 	(FLAG_IS_COMBO_LEFTORB_ACTIVATED);
		flag_on 	(FLAG_IS_COMBO_RIGHTORB_ACTIVATED);
		break;
	}//end of switch
	//if 1 or less shot away from computer award then do not light underground shot
	if (	flag_test(FLAG_IS_COMBO_UNDER_ACTIVATED)
		&&	(flag_test(FLAG_IS_COMPUTER_ACTIVATED)
		||	combo_goal == combo_counter + 1) )			flag_off 	(FLAG_IS_COMBO_UNDER_ACTIVATED);
}//end of function


/****************************************************************************
 *
 * display effects
 *
 ****************************************************************************/
void combo_effect_deff(void) {
	U16 fno;
	if (DM_IN_DMD_TEST) {
		combo_counter++;
		if (combo_counter % 3 == 0) 	flag_on(FLAG_VIDEO_MODE_ENABLED);
		else							flag_off(FLAG_VIDEO_MODE_ENABLED);

		if (combo_counter % 4 == 0) 	flag_on(FLAG_IS_COMPUTER_ACTIVATED);
		else							flag_off(FLAG_IS_COMPUTER_ACTIVATED);
	}

	sound_start (ST_EFFECT, SUBWAY2, SL_2S, SP_NORMAL);

	if (combo_counter % 4 == 0 ) {
		for (fno = IMG_COMBO_MARIO_START; fno <= IMG_COMBO_MARIO_END; fno += 2) {
			dmd_alloc_pair ();
			frame_draw(fno);
			dmd_show2 ();
			task_sleep (TIME_133MS);
		}//end of for loop
		sound_start (ST_EFFECT, SUBWAY2, SL_2S, SP_NORMAL);
		dmd_map_overlay ();
		dmd_clean_page_low ();
				if (flag_test (FLAG_IS_COMPUTER_ACTIVATED) ) sprintf ("COMPUTER READY");
				else 										 sprintf ("%d TO COMPUTER", combo_goal - combo_counter);
		font_render_string_center (&font_fixed6, DMD_MIDDLE_X, DMD_MED_CY_BOTTOM_LINE, sprintf_buffer);
		sprintf ("%d  COMBOS", combo_counter);
		font_render_string_center (&font_fixed10, DMD_MIDDLE_X - 15, DMD_MED_CY_1 + 4, sprintf_buffer);
		dmd_text_outline ();
		dmd_alloc_pair ();
		frame_draw(IMG_COMBO_MARIO_END);
		dmd_overlay_outline ();
		dmd_show2 ();
	}//end of 	if (combo_counter == 0 )

	if (combo_counter % 4 == 1) {
		for (fno = IMG_COMBO3_MARIO_START; fno <= IMG_COMBO3_MARIO_END; fno += 2) {
			dmd_alloc_pair ();
			frame_draw(fno);
			dmd_show2 ();
			task_sleep (TIME_133MS);
		}//end of for loop
		sound_start (ST_EFFECT, SUBWAY2, SL_2S, SP_NORMAL);
		dmd_map_overlay ();
		dmd_clean_page_low ();
				if (flag_test (FLAG_VIDEO_MODE_ENABLED) )	sprintf ("VIDEO READY");
				else 										sprintf ("%d TO VIDEO", combo_vm_goal - combo_counter);
		font_render_string_center (&font_fixed6, DMD_MIDDLE_X, DMD_MED_CY_BOTTOM_LINE, sprintf_buffer);
		sprintf ("%d  COMBOS", combo_counter);
		font_render_string_center (&font_fixed10, DMD_MIDDLE_X - 15, DMD_MED_CY_1 + 4, sprintf_buffer);
		dmd_text_outline ();
		dmd_alloc_pair ();
		frame_draw(IMG_COMBO3_MARIO_END);
		dmd_overlay_outline ();
		dmd_show2 ();
	}//end of 	if (combo_counter == 1)

	else if (combo_counter % 4 == 2) {
		for (fno = IMG_COMBO2_MARIO_START; fno <= IMG_COMBO2_MARIO_END; fno += 2) {
			dmd_alloc_pair ();
			frame_draw(fno);
			dmd_show2 ();
			task_sleep (TIME_133MS);
		}//end of for loop
		dmd_map_overlay ();
		dmd_clean_page_low ();
		sprintf ("%d", combo_counter);
		font_render_string_center (&font_halobold22num, DMD_MIDDLE_X, DMD_MIDDLE_Y, sprintf_buffer);
		dmd_text_outline ();
		dmd_alloc_pair ();
		frame_draw(IMG_COMBO2_MARIO_END);
		dmd_overlay_outline ();
		dmd_show2 ();
		}//end of if (combo_counter == 2)

	if (combo_counter % 4 == 3 ) {
		for (fno = IMG_COMBO4_MARIO_START; fno <= IMG_COMBO4_MARIO_END; fno += 2) {
			dmd_alloc_pair ();
			frame_draw(fno);
			dmd_show2 ();
			task_sleep (TIME_133MS);
		}//end of for loop
		sound_start (ST_EFFECT, SUBWAY2, SL_2S, SP_NORMAL);
		dmd_map_overlay ();
		dmd_clean_page_low ();
		sprintf ("%d  COMBOS", combo_counter);
		font_render_string_center (&font_halobold12, DMD_MIDDLE_X, DMD_MIDDLE_Y, sprintf_buffer);
		dmd_text_outline ();
		dmd_alloc_pair ();
		frame_draw(IMG_COMBO4_MARIO_END);
		dmd_overlay_outline ();
		dmd_show2 ();
	}//end of 	if (combo_counter == 3)

	task_sleep_sec (2);
	deff_exit ();
}//end of deff



