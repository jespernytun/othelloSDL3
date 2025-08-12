#include "logic.h"
#include <string.h>

// Quick function to check if we're in bounds or not :)
#define BOARD_SIZE 8
static inline bool in_bounds(int r, int c) {
	return (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE);
}

// Quick function to flip opponent
static inline Cell cell_opponent(Cell me) {
	if (me == CELL_BLACK) return CELL_WHITE;
	if (me == CELL_WHITE) return CELL_BLACK;
	return CELL_EMPTY; // "no opponent" tester
}

// This is the case from ADA_Othello translated to C
// We will however not be using a million billion if statements like we did last time
// Because we have learned since then
static inline void direction_to_delta(Direction d, int* dr, int* dc) {
	switch (d) {
	case DIR_N:  *dr = -1; *dc = 0;  break;
	case DIR_NE: *dr = -1; *dc = 1;  break;
	case DIR_E:  *dr =  0; *dc = 1;  break;
	case DIR_SE: *dr =  1; *dc = 1;  break;
	case DIR_S:  *dr =  1; *dc = 0;  break;
	case DIR_SW: *dr =  1; *dc = -1; break;
	case DIR_W:  *dr =  0; *dc = -1; break;
	case DIR_NW: *dr = -1; *dc = -1; break;
	default:
		// Unknown Direction – keep (0,0) so tests fail safely.
		*dr = 0; *dc = 0; break;
	}
}

void board_init_start(Board *b)
{
	// We create a totally empty board
	for (int r = 0; r < 8; r++)
		for (int c = 0; c < 8; c++)
			b->cell[r][c] = CELL_EMPTY;

	// Add starting pieces
	b->cell[3][3] = CELL_WHITE;
	b->cell[4][4] = CELL_WHITE;
	b->cell[3][4] = CELL_BLACK;
	b->cell[4][3] = CELL_BLACK;
}

bool board_place_if_empty(Board* b, uint8_t row, uint8_t col, Cell piece)
{
	if (row >= 8 || col >= 8) return false;
	if (b->cell[row][col] != CELL_EMPTY) return false;
	b->cell[row][col] = piece;
	return true;
}

bool test_direction_legal(const Board *b, uint8_t row, uint8_t col, Cell me, Direction d, uint8_t *out_flips )
{
	if (row >= BOARD_SIZE || col >= BOARD_SIZE) return false; // must be in bounds, not legal direction
	if (b->cell[row][col] != CELL_EMPTY) return false; // target must be empty, not legal direction

	int dr = 0, dc = 0;
	direction_to_delta(d, &dr, &dc); // Give us the deplacement needed for the given direction

	Cell opp = cell_opponent(me); // We need this to search for our enemy pieces
	int r = (int)row + dr;        // We apply the decalage to each of the directions
	int c = (int)col + dc;		

	// We quickly check that the piece next to us is indeed an opponents piece
	if (!in_bounds(r, c) || b->cell[r][c] != opp) {
		return false; // Not an opponent, not legal direction
	}

	// While loop, while in bounds and opponents piece next, loop;
	// We know if we hit one of our pieces we'll be legal
	uint8_t count = 0;
	while (in_bounds(r, c) && b->cell[r][c] == opp) {
		++count;
		r += dr; // Increment to check next piece
		c += dc; // Increment to check next piece
	}

	// We check what stopped us, out of bounds or our own piece?
	if (!in_bounds(r, c)) return false; // Out of bounds
	// Legal move confirmed
	if (b->cell[r][c] == me && count > 0) { // If on our piece and not on zero, redunant test
		if (out_flips) *out_flips = count;   // we out out_flips ADA style with our count
		return true; // Move was legal
	}
	// Armed with the knowledge of legality and the lenght of the string we can now flip some pieces!
	return false;
}

uint8_t turn_pieces_direction(Board* b,
	uint8_t row, uint8_t col,
	Cell me,
	Direction d)
{
	// We use the old function that we made above to get the pieces needed to flip
	uint8_t to_flip = 0;
	if (!test_direction_legal(b, row, col, me, d, &to_flip))
		return 0;

	// We get the incrementation
	int dr = 0, dc = 0;
	direction_to_delta(d, &dr, &dc);
	int r = (int)row + dr;
	int c = (int)col + dc;

	// We use our knowledge of how many pieces we need to flip!
	// We just flip the next "to_flip" pieces in the given direction
	for (uint8_t i = 0; i < to_flip; ++i) {
		b->cell[r][c] = me;
		r += dr;
		c += dc;
	}

	return to_flip;
}
