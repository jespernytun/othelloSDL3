#ifndef BUTTON_H
#define BUTTON_H


#include <SDL3/SDL.h>
#include <stdint.h>
#include "logic.h"


typedef enum { BUTTON_NORMAL, BUTTON_HOVER, BUTTON_PRESSED} BtnState; // Definition of different states of our buttons


typedef struct // Represents a tile on the Othello board
{
	SDL_FRect rect;  // x, y ,w ,h where x and y are the top left coordinates
	uint8_t row, col;
} Tile;

void tile_init(                             // We initialize the tile
	Tile *b,								// We input a tile
	float x, float y, float w, float h,     // Coordinates of the tile
	uint8_t row, uint8_t col				// Row and Col of the tile
);

bool tile_hit_test(         // Fucntion to test wether or not we press the tile
	const Tile* b,          // Tile in question
	float mx, float my      // Coordinates clicked that we check against
);

void tile_draw(const Tile* b, SDL_Renderer* r, const Board* board);


#endif // BUTTON_H