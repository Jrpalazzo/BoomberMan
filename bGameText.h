#ifndef BGAMETEXT_H
#define BGAMETEXT_H

#include "btexture.h"
#include "bTimer.h"
#include <iostream>

class GameText 
{
	public:
		static const int NUMBER_FRAMES = 10; 

		GameText();

		GameText(Texture &text1, int x, int y);

		~GameText();

		void setAnimationClips();

		void renderExplosion(SDL_Renderer* nRenderer, bool &explosionFlag); 

		void unPauseAnimationTimer();
		
		void pauseAnimationTimer();
		
		int updateGameTimer(int timer);

		//Shows the particle
		void render(SDL_Renderer* nRenderer);

		int getX();

		int getY();

	private:
		//Offsets
		int X, Y;
		SDL_Rect bSpriteClips[ NUMBER_FRAMES ];
		Texture *mTexture;
		Uint32 numberChange;
		Timer numberCounter;
		int gameTimer; 
};
#endif
