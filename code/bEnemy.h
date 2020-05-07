#pragma once
#include "bentity.h"
class Enemy :
	public Entity
{
	public:
	
		Enemy(Texture &text1,int x, int y);

		~Enemy();

		void renderEnemy(SDL_Renderer* nRenderer);

		void move();

		bool checkCollision(SDL_Rect a, SDL_Rect b);

	private:
		Texture *mTexture;
		int randomValue;
		static const int SPEED;
};

