#include "logic.h"
#include <string.h>

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