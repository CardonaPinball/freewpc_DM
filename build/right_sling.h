
/* This file was autogenerated by 'ctemp' from  for class sling+ spsol. */


#include <sling.h>

#undef INST_MASK
#define INST_MASK (1 << 1)

extern __fastram__ U8 right_sling_timer;

void right_sling_enable (void);
void right_sling_disable (void);

extern inline U8 right_sling_enabled_p (void)
{
	return sling_enables & INST_MASK;
}


extern inline U8 right_sling_running_p (void)
{
	return sling_running & INST_MASK;
}


extern inline void right_sling_service (void)
{
	/* If the timer is nonzero, then either the solenoid
	is ON, or it is in its forced OFF phase.  It is
	not necessary to poll the switch here. */
	if (unlikely (right_sling_timer))
	{
		/* Decrement the timer. */
		right_sling_timer--;

		/* Check for expiry.  Handle accordingly */
		if (right_sling_timer == 0)
		{
			if (right_sling_running_p ())
			{
				/* If the timer expires in the ON phase, then
				switch to the OFF phase.  Also, turn off the
				solenoid now. */
				sol_disable (SOL_RIGHT_SLING);
				right_sling_timer = 16;
				sling_running &= ~INST_MASK;
			}
			else
			{
				/* When the timer expires in the OFF phase, poll the
				switch to see that it cleared correctly.  If it hasn't,
				extend the off phase again and continue to do so until
				the switch is cleared. */
				if (rt_switch_poll (SW_RIGHT_SLING))
				{
					right_sling_timer = 16;
				}
			}
		}
	}
	else if (right_sling_enabled_p () && rt_switch_poll (SW_RIGHT_SLING))
	{
		/* When the solenoid is not running, poll its switch
		and see if it should be started. */
		sol_enable (SOL_RIGHT_SLING);
		sling_running |= INST_MASK;
		right_sling_timer = 3;
	}
}


