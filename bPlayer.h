#pragma once 
#include "bEntity.h"
#include "bTimer.h"
#include "bGuitar.h"
#include "bEnemy.h"
#include "bBlock.h"
#include <iostream>

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

		void playerInput(const Uint8* keys, std::vector<Block*> blocks, std::vector<Enemy*> enemies,
			SDL_Rect guitarRect, bool &guitarFlag, Guitar &guitar, bool &explosionFlag, SDL_Rect&);

		bool checkCollision(SDL_Rect a, SDL_Rect b);

		bool checkBlockCollision(SDL_Rect src, std::vector<Block*> blocks, int &curentBlockType);

		bool isMovefree(std::vector<Block*> blocks, int x, int y);

		void unPauseAnimationTimer();
		
		void pauseAnimationTimer();

	    void setAnimationClips();

		void renderPlayer(SDL_Renderer* nRenderer, SDL_Rect&);

		void drawPlayerCollision(SDL_Renderer* nRenderer);

		int getPlayerSpeed();

		std::string getState();
		void setState(std::string s);

	private:
		int yPrev;
		int xPrev;

		int pSpeed;

		Texture *mTexture;

		SDL_Rect bSpriteClips[ WALKING_ANIMATION_FRAMES ];
		int frame;
		Timer timer;
		Timer inputTimer; 

		int inputCounter; 
		Uint32 resumeInput;
		bool timerStart;

		bool collided;
		
		SDL_Rect nCollider; 

		std::string state;

		//bool collision;
		Facing direction;

	
};
