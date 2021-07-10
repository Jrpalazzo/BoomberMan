#include "bGameText.h"

GameText::GameText(){}

GameText::GameText(Texture &text1, int x, int y)
{
	X = x;
	Y = y;

	mTexture = &text1;

	setAnimationClips(); 

	numberCounter.start();

	gameTimer = 0;

}


GameText::~GameText()
{

}

void GameText::setAnimationClips()
{
	//Set sprite clips
	bSpriteClips[ 0 ].x =  0;
	bSpriteClips[ 0 ].y =  0;
	bSpriteClips[ 0 ].w =  32;
	bSpriteClips[ 0 ].h =  32;

	bSpriteClips[ 1 ].x =  32;
	bSpriteClips[ 1 ].y =  0;
	bSpriteClips[ 1 ].w =  32;
	bSpriteClips[ 1 ].h =  32;

	bSpriteClips[ 2 ].x =  64;
	bSpriteClips[ 2 ].y =  0;
	bSpriteClips[ 2 ].w =  32;
	bSpriteClips[ 2 ].h =  32;

	bSpriteClips[ 3 ].x =  96;
	bSpriteClips[ 3 ].y =  0;
	bSpriteClips[ 3 ].w =  32;
	bSpriteClips[ 3 ].h =  32;

	bSpriteClips[ 4 ].x = 128;
	bSpriteClips[ 4 ].y =  0;
	bSpriteClips[ 4 ].w =  32;
	bSpriteClips[ 4 ].h =  32;

	bSpriteClips[ 5 ].x = 160;
	bSpriteClips[ 5 ].y =  0;
	bSpriteClips[ 5 ].w =  32;
	bSpriteClips[ 5 ].h =  32;

	bSpriteClips[ 6 ].x = 192;
	bSpriteClips[ 6 ].y =  0;
	bSpriteClips[ 6 ].w =  32;
	bSpriteClips[ 6 ].h =  32;

	bSpriteClips[ 7 ].x = 224;
	bSpriteClips[ 7 ].y =  0;
	bSpriteClips[ 7 ].w =  32;
	bSpriteClips[ 7 ].h =  32;

	bSpriteClips[ 8 ].x = 256;
	bSpriteClips[ 8 ].y =  0;
	bSpriteClips[ 8 ].w =  32;
	bSpriteClips[ 8 ].h =  32;

	bSpriteClips[ 9 ].x = 288;
	bSpriteClips[ 9 ].y =  0;
	bSpriteClips[ 9 ].w =  32;
	bSpriteClips[ 9 ].h =  32;

}

int GameText::getX()
{
	return X;
}

int GameText::getY()
{
	return Y;
}

void GameText::render(SDL_Renderer* nRenderer)
{
	
	Uint32 numberChange = numberCounter.getTicks()/1000; 
	numberChange = numberChange%200;

	//std::cout << numberChange << std::endl;
	//std::cout << "full time " << (gameTimer-numberChange) << std:: endl;
	//std::cout << "hundreds " << (gameTimer-numberChange)%10 << std:: endl;
	//std::cout << "tens" << ((gameTimer-numberChange)%100)/10 << std:: endl;
	//std::cout << "ones" << (gameTimer-numberChange)/100 << std:: endl;

	SDL_Rect* currentClip = &bSpriteClips[(gameTimer-numberChange)%10];
	SDL_Rect* currentClip2 = &bSpriteClips[((gameTimer-numberChange)%100)/10];
	SDL_Rect* currentClip3 = &bSpriteClips[(gameTimer-numberChange)/100];

	mTexture->render(nRenderer, X, Y, currentClip);
	mTexture->render(nRenderer, X-32, Y, currentClip2);
	mTexture->render(nRenderer, X-64, Y, currentClip3);

	if(numberChange == 200)
	{
	  updateGameTimer(0);
	}
}

int GameText::updateGameTimer(int timer)
{
	gameTimer = timer;

	return gameTimer;
}