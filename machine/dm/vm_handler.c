/*
 * demolition man
 * vm_handler.c
 *
 * written by James Cardona
 *
 */
/* CALLSET_SECTION (vm_handler, __machine4__) */


#include <freewpc.h>
#include "dm/global_constants.h"


//constants


//local variables
U8 						video_mode_chooser;


//external variables


//internally called function prototypes  --external found at protos.h



/****************************************************************************
 * initialize  and exit
 ***************************************************************************/
CALLSET_ENTRY (vm_handler, start_player) {
	flag_off(FLAG_VIDEO_MODE_ENABLED);
	video_mode_chooser = 2; //kaboom is first - no longer random
}



/****************************************************************************
 *
 * body
 *
 ****************************************************************************/
U8 get_next_video_mode(void) {
	// if we are here then at least one VM is enabled as that is checked
	// prior to this function call

	//none of vm are disabled
	if (	system_config.disable_kaboom == NO
		&& 	system_config.disable_simon_says == NO
		&& 	system_config.disable_shooter == NO ) 		{ if (++video_mode_chooser > 2)	video_mode_chooser = 0; }

	//o/w check if 2 are disabled - 3 possible combinations
	else if (	system_config.disable_kaboom == YES
			&& 	system_config.disable_simon_says == YES ) 	video_mode_chooser = 2; //assign to shooter

	else if (	system_config.disable_kaboom == YES
			&& 	system_config.disable_shooter == YES ) 		video_mode_chooser = 1; //assign to simon says

	else if (	system_config.disable_shooter == YES
			&& 	system_config.disable_simon_says == YES ) 	video_mode_chooser = 0; //assign to kaboom

	//o/w check if 1 is disabled - 3 possible combinations
	else if ( system_config.disable_shooter == YES) { 		if (++video_mode_chooser > 1)	video_mode_chooser = 0; }
	else if ( system_config.disable_kaboom == YES ) { 		if (++video_mode_chooser > 2)	video_mode_chooser = 1; }
	else if ( system_config.disable_simon_says== YES ) { 	if (video_mode_chooser != 0)	video_mode_chooser = 0; else video_mode_chooser = 2; }

	return (video_mode_chooser);
}//end of function


