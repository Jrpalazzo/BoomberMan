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

	gMusic = Mix_LoadMUS("music/bomb_theme.wav");
	if (gMusic == NULL)
	{
		printf("Failed to load music. %s\n", Mix_GetError);
	}
}

Guitar::~Guitar()
{
	note1.free();
	note2.free();
	note3.free();

	Mix_FreeMusic(gMusic);
	gMusic = NULL;

}

void Guitar::create(SDL_Renderer* nRenderer, SDL_Rect& camera)
{
	drawGuitarCollision(nRenderer);

	/*
	if(explosionFlag == true){

		guitar.setColliderX(0);
		guitar.setColliderY(0);

		int curGuitarX = guitar.getX();
		int curGuitarY = guitar.getY();

		createExplosions(curGuitarX, curGuitarY);

		for(int i = 0; i < blocks.size(); ++i)
		{
			for(int j = 0; j < explosions.size(); ++j )
			{
				try
				{
					if (SDL_HasIntersection(&explosions[j]->getCollider(), &newPlayer.getCollider()))
					{
						newPlayer.free();
						newPlayer.setState("dead");
						break;
					}
					else
					{
						for (int z = 0; z < enemyCount; z++)
						{
							if (SDL_HasIntersection(&explosions[j]->getCollider(), &enemies[z]->getCollider()))
							{

								enemies.erase(enemies.begin() + z);

							}
						}
					}

					if (SDL_HasIntersection(&explosions[j]->getCollider(), &blocks[i]->getCollider()))
					{
						hasCollided = true;
						explosions[j]->setCollided(hasCollided);

						if (blocks[i]->getBlockType() == 2)
							blocks.erase(blocks.begin() + i);
					}
				}
				catch (std::exception& e)
				{
					std::cout << e.what() << '\n';
				}
			}


		}

		for(int i = 0; i < explosions.size(); ++i)
		{
			explosions[i]->renderExplosion(nRenderer, explosionFlag, camera);
			explosions[i]->setX(0);
			explosions[i]->setY(0);
		}

		//set the guitar to the origin for the next keypress

	}
	Mix_HaltMusic();
	*/

	renderGuitar(nRenderer, camera);

	//Go through particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i)
	{
		//Delete and replace dead particles
		if (particles[i]->isDead())
		{
			delete particles[i];

			particles[i] = new Particle(note1, note2, note3, X++, Y++);
		}
	}

	playMusic();

	//Show particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i)
	{
		particles[i]->render(nRenderer, camera);
	}

}

void Guitar::initalizeParticles(SDL_Renderer* nRenderer)
{
	if (!note1.loadFromFile(nRenderer, "graphics/note_1.png"))
	{
		printf("Failed to load note1 texture!\n");
	}

	if (!note2.loadFromFile(nRenderer, "graphics/note_2.png"))
	{
		printf("Failed to load note2 texture!\n");
	}

	if (!note3.loadFromFile(nRenderer, "graphics/note_3.png"))
	{
		printf("Failed to load note3 texture!\n");
	}

	//Initialize particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i)
	{
		particles[i] = new Particle(note1, note2, note3, mCollider.x, mCollider.y);
	}

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

void Guitar::renderGuitar(SDL_Renderer* nRenderer, SDL_Rect& camera)
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

	if(!guitarTimer.isStarted())
	{
		guitarTimer.start();
	}
	
	
	if(animationTimer == 11)
	{
		guitarTimer.stop();
	}

	//std::cout << "guitarFlag " << guitarFlag << " animationTimer " << animationTimer << " guitarX " << X << " guitarY " << Y <<std::endl;
}

void Guitar::playMusic()
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(gMusic, 0);
	}
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

