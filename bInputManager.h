#ifndef BINPUTMANAGER_h
#define BINPUTMANAGER_h

#include <SDL.h>
#include "bPlayer.h"
#include "bWindow.h"

class InputManager 
{
	public:
		InputManager();

		~InputManager();

		bool mainInputs(bool runState, SDL_Window* window, bool &guitarFlag);

	private:
		//Event handler
		SDL_Event e;
};
#endif 