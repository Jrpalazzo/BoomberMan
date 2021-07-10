#include "bInputManager.h"

InputManager::InputManager()
{
	
}

InputManager::~InputManager(){}

bool InputManager::mainInputs(bool runState, SDL_Window* window, bool &guitarFlag)
{

	 while( SDL_PollEvent( &e ) != 0 )
	 {
				
		//User requests quit
		if( e.type == SDL_QUIT )
		{
			///allocate some memory
			runState = false;
		}

		if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
		{
	
			if( e.type == SDL_QUIT )
				runState = false;
				
				switch(e.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						runState = false;
						break;
					case SDLK_RETURN:
				
						SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
						break;

				}
				break;
					
		}
		else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
		{
				
				 switch(e.key.keysym.sym)
				{
					//player place guitar
					case SDLK_z:
						guitarFlag = true; 
						break;
				}
				break;
		
		}
	
	
	}

	return runState; 

}

