
/* This file was autogenerated by 'ctemp' from  for class bivar2. */


 
/***********************************************************************
 * claw test:
 ***********************************************************************/
 

#include <freewpc.h>
#include <window.h>
#include <test.h>
#include "claw.h"

#define FRSR_WORKAROUND 1

enum {
	FIRST_TEST = 0,
	LEFT = FIRST_TEST,
	RIGHT,
	STOP,
	LAST_TEST = STOP
} claw_test_command;



char *claw_test_short_names[] = {
	"LEFT",
	"RIGHT",
	"STOP"
};

extern  claw_location_t claw_location;





void claw_test_draw (void) {
	dmd_alloc_low_clean ();
	//draw title
	font_render_string_center (&font_var5, 64, 2, "CLAW TEST");
	dmd_draw_horiz_line ((U16 *)dmd_low_buffer, 5);
	dmd_draw_horiz_line ((U16 *)dmd_low_buffer, 25);


	//display status of limit switches
	if (claw_location == 0) sprintf ("NONE");
	else if (claw_location == 1) sprintf ("LEFT");
	else if (claw_location == 2) sprintf ("RIGHT");
	font_render_string_center (&font_var5, 84, 13, sprintf_buffer);
	font_render_string_center (&font_var5, 44, 13, "LIMITS");

	//name of currently running test
	sprintf(claw_test_short_names[claw_test_command]);
	font_render_string_left (&font_var5, 0, 27, sprintf_buffer);

	dmd_show_low ();
}


void claw_test_init (void) { 
	global_flag_off(GLOBAL_FLAG_IS_CLAW_HOME); //turn off claw in home flag so that it is fixed when exiting
	claw_test_command = STOP; 
	if (switch_poll_logical (SW_CLAW_POSITION_2) ) claw_location = CLAW_LEFT;
	if (switch_poll_logical (SW_CLAW_POSITION_1) ) claw_location = CLAW_RIGHT;
}


void claw_test_thread (void) {
	for (;;) {
		task_sleep (TIME_1S);//this was set to run faster but seemed to cause problems
		claw_test_draw ();
	}
}



//up test button pressed
void claw_test_up (void) {
	if (claw_test_command < LAST_TEST)
		claw_test_command++;
}



//down test button pressed
void claw_test_down (void) {
	if (claw_test_command > FIRST_TEST)
		claw_test_command--;
}



//escape test button pressed
void claw_test_escape (void) {
	// stop everything
	claw_stop();
	window_pop();
}



//enter test button pressed
void claw_test_enter (void) {
	sound_send (SND_TEST_ENTER);
  	switch (claw_test_command) {
  		case LEFT:
				if (claw_location != CLAW_LEFT) claw_go_left();
			claw_test_command = STOP;
  		break;
  		case RIGHT:
			if (claw_location != CLAW_RIGHT) claw_go_right();
			claw_test_command = STOP;
  		break;
  		case STOP:
			claw_stop();
			claw_test_command = STOP;
  		break;
  	}
}



struct window_ops claw_test_window = {
	DEFAULT_WINDOW,
	.init = claw_test_init,
	.draw = claw_test_draw,
	.up = claw_test_up,
	.down = claw_test_down,
	.enter = claw_test_enter,
	.escape = claw_test_escape,
	.thread = claw_test_thread,
};



struct menu claw_test_item = {
	.name = "CLAW TEST", // needs CLAW for uppercase version of 'self' as test menu font doesn't have lower-case letters.
	.flags = M_ITEM,
	.var = { .subwindow = { &claw_test_window, NULL } },
};




