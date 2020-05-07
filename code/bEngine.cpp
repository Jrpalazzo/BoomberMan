#include "bEngine.h"

Engine::Engine()
{
  countedFrames = 0;
  runState = true;
  newPlayer = Player(); 
  guitarFlag = false; 
}

Engine::~Engine() { }

bool Engine::running(bool & quit)
{
	if(!quit)
	{
	   closeSDL();
	}

	return quit;
}

bool Engine::getRunState()
{
	return runState; 
}

bool Engine::initSDL()
{
	//Initialize SDL
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	fpsTimer.start();

	return true;
}

void Engine::closeSDL()
{
	//Destroy window	
	playManager.free(); 
	SDL_DestroyRenderer( nRenderer );
	window.free();
	nRenderer = NULL;
	IMG_Quit();
	SDL_Quit();

}

void Engine::updateFpsTimer()
{
	//If frame finished early
	int frameTicks = capTimer.getTicks();

	if( frameTicks < SCREEN_TICK_PER_FRAME )
	{
		//Wait remaining time
		SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
	}
}

void Engine::initWindow()
{
	//Set texture filtering to linear
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
		printf( "Warning: Linear texture filtering not enabled!" );
	}

	//Create window
	if( !window.init() )
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create renderer for window
		nRenderer = window.createRenderer();

		if( nRenderer == NULL )
		{
			printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor( nRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if( !( IMG_Init( imgFlags ) & imgFlags ) )
			{
				printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
			}

			if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			{
				printf("SDL_mixer did not initialize. %s\n", Mix_GetError);
			}
		}

		newPlayer.loadPlayerTexture(nRenderer);

		playManager.loadMedia(window, nRenderer);
		
	}
}


void Engine::update()
{
	capTimer.start();

	if(inputManager.mainInputs(runState, newPlayer, window.getWindow(), guitarFlag))
	{
		//Only draw when not minimized
		if( !window.isMinimized() )
		{
			//Calculate and correct fps
			float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );

			if( avgFPS > 2000000 )
			{
				avgFPS = 0;
			}
	
			//std::cout<< "Average Frames Per Second (With Cap) " << avgFPS << std::endl; 
			
			//Clear screen
			SDL_SetRenderDrawColor( nRenderer, 0, 120, 0, 0);
			SDL_RenderClear(nRenderer);

			++countedFrames;
	
			playManager.updateLevel(nRenderer, window, guitarFlag);

			newPlayer.movePlayer();

			newPlayer.renderPlayer(nRenderer); 

			SDL_RenderPresent( nRenderer );
		}

	}
	else
	{
		runState = false;
		running(runState);
	}

	updateFpsTimer();
	
}

