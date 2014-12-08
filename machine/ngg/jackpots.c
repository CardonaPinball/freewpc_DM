/*
 * demolition man
 * jackpots.c
 *
 * written by James Cardona
 *
 *
 */
/* CALLSET_SECTION (jackpots, __machine5__) */

#include <freewpc.h>
#include "ngg/global_constants.h" 


//local variables
U8 	jackpot_arrows;


//external variables


//prototypes

/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
void jackpot_reset (void) {
	jackpot_arrows = 0x0;
	lramp_jackpot_light_off();
	rramp_jackpot_light_off();
	sramp_jackpot_light_off();
	cramp_jackpot_light_off();
	underground_jackpot_light_off();
	ll_jackpot_light_off();
	rl_jackpot_light_off();
}//end of function



CALLSET_ENTRY (jackpot, start_player, start_ball, end_ball) 		{
	jackpot_reset();
	end_super_jackpot_reminder();

}





/****************************************************************************
 * body
 *
 ****************************************************************************/
void set_jackpot_arrows (U8 arrow_flag) {
	jackpot_arrows |= arrow_flag;  // flag or unflag the bit
}//end of function



void set_jackpot_arrows_all_off (void) {
	jackpot_arrows = 0x0;
}//end of function



__boolean get_jackpot_arrows (U8 arrow_flag) {
		if (jackpot_arrows & arrow_flag) return TRUE;
		else return FALSE;
}//end of function






void score_jackpot(void) {
	if 		(get_fortress_running ()  )				  		fortress_jackpot_made();
	else if (get_museum_running () )  						museum_jackpot_made();
	else if (get_cryoprison_running () )  					cryoprison_jackpot_made();
	else if (get_wasteland_running () )  					wasteland_jackpot_made();
	else if (get_demotime_running () )  					demotime_jackpot_made();
}//END OF FUNCTION



void score_super_jackpot (void) {
	if 		(get_fortress_running () )  					fortress_award_super_jackpot();
	else if (get_museum_running () )  						museum_award_super_jackpot();
	else if (get_cryoprison_running () )  					cryoprison_award_super_jackpot();
	else if (get_wasteland_running () )  					wasteland_award_super_jackpot();

	end_super_jackpot_reminder();
}//end of function




void choose_single_jackpot(void) {
	U8 random_chooser;
	random_chooser = random_scaled(7); // choose random # from 0 to 6
	U8 mask = 1;//make a 1 bit flag so that only 1 jackpot is lit
	mask <<= random_chooser;//slide the bit over a random # of times - could be 0
	//turn on the appropriate jackpot
	//TODO: handle jackpots already picked
	if (lramp_mask & mask) { set_jackpot_arrows(lramp_mask);  lramp_jackpot_light_on(); }
	if (rramp_mask & mask) { set_jackpot_arrows(rramp_mask);  rramp_jackpot_light_on(); }
	if (sramp_mask & mask) { set_jackpot_arrows(sramp_mask);  sramp_jackpot_light_on(); }
	if (cramp_mask & mask) { set_jackpot_arrows(cramp_mask);  cramp_jackpot_light_on(); }
	if (lloop_mask & mask) { set_jackpot_arrows(lloop_mask);  ll_jackpot_light_on(); }
	if (rloop_mask & mask) { set_jackpot_arrows(rloop_mask);  rl_jackpot_light_on(); }
	if (ugrnd_mask & mask) { set_jackpot_arrows(ugrnd_mask);  underground_jackpot_light_on(); }
}//end of function



void choose_random_jackpot(void) {
	jackpot_reset ();
	choose_single_jackpot();
	all_arrow_update(); // at arrow_handler.c
}//end of function



void choose_multiple_random_jackpot(U8 numOfJackpots) {
	jackpot_reset ();
	if (numOfJackpots > 5) set_all_jackpots ();
	else {
		U8 i;
		for (i = 0; i < numOfJackpots; i++) {
			choose_single_jackpot();
		}//end of loop
		all_arrow_update(); // at arrow_handler.c
	}//end of else
}//end of function



//this only used for wizard modes  --- CURRENTLY ONLY DEMO TIME
void set_all_jackpots (void) {
	set_jackpot_arrows(lramp_mask + rramp_mask + sramp_mask + cramp_mask + lloop_mask + rloop_mask + ugrnd_mask);
	lramp_jackpot_light_on();
	rramp_jackpot_light_on();
	sramp_jackpot_light_on();
	cramp_jackpot_light_on();
	ll_jackpot_light_on();
	rl_jackpot_light_on();
	underground_jackpot_light_on();
	all_arrow_update(); // at arrow_handler.c
}//end of function





