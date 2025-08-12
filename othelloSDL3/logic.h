// This game logic is inspired by my other project 

#ifndef LOGIC_H
#define LOGIC_H
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

 // We define a struct that will act as the board
typedef struct { uint8_t cell[8][8]; } Board;

// Types of cells that we can find on our board
typedef enum { CELL_WHITE = 0, CELL_BLACK = 1, CELL_EMPTY = 2 } Cell;

// Definition of players
typedef enum { PLAYER_WHITE = 1, PLAYER_BLACK = 2 } Player;

// Definition of gamestates
typedef enum
{
	RESULT_ONGOING = 0,
	RESULT_WHITE_WINS = 1,
	RESULT_BLACK_WINS = 2,
	RESULT_DRAW = 3,
} GameResult;

// Definition of coordinates on the game board name as in ADA_Othello
typedef struct { uint8_t row; uint8_t col; } Position;


// We're going to need a function that checks

#endif //LOGIC_H
