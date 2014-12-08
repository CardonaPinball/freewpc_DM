#include <freewpc.h>
#include "dm/global_constants.h"


void diverter_check (void) {
	if (	flag_test(FLAG_IS_R_RAMP_CLAWREADY)
		&&	!get_back_in_the_fridge_running()
		&&	!get_back_in_the_fridge_ending()
		&&	!get_fortress_running ()
		&&	!get_museum_running ()
		&&  !get_cryoprison_running ()
		&&  !get_wasteland_running ()
		&&  !get_demotime_running ()
		&&	!get_capture_simon_arrows (CAPSIM_RIGHTRAMP)
		&&	!is_huxley_running ()
		&&	!is_cryoclaw_mode_running () )
			rramp_clawready_on();
}//end of function
