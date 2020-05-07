
#include "bPlayer.h"

Player::Player() 
{ 
	X = 64;
	Y = 128;

	mCollider.x = 64;
	mCollider.y = 64;

	mCollider.w = Width;
	mCollider.h = Height;

    pVelX = 0;
    pVelY = 0;
	
	yPrev = 0;
	xPrev = 0;

    frame = 11; 

	pSpeed = 3;

	inputCounter = 0;

	setAnimationClips(); 

	timerStart = false;

	timer.start();

	direction = NONE;
    //inputTimer.start();

}
 
Player::~Player() {}
/*
void Player::playerInput(const Uint8* keys, std::vector<Block*> blocks, SDL_Rect guitarRect, bool &guitarFlag, Guitar &guitar, bool &explosionFlag)
{

	SDL_PumpEvents();

	resumeInput = inputTimer.getTicks()/250; 
	resumeInput = resumeInput%12;

	if((!inputTimer.isStarted()) && guitarFlag == true){
		
		resumeInput = 0;

		inputTimer.start();
			
		std::cout << "direction " << direction << std::endl;
		std::cout << "playerX " << X << " playerY " << X << " setX " << X - ( X % 64) << " setY " << Y - ( Y % 64) << std::endl; 

		guitar.setX(X - (X % 64));
		guitar.setY(Y - (Y % 64));

		if(direction == UP)
		{
			guitar.setX(X - (X % 64));
			guitar.setY(Y - (Y % 64)+64);

			if(direction == NONE)
			{
				guitar.setY(Y - (Y % 64));

			}
		}
		else if(direction == LEFT)
		{
			guitar.setY(Y - (Y % 64));
			guitar.setX(X - (X % 64)+64);

			if(direction == NONE)
			{
				guitar.setX(X - (X % 64));

			}
		}
		else 
		{
			guitar.setX(X - (X % 64));
			guitar.setY(Y - (Y % 64));
		}
	

	}
	

	if(resumeInput == 11){
		inputTimer.stop();
		
		explosionFlag = true;

		guitarFlag = false;

		//std::cout << "playerX " << X << " playerY " << Y << " guitarX " << guitar.getX() << " guitarY " << guitar.getY() << std::endl; 
	}

	if(keys[SDL_SCANCODE_UP]){
		yPrev = Y;
		Y -= pSpeed;
		mCollider.y = Y; 

		frame = 4;
		unPauseAnimationTimer();

		direction = UP;

		if(checkBlockCollision(mCollider, blocks))
		{
			if(mCollider.x < curBlock.x - 28)
			{
				X -= pSpeed;
				mCollider.x = X; 
			}
			else if(mCollider.x > curBlock.x  + 28)
			{
				X += pSpeed;
				mCollider.x = X; 
			}

			Y = yPrev;
			mCollider.y = Y; 
			direction = NONE;

		}

		if(checkCollision(mCollider, guitarRect))
		{
			if(Y > guitarRect.y)
			{
				Y = yPrev;
				mCollider.y = Y; 
				direction = NONE;

			}

		}

	}

	if(keys[SDL_SCANCODE_DOWN]){
		yPrev = Y;
		Y += pSpeed;
		mCollider.y = Y; 
		frame = 1;
		unPauseAnimationTimer();

		direction = DOWN;

		if(checkBlockCollision(mCollider, blocks))
		{
			if(mCollider.x < curBlock.x -28)
			{
				X -= pSpeed;
				mCollider.x = X; 
			}
			else if(mCollider.x > curBlock.x +28)
			{
				X += pSpeed;
				mCollider.x = X; 
			}

			Y = yPrev;
			mCollider.y = Y; 
			direction = NONE;
		}

		
		if(checkCollision(mCollider, guitarRect))
		{
			if(Y < guitarRect.y)
			{
				Y = yPrev;
				mCollider.y = Y; 
				direction = NONE;

			}

		}
	}

	if(keys[SDL_SCANCODE_LEFT]){
		xPrev = X;
		X -= pSpeed;
		mCollider.x = X;
		frame = 10;
		unPauseAnimationTimer();

		direction = LEFT;

		if(checkBlockCollision(mCollider, blocks))
		{
			if(mCollider.y < curBlock.y -28)
			{
				Y -= pSpeed;
				mCollider.y = Y; 
			}
			else if(mCollider.y > curBlock.y +28)
			{
				Y += pSpeed;
				mCollider.y = Y; 
			}

			X = xPrev;
			mCollider.x = X; 
			direction = NONE;
		}


		if(checkCollision(mCollider, guitarRect))
		{
			if(X > guitarRect.x)
			{
				X = xPrev;
				mCollider.x = X; 
				direction = NONE;

			}

		}

	}
	
	if(keys[SDL_SCANCODE_RIGHT]){
		
		
		xPrev = X;
		X += pSpeed;
		mCollider.x = X;
		frame = 7;
		unPauseAnimationTimer();

		direction = RIGHT;

	
		if(checkBlockCollision(mCollider, blocks))
		{
			if(mCollider.y < curBlock.y -28)
			{
				Y -= pSpeed;
				mCollider.y = Y; 
			}
			else if(mCollider.y > curBlock.y +28)
			{
				Y += pSpeed;
				mCollider.y = Y; 
			}

			X = xPrev;
			mCollider.x = X; 	
			direction = NONE;
		}
	
		if(checkCollision(mCollider, guitarRect))
		{
			if(X < guitarRect.x)
			{
				X = xPrev;
				mCollider.x = X; 
				direction = NONE;

			}

		}

	}
	

	
	//std:: cout << "inputTimer " << resumeInput << std::endl;
	//std::cout << "Player " << " guitarFlag " << guitarFlag<<std::endl;
	//std::cout << "inputCounter " << inputCounter << std::endl;
	//std::cout << "resumeInput " << resumeInput << std::endl;
}
*/

void Player::movePlayer()
{
	
	std::cout << "direction " << direction << std::endl;

	//Move the player left or right
	X += pVelX;
	mCollider.x = X;


	//Move the player up or down
	Y += pVelY;
	mCollider.y = Y;
}


void Player::setPlayerXVel(int x)
{
	pVelX = x;

}

void Player::setPlayerYVel(int y)
{
	pVelY = y;

}

int Player::getPlayerXVel()
{
	return pVelX;
}

int Player::getPlayerYVel()
{
	return pVelY;
}

int Player::getPlayerSpeed()
{
	return pSpeed;
}

void Player::setAnimationClips()
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


bool Player::checkCollision(SDL_Rect a, SDL_Rect b)
{
	if(SDL_HasIntersection(&a, &b))
	{
		curBlock = b;
		return true;
	}	

	return false; 
}

bool Player::checkBlockCollision(SDL_Rect src, std::vector<Block*> blocks)
{
	for(int i = 0; i < blocks.size(); ++i )
	{
		if(checkCollision(src, blocks[i]->getCollider()))
		{
			return true;
		}
	}

	return false; 
}

/*
void Player::renderPlayer(SDL_Renderer* nRenderer, SDL_Rect& camera)
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

	//renders the spritesheet pointing to player 
	this->render( nRenderer, X- camera.x, Y- camera.y, currentClip );
}
*/

void Player::loadPlayerTexture(SDL_Renderer* nRenderer)
{
	if(!this->loadFromFile(nRenderer, "graphics/boomer_strip2.png")) {
		printf( "Failed to load entity!\n" );
	}
}
	
void Player::renderPlayer(SDL_Renderer* nRenderer)
{
	//Render current frame
	Uint32 animationTimer = timer.getTicks()/150; 
	animationTimer = animationTimer%2;
	animationTimer += frame;

	std::cout << animationTimer << std::endl;

	if(timer.isPaused())
	{
		//sets to the original frame 
		animationTimer = frame-1;
	}

	//std::cout << animationTimer << std::endl;
	SDL_Rect* currentClip = &bSpriteClips[animationTimer];

	//renders the spritesheet pointing to player 
	this->render( nRenderer, X, Y, currentClip );
}

void Player::drawPlayerCollision(SDL_Renderer* nRenderer)
{
	SDL_SetRenderDrawColor(nRenderer, 0,0,0,255);
	SDL_RenderDrawRect(nRenderer, &mCollider);  
}

void Player::unPauseAnimationTimer()
{
		timer.unpause();
}

void Player::pauseAnimationTimer()
{
	timer.pause();
}