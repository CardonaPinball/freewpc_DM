#--------------------------------------------------------------------------
# System description for FreeWPC
# (C) Copyright 2006-2011 by Brian Dominy <brian@oddchange.com>
#
# See tools/genmachine for more information about the format of this file.
#--------------------------------------------------------------------------


#--------------------------------------------------------------------------
# This file contains definitions that are common to every WPC generation.
# You should *NOT* include this file from your machine description;
# rather include the file for the generation applicable to your machine.
# It will include this for you.
#--------------------------------------------------------------------------

include platform/generic.md

[lamps]
11: First Lamp
88: Last Lamp

[switches]
D1: Left Coin, cabinet
D2: Center Coin, cabinet
D3: Right Coin, cabinet
D4: Fourth Coin, cabinet
D5: Escape, service, intest, cabinet, button
D6: Down, service, intest, cabinet, button
D7: Up, service, intest, cabinet, button
D8: Enter, service, intest, cabinet, button
22: Coin Door Closed, cabinet, edge, intest
24: Always Closed, virtual, c_decl(sw_unused)

[drives]
H1: High Power Sol. 1, notinstalled
H2: High Power Sol. 2, notinstalled
H3: High Power Sol. 3, notinstalled
H4: High Power Sol. 4, notinstalled
H5: High Power Sol. 5, notinstalled
H6: High Power Sol. 6, notinstalled
H7: High Power Sol. 7, notinstalled
H8: High Power Sol. 8, notinstalled

L1: Low Power Sol. 1, notinstalled
L2: Low Power Sol. 2, notinstalled
L3: Low Power Sol. 3, notinstalled
L4: Low Power Sol. 4, notinstalled
L5: Low Power Sol. 5, notinstalled
L6: Low Power Sol. 6, notinstalled
L7: Low Power Sol. 7, notinstalled
L8: Low Power Sol. 8, notinstalled

G1: Flasher 1, notinstalled
G2: Flasher 2, notinstalled
G3: Flasher 3, notinstalled
G4: Flasher 4, notinstalled
G5: Flasher 5, notinstalled
G6: Flasher 6, notinstalled
G7: Flasher 7, notinstalled
G8: Flasher 8, notinstalled

A1: General Sol. 1, notinstalled
A2: General Sol. 2, notinstalled
A3: General Sol. 3, notinstalled
A4: General Sol. 4, notinstalled

[gi]
0: G.I. String 1
1: G.I. String 2
2: G.I. String 3
3: G.I. String 4
4: G.I. String 5


[lamplists]
ALL: 11..88
Ball Save: %ball-save

[fonts]
mono9:
tinynum:
var5:
fixed6:
fixed10:
term6:
symbol:
bitmap8:
mono5:		
lucida9:	# used in common/score_deff_dmd.c only, could be replaced

#####################################################################################
# the below system fonts were eliminated to allow more custom fonts
#times8:	#replaced with term6 -- was only used on common/highscore.c for one line
#cu17: 		#replaced with fixed10 -- was only used on common/effect.c for one line
#num5x7:	replaced with var5 -- was only used on try/new_match.c for one line

