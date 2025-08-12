#include "button.h"
#include <SDL3/SDL.h>

void tile_init(Tile* b, float x, float y, float w, float h, uint8_t row, uint8_t col)
{
	b->rect.x = x;
	b->rect.y = y;
	b->rect.w = w;
	b->rect.h = h;
	b->row = row;
	b->col = col;
}

bool tile_hit_test(const Tile* b, float mx, float my)
{
	return(
		mx >= b->rect.x &&
		mx <= b->rect.x + b->rect.w && // Check if we clicked to the right of top left, but not too far right of top left of button
		my >= b->rect.y &&
		my <= b->rect.y + b->rect.h); // Check if we clicked under the top left corner, but not too far under top left corner of button
	// if yes we are on the button and we retun True
	// else, we're off and return False
}

void tile_draw(const Tile* b, SDL_Renderer* r, const Board* board)
{
	// Color the empty tile dark green
	SDL_SetRenderDrawColor(r, 0, 128, 0, 255);
	SDL_RenderFillRect(r, &b->rect);

	Cell piece = board->cell[b->row][b->col]; // We get what kind of piece we have on the Tile

	if (piece != CELL_EMPTY) // We check if there is a piece
	{
		float cx = b->rect.x + b->rect.w / 2.0f;
		float cy = b->rect.y + b->rect.h / 2.0f;
		float radius = (b->rect.w < b->rect.h ? b->rect.w : b->rect.h) * 0.4f;

		if (piece == CELL_WHITE)
			SDL_SetRenderDrawColor(r, 255, 255, 255, 255); // The piece is white, we render a white piece
		else
			SDL_SetRenderDrawColor(r, 0, 0, 0, 255); // The piece is not white, we render a black piece

		for (int w = -radius; w <= radius; w++)
		{
			for (int h = -radius; h <= radius; h++)
			{
				if (w * w + h * h < radius * radius)
				{
					SDL_RenderPoint(r, cx + w, cy + h);
				}
			}
		}
	}
	// We want to make sure we can tell the buttons appart so we make a radius
	SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
	SDL_RenderRect(r, &b->rect);
}