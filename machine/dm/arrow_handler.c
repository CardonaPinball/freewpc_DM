/*
 * demolition man
 * arrow_handler.c
 *
 * written by James Cardona
 *
 */

#include <freewpc.h>
#include "dm/global_constants.h"

//local variables

//prototypes

/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
CALLSET_ENTRY (arrow_handler, start_player, start_ball) 	{
	flag_off (FLAG_IS_UGROUND_ARROW_ACTIVATED);

	flag_off (FLAG_IS_R_LOOP_ARROW_ACTIVATED);
	flag_off (FLAG_IS_L_LOOP_ARROW_ACTIVATED);

	flag_off (FLAG_IS_L_RAMP_ARROW_ACTIVATED);
	flag_off (FLAG_IS_C_RAMP_ARROW_ACTIVATED);
	flag_off (FLAG_IS_S_RAMP_ARROW_ACTIVATED);
	flag_off (FLAG_IS_R_RAMP_ARROW_ACTIVATED);
}//end of function


/****************************************************************************
 *
 * Arrow handlers
 *
 ****************************************************************************/
void center_ramp_arrow_update(void) {
	if (	get_capture_simon_arrows (CAPSIM_CENTERRAMP)
		||	is_acmag_running ()
		||	flag_test (FLAG_IS_COMBO_CENTERRAMP_ACTIVATED)
	//	||	get_jackpot_arrows(cramp_mask)
		)
		cramp_arrow_light_on();
	else
		cramp_arrow_light_off();
}//end of function



void uground_arrow_update(void) {
	if (	get_capture_simon_arrows (CAPSIM_UNDERGRND)
		||	flag_test (FLAG_IS_COMBO_UNDER_ACTIVATED)
	//	||	get_jackpot_arrows(ugrnd_mask)
		)
			underground_arrow_light_on();
	else
			underground_arrow_light_off();
}//end of function



void l_ramp_arrow_update(void) {
	if (	get_capture_simon_arrows (CAPSIM_LEFTRAMP)
		||	flag_test (FLAG_IS_COMBO_LEFTRAMP_ACTIVATED)
	//	||	get_jackpot_arrows(lramp_mask)
		)
		lramp_arrow_light_on();
	else
		lramp_arrow_light_off();
}//end of function



void s_ramp_arrow_update(void) {
	if (	get_capture_simon_arrows(CAPSIM_SIDERAMP)
		||	flag_test (FLAG_IS_COMBO_SIDERAMP_ACTIVATED)
	//	||	get_jackpot_arrows(sramp_mask)
		)
		sramp_arrow_light_on();
	else
		sramp_arrow_light_off();
}//end of function


void r_ramp_arrow_update(void) {
	if (	get_capture_simon_arrows(CAPSIM_RIGHTRAMP)
		||	flag_test (FLAG_IS_COMBO_RIGHTRAMP_ACTIVATED)
	//	||	get_jackpot_arrows(rramp_mask)
		)
		rramp_arrow_light_on();
	else
		rramp_arrow_light_off();
}//end of function




void l_orb_arrow_update(void) {
	if (	get_capture_simon_arrows (CAPSIM_LEFTORB)
		||	flag_test (FLAG_IS_COMBO_LEFTORB_ACTIVATED)
	//	||	get_jackpot_arrows(lloop_mask)
		)
		ll_arrow_light_on();
	else
		ll_arrow_light_off();
}//end of function



void r_orb_arrow_update(void) {
	if (	get_capture_simon_arrows (CAPSIM_RIGHTORB)
		||	flag_test (FLAG_IS_COMBO_RIGHTORB_ACTIVATED)
	//	||	get_jackpot_arrows(rloop_mask)
		)
		rl_arrow_light_on();
	else
		rl_arrow_light_off();
}//end of function


void all_arrow_update(void) {
	center_ramp_arrow_update();
	l_ramp_arrow_update();
	r_ramp_arrow_update();
	s_ramp_arrow_update();
	l_orb_arrow_update();
	r_orb_arrow_update();
	uground_arrow_update();
}//end of function
