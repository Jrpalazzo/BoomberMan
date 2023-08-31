#include "bEngine.h"

Engine::Engine()
{
  countedFrames = 0;
  runState = true;
  resetState = false;
  newPlayer = Player(); 
  guitarFlag = false; 
  initalizeLevel = true;

  playManager = new PlayManager();
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

bool Engine::getResetState()
{
	return resetState; 
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
	playManager->free(); 
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
	}
}


void Engine::update()
{
	capTimer.start();

	/*
	For levels:
	create an enum - ie LEVEL1
	Pass through the playManager to determine what enemies are drawn and title screen displayed or not

	*/
	if(initalizeLevel){
		playManager->loadMedia(window, nRenderer);
		initalizeLevel = false;	
	}

	if(inputManager.mainInputs(runState, window.getWindow(), guitarFlag))
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
			//SDL_SetRenderDrawColor( nRenderer, 0, 120, 0, 0);
			//SDL_RenderClear(nRenderer);

			++countedFrames;

			////Collision Events
			//for(int i = 0;i < Entity::entityColList.size();++i) {
			//	Entity* entityA = Entity::entityColList.at(i);

			//	if(entityA == NULL || entityA == NULL) continue;

			//	newPlayer.checkCollision(entityA->getCollider());
			//	
			//	
			//}
		
			//player state is stored as "dead" constantly
			/////////////////////////////////////////////
			//NEED TO DELETE GUITAR Keeps killing player
			//REWORK createGuitar function 
			//USE A COORDINATE MAP system instead 

			/* x
			   x 
			 xxxx0 <- death at position (2,4) no rectangle collisions needed 
			   x  
			   x
			*/ 
			if (playManager->checkPlayerDeath())
			{
				playManager->free();
				delete playManager;

				playManager = new PlayManager();
				playManager->loadMedia(window, nRenderer);

				SDL_Delay(1000);
			}
			else
			{
				playManager->updateLevel(nRenderer, window, guitarFlag, resetState);
			}
			
		}
	}
	else
	{
		runState = false;
		running(runState);
	}

	updateFpsTimer();
}

