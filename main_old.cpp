#include "bWindow.h"
#include "bTexture.h"
#include <iostream>
#include <stdio.h>
#include <fstream>

//Start up SDL and create the window
bool init();

//Free media and shut down SDL
void close();

//Loads media
bool loadMedia();

//foreground textures
bTexture backgroundTexture;
bTexture selectorTexture;
bTexture tileTexture;
bTexture tileTexture2;
bTexture boomerTexture;

const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

/*
 TO DO:
 FIX-high cpu usage. 


*/

//The application time based timer
class LTimer
{
    public:
		//Initializes variables
		LTimer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

    private:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
};

LTimer::LTimer()
{
    //Initialize the variables
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;
}

void LTimer::start()
{
    //Start the timer
    mStarted = true;

    //Unpause the timer
    mPaused = false;

    //Get the current clock time
    mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void LTimer::stop()
{
    //Stop the timer
    mStarted = false;

    //Unpause the timer
    mPaused = false;

	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void LTimer::pause()
{
    //If the timer is running and isn't already paused
    if( mStarted && !mPaused )
    {
        //Pause the timer
        mPaused = true;

        //Calculate the paused ticks
        mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
    }
}

void LTimer::unpause()
{
    //If the timer is running and paused
    if( mStarted && mPaused )
    {
        //Unpause the timer
        mPaused = false;

        //Reset the starting ticks
        mStartTicks = SDL_GetTicks() - mPausedTicks;

        //Reset the paused ticks
        mPausedTicks = 0;
    }
}

Uint32 LTimer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

    //If the timer is running
    if( mStarted )
    {
        //If the timer is paused
        if( mPaused )
        {
            //Return the number of ticks when the timer was paused
            time = mPausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - mStartTicks;
        }
    }

    return time;
}

bool LTimer::isStarted()
{
	//Timer is running and paused or unpaused
    return mStarted;
}

bool LTimer::isPaused()
{
	//Timer is running and paused
    return mPaused && mStarted;
}

//Pass the nWindow as reference to change window size
bool init(bWindow& nWindow, SDL_Renderer*& nRenderer)
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
		if( !nWindow.init() )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			nRenderer = nWindow.createRenderer();
		
			if( nRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
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
					success = false;
				}
			}
		}
	}

	return success;
}


bool loadMedia(bTexture& texture, SDL_Renderer*& nRenderer)
{
	
	//Loading success flag
	bool success = true;

	//Load Title Screen
	/*
	//Load scene texture
	if( !backgroundTexture.loadFromFile(nRenderer, "graphics/boomer_title.png" ) )
	{
		printf( "Failed to load window texture!\n" );
		success = false;
	}

	//Load scene texture
	if( !selectorTexture.loadFromFile(nRenderer, "graphics/selector.png" ) )
	{
		printf( "Failed to load window texture!\n" );
		success = false;
	}
	*/

	//Load scene texture
	if( !tileTexture.loadFromFile(nRenderer, "graphics/tile1.png" ) )
	{
		printf( "Failed to load window texture!\n" );
		success = false;
	}

	//Load scene texture
	if( !boomerTexture.loadFromFile(nRenderer, "graphics/boomer_1.png" ) )
	{
		printf( "Failed to load window texture!\n" );
		success = false;
	}

	/*
	//Load scene texture
	if( !tileTexture2.loadFromFile(nRenderer, "graphics/tile2.png" ) )
	{
		printf( "Failed to load window texture!\n" );
		success = false;
	}
	*/

	return success;
}

void close(bWindow& nWindow, SDL_Renderer*& nRenderer)
{

	//Destroy window	
	SDL_DestroyRenderer( nRenderer );
	nWindow.free();

	SDL_Quit();
}

int main( int argc, char* args[] )
{
	auto time = SDL_GetTicks();

	SDL_Renderer* nRenderer = NULL;

	bWindow nWindow;
	bTexture nTexture; 
	
	//Start up SDL and create window
	if( !init(nWindow,nRenderer) )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		std::cout << "window_width " << nWindow.getWidth() << std::endl;
		std::cout << "window_height " << nWindow.getHeight() << std::endl;

		std::cout << "background_width " << nTexture.getWidth() << std::endl;
		std::cout << "background_height " << nTexture.getHeight() << std::endl;

		//Load media
		if( !loadMedia(nTexture,nRenderer) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The frames per second timer
			LTimer fpsTimer;

			//The frames per second cap timer
			LTimer capTimer;

			//Start counting frames per second
			int countedFrames = 0;
			fpsTimer.start();

			//While application is running
			while( !quit )
			{
				//Start cap timer
				capTimer.start();

				//Handle events on queue
				//Use SDL_WaitEvent to block events?? 
				while( SDL_PollEvent( &e ) != 0 )
				{
				
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					switch(e.type)
					{
						case SDL_QUIT:
							quit = true;
						case SDL_KEYDOWN:
							switch(e.key.keysym.sym)
							{
								case SDLK_ESCAPE:
									quit = true;
									break;

							}
							break;
					}
					//Handle window events
					nWindow.handleEvent(nRenderer, e );


				}

				//Calculate and correct fps
				float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
				if( avgFPS > 2000000 )
				{
					avgFPS = 0;
				}

				//Only draw when not minimized
				if( !nWindow.isMinimized() )
				{
					//Clear screen

					SDL_SetRenderDrawColor( nRenderer, 0xFF,0xFF,0xFF,0xFF );
					SDL_RenderClear( nRenderer );

					//Load title screen and selector
					/*
					backgroundTexture.render(nRenderer, ( nWindow.getWidth() - backgroundTexture.getWidth() ) / 2, 
						( nWindow.getHeight() - backgroundTexture.getHeight() ) / 2 );

						
					selectorTexture.render(nRenderer, (( nWindow.getWidth() - selectorTexture.getWidth() ) / 2)-300, 
						(( nWindow.getHeight() - selectorTexture.getHeight() ) / 2)+242 );
					*/
					
					
					
					int map[220] = {
									1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
									1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
									1,0,0,0,0,0,1,1,1,0,0,1,0,1,0,1,0,1,0,1,
									1,0,0,0,0,0,1,1,1,0,0,1,0,1,0,1,0,1,0,1,
									1,0,0,0,0,0,1,1,1,0,0,1,0,1,0,1,0,1,0,1,
									1,0,0,0,0,0,1,1,1,0,0,1,0,1,0,1,0,1,0,1,
									1,0,0,0,0,0,1,1,1,0,0,1,0,1,0,1,0,1,0,1,
									1,0,0,0,0,0,1,1,1,0,0,1,0,1,0,1,0,1,0,1,
									1,0,0,0,0,0,1,1,1,0,0,1,0,1,0,1,0,1,0,1,
									1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
									1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
					              };
					

					//Open the map
                    //std::ifstream map( "map.txt" );

					int x = 0;
					int y = 0;

					int SCREEN_WIDTH = 20;
					
					//int tile = -1;

					for(int i = 0; i <= 220; ++i){
							if(map[i]> 0){
							
								tileTexture.render(nRenderer, x*64, y*64);
								//std::cout<< x << ',' << y << std::endl;	
								
							}

							x++;

							if(x >= SCREEN_WIDTH )
							{
								x = 0;
								y += 1;
							}

							
					}
					
					/*
					for(int i = 0; i <= 220; ++i){
							map >> tile;
							if(tile> 0 && ( tile < 220 ) ){
							
								tileTexture.render(nRenderer, x*64, y*64);
								//std::cout<< x << ',' << y << std::endl;	
								
							}

							if(x >= SCREEN_WIDTH)
							{
								x = 0;
								y += 1;
							}

							x++;
					}
					*/
					boomerTexture.render(nRenderer, 64, 64);
					//Update screen
					SDL_RenderPresent( nRenderer );
					
				}

				++countedFrames;

				//If frame finished early
				int frameTicks = capTimer.getTicks();
				if( frameTicks < SCREEN_TICK_PER_FRAME )
				{
					//Wait remaining time
					SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
				}
			 
		    }
		}	
	}

	//Free resources and close SDL
	close(nWindow, nRenderer);

	
	return 0;
}