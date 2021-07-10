#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <stdio.h>

class Game
{
	public:
		Game();

		~Game();

		bool init();

		bool loadMedia();

		void close();

		void clear();

		void update();

		

	private:
		SDL_Renderer* gRenderer;
		SDL_Window* gWindow;

		//Screen dimension constants
		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;
};

#endif 