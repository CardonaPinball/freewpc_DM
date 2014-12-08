/* Autogenerated from machine/dm/dm.md by genmachine */

#include <freewpc.h>

#undef TRIAC_GI_STRING
#define TRIAC_GI_STRING(x) (x)

const char *names_of_switches [NUM_SWITCHES] = {
   [SW_LEFT_COIN] = "LEFT COIN",
   [SW_CENTER_COIN] = "CENTER COIN",
   [SW_RIGHT_COIN] = "RIGHT COIN",
   [SW_FOURTH_COIN] = "FOURTH COIN",
   [SW_ESCAPE] = "ESCAPE",
   [SW_DOWN] = "DOWN",
   [SW_UP] = "UP",
   [SW_ENTER] = "ENTER",
   [SW_LAUNCH_BUTTON] = "LAUNCH BUTTON",
   [SW_LEFT_HANDLE_BUTTON] = "LEFT HANDLE BUTTON",
   [SW_START_BUTTON] = "START BUTTON",
   [SW_TILT] = "TILT",
   [SW_LEFT_OUTLANE] = "LEFT OUTLANE",
   [SW_LEFT_INLANE] = "LEFT INLANE",
   [SW_RIGHT_INLANE] = "RIGHT INLANE",
   [SW_RIGHT_OUTLANE] = "RIGHT OUTLANE",
   [SW_SLAM_TILT] = "SLAM TILT",
   [SW_COIN_DOOR_CLOSED] = "COIN DOOR CLOSED",
   [SW_BUYIN_BUTTON] = "BUYIN BUTTON",
   [SW_ALWAYS_CLOSED] = "ALWAYS CLOSED",
   [SW_CLAW_POSITION_1] = "CLAW POSITION 1",
   [SW_CLAW_POSITION_2] = "CLAW POSITION 2",
   [SW_SHOOTER] = "SHOOTER",
   [SW_NOT_USED_1] = "NOT USED 1",
   [SW_TROUGH_1] = "TROUGH 1",
   [SW_TROUGH_2] = "TROUGH 2",
   [SW_TROUGH_3] = "TROUGH 3",
   [SW_TROUGH_4] = "TROUGH 4",
   [SW_TROUGH_5] = "TROUGH 5",
   [SW_TROUGH_JAM] = "TROUGH JAM",
   [SW_NOT_USED_2] = "NOT USED 2",
   [SW_STANDUP_5] = "STANDUP 5",
   [SW_LEFT_SLING] = "LEFT SLING",
   [SW_RIGHT_SLING] = "RIGHT SLING",
   [SW_LEFT_JET] = "LEFT JET",
   [SW_TOP_SLING] = "TOP SLING",
   [SW_RIGHT_JET] = "RIGHT JET",
   [SW_RIGHT_RAMP_ENTER] = "RIGHT RAMP ENTER",
   [SW_RIGHT_RAMP_EXIT] = "RIGHT RAMP EXIT",
   [SW_RIGHT_FREEWAY] = "RIGHT FREEWAY",
   [SW_LEFT_RAMP_ENTER] = "LEFT RAMP ENTER",
   [SW_LEFT_RAMP_EXIT] = "LEFT RAMP EXIT",
   [SW_CENTER_RAMP] = "CENTER RAMP",
   [SW_UPPER_REBOUND] = "UPPER REBOUND",
   [SW_LEFT_LOOP] = "LEFT LOOP",
   [SW_STANDUP_2] = "STANDUP 2",
   [SW_STANDUP_3] = "STANDUP 3",
   [SW_STANDUP_4] = "STANDUP 4",
   [SW_SIDE_RAMP_ENTER] = "SIDE RAMP ENTER",
   [SW_SIDE_RAMP_EXIT] = "SIDE RAMP EXIT",
   [SW_LEFT_ROLLOVER] = "LEFT ROLLOVER",
   [SW_CENTER_ROLLOVER] = "CENTER ROLLOVER",
   [SW_RIGHT_ROLLOVER] = "RIGHT ROLLOVER",
   [SW_EJECT] = "EJECT",
   [SW_ELEVATOR_INDEX] = "ELEVATOR INDEX",
   [SW_NOT_USED_3] = "NOT USED 3",
   [SW_CHASE_CAR_1] = "CHASE CAR 1",
   [SW_CHASE_CAR_2] = "CHASE CAR  2",
   [SW_TOP_POPPER] = "TOP POPPER",
   [SW_ELEVATOR_HOLD] = "ELEVATOR HOLD",
   [SW__NOT_USED_4] = " NOT USED 4",
   [SW_BOTTOM_POPPER] = "BOTTOM POPPER",
   [SW_EYEBALL_STANDUP] = "EYEBALL STANDUP",
   [SW_STANDUP_1] = "STANDUP 1",
   [SW_CLAW_CAPTURE_SIMON] = "CLAW CAPTURE SIMON",
   [SW_CLAW_SUPER_JETS] = "CLAW SUPER JETS",
   [SW_CLAW_PRISON_BREAK] = "CLAW PRISON BREAK",
   [SW_CLAW_FREEZE] = "CLAW FREEZE",
   [SW_CLAW_ACMAG] = "CLAW ACMAG",
   [SW_UPPER_LEFT_FLIPPER_GATE] = "UPPER LEFT FLIPPER GATE",
   [SW_CAR_CHASE_STANDUP] = "CAR CHASE STANDUP",
   [SW_LOWER_REBOUND] = "LOWER REBOUND",
   [SW_L_R_FLIPPER_EOS] = "L. R. FLIPPER EOS",
   [SW_L_R_FLIPPER_BUTTON] = "L. R. FLIPPER BUTTON",
   [SW_L_L_FLIPPER_EOS] = "L. L. FLIPPER EOS",
   [SW_L_L_FLIPPER_BUTTON] = "L. L. FLIPPER BUTTON",
   [SW_U_R_FLIPPER_EOS] = "U. R. FLIPPER EOS",
   [SW_U_R_FLIPPER_BUTTON] = "U. R. FLIPPER BUTTON",
   [SW_U_L_FLIPPER_EOS] = "U. L. FLIPPER EOS",
   [SW_U_L_FLIPPER_BUTTON] = "U. L. FLIPPER BUTTON",
};

const char *names_of_drives [NUM_POWER_DRIVES] = {
   [SOL_BALLSERVE] = "BALLSERVE",
   [SOL_BOTTOM_POPPER] = "BOTTOM POPPER",
   [SOL_LAUNCH] = "LAUNCH",
   [SOL_TOP_POPPER] = "TOP POPPER",
   [SOL_DIVERTER_POWER] = "DIVERTER POWER",
   [SOL_NOT_USED_H6_50V] = "NOT USED H6 50V",
   [SOL_KNOCKER] = "KNOCKER",
   [SOL_NOT_USED_H8_50V] = "NOT USED H8 50V",
   [SOL_LEFT_SLING] = "LEFT SLING",
   [SOL_RIGHT_SLING] = "RIGHT SLING",
   [SOL_LEFT_JET] = "LEFT JET",
   [SOL_TOP_SLING] = "TOP SLING",
   [SOL_RIGHT_JET] = "RIGHT JET",
   [SOL_EJECT] = "EJECT",
   [SOL_DIVERTER_HOLD] = "DIVERTER HOLD",
   [SOL__NOT_USED_L8_50V] = ": NOT USED L8 50V",
   [FLASH_CLAW_FLASHER] = "CLAW FLASHER",
   [SOL_ELEVATOR_MOTOR] = "ELEVATOR MOTOR",
   [SOL_CLAW_LEFT] = "CLAW LEFT",
   [SOL_CLAW_RIGHT] = "CLAW RIGHT",
   [FLASH_JETS_FLASHER] = "JETS FLASHER",
   [FLASH_SIDE_RAMP] = "SIDE RAMP",
   [FLASH_LEFT_RAMP_UP] = "LEFT RAMP UP",
   [FLASH_LEFT_RAMP_LOWER] = "LEFT RAMP LOWER",
   [SOL_SHAKER_MOTOR] = "SHAKER MOTOR",
   [FLASH_CAR_CHASE_LOWER] = "CAR CHASE LOWER",
   [FLASH_RIGHT_RAMP] = "RIGHT RAMP",
   [FLASH_EJECT_FL] = "EJECT FL",
   [SOL_LR_FLIP_POWER] = "L.R. FLIP POWER",
   [SOL_LR_FLIP_HOLD] = "L.R. FLIP HOLD",
   [SOL_LL_FLIP_POWER] = "L.L. FLIP POWER",
   [SOL_LL_FLIP_HOLD] = "L.L. FLIP HOLD",
   [SOL_CLAW_MAGNET] = "CLAW MAGNET",
   [SOL_NOT_USED] = "NOT USED",
   [SOL_UL_FLIP_POWER] = "U.L. FLIP POWER",
   [SOL_UL_FLIP_HOLD] = "U.L. FLIP HOLD",
   [FLASH_CAR_CHASE_UPPER] = "CAR CHASE UPPER",
   [FLASH_LOWER_REBOUND] = "LOWER REBOUND",
   [FLASH_EYEBALL] = "EYEBALL",
   [FLASH_CENTER_RAMP] = "CENTER RAMP",
   [FLASH_ELEVATOR_2] = "ELEVATOR 2",
   [FLASH_ELEVATOR_1] = "ELEVATOR 1",
   [FLASH_DIVERTER_FLASHER] = "DIVERTER FLASHER",
   [FLASH_RIGHT_RAMP_UP] = "RIGHT RAMP UP",
};

const char *names_of_lamps [PINIO_NUM_LAMPS] = {
   [LM_CHEST_PLATE] = "CHEST PLATE",
   [LM_FORTRESS_MULTIBALL] = "FORTRESS MULTIBALL",
   [LM_MUSEUM_MULTIBALL] = "MUSEUM MULTIBALL",
   [LM_CRYOPRISON_MULTIBALL] = "CRYOPRISON MULTIBALL",
   [LM_WASTELAND_MULTIBALL] = "WASTELAND MULTIBALL",
   [LM_SHOOT_AGAIN] = "SHOOT AGAIN",
   [LM_ACCESS_CLAW] = "ACCESS CLAW",
   [LM_LEFT_RAMP_EXPLODE] = "LEFT RAMP EXPLODE",
   [LM_RIGHT_RAMP_JACKPOT] = "RIGHT RAMP JACKPOT",
   [LM_RIGHT_LOOP_EXPLODE] = "RIGHT LOOP EXPLODE",
   [LM_LIGHT_QUICK_FREEZE] = "LIGHT QUICK FREEZE",
   [LM_FREEZE_4] = "FREEZE 4",
   [LM_CLAW_READY] = "CLAW READY",
   [LM_FREEZE_3] = "FREEZE 3",
   [LM_FREEZE_2] = "FREEZE 2",
   [LM_FREEZE_1] = "FREEZE 1",
   [LM_RIGHT_LOOP_JACKPOT] = "RIGHT LOOP JACKPOT",
   [LM_STANDUP_5] = "STANDUP 5",
   [LM_RIGHT_RAMP_ARROW] = "RIGHT RAMP ARROW",
   [LM_LEFT_RAMP_JACKPOT] = "LEFT RAMP JACKPOT",
   [LM_LEFT_LOOP_JACKPOT] = "LEFT LOOP JACKPOT",
   [LM_CAR_CRASH_TOP] = "CAR CRASH TOP",
   [LM_STANDUP_1] = "STANDUP 1",
   [LM_CAR_CRASH_CENTER] = "CAR CRASH CENTER",
   [LM_RIGHT_RAMP_EXPLODE] = "RIGHT RAMP EXPLODE",
   [LM_RIGHT_RAMP_CAR_CHASE] = "RIGHT RAMP CAR CHASE",
   [LM_QUICK_FREEZE] = "QUICK FREEZE",
   [LM_LEFT_RAMP_CAR_CHASE] = "LEFT RAMP CAR CHASE",
   [LM_EXTRA_BALL] = "EXTRA BALL",
   [LM_START_MULTIBALL] = "START MULTIBALL",
   [LM_CAR_CRASH_BOTTOM] = "CAR CRASH BOTTOM",
   [LM_LEFT_LOOP_EXPLODE] = "LEFT LOOP EXPLODE",
   [LM_UNDERGROUND_ARROW] = "UNDERGROUND ARROW",
   [LM_UNDERGROUND_JACKPOT] = "UNDERGROUND JACKPOT",
   [LM_STANDUP_2] = "STANDUP 2",
   [LM_LEFT_RAMP_ARROW] = "LEFT RAMP ARROW",
   [LM_SIDE_RAMP_JACKPOT] = "SIDE RAMP JACKPOT",
   [LM_SIDE_RAMP_ARROW] = "SIDE RAMP ARROW",
   [LM_LEFT_LOOP_ARROW] = "LEFT LOOP ARROW",
   [LM_CENTER_RAMP_JACKPOT] = "CENTER RAMP JACKPOT",
   [LM_CLAW_CAPTURE_SIMON] = "CLAW CAPTURE SIMON",
   [LM_CLAW_SUPER_JETS] = "CLAW SUPER JETS",
   [LM_CLAW_PRISON_BREAK] = "CLAW PRISON BREAK",
   [LM_CLAW_FREEZE] = "CLAW FREEZE",
   [LM_CLAW_ACMAG] = "CLAW ACMAG",
   [LM_MIDDLE_ROLLOVER] = "MIDDLE ROLLOVER",
   [LM_TOP_ROLLOVER] = "TOP ROLLOVER",
   [LM_LOWER_ROLLOVER] = "LOWER ROLLOVER",
   [LM_SUPER_JACKPOT] = "SUPER JACKPOT",
   [LM_COMPUTER] = "COMPUTER",
   [LM_DEMO_TIME] = "DEMO TIME",
   [LM_NOT_USED_1] = "NOT USED 1",
   [LM_NOT_USED_2] = "NOT USED 2",
   [LM_STANDUP_4] = "STANDUP 4",
   [LM_STANDUP_3] = "STANDUP 3",
   [LM_RETINA_SCAN] = "RETINA SCAN",
   [LM_CENTER_RAMP_MIDDLE] = "CENTER RAMP MIDDLE",
   [LM_CENTER_RAMP_OUTER] = "CENTER RAMP OUTER",
   [LM_CENTER_RAMP_INNER] = "CENTER RAMP INNER",
   [LM_CENTER_RAMP_ARROW] = "CENTER RAMP ARROW",
   [LM_RIGHT_LOOP_ARROW] = "RIGHT LOOP ARROW",
   [LM_BUY_IN_BUTTON] = "BUY IN BUTTON",
   [LM_BALL_LAUNCH] = "BALL LAUNCH",
   [LM_START_BUTTON] = "START BUTTON",
};

const char *names_of_containers [NUM_DEVICES] = {
   [DEVNO_TOP_SOL] = "TOP SOL",
   [DEVNO_SUBWAY_VUK] = "SUBWAY VUK",
   [DEVNO_TROUGH] = "TROUGH",
   [DEVNO_EYEBALL_EJECT] = "EYEBALL EJECT",
};

const char *names_of_deffs [MAX_DEFFS] = {
   [DEFF_NULL] = "NULL",
   [DEFF_AMODE] = "AMODE",
   [DEFF_SCORES] = "SCORES",
   [DEFF_SCORES_IMPORTANT] = "SCORES IMPORTANT",
   [DEFF_SCORE_GOAL] = "SCORE GOAL",
   [DEFF_CREDITS] = "CREDITS",
   [DEFF_TILT_WARNING] = "TILT WARNING",
   [DEFF_TILT] = "TILT",
   [DEFF_VOLUME_CHANGE] = "VOLUME CHANGE",
   [DEFF_SLAM_TILT] = "SLAM TILT",
   [DEFF_STATUS_REPORT] = "STATUS REPORT",
   [DEFF_NONFATAL_ERROR] = "NONFATAL ERROR",
   [DEFF_HSENTRY] = "HSENTRY",
   [DEFF_HSCREDITS] = "HSCREDITS",
   [DEFF_LOCATING_BALLS] = "LOCATING BALLS",
   [DEFF_PLAYER_TOURNAMENT_READY] = "PLAYER TOURNAMENT READY",
   [DEFF_SYSTEM_RESET] = "SYSTEM RESET",
   [DEFF_COIN_DOOR_BUTTONS] = "COIN DOOR BUTTONS",
   [DEFF_PLUNGE_BALL] = "PLUNGE BALL",
   [DEFF_COIN_DOOR_POWER] = "COIN DOOR POWER",
   [DEFF_BALL_SAVE] = "BALL SAVE",
   [DEFF_SHOOT_AGAIN] = "SHOOT AGAIN",
   [DEFF_DM_GAME_OVER] = "DM GAME OVER",
   [DEFF_BALLSEARCH] = "BALLSEARCH",
   [DEFF_ENTER_INITIALS] = "ENTER INITIALS",
   [DEFF_CLW_INLANES_EFFECT] = "CLW INLANES EFFECT",
   [DEFF_QF_INLANES_EFFECT] = "QF INLANES EFFECT",
   [DEFF_COMBO_EFFECT] = "COMBO EFFECT",
   [DEFF_SKILLSHOT] = "SKILLSHOT",
   [DEFF_ROLLOVERS_EFFECT] = "ROLLOVERS EFFECT",
   [DEFF_ALL_ROLLOVERS_EFFECT] = "ALL ROLLOVERS EFFECT",
   [DEFF_JETS_EFFECT] = "JETS EFFECT",
   [DEFF_JETS_COMPLETED_EFFECT] = "JETS COMPLETED EFFECT",
   [DEFF_STANDUPFRENZY_START_EFFECT] = "STANDUPFRENZY START EFFECT",
   [DEFF_STANDUPFRENZY_EFFECT] = "STANDUPFRENZY EFFECT",
   [DEFF_STANDUP_EFFECT] = "STANDUP EFFECT",
   [DEFF_EXPLODE_START_EFFECT] = "EXPLODE START EFFECT",
   [DEFF_EXPLODE_EFFECT] = "EXPLODE EFFECT",
   [DEFF_EXPLODE_HIT_EFFECT] = "EXPLODE HIT EFFECT",
   [DEFF_CAR_CHASE_START_EFFECT] = "CAR CHASE START EFFECT",
   [DEFF_CAR_CHASE_EFFECT] = "CAR CHASE EFFECT",
   [DEFF_CAR_CHASE_HIT_EFFECT] = "CAR CHASE HIT EFFECT",
   [DEFF_CARCRASH_EFFECT] = "CARCRASH EFFECT",
   [DEFF_UNDERGROUND_EFFECT] = "UNDERGROUND EFFECT",
   [DEFF_COMPUTER_AWARD] = "COMPUTER AWARD",
   [DEFF_CRYOCLAW_EFFECT] = "CRYOCLAW EFFECT",
   [DEFF_BONUS] = "BONUS",
   [DEFF_CAPTURE_SIMON_START_EFFECT] = "CAPTURE SIMON START EFFECT",
   [DEFF_CAPTURE_SIMON_EFFECT] = "CAPTURE SIMON EFFECT",
   [DEFF_CAPTURE_SIMON_HIT_EFFECT] = "CAPTURE SIMON HIT EFFECT",
   [DEFF_CAPTURE_SIMON_END_EFFECT] = "CAPTURE SIMON END EFFECT",
   [DEFF_FREEZE_EFFECT] = "FREEZE EFFECT",
   [DEFF_PRISON_BREAK_START_EFFECT] = "PRISON BREAK START EFFECT",
   [DEFF_PRISON_BREAK_EFFECT] = "PRISON BREAK EFFECT",
   [DEFF_PRISON_BREAK_HIT_EFFECT] = "PRISON BREAK HIT EFFECT",
   [DEFF_FORTRESS_START_EFFECT] = "FORTRESS START EFFECT",
   [DEFF_FORTRESS_JACKPOT_EFFECT] = "FORTRESS JACKPOT EFFECT",
   [DEFF_FORTRESS_EFFECT] = "FORTRESS EFFECT",
   [DEFF_FORTRESS_SUPER_JACKPOT] = "FORTRESS SUPER JACKPOT",
   [DEFF_WASTELAND_START_EFFECT] = "WASTELAND START EFFECT",
   [DEFF_WASTELAND_JACKPOT_EFFECT] = "WASTELAND JACKPOT EFFECT",
   [DEFF_WASTELAND_EFFECT] = "WASTELAND EFFECT",
   [DEFF_WASTELAND_SUPER_JACKPOT] = "WASTELAND SUPER JACKPOT",
   [DEFF_ACMAG_START_EFFECT] = "ACMAG START EFFECT",
   [DEFF_ACMAG_EFFECT] = "ACMAG EFFECT",
   [DEFF_ACMAG_HIT_EFFECT] = "ACMAG HIT EFFECT",
   [DEFF_LASER_SHOT] = "LASER SHOT",
   [DEFF_SUPERJETS_EFFECT] = "SUPERJETS EFFECT",
   [DEFF_EXTRA_BALL_EFFECT] = "EXTRA BALL EFFECT",
   [DEFF_EJECT_EFFECT] = "EJECT EFFECT",
   [DEFF_KABOOM] = "KABOOM",
   [DEFF_KABOOM_ABORT] = "KABOOM ABORT",
   [DEFF_KABOOM_INTRO] = "KABOOM INTRO",
   [DEFF_KABOOM_END] = "KABOOM END",
   [DEFF_SHOOTER] = "SHOOTER",
   [DEFF_SHOOTER_ABORT] = "SHOOTER ABORT",
   [DEFF_SHOOTER_INTRO] = "SHOOTER INTRO",
   [DEFF_SHOOTER_END] = "SHOOTER END",
   [DEFF_SIMON_SAYS] = "SIMON SAYS",
   [DEFF_SIMON_SAYS_INTRO] = "SIMON SAYS INTRO",
   [DEFF_SIMON_SAYS_RUNNER] = "SIMON SAYS RUNNER",
   [DEFF_SIMON_SAYS_READY] = "SIMON SAYS READY",
   [DEFF_SIMON_SAYS_WRONG] = "SIMON SAYS WRONG",
   [DEFF_SIMON_SAYS_ABORT] = "SIMON SAYS ABORT",
   [DEFF_SIMON_SAYS_WATCH] = "SIMON SAYS WATCH",
   [DEFF_SIMON_SAYS_INDY] = "SIMON SAYS INDY",
   [DEFF_SIMON_SAYS_END] = "SIMON SAYS END",
   [DEFF_TOP_POPPER_EFFECT] = "TOP POPPER EFFECT",
   [DEFF_EYEBALL_EFFECT] = "EYEBALL EFFECT",
   [DEFF_STARTUP_EFFECT] = "STARTUP EFFECT",
   [DEFF_MUSEUM_START_EFFECT] = "MUSEUM START EFFECT",
   [DEFF_MUSEUM_JACKPOT_EFFECT] = "MUSEUM JACKPOT EFFECT",
   [DEFF_MUSEUM_EFFECT] = "MUSEUM EFFECT",
   [DEFF_MUSEUM_SUPER_JACKPOT] = "MUSEUM SUPER JACKPOT",
   [DEFF_CRYOPRISON_START_EFFECT] = "CRYOPRISON START EFFECT",
   [DEFF_CRYOPRISON_JACKPOT_EFFECT] = "CRYOPRISON JACKPOT EFFECT",
   [DEFF_CRYOPRISON_EFFECT] = "CRYOPRISON EFFECT",
   [DEFF_CRYOPRISON_SUPER_JACKPOT] = "CRYOPRISON SUPER JACKPOT",
   [DEFF_DEMOTIME_START_EFFECT] = "DEMOTIME START EFFECT",
   [DEFF_DEMOTIME_JACKPOT_EFFECT] = "DEMOTIME JACKPOT EFFECT",
   [DEFF_DEMOTIME_INFO_EFFECT] = "DEMOTIME INFO EFFECT",
   [DEFF_DEMOTIME_EFFECT] = "DEMOTIME EFFECT",
   [DEFF_HUXLEY_INFO_EFFECT] = "HUXLEY INFO EFFECT",
   [DEFF_HUXLEY_START_EFFECT] = "HUXLEY START EFFECT",
   [DEFF_HUXLEY_EFFECT] = "HUXLEY EFFECT",
   [DEFF_HUXLEY_HIT_EFFECT] = "HUXLEY HIT EFFECT",
   [DEFF_BITF_START_EFFECT] = "BITF START EFFECT",
   [DEFF_BITF_HIT_EFFECT] = "BITF HIT EFFECT",
   [DEFF_BITF_INFO_EFFECT] = "BITF INFO EFFECT",
   [DEFF_BITF_EFFECT] = "BITF EFFECT",
   [DEFF_BITF_END_EFFECT] = "BITF END EFFECT",
};

const char *names_of_leffs [MAX_LEFFS] = {
   [LEFF_NULL] = "NULL",
   [LEFF_AMODE] = "AMODE",
   [LEFF_TILT_WARNING] = "TILT WARNING",
   [LEFF_TILT] = "TILT",
   [LEFF_BALL_SAVE] = "BALL SAVE",
   [LEFF_EXTRABALL] = "EXTRABALL",
   [LEFF_TOP_POPPER] = "TOP POPPER",
   [LEFF_EJECT] = "EJECT",
   [LEFF_FLASH_ALL] = "FLASH ALL",
   [LEFF_BOT2TOP] = "BOT2TOP",
   [LEFF_TOP2BOT] = "TOP2BOT",
   [LEFF_RIGHT2LEFT] = "RIGHT2LEFT",
   [LEFF_LEFT2RIGHT] = "LEFT2RIGHT",
   [LEFF_NO_GI_ONESEC] = "NO GI ONESEC",
   [LEFF_NO_GI_TWOSEC] = "NO GI TWOSEC",
   [LEFF_TURN_OFF_GI] = "TURN OFF GI",
   [LEFF_FLASH_GI] = "FLASH GI",
   [LEFF_FLASH_UL_GI] = "FLASH UL GI",
   [LEFF_FLASH_UR_GI] = "FLASH UR GI",
   [LEFF_FLASH_LL_GI] = "FLASH LL GI",
   [LEFF_FLASH_LR_GI] = "FLASH LR GI",
   [LEFF_FRENZY1] = "FRENZY1",
   [LEFF_FRENZY2] = "FRENZY2",
   [LEFF_FRENZY3] = "FRENZY3",
   [LEFF_FRENZY4] = "FRENZY4",
   [LEFF_FRENZY5] = "FRENZY5",
   [LEFF_LEFT_RAMP] = "LEFT RAMP",
   [LEFF_RIGHT_RAMP] = "RIGHT RAMP",
   [LEFF_CENTER_RAMP] = "CENTER RAMP",
   [LEFF_SIDE_RAMP] = "SIDE RAMP",
   [LEFF_RAMP_QUICKFREEZE] = "RAMP QUICKFREEZE",
   [LEFF_RAMP_CLAWREADY] = "RAMP CLAWREADY",
   [LEFF_LOWER_REBOUND] = "LOWER REBOUND",
   [LEFF_UPPER_REBOUND] = "UPPER REBOUND",
   [LEFF_ORBITS_RUNNER] = "ORBITS RUNNER",
   [LEFF_FREEZE] = "FREEZE",
   [LEFF_CAR_CHASE] = "CAR CHASE",
   [LEFF_ACMAG] = "ACMAG",
   [LEFF_EXPLODE] = "EXPLODE",
   [LEFF_CLAW] = "CLAW",
   [LEFF_MB_START] = "MB START",
   [LEFF_INLANE_QUICK_FREEZE] = "INLANE QUICK FREEZE",
   [LEFF_INLANE_CRYOCLAW] = "INLANE CRYOCLAW",
   [LEFF_UNDERGROUND] = "UNDERGROUND",
   [LEFF_COMPUTER_AWARD] = "COMPUTER AWARD",
   [LEFF_EYEBALL] = "EYEBALL",
   [LEFF_JACKPOT] = "JACKPOT",
   [LEFF_JACKPOT1] = "JACKPOT1",
   [LEFF_JACKPOT2] = "JACKPOT2",
   [LEFF_JACKPOT3] = "JACKPOT3",
   [LEFF_JACKPOT4] = "JACKPOT4",
   [LEFF_SUPER_JACKPOT] = "SUPER JACKPOT",
   [LEFF_SKILLSHOT] = "SKILLSHOT",
   [LEFF_CAR_CRASH_RUNNER] = "CAR CRASH RUNNER",
};

const char *names_of_lamplists [MAX_LAMPLIST] = {
   [LAMPLIST_ALL] = "ALL",
   [LAMPLIST_BALL_SAVE] = "BALL SAVE",
   [LAMPLIST_RIGHT_RAMP_AWARDS] = "RIGHT RAMP AWARDS",
   [LAMPLIST_LEFT_RAMP_AWARDS] = "LEFT RAMP AWARDS",
   [LAMPLIST_RIGHT_LOOP_AWARDS] = "RIGHT LOOP AWARDS",
   [LAMPLIST_LEFT_LOOP_AWARDS] = "LEFT LOOP AWARDS",
   [LAMPLIST_FREEZE] = "FREEZE",
   [LAMPLIST_ROLLOVERS] = "ROLLOVERS",
   [LAMPLIST_MULTIBALLS] = "MULTIBALLS",
   [LAMPLIST_CLAW] = "CLAW",
   [LAMPLIST_UNDERGROUND_SCOOP] = "UNDERGROUND SCOOP",
   [LAMPLIST_STANDUPS] = "STANDUPS",
   [LAMPLIST_CENTER_RAMP] = "CENTER RAMP",
   [LAMPLIST_SIDE_RAMP] = "SIDE RAMP",
   [LAMPLIST_INLANES] = "INLANES",
   [LAMPLIST_CAR_CRASH] = "CAR CRASH",
   [LAMPLIST_AMODE_ALL] = "AMODE ALL",
   [LAMPLIST_LEFT_RIGHT] = "LEFT RIGHT",
   [LAMPLIST_RIGHT_LEFT] = "RIGHT LEFT",
   [LAMPLIST_BOTTOM_TOP] = "BOTTOM TOP",
   [LAMPLIST_TOP_BOTTOM] = "TOP BOTTOM",
   [LAMPLIST_CIRCLE_OUT1] = "CIRCLE OUT1",
   [LAMPLIST_CIRCLE_OUT2] = "CIRCLE OUT2",
   [LAMPLIST_CIRCLE_OUT3] = "CIRCLE OUT3",
   [LAMPLIST_CIRCLE_OUT4] = "CIRCLE OUT4",
   [LAMPLIST_CIRCLE_OUT5] = "CIRCLE OUT5",
   [LAMPLIST_RED_LAMPS] = "RED LAMPS",
   [LAMPLIST_WHITE_LAMPS] = "WHITE LAMPS",
   [LAMPLIST_YELLOW_LAMPS] = "YELLOW LAMPS",
};

const char *names_of_gi [] = {
   [GI_BACKBOX] = "BACKBOX",
   [GI_URIGHT_PLAYFIELD] = "U.RIGHT PLAYFIELD",
   [GI_ULEFT_PLAYFIELD] = "U.LEFT PLAYFIELD",
   [GI_LRIGHT_PLAYFIELD] = "L.RIGHT PLAYFIELD",
   [GI_LLEFT_PLAYFIELD] = "L.LEFT PLAYFIELD",
};

const char *names_of_fonts [MAX_FONTS] = {
   [FON_MONO9] = "MONO9",
   [FON_TINYNUM] = "TINYNUM",
   [FON_VAR5] = "VAR5",
   [FON_FIXED6] = "FIXED6",
   [FON_FIXED10] = "FIXED10",
   [FON_TERM6] = "TERM6",
   [FON_SYMBOL] = "SYMBOL",
   [FON_BITMAP8] = "BITMAP8",
   [FON_MONO5] = "MONO5",
   [FON_LUCIDA9] = "LUCIDA9",
   [FON_BITCUBE10] = "BITCUBE10",
   [FON_HALOBOLD12] = "HALOBOLD12",
   [FON_HALOBOLD14] = "HALOBOLD14",
   [FON_DMGRAPHS] = "DMGRAPHS",
   [FON_HALOBOLD22NUM] = "HALOBOLD22NUM",
};


