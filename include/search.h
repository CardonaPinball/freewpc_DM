#ifndef _SEARCH_H
#define _SEARCH_H

extern U8 ball_search_count;

__common__ void ball_search_timer_reset (void);
__common__ bool ball_search_timed_out (void);
__common__ void ball_search_timeout_set (U8 secs);
__common__ void ball_search_monitor_start (void);
__common__ void ball_search_monitor_stop (void);
__common__ void ball_search_run (void);
__common__ void ball_search_now (void);
__common__ void tilt_force_ball_search (void);

#ifdef MACHINE_BALL_SEARCH_TIME
#define BS_TIMEOUT_DEFAULT MACHINE_BALL_SEARCH_TIME
#else
#define BS_TIMEOUT_DEFAULT	20
#endif

#endif /* _SEARCH_H */
