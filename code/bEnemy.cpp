#include "bEnemy.h"
#include <math.h>

const int Enemy::SPEED = 3;

Enemy::Enemy(Texture &text1,int x, int y)
{
	X = x;
	Y = y;

	mTexture = &text1;

	mCollider.w = Width;
	mCollider.h = Height;
	randomValue = rand() % 4;
}


Enemy::~Enemy()
{
}

void Enemy::renderEnemy(SDL_Renderer* nRenderer)
{

	//renders the spritesheet pointing to player 
	mTexture->render(nRenderer, X, Y);
}

void Enemy::move()
{
	switch(randomValue)
	{
		case 0:
			X-=SPEED;
			break;
		case 1:
			Y+=SPEED;
			break;
		case 2:
			Y-=SPEED;
			break;
		case 3:
			Y+=SPEED;
			break;
		default:
			break;
	}

}

bool Enemy::checkCollision(SDL_Rect a, SDL_Rect b)
{
	if(SDL_HasIntersection(&a, &b))
	{
		return true;
	}	

	return false; 
}
