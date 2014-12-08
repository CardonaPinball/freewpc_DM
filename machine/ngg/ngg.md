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
Title: Good Gofers
#DMD: Yes
#Fliptronic: Yes
#DCS: Yes
#WPC95: Yes

Lamp-Matrix-Width: 19
Lamp-Matrix-Height: 34





##########################################################################
# Include standard definitions that apply to all WPC games.
##########################################################################
include platform/wpc/wpc95.md





##########################################################################
# Use 'define' to emit a plain #define for anything not covered by
# some other means.
##########################################################################


##########################################################################
# special hardware flags
##########################################################################
define MACHINE_NGG
define MACHINE_HAS_UPPER_RIGHT_FLIPPER



##########################################################################
# The model of pinball is encoded on three digits and must match that expected by the game PROM (see list below).
#
# The serial number has six digits and matches the one printed on the labels inside the pinball machine, 
# a supplementary number five-digit it is associated. If you do not know these numbers, you can use the generic 
# values 123456 12345, or 999999 99999.
#
#N° 	Type 	Pinball 	    				N° 	Type 	Pinball
#524	WPC-S	Red & Ted's Road Show 			541	WPC-95	Attack From Mars
#525	WPC-S	No Fear 						547	WPC-95	Tales Of The Arabian Nights
#526	WPC-S	Indianapolis 500 				548	WPC-95	Scarred Stiff
#529	WPC-S	Flintstones 					550	WPC-95	Congo
#530	WPC-S	Dirty Harry 					552	WPC-95	Junk Yard
#531	WPC-S	World Cup Soccer 94 			553	WPC-95	NBA Fast Break
#532	WPC-S	The Shadow 						559	WPC-95	Medieval Madness
#536	WPC-S	Corvette 						561	WPC-95	No Good Gofers
#539	WPC-S	Theatre Of Magic 				562	WPC-95	Cirqus Voltaire
#124	WPC-S	Theatre Of Magic (Home) 		563	WPC-95	Champion Pub
#542	WPC-S	Johnny Mnemonic 				565	WPC-95	Monster Bash
#544	WPC-S	Who Dunnit 						566	WPC-95	Cactus Canyon
#551	WPC-S	Jackbot 						903	WPC-95	Safe Cracker
#620	WPC-S	Pinball Circus 					905	WPC-95	Ticket Tac Toe
#584	WPC-S	Test Fixture 					648	WPC-95	Test Fixture
##########################################################################
define MACHINE_NUMBER 561



##########################################################################
# timing overrides
##########################################################################
define MACHINE_BALL_SAVE_TIME       7
define MACHINE_MAX_BALLS            6
define AUTOFIRE_DELAY 				20
define MACHINE_BALL_SEARCH_TIME 	10



##########################################################################
# effects overrides
##########################################################################
#define MACHINE_ADD_CREDIT_SOUND PLONK 
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
define IN_DMD_TEST TRUE
define IN_CAB_TEST TRUE




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
#TODO colors of lights 

[lamps]
11: Outlane Extra Ball, amber, x( 1), y(25)
12: Kickback, amber, x( 1), y(26)
13: Lower Driving Range, amber,x( 2), y(21)
14: Shoot Again, shoot-again, amber, x(11), y(30)
15: Special, amber,x(19), y(24)
16: Wheel Value, amber,x(13), y(18)
17: Jet Lightning, amber, x( 4), y(15)
18: Hole 8, amber, x(14), y(25)

21: Hole 5,red,x(11), y(14)
22: Hole 4, amber, x( 9), y(21)
23: Hole 3, amber, x( 8), y(24)
24: Hit Bud, amber,x(10), y(25)
25: Hole 1, amber, x( 6), y(12)
26: 2X, amber, x( 6), y(12)
27: Cart Path 2, amber,x( 9), y(28)
28: 5X Cart Path, red, x(11), y(29)

31: Hole 6, red, x(12), y(23)
32: Hole 7, red, x(13), y(24)
33: Hole 2, white, x(7), y(25)
34: Hit Buzz, white, x(12), y(25)
35: Hole 9, white, x(14), y( 6)
36: 4X, red, x(14), y(27)
37: Cart Path 4, yellow, x(12), y(28)
38: 3X, white, x(11), y(28)

41: Driving range, yellow,x(11), y(17)
42: Increase Golf Cart, yellow,x(11), y(16)
43: Increase Buzz Value, yellow,x(10), y(15)
44: Increase Bud Value, yellow,x( 9), y(14)
45: Newton Drive, yellow,x( 8), y(13)
46: Collect, red,x( 6), y(12)
47: Ripoff, red, x(10), y(12)
48: Left Loop Drive, white,x( 5), y(11)

51: K1 Kick, white,x(17), y(14)
52: I Kick, white,x(17), y(15)
53: C Kick, orange,x(16), y(16)
54: K2 Kick, white,x(16), y(17)
55: Skill Shot, white,x(14), y(10)
56: Relight Jackpot, orange,x(15), y( 6)
57: Right Ramp Lock, red,  x(15), y( 7)
58: right Ramp Drive, orange,x(15), y( 8)

61: 4 Strokes,red, x( 7), y(18)
62: 3 Strokes, orange, x( 8), y(19)
63: 2 Strokes, yellow, x( 6), y(20)
64: 5 Strokes, yellow,x( 5), y(18)
65: 7 Strokes, yellow,x( 4), y(21)
66: 6 Strokes, red,x( 4), y(19)
67: Left Spinner, white,x( 4), y(10)
68: Trap Ready, orange,x( 3), y(17)

71: Advance Trap, yellow, x(11), y(18)
72: Center Drive, yellow, x(12), y( 7)
73: Center Lock, yellow, x(12), y( 6)
74: Get TNT, yellow, x(12), y( 4)
75: Center Raise Gofer, yellow, x(13), y( 4) 
76: Right Spinner, yellow, x(19), y( 2)
77: Right Loop Drive, orange, x(18), y( 4)
78: Bottom Jet Bumper, red, x(23), y(15)

81: Side Ramp Drive, yellow,x(10), y( 4)
82: Extra Ball, extra-ball,white, x(11), y( 2)
83: Multiball, yellow,x(11), y( 3)
84: Jackpot, red,x(11), y( 5)
85: Putt Out, yellow,x(11), y( 1)
86: Top Jet Bumper, yellow,x( 1), y( 9)
87: middle Jet Bumper, yellow, x( 2), y(11)
88: Start Button, start, cabinet, yellow, x( 2), y(31)





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
#, sound(TILT)
#45: Right Jet, ingame, c_decl(sw_jet)
#73: Top Popper, opto, edge, novalid, debounce(TIME_200MS)

11: Launch Button, launch-button, cabinet, novalid
12: Left Ramp Make, ingame
13: Start Button, start-button, cabinet, intest, novalid, debounce(TIME_100MS)
14: Tilt, tilt, noscore, ingame, novalid, cabinet
15: center Ramp Make, ingame 
16: Left Outlane 1, ingame
17: Right Inlane, ingame
18: Shooter Lane, edge, shooter, noscore, debounce(TIME_200MS), novalid

21: Slam Tilt, slam-tilt, ingame, novalid, cabinet
22: Coin Door Closed, noscore,novalid
23: Jet Advance Standup, ingame
24: Always Closed, noscore,novalid
25: Underground Pass, ingame 
26: Left Inlane, ingame
27: Left Outlane 2, ingame
28: Kickback, ingame

31: Trough Eject, noscore, novalid, opto
32: Trough 1, noscore, novalid, opto
33: Trough 2, noscore, novalid, opto
34: Trough 3, noscore, novalid, opto
35: Trough 4, noscore, novalid, opto
36: Trough 5, noscore, novalid, opto
37: Trough 6, noscore, novalid, opto
38: Jet Popper, ingame, novalid, opto

41: Left Gofer Down, ingame, opto
42: Right Gofer Down, ingame, opto

44: Putt Out Popper, ingame, opto
45: Right Popper Jam, noscore,ingame, opto
46: Right Popper, ingame, opto
47: Left Ramp Down, ingame, novalid 
48: Right Ramp Down, ingame, novalid 

51: Left Sling sw, ingame, c_decl(sw_sling) 
52: Right Sling sw, ingame, c_decl(sw_sling)
53: Top Jet Bumper, ingame, lamp(LM_TOP_JET_BUMPER)
54: Middle Jet Bumper, ingame, lamp(LM_MIDDLE_JET_BUMPER)
55: Bottom Jet Bumper, ingame, lamp(LM_BOTTOM_JET_BUMPER)
56: Top Skill Shot, ingame
57: Middle Skill Shot, ingame
58: Lower Skill Shot, ingame

61: Left Spinner, ingame
62: Right Spinner, ingame
63: Inner Wheel Opto, ingame, novalid,opto 
64: Outer Wheel Opto, ingame, novalid,opto 
65: Left Gofer 1a, ingame, novalid
66: Left Gofer 2a, ingame, novalid
67: Behind Left Gofer, ingame, novalid
68: Hole in One, ingame, novalid

71: Left Cart Path, ingame
72: Right Cart Path, ingame
73: Right Ramp Make, ingame
74: Golf Cart, ingame, novalid
75: Left Gofer 1b, ingame, novalid
76: Left Gofer 2b, ingame, novalid

77: Advance Trap Value, ingame
78: Sand Trap Eject, ingame, novalid

81: Kick Advance, ingame
82: K1 Kick, ingame
83: I Kick, ingame
84: C Kick, ingame
85: K2 Kick, ingame
86: Captive Ball, ingame




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
H1: Launch, launch, nosearch, duty(SOL_DUTY_100), time(TIME_133MS)
H2: Kickback, time(TIME_200MS)
H3: Clubhouse Kicker, duty(SOL_DUTY_50), time(TIME_200MS)
H4: Left Gofer Up, duty(SOL_DUTY_50), time(TIME_200MS)
H5: Right Gofer Up, duty(SOL_DUTY_50), time(TIME_200MS)
H6: Jet Popper, duty(SOL_DUTY_50), time(TIME_200MS)
H7: Left Eject, duty(SOL_DUTY_50), time(TIME_200MS)
H8: Upper Right Eject, duty(SOL_DUTY_50), time(TIME_200MS)

L1: BallServe, ballserve, duty(SOL_DUTY_100), time(TIME_133MS)
L2: Left Sling Sol, duty(SOL_DUTY_75)
L3: Right Sling Sol, duty(SOL_DUTY_75)
L3: Top Jet Bumper, duty(SOL_DUTY_100)
L4: Middle Jet Bumper, duty(SOL_DUTY_100)
L5: bottom Jet Bumper, duty(SOL_DUTY_100)
L6: Left Gofer Down, duty(SOL_DUTY_50), time(TIME_200MS)
L7: Right Gofer Down, duty(SOL_DUTY_50), time(TIME_200MS)

F1: Jet Flasher, flash, nosearch
F2: Lower Left Flasher, flash, nosearch
F3: Left Spinner Flasher, flash, nosearch
F4: Right Spinner Flasher, flash, nosearch
F5: Lower Right Flasher, flash, nosearch

F8: Underground Passs, flash, nosearch

G1: Sand Trap Flasher, flash, nosearch
G2: Wheel Flasher, flash, nosearch
G3: Left Ramp Down,  duty(SOL_DUTY_50)
G4: Right Ramp Down,  duty(SOL_DUTY_50)

F1: L.R. Flip Power, time(TIME_33MS)
F2: L.R. Flip Hold, time(TIME_100MS)
F3: L.L. Flip Power, time(TIME_33MS)
F4: L.L. Flip Hold, time(TIME_100MS)
F5: U.R. Flip Power, time(TIME_33MS)
F6: U.R. Flip Hold, time(TIME_100MS)
F7: Ball Launch Ramp, time(TIME_33MS)

A1: Upper Right 1 Flasher, flash, nosearch
A2: Upper Right 2 Flasher, flash, nosearch
A3: Upper Right 3 Flasher, flash, nosearch
A4: Upper Playfield Right Flasher, flash, nosearch
A5: Upper Playfield Left Flasher, flash, nosearch
A6: Upper Left 3 Flasher, flash, nosearch
A7: Upper Left 2 Flasher, flash, nosearch
A8: Upper Left 1 Flasher, flash, nosearch




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
Left Sling: driver(sling), sw=SW_LEFT_SLING_SW, sol=SOL_LEFT_SLING_SOL, ontime=3, offtime=16

#Right Sling: driver(sling), sw=SW_RIGHT_SLING_SW, sol=SOL_RIGHT_SLING_SOL, ontime=3, offtime=16

#Left Jet: driver(jet), sw=SW_LEFT_JET, sol=SOL_LEFT_JET, ontime=3, offtime=16
#Right Jet: driver(jet), sw=SW_RIGHT_JET, sol=SOL_RIGHT_JET, ontime=3, offtime=16

#Top Jet: driver(jet), sw=SW_TOP_JET, sol=SOL_TOP_SLING, ontime=3, offtime=16
#Diverter: driver(divhold), power_sol=SOL_DIVERTER_POWER, hold_sol=SOL_DIVERTER_HOLD, mode=0, power_pulse_ms=64, schedule_ms=32, includetest(yes)

#Claw: driver(bivar2), left_sol=SOL_CLAW_LEFT, right_sol=SOL_CLAW_RIGHT, left_sw=SW_CLAW_POSITION_2, right_sw=SW_CLAW_POSITION_1, includetest(yes)

#Shaker: driver(shakermotor),  sol=SOL_SHAKER_MOTOR



##########################################################################
# General Illumination
##########################################################################
[gi]
0: Left Side String
1: Right Side String
2: Gofer Spotlight
3: Illumination String 4
4: Illumination String 5





##########################################################################
# Tests
# These are additional test items that should appear in the TESTS menu.
##########################################################################
[tests]
#diverter: 		#autogenerated-test, see defintion in [templates] section.

#slam ramp:




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
Multipliers: 2X, 3X, 4X, Cart Path 2, Cart Path 4
Holes: Hole 1, Hole 2, Hole 3, Hole 4, Hole 5, Hole 6, Hole 7, Hole 8, Hole 9
Strokes: 4 Strokes, 3 Strokes, 2 Strokes, 5 Strokes, 7 Strokes, 6 Strokes
Right Ramp Awards: Relight Jackpot, Right Ramp Lock, right Ramp Drive
Left Ramp Awards: Center Drive, Center Lock, Get TNT, Center Raise Gofer
Putting Green Awards: Extra Ball, Multiball,  Putt Out
Amode All: Multipliers, Holes, Strokes, Right Ramp Awards, Left Ramp Awards, Putting Green Awards

Left Right: PF:lamp_sort_bottom_to_top
Right Left: PF:lamp_sort_top_to_bottom
Bottom Top: PF:lamp_sort_left_to_right
Top Bottom: PF:lamp_sort_right_to_left

Amode Rand: Amode All






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
#Top Sol: Top Popper, Top Popper
#Subway VUK: Bottom Popper, Bottom Popper

Trough: BallServe, init_max_count(6), Trough 1, Trough 2, Trough 3, Trough 4, Trough 5, Trough 6

#Lock: Lock Release, init_max_count(0), Lock 



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
IS_EXTRABALL_LIT:
IS_MULTIBALL_ENABLED:






##########################################################################
# System-wide bit flags.
#
#limit of 32 total
##########################################################################
[globalflags]




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
#
#exocet10:  very gothic
#exocet14:  very gothic
#halobold12: DEMO MAN
#halobold14: DEMO MAN
#dmgraphs:   DEMO MAN
#bitcube10:
#
#telemarines10:  T2?
#telemarines14:  T2?
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
fixed6:
halobold12:
halobold14:

##########################################################################
# Display effects  -- text page (?)
##########################################################################
[deffs]
#clw inlanes effect: PRI_GAME_LOW4, D_QUEUED+D_TIMEOUT
#combo effect: PRI_GAME_LOW2, D_RESTARTABLE
#skillshot: PRI_SPECIAL

##########################################################################
# Display effects  -- common page (?)
##########################################################################


##########################################################################
# Display effects  -- page 1 (56)
##########################################################################


##########################################################################
# Display effects  -- page 2 (55)
##########################################################################
#bonus: page(MACHINE2_PAGE), PRI_BONUS, D_QUEUED



##########################################################################
# Display effects  -- page 3 (54)
##########################################################################



##########################################################################
# Display effects  -- page 4 (53)
##########################################################################
#troubleshooting: page(MACHINE4_PAGE), PRI_SCORES_IMPORTANT, D_QUEUED




##########################################################################
# Display effects  -- page 5 (52)
##########################################################################



##########################################################################
#
# Lamp effects  -- page 4 (53)
#
##########################################################################
[leffs]
#Amode: runner, PRI_LEFF1, LAMPS(AMODE_ALL), GI(ALL), page(MACHINE4_PAGE)

#top popper: shared, PRI_LEFF2, page(MACHINE4_PAGE)
#extraball: PRI_LEFF3, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)

#flash all: PRI_LEFF3, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)
#bot2top: PRI_LEFF3, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)
#top2bot: PRI_LEFF3, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)
#right2left: PRI_LEFF3, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)
#left2right: PRI_LEFF3, LAMPS(AMODE_ALL), page(MACHINE4_PAGE)
#no gi onesec: PRI_LEFF1, GI(ALL), page(MACHINE4_PAGE)
#no gi twosec: PRI_LEFF1, GI(ALL), page(MACHINE4_PAGE)
#turn off gi: PRI_LEFF1, GI(ALL), page(MACHINE4_PAGE)
#turn on gi: PRI_LEFF1, GI(ALL), page(MACHINE4_PAGE)
#flash gi: PRI_LEFF1, GI(ALL), page(MACHINE4_PAGE)

