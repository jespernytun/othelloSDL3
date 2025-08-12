// This game logic is inspired by my other project 

#ifndef LOGIC_H
#define LOGIC_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>


//
// STRUCTS AND ENUMS
//

// Types of cells that we can find on our board
typedef enum { CELL_WHITE = 0, CELL_BLACK = 1, CELL_EMPTY = 2 } Cell;

// We define a struct that will act as the board
#define BOARD_SIZE 8
typedef struct { uint8_t cell[BOARD_SIZE][BOARD_SIZE]; } Board;

// Definition of players
typedef enum { PLAYER_WHITE = 1, PLAYER_BLACK = 2 } Player;

// Definition of gamestates if we want to make a menu later or something
typedef enum
{
	RESULT_ONGOING = 0,
	RESULT_WHITE_WINS = 1,
	RESULT_BLACK_WINS = 2,
	RESULT_DRAW = 3,
} GameResult;


// Eight compass directions for scanning the board
enum Direction {
    DIR_N = 0,  // (-1,  0)
    DIR_NE,     // (-1, +1)
    DIR_E,      // ( 0, +1)
    DIR_SE,     // (+1, +1)
    DIR_S,      // (+1,  0)
    DIR_SW,     // (+1, -1)
    DIR_W,      // ( 0, -1)
    DIR_NW      // (-1, -1)
};
typedef enum Direction Direction; // I don't understand at all why this was nessecary but without it it does not work at all

// Definition of coordinates on the game board name as in ADA_Othello
typedef struct { uint8_t row; uint8_t col; } Position;

//
// FUNCTIONS
//

// Creates an empty board
void board_init_start(Board* b);

//
// MOVE VALIDATION
//

// We check if the board is empty (first step) 
bool board_place_if_empty(
	Board* b,
	uint8_t row, uint8_t col,
	Cell piece
);

bool test_direction_legal(
	const Board* b,
	uint8_t row, uint8_t col,    // Starting cell
	Cell me,                     // Current player
	Direction d,				 // Direction we are going to check
	uint8_t* out_flips			 // Number of flips to be used by turn_pieces_direction
);

uint8_t turn_pieces_direction(
	Board* b,
	uint8_t row, uint8_t col,
	Cell me,
	Direction d
);


#endif //LOGIC_H
