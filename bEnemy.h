#pragma once
#include "bentity.h"
#include "bBlock.h"
#include "bTimer.h"
#include <time.h>

class Enemy :
	public Entity
{
	public:
		
		static const int 	WALKING_ANIMATION_FRAMES = 8; 

		enum Facing
		{
			RIGHT,
			LEFT,
			UP,
			DOWN,
			NONE
		};


		Enemy(Texture &text1,int x, int y, int rValue);

		~Enemy();

		void setAnimationClips();

		void renderEnemy(SDL_Renderer* nRenderer, SDL_Rect& camera);

		bool isMovefree(std::vector<Block*> blocks, int x, int y);

		void move(std::vector<Block*> blocks);

		bool checkBlockCollision(SDL_Rect src, std::vector<Block*> blocks);

		bool checkCollision(SDL_Rect a, SDL_Rect b);

		void drawEnemyCollision(SDL_Renderer* nRenderer);

		std::string getState();

		void setState(std::string s);

	private:
		SDL_Rect bSpriteClips[ WALKING_ANIMATION_FRAMES ];
		int frame;
		Timer timer;
		Uint32 randomValueTimer;
		Texture *mTexture;
		int randomValue;
		static const int SPEED;
		Facing direction;
		int yPrev;
		int xPrev;
		std::string state;

};

