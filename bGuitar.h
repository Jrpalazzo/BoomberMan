#pragma once
#include "SDL_mixer.h"
#include "bEntity.h"
#include "bTimer.h"
#include "bTexture.h"

class Guitar : public Entity
{
	public:
		static const int GUITAR_ANIMATION_FRAMES = 12; 

		Guitar();

		~Guitar();

		void setAnimationClips();

		void renderGuitar(SDL_Renderer* nRenderer, bool &guitarFlag, SDL_Rect& camera);

		void unPauseAnimationTimer();
		
		void pauseAnimationTimer();

		void drawGuitarCollision(SDL_Renderer* nRenderer);

	private:
		int frame;
		SDL_Rect bSpriteClips[ GUITAR_ANIMATION_FRAMES ];
		Timer guitarTimer; 
		int animationCounter; 
		Uint32 animationTimer;
		bool stopTimer; 
		//Type of particle
		Texture *mTexture;
};


