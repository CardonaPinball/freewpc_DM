/*
 * demolition man
 * global_constants.h
 *
 * written by James Cardona
 *
 */
#include <freewpc.h>


#ifndef _DM_GLOBAL_CONSTANTS_H
#define _DM_GLOBAL_CONSTANTS_H
/****************************************************************************
 * flag constants for bit masks
 ****************************************************************************/
//MODE 1 FLAGS
#define 	ACMAG_COMPLETED 		0x1/* Bitmask  */
#define 	FRENZY_COMPLETED 		0x2/* Bitmask  */
#define 	BREAKOUT_COMPLETED 		0x4/* Bitmask  */
#define 	SJETS_COMPLETED 		0x8/* Bitmask  */
#define 	CAP_SIM_COMPLETED 		0x10/* Bitmask  */
#define 	EXPLODE_COMPLETED 		0x20/* Bitmask  */
#define 	CHASE_COMPLETED 		0x40/* Bitmask  */
#define 	HUXLEY_COMPLETED 		0x80/* Bitmask  */

//MODE 2 FLAGS
#define 	FORTRESS_COMPLETED 		0x1/* Bitmask  */
#define 	MUSEUM_COMPLETED 		0x2/* Bitmask  */
#define 	WASTELAND_COMPLETED 	0x4/* Bitmask  */
#define 	CRYO_COMPLETED 			0x8/* Bitmask  */
#define 	DTIME_COMPLETED 		0x10/* Bitmask  */
#define 	BITF_COMPLETED 			0x20/* Bitmask  */


//capture_simon_arrow FLAG
#define 	CAPSIM_SIDERAMP 		0x1/* Bitmask  */
#define 	CAPSIM_SIDERAMP_OFF 	0xFE/* Bitmask  */
#define 	CAPSIM_LEFTRAMP 		0x2/* Bitmask  */
#define 	CAPSIM_LEFTRAMP_OFF 	0xFD/* Bitmask  */
#define 	CAPSIM_RIGHTRAMP 		0x4/* Bitmask  */
#define 	CAPSIM_RIGHTRAMP_OFF 	0xFB/* Bitmask  */
#define 	CAPSIM_UNDERGRND 		0x8/* Bitmask  */
#define 	CAPSIM_UNDERGRND_OFF 	0xF7/* Bitmask  */
#define 	CAPSIM_CENTERRAMP 		0x10/* Bitmask  */
#define 	CAPSIM_CENTERRAMP_OFF 	0xEF/* Bitmask  */
#define 	CAPSIM_LEFTORB	 		0x20/* Bitmask  */
#define 	CAPSIM_LEFTORB_OFF 		0xDF/* Bitmask  */
#define 	CAPSIM_RIGHTORB 		0x40/* Bitmask  */
#define 	CAPSIM_RIGHTORB_OFF 	0xBF/* Bitmask  */


//jackpot ramps constants for masks
#define lramp_mask  0x1
#define rramp_mask  0x2
#define sramp_mask  0x4
#define cramp_mask  0x8
#define lloop_mask  0x10 /*since this is hex, 10h = 16d*/
#define rloop_mask  0x20 /*since this is hex, 20h = 32d*/
#define ugrnd_mask  0x40 /*since this is hex, 40h = 64d*/













/****************************************************************************
 * DMD display coordinates
 ****************************************************************************/
//max width is 128
#define DMD_MIDDLE_X 	64
#define DMD_MIDDLE_Y	16

#define DMD_LEFT_X 		10
#define DMD_RIGHT_X 	90

/****************************************************************************/
//for large fonts of height > 16 but < 30
#define DMD_BIG_CY_Cent 16


//max height is 32 - for larger fonts less than 14
#define DMD_BIG_CY_Top 	8
#define DMD_BIG_CY_Bot 	24


//max height is 32 - these are for fonts of height 9 and number is center of font
#define DMD_MED_CY_1 	5
#define DMD_MED_CY_2 	14
#define DMD_MED_CY_BOTTOM_LINE 	25


//max height is 32 - these are for fonts of height 5 and number is center of font
#define DMD_SMALL_CY_1 	4
#define DMD_SMALL_CY_2 	10
#define DMD_SMALL_CY_3 	16
#define DMD_SMALL_CY_4 	22
#define DMD_SMALL_CY_BOTTOM_LINE 	28






/****************************************************************************
 * SCORING CONSTANTS - CLAW MODES
 ****************************************************************************/
// no start points
// each successive mode start score higher
#define ACMAG_HIT_SCORE_1 		SC_5M
#define ACMAG_HIT_SCORE_2  		SC_8M

// no start points
// each successive mode start score higher
#define CAPSIM_HIT_SCORE_1 		SC_5M
#define CAPSIM_HIT_SCORE_2  	SC_8M
#define CAPSIM_HIT_SCORE_3  	SC_15M
#define CAP_SIM_COMPLETED_SCORE	SC_10M

//This is a "fast scoring" mode where all small point switches such as jets and rebounds score higher
#define PRIS_BREAK_START_SCORE1	SC_10M
#define PRIS_BREAK_START_SCORE2	SC_15M
#define PRIS_BREAK_HIT_SCORE	SC_500K

//standup frenzy - hit al the standup targets
#define FRENZY_START_SCORE		SC_10M
#define FRENZY_HIT_SCORE		SC_3M
#define FRENZY_ADD_SCORE		SC_1M //NUMBER HITS * THIS NUMBER

//superjets - goal is typically 20 or 25 jets hit within the time limit
#define SUPERJETS_START_SCORE1	SC_6M
#define SUPERJETS_START_SCORE2	SC_12M
#define SUPERJETS_HIT_SCORE1	SC_1M
#define SUPERJETS_HIT_SCORE2	SC_2M
#define SUPERJETS_GOAL_SCORE	SC_10M



/****************************************************************************
 * SCORING CONSTANTS - MULTIBALLS
 ****************************************************************************/
//multiball jackpot scores
#define FORTRESS_MB_SCORE				SC_5M //start of mode
#define FORTRESS_JP_MB_SCORE			SC_10M
#define FORTRESS_SUPER_JP_MB_SCORE		SC_20M

#define MUSEUM_MB_SCORE					SC_10M //start of mode
#define MUSEUM_JP_MB_SCORE				SC_15M
#define MUSEUM_SUPER_JP_MB_SCORE		SC_25M

#define WASTELAND_MB_SCORE				SC_10M //start of mode
#define WASTELAND_JP_MB_SCORE			SC_15M
#define WASTELAND_SUPER_JP_MB_SCORE		SC_25M

#define CRYOPRISON_MB_SCORE				SC_15M //start of mode
#define CRYOPRISON_JP_MB_SCORE			SC_15M
#define CRYOPRISON_SUPER_JP_MB_SCORE	SC_30M


/****************************************************************************
 * SCORING CONSTANTS - NON-CLAW MODES
 ****************************************************************************/
// no start points
// each successive mode start score higher
#define CARCHASE_HIT_SCORE_1 	SC_6M
#define CARCHASE_HIT_SCORE_2  	SC_12M

#define EXPLODE_START  			SC_1M
#define EXPLODE_SCORE			SC_200K //this is multiplied by count down timer (30 to 0)




/****************************************************************************
 * SCORING CONSTANTS - WIZARD MODES
 ****************************************************************************/
//started by starting 4 non-claw modes and making a huxley
//which is hitting the retina scan in reverse
#define HUXLEY_START_SCORE			SC_15M
#define HUXLEY_MODE_HIT_SCORE		SC_3M

//started by starting 5 claw modes and making underground shot
//like a normal MB mode except all jackpot shots are lit
#define DEMOTIME_JP_MB_SCORE		SC_15M


//started by completing all 4 multiballs modes and making top popper shot
#define BACK_IN_THE_FRIDGE_SCORE		SC_15M
#define BACK_IN_THE_FRIDGE_HIT_SCORE	SC_15M



/****************************************************************************
 * SCORING CONSTANTS - REGULAR SWITCHES
 ****************************************************************************/
//NOTE: car crash end switch are not listed here since their values are listed on the playfield lights
//and then should not be changed:: they are 3M, 6M, and 10M
#define CARCRASH_SCORE_CAR1		SC_250K
#define CARCRASH_SCORE_CAR2		SC_500K //if playfield light not lit

//THIS IS MULTIPLIED BY RETINA SCAN MULTIPLIER - max of 2
#define EJECT_SCORE 			SC_1M

#define EYEBALL_SCORE			SC_1M

//LOCATED AT SIMPLE SWITCHES
#define OUTLANE_SCORE			SC_5770
#define SIMPLE_SWITCH			SC_1010
#define SLING_SCORE				SC_540

#define INLANE_SCORE			SC_5770

#define HUXLEY_SCORE			SC_1M

#define STANDUP_SCORE			SC_100K

#define JETS_HIT_SCORE			SC_250K
#define JETS_GOAL_SCORE1		SC_3M //HITTING A BUNCH OF JETS - 20 OR MORE
#define JETS_GOAL_SCORE2		SC_4M
#define JETS_GOAL_SCORE3		SC_5M
#define JETS_GOAL_SCORE4		SC_6M
#define JETS_GOAL_SCORE5		SC_7M

#define ORBIT_SCORE				SC_100K
#define ORBIT_GOAL_SCORE		SC_250K

#define ALL_ROLLOVERS_SCORE		SC_1M
#define ROLLOVERS_SCORE1		SC_100K //ROLLOVERS HIT THAT ARE ALREADY LIT
#define ROLLOVERS_SCORE2		SC_250K //ROLLOVERS HIT THAT ARE NOT ALREADY LIT

#define RAMPS_ENTER_SCORE		SC_100K
#define RAMPS_MADE_SCORE		SC_250K

#define TOP_POP_SCORE			SC_100K
#define BOT_POP_SCORE			SC_100K

#define SKILLSHOT_SCORE			SC_1M

#define LASER_SHOT_SCORE		SC_3M

#endif /* _DM_GLOBAL_CONSTANTS_H */
