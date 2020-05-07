#pragma once
#include "bEntity.h"
#include "bTimer.h"
#include "bGuitar.h"
#include "bBlock.h"
#include <vector>

class Player : public Entity
{
    public:

		static const int 	WALKING_ANIMATION_FRAMES = 12; 
		
		enum Facing
		{
			RIGHT,
			LEFT,
			UP,
			DOWN,
			NONE
		};

		Player();
 
        ~Player();

		//void playerInput(const Uint8* keys, std::vector<Block*> blocks, SDL_Rect guitarRect, bool &guitarFlag, Guitar &guitar, bool &explosionFlag);

	    void setAnimationClips();

		void loadPlayerTexture(SDL_Renderer* nRenderer);

		//void renderPlayer(SDL_Renderer* nRenderer, SDL_Rect& camera); 
		void renderPlayer(SDL_Renderer* nRenderer);

		void unPauseAnimationTimer();
		
		void pauseAnimationTimer();

		bool checkCollision(SDL_Rect src, SDL_Rect dest); 

		bool checkBlockCollision(SDL_Rect src, std::vector<Block*> blocks);

		void drawPlayerCollision(SDL_Renderer* nRenderer);

		void movePlayer();

		int getPlayerSpeed();

		void setPlayerXVel(int x);

		void setPlayerYVel(int y);

		int getPlayerXVel();

		int getPlayerYVel();

	private:
		int pVelX;
		int pVelY;

		int yPrev;
		int xPrev;

		int pSpeed;

		SDL_Rect bSpriteClips[ WALKING_ANIMATION_FRAMES ];
		int frame;
		Timer timer;
		Timer inputTimer; 

		int inputCounter; 
		Uint32 resumeInput;
		bool timerStart;

		SDL_Rect curBlock;
		//bool collision;
		Facing direction;

		friend class InputManager;
	
};
