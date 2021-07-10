#include "bEnemy.h"
#include <math.h>

const int Enemy::SPEED = 1.25;

Enemy::Enemy(Texture &text1,int x, int y, int rValue)
{
	X = x;
	Y = y;

	yPrev = 0;
	xPrev = 0;

	mTexture = &text1;
	
	mCollider.x = X;
	mCollider.y = Y;

	mCollider.w = Width-4;
	mCollider.h = Height-4;

	direction = Facing(rand() % 3);	

	setAnimationClips(); 

	//direction = UP;

	//std::cout<<direction<<std::endl;

	timer.start();

	randomValue = rValue;

	state = "alive";
	//std::cout << randomValue << std::endl;
}


Enemy::~Enemy()
{
}

void Enemy::setAnimationClips()
{
	//Set sprite clips
	bSpriteClips[ 0 ].x =   0;
	bSpriteClips[ 0 ].y =   0;
	bSpriteClips[ 0 ].w =  64;
	bSpriteClips[ 0 ].h =  64;

	bSpriteClips[ 1 ].x =  64;
	bSpriteClips[ 1 ].y =   0;
	bSpriteClips[ 1 ].w =  64;
	bSpriteClips[ 1 ].h =  64;

	bSpriteClips[ 2 ].x =  128;
	bSpriteClips[ 2 ].y =   0;
	bSpriteClips[ 2 ].w =  64;
	bSpriteClips[ 2 ].h =  64;

	bSpriteClips[ 3 ].x =  192;
	bSpriteClips[ 3 ].y =   0;
	bSpriteClips[ 3 ].w =  64;
	bSpriteClips[ 3 ].h =  64;

	bSpriteClips[ 4 ].x =  256;
	bSpriteClips[ 4 ].y =   0;
	bSpriteClips[ 4 ].w =  64;
	bSpriteClips[ 4 ].h =  64;

	bSpriteClips[ 5 ].x =  320;
	bSpriteClips[ 5 ].y =   0;
	bSpriteClips[ 5 ].w =  64;
	bSpriteClips[ 5 ].h =  64;

	bSpriteClips[ 6 ].x =  384;
	bSpriteClips[ 6 ].y =   0;
	bSpriteClips[ 6 ].w =  64;
	bSpriteClips[ 6 ].h =  64;

	bSpriteClips[ 7 ].x =  448;
	bSpriteClips[ 7 ].y =   0;
	bSpriteClips[ 7 ].w =  64;
	bSpriteClips[ 7 ].h =  64;

}

void Enemy::renderEnemy(SDL_Renderer* nRenderer, SDL_Rect& camera)
{
	//Render current frame
	Uint32 animationTimer = timer.getTicks()/150; 
	animationTimer = animationTimer%2;
	animationTimer += frame;

	if(timer.isPaused())
	{
		//sets to the original frame 
		animationTimer = frame-1;
	}

	//std::cout << animationTimer << std::endl;
	SDL_Rect* currentClip = &bSpriteClips[animationTimer];

	//renders the spritesheet pointing to enemy 
	mTexture->render(nRenderer, X-camera.x, Y-camera.y, currentClip );
}

void Enemy::setState(std::string s)
{
	state = s;
}

std::string Enemy::getState()
{
	return state;
}

void Enemy::move(std::vector<Block*> blocks)
{
	/*
		use the isFree method from player to check open space
	*/
	//randomValueTimer = timer.getTicks()/250; 
	//randomValueTimer = randomValueTimer%12;

	//if(randomValueTimer == 11)
	//{
	//	//std::cout << "yup" << std::endl;
	//	//randomValue = rand()%3;
	//	//direction = Facing(rand() % 3);
	//}
	switch(direction)
	{
		case 0:
			direction = RIGHT;
			frame = 4;
			X+=SPEED;
			mCollider.x = X;
			if(checkBlockCollision(mCollider, blocks))
			{
				direction = LEFT;
			}
			if(isMovefree(blocks, X+64, Y))
			{
				mCollider.x = X;
				direction = Facing(2 +rand() % 2);
				//randomValue = rand()%3;
					
			}
			break;
		case 1:
			direction = LEFT;
			frame = 6;
			X-=SPEED;
			mCollider.x = X;
			if(checkBlockCollision(mCollider, blocks))
			{
				direction = RIGHT;
			}
			if(isMovefree(blocks, X-64, Y))
			{
					mCollider.x = X;
					direction = Facing(2+ rand() % 2);
					//randomValue = rand()%3;
					
			}
			break;
		case 2:
			direction = UP;
			frame = 2;
			Y-=SPEED;
			mCollider.y = Y;
			if(checkBlockCollision(mCollider, blocks))
			{
				direction = DOWN;
			}
			if(isMovefree(blocks, X, Y-64))
			{
					mCollider.y = Y;
					direction = Facing(rand() % 2);
					//randomValue = rand()%3;
					
			}
			break;
		case 3:
			direction = DOWN;
			frame = 0;
			Y+=SPEED;
			mCollider.y = Y;
			if(checkBlockCollision(mCollider, blocks))
			{
				direction = UP;
			}
			if(isMovefree(blocks, X, Y+64))
			{
				mCollider.y = Y;
				direction = Facing(rand() % 2);
				//randomValue = rand()%3;
					
			}
			break;
		default:
			direction = NONE;
			break;
	}
	

}

bool Enemy::isMovefree(std::vector<Block*> blocks, int x, int y)
{
	for(int i = 0; i < blocks.size(); ++i)
	{
	   if(blocks[i]->getX() == x && blocks[i]->getY() == y)
	   {
			//std::cout<<"blockX " << blocks[i]->getX() << " blockY " << blocks[i]->getY() << " type " << blocks[i]->getBlockType() << std::endl;

			return true;
		   
	   }
	}

	return false;
}

bool Enemy::checkBlockCollision(SDL_Rect src, std::vector<Block*> blocks)
{
	for(int i = 0; i < blocks.size(); ++i)
	{
		if(checkCollision(src, blocks[i]->getCollider()))
		{
			return true;
		}

	}

	return false;
}

bool Enemy::checkCollision(SDL_Rect a, SDL_Rect b)
{
	if(SDL_HasIntersection(&a, &b))
	{   
		return true;
	}	

	return false; 
}


void Enemy::drawEnemyCollision(SDL_Renderer* nRenderer)
{
	SDL_SetRenderDrawColor(nRenderer, 255,0,0,255);
	SDL_RenderDrawRect(nRenderer, &mCollider);  
}

