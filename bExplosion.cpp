#include "bExplosion.h"

//const int Explosion::EXPLOSION_ANIMATION_FRAMES;

Explosion::Explosion(Texture &text1, int x, int y)
{
	X = x;
	Y = y;

	mTexture = &text1;

	mCollider.w = Width-8;
	mCollider.h = Height-8;

	setAnimationClips(); 

	timer.start();
}


Explosion::~Explosion()
{
}

void Explosion::setAnimationClips()
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

	bSpriteClips[ 8 ].x =  512;
	bSpriteClips[ 8 ].y =   0;
	bSpriteClips[ 8 ].w =  64;
	bSpriteClips[ 8 ].h =  64;

}

void Explosion::renderExplosion(SDL_Renderer* nRenderer, bool &explosionFlag, SDL_Rect& camera)
{

	//mCollider.x = X;
	//mCollider.y = Y;

	if(!collisionFlag){
		//Render current frame
		Uint32 animationTimer = timer.getTicks()/150; 
		animationTimer = animationTimer%8;

		std::cout << animationTimer << std::endl;
		SDL_Rect* currentClip = &bSpriteClips[animationTimer];

		//renders the spritesheet pointing to player 
		mTexture->render(nRenderer, X-camera.x, Y-camera.y, currentClip);

		if(animationTimer == 3)
		{
			explosionFlag = false;
			animationTimer = 0;
			mCollider.x = 0;
			mCollider.y = 0;
		}

	}

	//change the collision to match the current guitar location
	
	//std::cout<< "xCollider " << mCollider.x << std::endl;
	//std::cout<< "yCollider " << mCollider.y << std::endl;

	collisionFlag = false;

	/*
	SDL_Rect* currentClip = &bSpriteClips[0];

	mTexture->render(nRenderer, X, Y, currentClip);
	explosionFlag = false;
	*/

	//std::cout << "animationTimer " << animationTimer << std::endl; 
}

void Explosion::drawExplosionCollision(SDL_Renderer* nRenderer)
{
	SDL_SetRenderDrawColor(nRenderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(nRenderer, &mCollider);  
}

void Explosion::unPauseAnimationTimer()
{
		timer.unpause();
}

void Explosion::pauseAnimationTimer()
{
		timer.pause();
}

bool Explosion::hasCollided()
{
	return collisionFlag;
}

void Explosion::setCollided(bool collision)
{
	collisionFlag = collision; 
}

void Explosion::resetCollision()
{
	mCollider.x = X;
	mCollider.y = Y;

}