
/* This file was autogenerated by 'ctemp' from  for class shakermotor. */


/*
 * demolition man
 * shaker.c
 *
 * written by James Cardona
 *
 *
 * */
/* CALLSET_SECTION (shaker, __machine4__) */

#include <freewpc.h>
#include "shaker.h"


//the time unit count that, when reached, should turn on shaker
__fastram__ time_unit_t shaker_on_time;

//keep track of time ticks of shaker on and off time
__fastram__ time_unit_t shaker_on_off_time_counter;


//what is total of off and on time
// (since we specify on time above, this effectively sets the duty cycle)
__fastram__ time_unit_t shaker_on_off_total_time;

//how long is shaker to run
__fastram__ time_unit_t shaker_timeout;


__fastram__ __boolean timeout;






/* Start the output using duty/duration */
void shaker_start (shaker_power_t on_time, U8 timeout_time) {
	if (timeout) {
				timeout = FALSE;
				rtt_disable ();
				sol_disable (SOL_SHAKER_MOTOR);
			
				shaker_on_off_time_counter	= 16;
				shaker_on_off_total_time 	= 16;
			
				if (on_time > SHAKER_HALF_ON) 			on_time = SHAKER_HALF_ON;
				if (on_time == SHAKER_OFF) 				shaker_on_time	= 0;
				if (on_time == SHAKER_ONE_QUARTER_ON) 	shaker_on_time	= 4;
				if (on_time == SHAKER_THREE_EIGTH_ON) 	shaker_on_time	= 6;
				if (on_time == SHAKER_HALF_ON) 			shaker_on_time	= 8;
			//	if (on_time == SHAKER_THREEQUARTER_ON) 	shaker_on_time	= 12;
			//	if (on_time == SHAKER_FULL_ON) 			shaker_on_time	= 16;
			
				//since timeout is called once for every pass through the timer
				// we have 4ms * 16 counts = 64ms for 1 pass
				//and then a max time out of 16 yields 16 * 64ms = approximately 1 second
				if (timeout_time > 16) 	timeout_time = 16;
				shaker_timeout	= timeout_time;
			
				rtt_enable ();
				task_sleep_sec(1);
				timeout = TRUE;
	}
}//end of function



/* Stop the output */
void shaker_stop (void) {
	rtt_disable ();
	sol_disable (SOL_SHAKER_MOTOR);
	shaker_on_off_time_counter 	= 0;
	shaker_on_off_total_time 	= 0;
	shaker_on_time 				= 0;
	rtt_enable ();
				task_sleep_sec(1);
				timeout = TRUE;
}



CALLSET_ENTRY (shaker, init) {
	timeout = TRUE;
	shaker_on_off_time_counter 	= 0;
	shaker_timeout 				= 0;
	shaker_on_off_total_time 	= 0;
	shaker_on_time 				= 0;
}



CALLSET_ENTRY (shaker, tilt, stop_game, amode_start) {
	shaker_stop ();
}

