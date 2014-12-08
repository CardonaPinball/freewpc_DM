/*
 */

#ifndef _BALLSAVE_H
#define _BALLSAVE_H

__common__ bool ballsave_test_active (void);
__common__ U8 ballsave_get_timer (void);
__common__ void ballsave_add_time(U8 secs);
__common__ void ballsave_disable(void);


#endif /* BALLSAVE_H */
