// This game logic is inspired by my other project 

#ifndef LOGIC_H
#define LOGIC_H
#include <stdio.h>
#include <stdbool.h>

typedef struct // We define a struct that will act as the board
{
	uint8_t cell[8][8]; 
} Board;

// We define the different types of content that can be contained in a cell on our board
typedef enum {CELL_WHITE = 0, CELL_BLACK = 1, CELL_EMPTY = 2} Cell;

// We define the game_init and game_reset functions for later
void game_init(Board* g);
void game_reset(Board* g);
// We point towards to the game to make sure that we edit the actual game board in memory