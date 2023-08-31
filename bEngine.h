#ifndef BENGINE_H
#define BENGINE_H

#include <stdio.h>
#include <iostream>
#include "bEntity.h"
#include "bTexture.h"
#include "bTimer.h"
#include "bWindow.h"
#include "bBlock.h"
#include "bPlayManager.h"
#include "bInputManager.h"
#include "bCollisionManager.h"
#include "bPlayer.h"

class Engine 
{
	public:
		Engine();

		~Engine();

		void update();

		void initFpsTimer();

		bool initSDL();

		void initWindow();

		void closeSDL();

		bool running(bool & quit);	

		bool getRunState();

		bool getResetState();

		void updateFpsTimer();

	private:
		//The frames per second timer
		Timer fpsTimer;

		//The frames per second cap timer
		Timer capTimer;

		//Start counting frames per second
		int countedFrames;

		static const int SCREEN_FPS = 60;
		static const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

		SDL_Renderer* nRenderer; 

		PlayManager* playManager; 

		InputManager inputManager; 

		Player newPlayer;

		Window window; 

		bool initalizeLevel;

		bool resetState;

		bool gameOverState;

		//Main loop flag
		bool runState;

		//Guitar flag
		bool guitarFlag; 
};
#endif 
