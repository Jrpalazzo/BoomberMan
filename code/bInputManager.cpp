#include "bInputManager.h"

InputManager::InputManager()
{
	
}

InputManager::~InputManager(){}

bool InputManager::mainInputs(bool runState, Player &player, SDL_Window* window, bool &guitarFlag)
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
			{
				///allocate some memory
				runState = false;
			}
				switch(e.key.keysym.sym)
				{
					//player movment
					case SDLK_UP:
						player.pVelY -= player.pSpeed;
						player.direction = player.Facing::UP;
						player.unPauseAnimationTimer();
						player.frame = 4;
						break;
					case SDLK_DOWN:
						player.pVelY += player.pSpeed;
						player.direction = player.Facing::DOWN;
						player.unPauseAnimationTimer();
						player.frame = 1;
						break;
					case SDLK_RIGHT:
						player.pVelX += player.pSpeed;
						player.direction = player.Facing::RIGHT;
						player.unPauseAnimationTimer();
						player.frame = 7;
						break;
					case SDLK_LEFT:
						player.pVelX -= player.pSpeed;
						player.direction = player.Facing::LEFT;
						player.unPauseAnimationTimer();
						player.frame = 10;
						break;
				
					case SDLK_ESCAPE:
						runState = false;
						break;
					case SDLK_RETURN:
				
						SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
						break;

					/*case SDLK_z:
						guitarFlag = true; 
						break;*/
				}
				break;
		}
		else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
		{
				
				 switch(e.key.keysym.sym)
				{
					//player movment
					case SDLK_UP:
						player.pVelY = 0;
						break;
					case SDLK_DOWN:
						player.pVelY = 0;
						break;
					case SDLK_RIGHT:
						player.pVelX = 0;
				
						break;
					case SDLK_LEFT:
						player.pVelX = 0;
				
						break;
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

