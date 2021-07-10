#pragma once
#include "bentity.h"
#include "bTimer.h"

class Explosion :
	public Entity
{
	public:
		 

		Explosion(Texture &text1,int x, int y);

		~Explosion();

		void setAnimationClips();

		void renderExplosion(SDL_Renderer* nRenderer, bool &explosionFlag, SDL_Rect& camera); 

		void unPauseAnimationTimer();
		
		void pauseAnimationTimer();

		bool hasCollided();

		void setCollided(bool collision);

		void drawExplosionCollision(SDL_Renderer* nRenderer);

		void resetCollision();
		
		void zeroCollision();

	private:
		static const int EXPLOSION_ANIMATION_FRAMES = 9;
		SDL_Rect bSpriteClips[ EXPLOSION_ANIMATION_FRAMES ];
		Texture *mTexture;
		int frame;
		int pSpeed; 
		Timer timer;
		int inputCounter; 
		Uint32 resumeInput;
		bool collisionFlag; 
};

