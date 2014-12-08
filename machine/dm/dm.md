#--------------------------------------------------------------------------
# Demolition Man Machine description for FreeWPC
# See tools/genmachine for more information about the format of this file.
#--------------------------------------------------------------------------
# This file describes many characteristics of a pinball machine,
# mostly physical stuff, although some rules can be coded here also.
#--------------------------------------------------------------------------
##########################################################################
# General section (before a [section] header is given.
# Miscellaneous parameters are specified here.
##########################################################################
Title: Demolition Time
#the following tags are required because the wpc-dcs md is not finished
DMD: Yes
Fliptronic: Yes
DCS: Yes
WPC95: No

Lamp-Matrix-Width: 18
Lamp-Matrix-Height: 34





##########################################################################
# Include standard definitions that apply to all WPC games.
##########################################################################
include platform/wpc/wpc-dcs.md





##########################################################################
# Use 'define' to emit a plain #define for anything not covered by
# some other means.
##########################################################################


##########################################################################
# special hardware flags
##########################################################################
define MACHINE_DEMO_MAN
define MACHINE_HAS_FLIPPER_GUN_HANDLES
define MACHINE_HAS_UPPER_LEFT_FLIPPER
#this means we have X type sols below and the X expansion board
define MACHINE_SOL_EXTBOARD1

##########################################################################
# timing overrides
##########################################################################
define MACHINE_BALL_SAVE_TIME       7
define MACHINE_MAX_BALLS            5
define AUTOFIRE_DELAY 				20
define MACHINE_BALL_SEARCH_TIME 	10

##########################################################################
# effects overrides
##########################################################################
define MACHINE_ADD_CREDIT_SOUND PLONK 
#define MACHINE_AMODE_FLIPPER_SOUND_CODE

#define MACHINE_VOLUME_CHANGE_MUSIC MUS_HIGH_SCORE

##########################################################################
# additions/changes to configuration menu
##########################################################################
define CONFIG_DIFFICULTY_LEVEL 

#comment this out in production
define DEVELOPMENT_MENU

##########################################################################
# changes to default image generator in tools/ingld.c
##########################################################################
define LOWER_IMAGE_BRIGHTNESS2



##########################################################################
# changes to default hardware behavior
##########################################################################
define COIN_DOOR_OPENED_TIMERS_OFF


##########################################################################
# make this TRUE for testing
# 
#  this will decrease the amount of hits needed to
#  activate certain features
#  AND add ability to increment things with the left gun handle button
#  see code at simple_switches.c
##########################################################################
define DM_IN_DMD_TEST FALSE
define DM_IN_CAB_TEST FALSE
define TROUGH_TEST FALSE



##########################################################################
# Lamp Description
# The key is given in column/row format.  The first parameter must be
# the lamp name.  Optionally you can specify a color, and x() and y()
# for the location on the playfield.  Only a subset of lamp colors are
# recognized; see tools/genmachine for details.  Lamp location is
# given in terms of the Lamp-Matrix-Width and Lamp-Matrix-Height.
##########################################################################
[lamps]
#two lights on either side by slings
11: Chest Plate, ball-save, red, x(28), y(6) 
12: Fortress Multiball, white, x(33), y(9)
13: Museum Multiball, white, x(31), y(9)
14: Cryoprison Multiball, white, x(29), y(9)
15: Wasteland Multiball, white, x(30), y(9)
16: Shoot Again, shoot-again, red, x(34), y(9) #light at very bottom
17: Access Claw, yellow, x(26), y(1)
18: Left Ramp Explode, yellow, x(22), y(9)
21: Right Ramp Jackpot, red, x(22), y(14)
22: Right Loop Explode, yellow,	x(23), y(15)
23: Light Quick Freeze, yellow, x(27), y(15)
24: Freeze 4, white, x(26), y(14)
25: Claw Ready, yellow, x(25), y(12)
26: Freeze 3, white, x(28), y(12)
27: Freeze 2, white, x(28), y(6)
28: Freeze 1, white, x(26), y(2)
31: Right Loop Jackpot, red, x(21), y(16)
32: Standup 5, blue, x(19), y(15)
33: Right Ramp Arrow, red, x(19), y(14)
34: Left Ramp Jackpot, red, x(20), y(8)
35: Left Loop Jackpot, red, x(19), y(6)
36: Car Crash Top, yellow, x(20), y(2)
37: Standup 1, blue, x(21), y(5)
38: Car Crash Center, yellow, x(22), y(3)
41: Right Ramp Explode, yellow, x(23), y(14)
42: Right Ramp Car Chase, yellow, x(24), y(13)
43: Quick Freeze, yellow, x(24), y(10)
44: Left Ramp Car Chase, yellow, x(23), y(9)
45: Extra Ball, extra-ball, yellow, x(24), y(9)
46: Start Multiball, yellow, x(23), y(8)
47: Car Crash Bottom, yellow, x(23), y(4)
48: Left Loop Explode, yellow, x(22), y(7)
51: Underground Arrow, red, x(11), y(10)
52: Underground Jackpot, red, x(12), y(9)
53: Standup 2, blue, x(13), y(8)
54: Left Ramp Arrow, red, x(14), y(7)
55: Side Ramp Jackpot, red, x(16), y(9)
56: Side Ramp Arrow, red, x(15), y(9)
57: left Loop Arrow, red, x(14), y(4)
58: Center Ramp Jackpot, red, x(10), y(9)
61: Claw Capture Simon,	red, x(1), y(7)
62: Claw Super Jets, red, x(3), y(6)
63: Claw Prison Break, red, x(4), y(5)
64: Claw Freeze, red, x(5), y(2)
65: Claw Acmag, red, x(5), y(1)
66: Middle Rollover, green, x(2), y(14)
67: Top Rollover, green, x(2), y(15)
68: Lower Rollover, green, x(2), y(17)
71: Super Jackpot, yellow, x(7), y(11)
72: Computer, blue, x(8), y(11)
73: Demo Time, yellow, 	x(9), y(11)
74: Not Used 1
75: Not Used 2
76: Standup 4, blue, x(18), y(13)
77: Standup 3, blue, x(17), y(10)
78: Retina Scan, yellow, x(23), y(1)
81: Center Ramp Middle, red, x(6), y(9)
82: Center Ramp Outer, red,	x(6), y(8)
83: Center Ramp Inner, red, x(6), y(9)
84: Center Ramp Arrow, red, x(9), y(9)
85: Right Loop Arrow, red, x(16), y(18)
86: Buy In Button, buyin, cabinet, yellow, x(33), y(18)
87: Ball Launch, launch, cabinet, red, x(34), y(16)
88: Start Button, start, cabinet, yellow, x(1), y(1)





##########################################################################
# Switch Description
# The key is in column/row format.  The first parameter must be the switch
# name.  Options can be given in any order:
#    ingame - only service the switch during a game
#    intest - also service the switch in test mode
#    novalid - tripping this switch does NOT mark ball in play
#    standup - this is a standup
#    button - this is a button
#    edge - this switch should be serviced on either transition
#    opto - this switch is optical and activates on closed->open
#
# These parameters mark various well-known switches.  Only one of these
# can exist per type:
#    outhole, slam-tilt, tilt, shooter, start-button, buyin-button
#
# Use sound() to invoke a sound call automatically when the switch activates.
# Use lamp() to flicker a lamp automatically on activation.  TODO:
#   this requires the c_name, and not the friendly md name.
# Use c_decl() to override the default name of the switch event.
#
##########################################################################
[switches]
11: Launch Button, launch-button, cabinet, novalid
12: Left Handle Button, cabinet, novalid
13: Start Button, start-button, cabinet, intest, novalid, debounce(TIME_100MS)
14: Tilt, tilt, ingame, novalid, cabinet, sound(TILT)
15: Left Outlane, ingame 
16: Left Inlane, ingame
17: Right Inlane, ingame
18: Right Outlane, ingame

21: Slam Tilt, slam-tilt, ingame, novalid, cabinet, sound(TILT)
22: Coin Door Closed, novalid, cabinet, edge, intest
23: Buyin Button, buyin-button, cabinet, novalid
24: Always Closed, novalid
25: Claw Position 1, opto, noscore, novalid
26: Claw Position 2, opto, noscore, novalid
27: Shooter, shooter, noscore, novalid, edge
28: Not Used 1, novalid

31: Trough 1, noscore, novalid, opto
32: Trough 2, noscore, novalid, opto
33: Trough 3, noscore, novalid, opto
34: Trough 4, noscore, novalid, opto
35: Trough 5, noscore, novalid, opto
36: Trough Jam, noscore, novalid, opto
37: Not Used 2, novalid
38: Standup 5, ingame, standup

41: Left Sling, ingame, c_decl(sw_sling)
42: Right Sling, ingame, c_decl(sw_sling)
43: Left Jet, ingame, c_decl(sw_jet)
44: Top Sling, ingame, c_decl(sw_jet)
45: Right Jet, ingame, c_decl(sw_jet)
46: Right Ramp Enter, ingame
47: Right Ramp Exit, ingame
48: Right Freeway, ingame

51: Left Ramp Enter, ingame
52: Left Ramp Exit, ingame
53: Center Ramp, ingame
54: Upper Rebound, ingame, novalid
55: Left Loop, ingame 
56: Standup 2, standup, ingame
57: Standup 3, standup, ingame
58: Standup 4, standup, ingame

61: Side Ramp Enter, ingame
62: Side Ramp Exit, ingame
63: Left Rollover, ingame
64: Center Rollover, ingame
65: Right Rollover, ingame
66: Eject, ingame
67: Elevator Index, opto, noscore, novalid
68: Not Used 3, novalid

71: Chase Car 1, opto, novalid
72: Chase Car  2, opto, novalid
73: Top Popper, opto, edge, novalid, debounce(TIME_200MS)
74: Elevator Hold, opto, noscore, novalid
75:  Not Used 4, novalid
76: Bottom Popper, opto, edge, , novalid, debounce(TIME_200MS)
77: Eyeball Standup, standup, ingame
78: Standup 1, standup, ingame

81: Claw Capture Simon, ingame
82: Claw Super Jets, ingame
83: Claw Prison Break, ingame
84: Claw Freeze, ingame
85: Claw Acmag, ingame
86: Upper Left Flipper Gate, ingame
87: Car Chase Standup, ingame
88: Lower Rebound, ingame





##########################################################################
# Drives
# This describes the names of the solenoid/motor drives.
# Hn = high power solenoids
# Ln = low power solenoids
# Gn = general purpose solenoids
# etc.
#
# The following options are supported:
#    flash - this is a flasher (default is solenoid, flash implies nosearch)
#    motor - this is a motor (default is solenoid)
#    nosearch - do not activate this during ball search
#
# The following options denote well-known drives:
#    knocker, ballserve, launch
#
##########################################################################
# THIS IS LIST IS SHOWN IN THE SAME ORDER AS THE SOLENOID/FLASHER TABLE
[drives]
#H = high power J130
#### these are all 50v power
H1: BallServe, ballserve, duty(SOL_DUTY_100), time(TIME_133MS)
H2: Bottom Popper, time(TIME_133MS) 
H3: Launch, launch, nosearch, duty(SOL_DUTY_100), time(TIME_133MS)
H4: Top Popper, time(TIME_100MS)
H5: Diverter Power, duty(SOL_DUTY_75)
H6: Not Used H6 50v, nosearch
H7: Knocker, knocker, time(TIME_16MS), nosearch
H8: Not Used H8 50v, nosearch

#L = low power J127
#### these are all 50v power
L1: Left Sling, duty(SOL_DUTY_100)
L2: Right Sling, duty(SOL_DUTY_100)
L3: Left Jet, duty(SOL_DUTY_100)
L4: Top Sling, duty(SOL_DUTY_100)
L5: Right Jet, duty(SOL_DUTY_100)

L6: Eject, duty(SOL_DUTY_37), time(TIME_33MS)
#########L6: Eject, duty(SOL_DUTY_25), time(TIME_33MS) - too weak
L7: Diverter Hold, nosearch
L8: : Not Used L8 50v, nosearch

# G = J126 on Power Driver Board
#### these are all 20v power
G1: Claw Flasher, flash, nosearch

G2: Elevator Motor, motor, nosearch
G3: Claw Left, motor, nosearch
G4: Claw Right, motor, nosearch

G5: Jets Flasher, flash, nosearch
G6: Side Ramp, flash, nosearch
G7: Left Ramp Up, flash, nosearch
G8: Left Ramp Lower, flash, nosearch

# A = J122
#### these are all 20v power
A1: Shaker Motor, motor, nosearch

#A1: Car Chase Center Flasher, flash, nosearch

A2: Car Chase Lower, flash, nosearch
A3: Right Ramp, flash, nosearch
A4: Eject Fl, flash, nosearch

# F = J902 on Fliptronic II
#### these are all 50v power
F1: L.R. Flip Power
F2: L.R. Flip Hold
F3: L.L. Flip Power
F4: L.L. Flip Hold
F5: Claw Magnet, duty(SOL_DUTY_62) 
F6: Not Used, nosearch
F7: U.L. Flip Power, time(TIME_33MS)
F8: U.L. Flip Hold, time(TIME_100MS)

#X = J4 on 8 driver board
#### these are all 20v power
X1: Car Chase Upper, flash, nosearch
X2: Lower Rebound, flash, nosearch
X3: Eyeball, flash, nosearch
X4: Center Ramp, flash, nosearch
X5: Elevator 2, flash, nosearch
X6: Elevator 1, flash, nosearch
X7: Diverter flasher, flash, nosearch
X8: Right Ramp Up, flash, nosearch





##########################################################################
# templates
# This section contains template definitions for device drivers.
# For each device requiring a driver, it specifies the file that
# contains the template code, and any parameters for the specific
# device.
# 
# some of the templates have auto generated function calls in them that you will
# use to start and stop the coil.  For example divhold.ct creates functions
# self_start and self_stop, where self is the name of the diverter that you specify.
#
# look in the drivers directory for details on each driver
# the templates are autogenrated by ctemp in tools directory
#
# some notes on the various kinds of parameters
#
# note - spaces between parameters and arguments will cause crashes
#
# divhold
# mode --Set to 1 if the solenoids are fliptronic powered, 0 == normal
# power_pulse_ms --Durations of the pulse for the full power solenoid (in ms) must be divisible by the value used by the schedule_ms parameter
# schedule_ms  --try 32 first as highest number, then experiment down from there
#
# spsol
# ontime - how long the coil is kept on
# offtime - how long the coil is kept off after it was fired, before polling the switch again.  This prevents constant lock-on.
# auto 	- if nonzero, then automatically enable during start ball.
#
##########################################################################
[templates]
Left Sling: driver(sling), sw=SW_LEFT_SLING, sol=SOL_LEFT_SLING, ontime=3, offtime=16
Right Sling: driver(sling), sw=SW_RIGHT_SLING, sol=SOL_RIGHT_SLING, ontime=3, offtime=16
Left Jet: driver(jet), sw=SW_LEFT_JET, sol=SOL_LEFT_JET, ontime=3, offtime=16
Right Jet: driver(jet), sw=SW_RIGHT_JET, sol=SOL_RIGHT_JET, ontime=3, offtime=16
Top Sling: driver(jet), sw=SW_TOP_SLING, sol=SOL_TOP_SLING, ontime=3, offtime=16
Diverter: driver(divhold), power_sol=SOL_DIVERTER_POWER, hold_sol=SOL_DIVERTER_HOLD, mode=0, power_pulse_ms=64, schedule_ms=32, includetest(yes)

Elevator: driver(motorbank2), sol=SOL_ELEVATOR_MOTOR, up_sw_event=SW_ELEVATOR_HOLD, down_sw_event=SW_ELEVATOR_INDEX, initial_position=ELEVATOR_DOWN, includetest(yes)

Claw: driver(bivar2), left_sol=SOL_CLAW_LEFT, right_sol=SOL_CLAW_RIGHT, left_sw=SW_CLAW_POSITION_2, right_sw=SW_CLAW_POSITION_1, includetest(yes)

ClawMagnet: driver(magnet), sol=SOL_CLAW_MAGNET

Shaker: driver(shakermotor),  sol=SOL_SHAKER_MOTOR



##########################################################################
# General Illumination
##########################################################################
[gi]
0: Backbox
1: U.Right Playfield
2: U.Left Playfield
3: L.Right Playfield
4: L.Left Playfield





##########################################################################
# Tests
# These are additional test items that should appear in the TESTS menu.
##########################################################################
[tests]
diverter: 		#autogenerated-test, see defintion in [templates] section.
elevator:		#autogenerated-test, see defintion in [templates] section.
claw:			#autogenerated-test, see defintion in [templates] section.





##########################################################################
# Lampsets
# These denote logical groupings of lamps.
# The key is a textual name for the set.  The options specify which lamps
# are a part of that set.  You can specify 1 or more lamp values,
# separated by commas, where each value can be: 1) a single lamp name,
# 2) another lampset name, already defined, or 3) a lamp range in the
# form lamp1..lampN.
#
# The special construct PF:function indicates that a Perl subroutine
# should be used to select and sort the lamps.  Some functions are
# builtin to genmachine; others can be defined by you and included
# via the 'perlinclude' directive.
#
# Note that a lampset may contain only one lamp.  The lampset is the
# unit of 'allocation' for a lamp effect.
##########################################################################
[lamplists]
Right Ramp Awards: Right Ramp Arrow, Right Ramp Jackpot, Right Ramp Explode, Right Ramp Car Chase, Claw Ready
Left Ramp Awards: Left Ramp Arrow, Left Ramp Jackpot, Left Ramp Explode, Left Ramp Car Chase, Quick Freeze
Right Loop Awards: Right Loop Arrow, Right Loop Jackpot, Right Loop Explode
Left Loop Awards: left Loop Arrow, Left Loop Jackpot, Left Loop Explode, Start Multiball, Extra Ball
Freeze: Freeze 1, Freeze 2, Freeze 3, Freeze 4
Rollovers: Middle Rollover, Top Rollover, Lower Rollover
Multiballs: Fortress Multiball, Museum Multiball, Cryoprison Multiball, Wasteland Multiball
Claw: Claw Capture Simon, Claw Super Jets, Claw Prison Break, Claw Freeze, Claw Acmag 
Underground Scoop: Underground Arrow, Underground Jackpot
Standups: Standup 1, Standup 2, Standup 3, Standup 4, Standup 5
Center Ramp: Center Ramp Arrow, Center Ramp Middle, Center Ramp Outer, Center Ramp Inner, Center Ramp Jackpot
Side Ramp: Side Ramp Jackpot, Side Ramp Arrow
Inlanes: Access Claw, Light Quick Freeze
Car Crash: Car Crash Top, Car Crash Center, Car Crash Bottom

Amode All: Right Ramp Awards, Left Ramp Awards, Right Loop Awards, Left Loop Awards, Freeze, Rollovers, Multiballs, 
Claw, Underground Scoop, Standups, Center Ramp, Side Ramp, Inlanes, Car Crash

Left Right: PF:lamp_sort_bottom_to_top
Right Left: PF:lamp_sort_top_to_bottom
Bottom Top: PF:lamp_sort_left_to_right
Top Bottom: PF:lamp_sort_right_to_left
Circle Out1: PF:lamp_sort_circle_out1
Circle Out2: PF:lamp_sort_circle_out2
Circle Out3: PF:lamp_sort_circle_out3
Circle Out4: PF:lamp_sort_circle_out4
Circle Out5: PF:lamp_sort_circle_out5

Red Lamps: COLOR:red
White Lamps: COLOR:white
Yellow Lamps: COLOR:yellow





##########################################################################
# Containers
# These denote devices that can hold, count, and eject pinballs.
# The key is the name of the device.  The first parameter is the name
# of the solenoid that kicks out a ball.  The 'trough' parameter should
# be specified on the single trough device.  The 'init_max_count'
# parameter should say how many balls are normally held in this device
# at startup.  The remaining parameters are the names of the switches
# that count pinball, in front from entry to exit.
##########################################################################
[containers]
#name: solenoid, switch
Top Sol: Top Popper, Top Popper
Subway VUK: Bottom Popper, Bottom Popper
Trough: BallServe, init_max_count(5), Trough 1, Trough 2, Trough 3, Trough 4, Trough 5

Eyeball Eject: Eject, Eject



##########################################################################
##########################################################################
##########################################################################
#------------------------------------------------------------------------
# The remaining sections describe software aspects, and not the physical
# machine.
#------------------------------------------------------------------------
##########################################################################
##########################################################################
##########################################################################





##########################################################################
# Items for the Feature Adjustments menu.  Parameters indicate the
# type of adjustment and the default value.
##########################################################################
[adjustments]





##########################################################################
# Items for the Feature Audits menu.
##########################################################################
[audits]





##########################################################################
# Sound calls for well-known events
##########################################################################
[system_sounds]





##########################################################################
# Music calls for well-known events
##########################################################################
[system_music]





##########################################################################
# A list of all scores needed by the game rules.
##########################################################################
[scores]
540:
1010:
5K:
5770:
10K:
25K:
50K:
75K:
100K:
150K:
200K:
250K:
500K:
750K:
1M:
2M:
3M:
4M:
5M:
6M:
7M:
8M:
9M:
10M:
11M:
12M:
13M:
15M:
20M:
25M:
30M:
35M:
40M:
45M:
50M:
100M:  #used for score compare in bonus display





##########################################################################
# The default high scores.  Use GC to indicate the grand champion.
# The parameters are the initials followed by the score value.  Periods
# may optionally be used to group digits, but they are not necessary.
# Commas _cannot_ be used for this purpose since they separate parameters.
##########################################################################
[highscores]





##########################################################################
# Per-player bit flags.
#
#limit of 128 total
##########################################################################
[flags]
IS_LRAMP_QUICKFREEZE_ACTIVATED:
IS_COMPUTER_ACTIVATED:
IS_EXTRABALL_LIT:
IS_MULTIBALL_ENABLED:
IS_R_RAMP_CLAWREADY:
IS_DEMOTIME_ENABLED:
BACK_IN_THE_FRIDGE_ACTIVATED:
VIDEO_MODE_ENABLED:
IS_CARCHASE_MODE_ENABLED:
IS_EXPLODE_MODE_ENABLED:
IS_HUXLEY_ENABLED:
IS_CC3_LIT:
IS_CC6_LIT:
IS_CC10_LIT:
IS_QUICK_FREEZE_ACTIVATED:
IS_ACCESS_CLAW_ACTIVATED:
IS_EYEBALL_EB_MADE:
LASER_SHOT_ENABLED:
#18

VIDEO_MODE_RUNNING:	

IS_COMBO_SIDERAMP_ACTIVATED:
IS_COMBO_LEFTRAMP_ACTIVATED:
IS_COMBO_RIGHTRAMP_ACTIVATED:
IS_COMBO_UNDER_ACTIVATED:
IS_COMBO_CENTERRAMP_ACTIVATED:
IS_COMBO_LEFTORB_ACTIVATED:
IS_COMBO_RIGHTORB_ACTIVATED:

IS_UGROUND_ARROW_ACTIVATED:
IS_L_LOOP_ARROW_ACTIVATED:
IS_R_LOOP_ARROW_ACTIVATED:
IS_L_RAMP_ARROW_ACTIVATED:
IS_C_RAMP_ARROW_ACTIVATED:
IS_S_RAMP_ARROW_ACTIVATED:
IS_R_RAMP_ARROW_ACTIVATED:
#34





##########################################################################
# System-wide bit flags.
#
#limit of 32 total
##########################################################################
[globalflags]
IS_BALL_ON_CLAW:
IS_CLAW_HOME:
#IS_CLAW_IN_BALL_SEARCH:




##########################################################################
# Fonts used in this game.
# these are in addition to default fonts
# default fonts do not have to be listed (they are declared under platform/wpc/wpc-common.md) and are:
# font_mono9
# font_fixed10		---good only for very short words
# font_tinynum
# font_var5			---small text messages
# font_fixed6 		---standups and standup frenzy
# font_fixed10 		---fortress MB
# font_term6     	---car crash and car chase freeze  and many smaller lines
# font_fixed10		---capture simon
# font_bitmap8

# these are disabled
# font_num5x7
# font_cu17		
# font_timess8
#
# The number at the end doesn't correspond to their point size like you would think.
# The best thing to do is look at the actual font in the development menu
# Here are others that are available - from the fonts directory
#exocet10:
#exocet14:

#telemarines10:
#telemarines14:
#lithograph:	
#v5prc:			
#steel:			
#antiqua:
#bitoutline:
#fireball:
#fipps:

#pcsenior:		#---good only for very short words
#addlg:			#---good only for very short words
#Adore64:		#---good only for very short words, remember to drop the cap A when using this in your code
#ffextra:		#---these are not letters, but symbols, like wingdings
#times10:
#arcadepi:
#micron55:
#pixchicago:
#px_sans_nouveaux:
#twizone:
#uni05_54:
#uni05_63:
#uni05_64:
#xpaiderp:
#fixed12:
#arial11b:
#emulogic
#nayupixel10:
#quadrit:
#arial11a:
#abstract:
#c64:			#---similar to amiga4ever
#pixelmix:
#hellovetica:


###problems with these
#utopia:		---looks garbled
#schu:			---looks garbled
#joystix:		---don't show
#ambitsek:		---don't show
#uni05_53:
#v5prd:
#v5prf:
#bitmap:
#arial11:
#miscfixed:
#luctype:
##########################################################################
#can pick, at most, 4 to 10 extra fonts, depending on file size, outside of the system fonts without
#receiving compile errors for overflowing the fonts page 
#
#FYI: to allow more fonts, I deleted some of the system fonts
##########################################################################
[fonts]
bitcube10:
fixed6:
halobold12:
halobold14:
dmgraphs:
halobold22num:


##########################################################################
# Display effects  -- text page (?)
##########################################################################
[deffs]
clw inlanes effect: PRI_GAME_LOW4, D_QUEUED+D_TIMEOUT
qf inlanes effect: PRI_GAME_LOW4, D_QUEUED+D_TIMEOUT

combo effect: PRI_GAME_LOW2, D_RESTARTABLE

skillshot: PRI_SPECIAL

##########################################################################
# Display effects  -- common page (?)
##########################################################################
# THIS IS OLD NOTE - STUFF MOVED BACK
#check generic.md for stuff I stuck on the common page because I ran out of room


##########################################################################
# Display effects  -- page 1 (56)
##########################################################################
rollovers effect: page(MACHINE_PAGE), PRI_GAME_LOW5, D_RESTARTABLE
all rollovers effect: page(MACHINE_PAGE), PRI_GAME_LOW6

jets effect: page(MACHINE_PAGE), PRI_GAME_LOW5, D_RESTARTABLE
jets completed effect: page(MACHINE_PAGE), PRI_GAME_LOW6, D_QUEUED

standupfrenzy start effect: page(MACHINE_PAGE), PRI_GAME_MODE4
standupfrenzy effect: page(MACHINE_PAGE), PRI_GAME_MODE3, D_QUEUED
standup effect: page(MACHINE_PAGE), PRI_GAME_LOW4


##########################################################################
# Display effects  -- page 2 (55)
##########################################################################
explode start effect: page(MACHINE2_PAGE), PRI_GAME_MODE4
explode effect: page(MACHINE2_PAGE), PRI_GAME_MODE1, D_QUEUED
explode hit effect: page(MACHINE2_PAGE), PRI_GAME_QUICK1, D_RESTARTABLE

car chase start effect: page(MACHINE2_PAGE), PRI_GAME_MODE4
car chase effect: page(MACHINE2_PAGE), PRI_GAME_MODE1, D_QUEUED
car chase hit effect: page(MACHINE2_PAGE), PRI_GAME_QUICK1, D_RESTARTABLE

carcrash effect: page(MACHINE2_PAGE), PRI_GAME_LOW6

underground effect: page(MACHINE2_PAGE), PRI_GAME_LOW5
computer award: page(MACHINE2_PAGE), PRI_GAME_QUICK6

cryoclaw effect: page(MACHINE2_PAGE), PRI_GAME_MODE5, D_QUEUED

bonus: page(MACHINE2_PAGE), PRI_BONUS, D_QUEUED



##########################################################################
# Display effects  -- page 3 (54)
##########################################################################
capture simon start effect: page(MACHINE3_PAGE), PRI_GAME_MODE5
capture simon effect: page(MACHINE3_PAGE), PRI_GAME_MODE2, D_QUEUED
capture simon hit effect: page(MACHINE3_PAGE), PRI_GAME_MODE6, D_RESTARTABLE
capture simon end effect: page(MACHINE3_PAGE), PRI_GAME_MODE5, D_QUEUED

freeze effect: page(MACHINE3_PAGE), PRI_GAME_QUICK7

prison break start effect: page(MACHINE3_PAGE), PRI_GAME_MODE3
prison break effect: page(MACHINE3_PAGE), PRI_GAME_MODE2, D_QUEUED
prison break hit effect: page(MACHINE3_PAGE), PRI_GAME_QUICK1, D_RESTARTABLE

fortress start effect: page(MACHINE3_PAGE), PRI_MULTIBALL2, D_QUEUED
fortress jackpot effect: page(MACHINE3_PAGE), PRI_JACKPOT, D_QUEUED+D_RESTARTABLE
fortress effect: page(MACHINE3_PAGE), PRI_MULTIBALL1
fortress super jackpot: page(MACHINE3_PAGE), PRI_SUPER_JACKPOT, D_QUEUED+D_RESTARTABLE

wasteland start effect: page(MACHINE3_PAGE), PRI_MULTIBALL2, D_QUEUED
wasteland jackpot effect: page(MACHINE3_PAGE), PRI_JACKPOT, D_QUEUED+D_RESTARTABLE
wasteland effect: page(MACHINE3_PAGE), PRI_MULTIBALL1
wasteland super jackpot: page(MACHINE3_PAGE), PRI_SUPER_JACKPOT, D_QUEUED+D_RESTARTABLE

acmag start effect: page(MACHINE3_PAGE), PRI_GAME_MODE5
acmag effect: page(MACHINE3_PAGE), PRI_GAME_MODE2, D_QUEUED
acmag hit effect: page(MACHINE3_PAGE),PRI_GAME_QUICK1, D_RESTARTABLE

laser shot: page(MACHINE3_PAGE), PRI_GAME_MODE2, D_QUEUED

superjets effect: page(MACHINE3_PAGE), PRI_GAME_MODE1, D_QUEUED

extra ball effect: page(MACHINE3_PAGE), PRI_GAME_QUICK2, D_QUEUED




##########################################################################
# Display effects  -- page 4 (53)
##########################################################################
eject effect: page(MACHINE4_PAGE), PRI_GAME_LOW5

kaboom: page(MACHINE4_PAGE), PRI_VIDEO_MODE, D_QUEUED+D_RESTARTABLE
kaboom abort: page(MACHINE4_PAGE), PRI_VIDEO_MODE2, D_QUEUED
kaboom intro: page(MACHINE4_PAGE), PRI_VIDEO_MODE, D_QUEUED
kaboom end: page(MACHINE4_PAGE), PRI_VIDEO_MODE, D_QUEUED

shooter: page(MACHINE4_PAGE), PRI_VIDEO_MODE, D_QUEUED+D_RESTARTABLE
shooter abort: page(MACHINE4_PAGE), PRI_VIDEO_MODE2, D_QUEUED
shooter intro: page(MACHINE4_PAGE), PRI_VIDEO_MODE, D_QUEUED
shooter end: page(MACHINE4_PAGE), PRI_VIDEO_MODE, D_QUEUED

simon says: page(MACHINE4_PAGE), PRI_VIDEO_MODE, D_QUEUED+D_RESTARTABLE
simon says intro: page(MACHINE4_PAGE), PRI_VIDEO_MODE1, D_QUEUED
simon says runner: page(MACHINE4_PAGE), PRI_VIDEO_MODE3, D_QUEUED
simon says ready: page(MACHINE4_PAGE), PRI_VIDEO_MODE2, D_QUEUED
simon says wrong: page(MACHINE4_PAGE), PRI_VIDEO_MODE2, D_QUEUED
simon says abort: page(MACHINE4_PAGE), PRI_VIDEO_MODE2, D_QUEUED
simon says watch: page(MACHINE4_PAGE), PRI_VIDEO_MODE2, D_QUEUED
simon says indy: page(MACHINE4_PAGE), PRI_VIDEO_MODE1, D_QUEUED
simon says end: page(MACHINE4_PAGE), PRI_VIDEO_MODE3, D_QUEUED

top popper effect: page(MACHINE4_PAGE), PRI_GAME_LOW5

eyeball effect: page(MACHINE4_PAGE), PRI_GAME_LOW2, D_QUEUED

startup effect: page(MACHINE4_PAGE), PRI_BALL_LAUNCH_MENU, D_QUEUED

#troubleshooting: page(MACHINE4_PAGE), PRI_SCORES_IMPORTANT, D_QUEUED




##########################################################################
# Display effects  -- page 5 (52)
##########################################################################
museum start effect: page(MACHINE5_PAGE), PRI_MULTIBALL2, D_QUEUED
museum jackpot effect: page(MACHINE5_PAGE), PRI_JACKPOT, D_QUEUED+D_RESTARTABLE
museum effect: page(MACHINE5_PAGE), PRI_MULTIBALL1
museum super jackpot: page(MACHINE5_PAGE), PRI_SUPER_JACKPOT, D_QUEUED+D_RESTARTABLE

cryoprison start effect: page(MACHINE5_PAGE), PRI_MULTIBALL2, D_QUEUED
cryoprison jackpot effect: page(MACHINE5_PAGE), PRI_JACKPOT, D_QUEUED+D_RESTARTABLE
cryoprison effect: page(MACHINE5_PAGE), PRI_MULTIBALL1
cryoprison super jackpot: page(MACHINE5_PAGE), PRI_SUPER_JACKPOT, D_QUEUED+D_RESTARTABLE

demotime start effect: page(MACHINE5_PAGE), PRI_WIZARD2, D_QUEUED
demotime jackpot effect: page(MACHINE5_PAGE), PRI_WIZARD_JACKPOT, D_RESTARTABLE
demotime info effect: page(MACHINE5_PAGE), PRI_GAME_LOW5, D_QUEUED
demotime effect: page(MACHINE5_PAGE), PRI_WIZARD1

huxley info effect: page(MACHINE5_PAGE), PRI_GAME_LOW5, D_QUEUED+D_RESTARTABLE
huxley start effect: page(MACHINE5_PAGE), PRI_WIZARD2
huxley effect: page(MACHINE5_PAGE), PRI_WIZARD1, D_QUEUED
huxley hit effect: page(MACHINE5_PAGE), PRI_WIZARD_JACKPOT, D_RESTARTABLE

bitf start effect: page(MACHINE5_PAGE), PRI_WIZARD2, D_QUEUED
bitf hit effect: page(MACHINE5_PAGE), PRI_WIZARD_JACKPOT, D_RESTARTABLE
bitf info effect: page(MACHINE5_PAGE), PRI_GAME_LOW5, D_QUEUED
bitf effect: page(MACHINE5_PAGE), PRI_WIZARD1
bitf end effect: page(MACHINE5_PAGE), PRI_WIZARD2, D_QUEUED


##########################################################################
#
# Lamp effects  -- page 4 (53)
#
##########################################################################
[leffs]
extraball: PRI_LEFF3, LAMPS(AMODE_ALL), page(MACHINE3_PAGE)


Amode: runner, PRI_LEFF1, LAMPS(AMODE_ALL), GI(ALL), page(MACHINE4_PAGE)

top popper: shared, PRI_LEFF2, page(MACHINE4_PAGE)
eject: shared, PRI_LEFF2, page(MACHINE4_PAGE) 

flash all: PRI_LEFF3, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)
bot2top: PRI_LEFF3, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)
top2bot: PRI_LEFF3, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)
right2left: PRI_LEFF3, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)
left2right: PRI_LEFF3, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)
no gi onesec: PRI_LEFF1, GI(ALL), page(MACHINE4_PAGE)
no gi twosec: PRI_LEFF1, GI(ALL), page(MACHINE4_PAGE)
turn off gi: PRI_LEFF1, GI(ALL), page(MACHINE4_PAGE)
flash gi: PRI_LEFF1, GI(ALL), page(MACHINE4_PAGE)
flash ul gi: PRI_LEFF1, GI(ALL), page(MACHINE4_PAGE)
flash ur gi: PRI_LEFF1, GI(ALL), page(MACHINE4_PAGE)
flash ll gi: PRI_LEFF1, GI(ALL), page(MACHINE4_PAGE)
flash lr gi: PRI_LEFF1, GI(ALL), page(MACHINE4_PAGE)

frenzy1: shared, PRI_LEFF2, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)
frenzy2: shared, PRI_LEFF2, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)
frenzy3: shared, PRI_LEFF2, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)
frenzy4: shared, PRI_LEFF2, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)
frenzy5: shared, PRI_LEFF2, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)


left ramp: shared, PRI_LEFF2, page(MACHINE4_PAGE)
right ramp: shared, PRI_LEFF2, page(MACHINE4_PAGE)
center ramp: shared, PRI_LEFF2, page(MACHINE4_PAGE)
side ramp: shared, PRI_LEFF2, page(MACHINE4_PAGE)
ramp quickfreeze: shared, PRI_LEFF1, LAMPS(LEFT_RAMP_AWARDS), page(MACHINE4_PAGE)
ramp clawready: shared, PRI_LEFF1, LAMPS(RIGHT_RAMP_AWARDS), page(MACHINE4_PAGE)

lower rebound: shared, PRI_LEFF2, page(MACHINE4_PAGE)
upper rebound: shared, PRI_LEFF2, page(MACHINE4_PAGE) 

orbits runner: shared, PRI_LEFF1, LAMPS(LEFT_LOOP_AWARDS), page(MACHINE4_PAGE)

freeze: PRI_LEFF3, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)

car chase: PRI_LEFF3, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)
acmag: PRI_LEFF3, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)
explode: PRI_LEFF3, GI(ALL), page(MACHINE4_PAGE)
claw: shared, PRI_LEFF2, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)
mb start: shared, PRI_LEFF2, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)

inlane quick freeze: shared, PRI_LEFF1, LAMPS(LEFT_RAMP_AWARDS), page(MACHINE4_PAGE)
inlane cryoclaw: shared, PRI_LEFF1, LAMPS(RIGHT_RAMP_AWARDS), page(MACHINE4_PAGE)

Underground: shared, PRI_LEFF2, LAMPS(UNDERGROUND_SCOOP), page(MACHINE4_PAGE)
computer award: PRI_LEFF3, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)

eyeball: shared, PRI_LEFF2, page(MACHINE4_PAGE)

jackpot: PRI_LEFF3, GI(ALL), page(MACHINE4_PAGE)
jackpot1: PRI_LEFF3, GI(ALL), page(MACHINE4_PAGE)
jackpot2: PRI_LEFF3, GI(ALL), page(MACHINE4_PAGE)
jackpot3: PRI_LEFF3, GI(ALL), page(MACHINE4_PAGE)
jackpot4: PRI_LEFF3, GI(ALL), page(MACHINE4_PAGE)
super jackpot: PRI_LEFF4, GI(ALL), page(MACHINE4_PAGE)

skillshot: shared, PRI_LEFF2, page(MACHINE4_PAGE)

car crash runner: PRI_LEFF1, LAMPS(CAR_CRASH), page(MACHINE4_PAGE)

