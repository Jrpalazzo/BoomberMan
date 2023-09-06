#pragma once
#include "SDL_mixer.h"
#include "bEntity.h"
#include "bTimer.h"
#include "bTexture.h"
#include "bParticle.h"

class Guitar : public Entity
{
	public:
		static const int GUITAR_ANIMATION_FRAMES = 12; 
		static const int TOTAL_PARTICLES = 9;

		Guitar();

		~Guitar();

		void initalizeParticles(SDL_Renderer* nRenderer);

		void setAnimationClips();

		void create(SDL_Renderer*  nRenderer, SDL_Rect& camera);

		void renderGuitar(SDL_Renderer* nRenderer, SDL_Rect& camera);

		void unPauseAnimationTimer();

		void playMusic();
	
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
		//The particles
		Texture note1;
		Texture note2;
		Texture note3;
		Particle* particles[TOTAL_PARTICLES];
		Mix_Music* gMusic;

};


