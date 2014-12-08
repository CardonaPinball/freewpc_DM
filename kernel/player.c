/**
 * Some state needs to be "per-player" and not global.
 * We will keep all data 'global' so that access can be fast and easy.
 * We will reserve space for each player so that this data can then be
 * swapped in/out quickly whenever the current player changes.
 *
 * These are termed "local variables" throughout the code.  To declare
 * a local, simply prefix its declaration with "__local__".  The
 * linker will put all locals into a special section of RAM, where
 * these functions expect them.
 *
 * There are also "local flags", which are implemented as a
 * separate bit matrix.
 */

#include <freewpc.h>

/** In simulation, we have to declare the save areas explicitly. */
#ifdef CONFIG_NATIVE
U8 local_save_area[MAX_PLAYERS+1][LOCAL_SIZE];

#undef LOCAL_BASE
#define LOCAL_BASE (&local_save_area[0][0])
#undef LOCAL_SAVE_BASE
#define LOCAL_SAVE_BASE(p) (&local_save_area[p][0])
#endif



/**
 * The save area for each player is arranged as follows:
 */
struct player_save_area {
	U8 local_lamps[NUM_LAMP_COLS];
	U8 local_flags[BITS_TO_BYTES (MAX_FLAGS)];
	U8 local_vars[0];
};


#define save_area ((struct player_save_area *)(LOCAL_SAVE_BASE(player_up)))




/**
 * Initialize the player save areas at the beginning of a game.
 * All flags/lamps are turned off, and all local vars are zeroed.
 */
void player_start_game (void) {
	/* Clear all player local data */
	memset (LOCAL_BASE, 0, LOCAL_SIZE * (MAX_PLAYERS + 1UL));

	/* Clear lamps/flags */
	memset (lamp_matrix, 0, NUM_LAMP_COLS);
	memset (bit_matrix, 0, BITS_TO_BYTES (MAX_FLAGS));
}




/**
 * Save player-local data just after a player's turn ends.
 */
void player_save (void) {
	/* Copy lamps/local flags into the save area */
	memcpy (save_area->local_lamps, lamp_matrix, NUM_LAMP_COLS);
	memcpy (save_area->local_flags, bit_matrix, BITS_TO_BYTES (MAX_FLAGS));

	/* Copy player locals into the save area */
	memcpy (save_area->local_vars, LOCAL_BASE, AREA_SIZE(local));
}


/**
 * Restore player-local data just before a new player's turn.
 */
void player_restore (void) {
	/* Restore lamps/bits from the save area */
	memcpy (lamp_matrix, save_area->local_lamps, NUM_LAMP_COLS);
	memcpy (bit_matrix, save_area->local_flags, BITS_TO_BYTES (MAX_FLAGS));
	
	/* Restore player locals from the save area */
	memcpy (LOCAL_BASE, save_area->local_vars, AREA_SIZE(local));
}

