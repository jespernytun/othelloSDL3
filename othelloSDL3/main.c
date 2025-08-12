// Othello game using SDL3
// This is the main file for the Othello game using SDL3, where I will be coding the graphical interface
// the game logic will be implemented in a separate file :)

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

//  We start by making a window

// definitions
SDL_Window* window;
SDL_Renderer* renderer;


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

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	if (event->type == SDL_EVENT_QUIT) { // If the event pointer points towards quit
		return SDL_APP_SUCCESS;  // We terminate with success
	}
	return SDL_APP_CONTINUE;  // Else, we continue
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
	SDL_SetRenderDrawColor(renderer, 30, 200, 60, 255);
	SDL_RenderClear(renderer);

	// TODO: Make the board

	SDL_RenderPresent(renderer);
	return SDL_APP_CONTINUE;
}

// Freeing the memory whenever we quit the app
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
	if (renderer) { SDL_DestroyRenderer(renderer); renderer = NULL; } // frees memeory of renderer if it exists
	if (window) { SDL_DestroyWindow(window);     window = NULL; } // frees memory of window if it exists
}

