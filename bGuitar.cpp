#include "bGuitar.h"

Guitar::Guitar()
{

	animationCounter = 0;
	setAnimationClips(); 
	mCollider.w = Width-4;
	mCollider.h = Height-4;
	X = 64;
	Y = 64; 
	mCollider.x = X;
	mCollider.y = Y;

}

Guitar::~Guitar()
{
}

void Guitar::setAnimationClips()
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

	bSpriteClips[ 9 ].x =  576;
	bSpriteClips[ 9 ].y =   0;
	bSpriteClips[ 9 ].w =  64;
	bSpriteClips[ 9 ].h =  64;
	
	bSpriteClips[ 10 ].x =  640;
	bSpriteClips[ 10 ].y =   0;
	bSpriteClips[ 10 ].w =  64;
	bSpriteClips[ 10 ].h =  64;

	bSpriteClips[ 11 ].x =  704;
	bSpriteClips[ 11 ].y =   0;
	bSpriteClips[ 11 ].w =  64;
	bSpriteClips[ 11 ].h =  64;	
}

void Guitar::renderGuitar(SDL_Renderer* nRenderer, bool &guitarFlag, SDL_Rect& camera)
{
	mCollider.x = X;
	mCollider.y = Y;

	//std::cout << "X " << X << std::endl;
	//std::cout << "Y " << Y << std::endl;

	//Render current frame
	animationTimer = guitarTimer.getTicks()/250; 
	animationTimer = animationTimer%12;
	
	//if(guitarTimer.isPaused())
	//{
	//	//sets to the original frame 
	//	animationTimer = frame-1;
	//}
	
	//std::cout << animationTimer << std::endl;
	SDL_Rect* currentClip = &bSpriteClips[animationTimer];
	
	//renders the spritesheet pointing to guitar
	this->render( nRenderer, X-camera.x, Y-camera.y, currentClip);

	if(guitarFlag == true && !guitarTimer.isStarted())
	{
		guitarTimer.start();
	}
	
	
	if(animationTimer == 11)
	{
		guitarTimer.stop();
	}

	//std::cout << "guitarFlag " << guitarFlag << " animationTimer " << animationTimer << " guitarX " << X << " guitarY " << Y <<std::endl;
}

void Guitar::drawGuitarCollision(SDL_Renderer* nRenderer)
{
	SDL_SetRenderDrawColor(nRenderer, 0,0,0xF,0xF);
	SDL_RenderDrawRect(nRenderer, &mCollider);  
}

void Guitar::unPauseAnimationTimer()
{
	guitarTimer.unpause();
}
		
void Guitar::pauseAnimationTimer()
{
	guitarTimer.pause();
}

