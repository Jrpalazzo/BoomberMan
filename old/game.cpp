#include "game.h"

Game::Game()
{
 gRenderer = NULL;
 gWindow = NULL;
}

bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, getScreenHeight(), SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			}
		}
	}

	return success;
}

int Game::getScreenHeight()
{
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	SCREEN_HEIGHT = dm.h;

	return SCREEN_HEIGHT;
}

int Game::getScreenWidth()
{
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	SCREEN_WIDTH = dm.w;

	return SCREEN_WIDTH;
}

void Game::clear()
{
 //Clear screen
 SDL_RenderClear( gRenderer );

}

void Game::update()
{
 //Update screen
 SDL_RenderPresent( gRenderer );

}

void Game::close()
{
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

