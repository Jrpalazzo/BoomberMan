
#include "bPlayer.h"

Player::Player() 
{ 
	yPrev = 0;
	xPrev = 0;

	nCollider.w = Width;
	nCollider.h = Height;

	mCollider.x = X;
	mCollider.y = Y;

	mCollider.w = Width;
	mCollider.h = Height;
	
    frame = 11; 

	timer.start();

	pSpeed =3;

	inputCounter = 0;

	setAnimationClips(); 

	direction = NONE;

	collided = false;
}
 
Player::~Player() {}


void Player::playerInput(const Uint8* keys, std::vector<Block*> blocks, std::vector<Enemy*> enemies,
	SDL_Rect guitarRect, bool &guitarFlag, Guitar &guitar, bool &explosionFlag, SDL_Rect& camera)
{
	//int xPrev, yPrev;

	SDL_PumpEvents();

	resumeInput = inputTimer.getTicks()/250; 
	resumeInput = resumeInput%12;

	int curentBlockType;

	if((!inputTimer.isStarted()) && guitarFlag == true){
		
		resumeInput = 0;

		inputTimer.start();
			
		//std::cout << "direction " << direction << std::endl;
		//std::cout << "playerX " << X << " playerY " << X << " setX " << X - ( X % 64) << " setY " << Y - ( Y % 64) << std::endl; 

		guitar.setX(X);
		guitar.setY(Y);

		if(direction == UP)
	    {
			guitar.setX(X - (X % 64));
		
			guitar.setY(Y - (Y % 64)+64);

			if(direction == NONE){
				guitar.setY(Y - (Y % 64));
			}
			
		}
		else if(direction == DOWN)
		{
			guitar.setX(X - (X % 64));
			guitar.setY(Y - (Y % 64));

			if(direction == NONE){
				guitar.setY(Y - (Y % 64)-64);
			}
		}
		else if(direction == RIGHT)
		{

			guitar.setX(X - (X % 64));
			guitar.setY(Y - (Y % 64));

			if(direction == NONE){
				guitar.setX(X - (X % 64)+64);
			}
		}
		else if(direction == LEFT)
		{
			guitar.setX(X - (X % 64));
			guitar.setY(Y - (Y % 64));

			if(direction == NONE){
				guitar.setX(X - (X % 64)-64);
			}
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

			if(checkBlockCollision(mCollider, blocks, curentBlockType))
			{

				if((mCollider.x < curBlock.x -40) && curentBlockType == 3 && !isMovefree(blocks, curBlock.x-64, curBlock.y))
				{
					X -= 1;
					mCollider.x = X;
					
				}
				else if((mCollider.x > curBlock.x +40) && curentBlockType == 3 && !isMovefree(blocks, curBlock.x+64, curBlock.y))
				{
					X += 1;;
					mCollider.x = X;
					
				}
				else
				{
					Y = yPrev;
					mCollider.y = Y; 
					direction = NONE;
				}


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

			for(int i = 0; i < enemies.size(); ++i)
			{
				if(checkCollision(mCollider, enemies[i]->getCollider()))
				{
					state = "dead";
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

			if(checkBlockCollision(mCollider, blocks, curentBlockType))
			{
				//std::cout<<curentBlockType<<std::endl;

				if((mCollider.x < curBlock.x -40) && curentBlockType == 3 && !isMovefree(blocks, curBlock.x-64, curBlock.y))
				{
					X -= 1;
					mCollider.x = X;
				
				}
				else if((mCollider.x > curBlock.x +40) && curentBlockType == 3 && !isMovefree(blocks, curBlock.x+64, curBlock.y))
				{
					
					X += 1;
					mCollider.x = X;
					
				}
				else
				{
					Y = yPrev;
					mCollider.y = Y;
					direction = NONE;
				}
				
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
			for(int i = 0; i < enemies.size(); ++i)
			{
				if(checkCollision(mCollider, enemies[i]->getCollider()))
				{
					state = "dead";
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

			if(checkBlockCollision(mCollider, blocks, curentBlockType))
			{
				if((mCollider.y < curBlock.y -40) && curentBlockType == 3 && !isMovefree(blocks, curBlock.x, curBlock.y-64))
				{
					
					Y -= 1;
					mCollider.y = Y; 
				
					
				}
				else if((mCollider.y > curBlock.y +40) && curentBlockType == 3 && !isMovefree(blocks, curBlock.x, curBlock.y+64))
				{
					
					Y += 1;
					mCollider.y = Y; 
				
				}
				else
				{
					X = xPrev;
					mCollider.x = X; 	
					direction = NONE;
				}
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
			for(int i = 0; i < enemies.size(); ++i)
			{
				if(checkCollision(mCollider, enemies[i]->getCollider()))
				{
					state = "dead";
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

			if(checkBlockCollision(mCollider, blocks, curentBlockType))
			{
				
				if((mCollider.y < curBlock.y -40) && curentBlockType == 3 && !isMovefree(blocks, curBlock.x, curBlock.y-64))
				{
					Y -= 1;
					mCollider.y = Y; 
					
					
				}
				else if((mCollider.y > curBlock.y +40) && curentBlockType == 3 && !isMovefree(blocks, curBlock.x, curBlock.y+64))
				{
					
					Y += 1;
					mCollider.y = Y; 
				
				}
				else
				{
					X = xPrev;
					mCollider.x = X; 	
					direction = NONE;
				}
				
			}

			
			
				
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
			for(int i = 0; i < enemies.size(); ++i)
			{
				if(checkCollision(mCollider, enemies[i]->getCollider()))
				{
					state = "dead";
				}

			}

		

	//std:: cout << "inputTimer " << resumeInput << std::endl;
	//std::cout << "Player " << " guitarFlag " << guitarFlag<<std::endl;
	//std::cout << "inputCounter " << inputCounter << std::endl;
	//std::cout << "resumeInput " << resumeInput << std::endl;
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


void Player::unPauseAnimationTimer()
{
	timer.unpause();
}
		
void Player::pauseAnimationTimer()
{
	timer.pause();
}

std::string Player::getState()
{
	return state;
}

void Player::setState(std::string s)
{
	state = s;
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

bool Player::checkBlockCollision(SDL_Rect src, std::vector<Block*> blocks, int & curentBlockType)
{
	for(int i = 0; i < blocks.size(); ++i)
	{
		if(checkCollision(mCollider, blocks[i]->getCollider()))
		{
			curentBlockType = blocks[i]->getBlockType();

			return true;
		}

	}

	return false;
}

bool Player::isMovefree(std::vector<Block*> blocks, int x, int y)
{
	for(int i = 0; i < blocks.size(); ++i)
	{
	   if(blocks[i]->getX() == x && blocks[i]->getY() == y)
	   {
		   if(blocks[i]->getBlockType() == 2)
		   {
			   //std::cout<<"blockX " << blocks[i]->getX() << " blockY " << blocks[i]->getY() << " type " << blocks[i]->getBlockType() << std::endl;

			   return true;
		   }
	   }
	}

	return false;

}

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
	this->render( nRenderer, X-camera.x, Y-camera.y, currentClip );

}


void Player::drawPlayerCollision(SDL_Renderer* nRenderer)
{
	SDL_SetRenderDrawColor(nRenderer, 255,0,0,255);
	SDL_RenderDrawRect(nRenderer, &mCollider);  
}

