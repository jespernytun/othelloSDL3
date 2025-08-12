// Othello game using SDL3
// This is the main file for the Othello game using SDL3, where I will be coding the graphical interface
// the game logic will be implemented in a separate file :)

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "logic.h"
#include "button.h"

//  global
static Board g_board;
static Tile g_tiles[8][8];
static Player g_player = PLAYER_BLACK; // Black statrs the game
static uint8_t g_flips = 0;

// definitions
SDL_Window* window;
SDL_Renderer* renderer;

static const Direction DIRS[8] = {
	DIR_N, DIR_NE, DIR_E, DIR_SE, DIR_S, DIR_SW, DIR_W, DIR_NW
};


// This first function will initialize the window where we will make our window
SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) 
{
	if (!SDL_Init(SDL_INIT_VIDEO)) // We initialize our code
	{
		SDL_Log("Error initializing SDL: %s", SDL_GetError()); // Check for failure
		return SDL_APP_FAILURE;
	}

	window = SDL_CreateWindow("OthelloSDL3", 800, 600, NULL); // We create our window
	if (!window) 
	{
		SDL_Log("Error creating SDL window: %s", SDL_GetError()); // Check for failure
		return SDL_APP_FAILURE;
	}

	renderer = SDL_CreateRenderer(window, NULL); // We create our renderer
	if (!renderer) 
	{
		SDL_Log("Error creating SDL renderer: %s", SDL_GetError()); // Check for failure
		return SDL_APP_FAILURE;
	}

	board_init_start(&g_board);

	// Calculate and fin size of board
	float winW = 800.0f, winH = 600.0f;    // Size of the window
	float tile = (winH < winW ? winH : winW) / 8.0f; // We find the smallest lenght and make our board fill that direction
	float boardW = tile * 8.0f, boardH = tile * 8.0f;
	float offX = (winW - boardW) * 0.5f; // We center the div :))
	float offY = (winH - boardH) * 0.5f;

	// We make a for loop to initialize all times, and offset it by whatever needed every time
	for (uint8_t r = 0; r < 8; r++) {
		for (uint8_t c = 0; c < 8; c++) {
			tile_init(&g_tiles[r][c],
				offX + c * tile, offY + r * tile,
				tile, tile, r, c);
		}
	}
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	if (event->type == SDL_EVENT_QUIT) { // If the event pointer points towards quit
		return SDL_APP_SUCCESS;  // We terminate with success
	}

	// We make an event type to track mouse clicks (left clicks in particular)
	if (event->type == SDL_EVENT_MOUSE_BUTTON_UP &&
		event->button.button == SDL_BUTTON_LEFT)
	{
		// We take note of where the mouse click was
		float mx = event->button.x;
		float my = event->button.y;

		// We check EVERY tile to see if it was clicked
		for (int r = 0; r < 8; r++) {
			for (int c = 0; c < 8; c++) {
				if (tile_hit_test(&g_tiles[r][c], mx, my)) {
					// Intermediary check to see what player is currently playing
					Cell piece = (g_player == PLAYER_WHITE) ? CELL_WHITE : CELL_BLACK;

					// Check if tile is occupied
					if (g_board.cell[r][c] != CELL_EMPTY) {
						SDL_Log("(%d,%d) occupied", r, c);
						goto end; // stop the search before we waste my memory
					}

					// Now we check legalty of move in all directions
					uint8_t total_flips = 0; // We use this to check if a direction is legal
					for (int i = 0; i < 8; ++i)
					{
						uint8_t flips = 0;
						Direction d = DIRS[i];
						if (test_direction_legal(&g_board, (uint8_t)r, (uint8_t)c, piece, d, &flips) && flips > 0)
						{
							SDL_Log("Legal %d,%d dir=%d flips=%u", r, c, (int)d, flips);
							// We add flips to the counter
							total_flips += turn_pieces_direction(&g_board, (uint8_t)r, (uint8_t)c, piece, d); // We turn the pieces
						}
					}
					// Check if indeed legal
					if (total_flips > 0) {
						// Legal confirmed
						g_board.cell[r][c] = piece; // We place the piece piece on the board
						g_player = (g_player == PLAYER_WHITE) ? PLAYER_BLACK : PLAYER_WHITE; // We change turns
					}
					// else goto end;
				}   
			}
		}
	}
	end:
	return SDL_APP_CONTINUE;  // Else, we continue
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
	SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
	SDL_RenderClear(renderer);

	for (int r = 0; r < 8; r++)
		for (int c = 0; c < 8; c++)
			tile_draw(&g_tiles[r][c], renderer, &g_board);

	SDL_RenderPresent(renderer);
	return SDL_APP_CONTINUE;
}

// Freeing the memory whenever we quit the app
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
	if (renderer) { SDL_DestroyRenderer(renderer); renderer = NULL; } // frees memeory of renderer if it exists
	if (window) { SDL_DestroyWindow(window);     window = NULL; } // frees memory of window if it exists
}

