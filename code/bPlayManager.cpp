#include "bPlayManager.h"

/*
TODO:
Fix bomb so it places directly on top of player, not in front or behind
Set the explosion renderer to play after there is a collison or not with a solid
*/

//Particle count
const int GRID_SIZE = 64;

const int TOTAL_PARTICLES = 9;
const int MAP_TILES = 231;

const int TOTAL_SOLIDS = 88;

const int LEVEL_WIDTH = 1300;
const int LEVEL_HEIGHT = 768;

const Uint8* keys = SDL_GetKeyboardState(NULL);

//Map tile amount 
int Map[MAP_TILES] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
					1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
					1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
					1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
					1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
					1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
					1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
					1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
					1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
					1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

bool guitarFlag = false;
bool explosionFlag = false; 

bool playMusic = false;

int curPlayerX = 0;
int curPlayerY = 0;


//The particles
Particle* particles[TOTAL_PARTICLES];

PlayManager::PlayManager(){
	gMusic = NULL;
    initalized = false;
	hasCollided = false;
	srand(time(NULL)); 
	blocks.reserve(209);
	deathTimer = 200;
}

PlayManager::~PlayManager() { }

void PlayManager::loadMedia(Window nWindow, SDL_Renderer* nRenderer)
{
	//load hud timer
	if( !hudTimerTexture.loadFromFile(nRenderer,"graphics/numbers_strip.png" ) )
	{
		printf( "Failed to load note3 texture!\n" );
	}

	//Load scene texture
	if( !tileTexture.loadFromFile(nRenderer, "graphics/tile1.png" ) )
	{
		printf( "Failed to load window texture!\n" );
	}

	if( !tileTexture2.loadFromFile(nRenderer,"graphics/tile2.png" ) )
	{
		printf( "Failed to load note3 texture!\n" );
	}

	if( !tileTexture3.loadFromFile(nRenderer,"graphics/tile3.png" ) )
	{
		printf( "Failed to load note3 texture!\n" );
	}

	/*
	//Load player surface
	if(!newPlayer.loadFromFile(nRenderer, "graphics/boomer_strip2.png")) {
		printf( "Failed to load entity!\n" );
	}
	*/

	if( !note1.loadFromFile(nRenderer,"graphics/note_1.png" ) )
	{
		printf( "Failed to load note1 texture!\n" );
	}

	if( !note2.loadFromFile(nRenderer,"graphics/note_2.png" ) )
	{
		printf( "Failed to load note2 texture!\n" );
	}

	if( !note3.loadFromFile(nRenderer,"graphics/note_3.png" ) )
	{
		printf( "Failed to load note3 texture!\n" );
	}

	if( !guitar.loadFromFile(nRenderer,"graphics/guitar_strip2.png" ) )
	{
		printf( "Failed to load note3 texture!\n" );
	}

	if( !explosionTexture.loadFromFile(nRenderer,"graphics/explosion_strip2.png" ) )
	{
		printf( "Failed to load note3 texture!\n" );
	}

	if( !enemy1Texture.loadFromFile(nRenderer,"graphics/enemy_1.png" ) )
	{
		printf( "Failed to load note3 texture!\n" );
	}

	gMusic = Mix_LoadMUS("music/bomb_theme.wav");
	if(gMusic == NULL)
	{
		printf("Failed to load music. %s\n", Mix_GetError);
	}

	//Initialize particles
    for( int i = 0; i < TOTAL_PARTICLES; ++i )
    {
		particles[ i ] = new Particle(note1,note2,note3, guitar.getX(), guitar.getY() );
    }

	for(int i = 0; i < 5; ++i){
			explosions.push_back(new Explosion(explosionTexture, guitar.getX(), guitar.getY()));		
	}

	hudTimer = GameText(hudTimerTexture, 128, 16);

	enemies.push_back(new Enemy(enemy1Texture, 128, 128));		
	
	generateMap(nRenderer);

	hudTimer.updateGameTimer(200);

	camera.x = 0;
	camera.y = 0;
	camera.w = nWindow.getWidth();
	camera.h = nWindow.getHeight();

	//std::cout << nWindow.getWidth() << std::endl; 
}

void PlayManager::drawHud(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, 188, 188, 188, 0);
	SDL_Rect rectangle;

	rectangle.x = 0;
	rectangle.y = 0;
	rectangle.w = 1216;
	rectangle.h = 64;

	SDL_RenderFillRect(renderer, &rectangle);

}

void PlayManager::generateMap(SDL_Renderer* nRenderer)
{
	//Randomly add blocks to the map
	int randValue = 0;
	int randBlock = 35;

	if(!initalized)
		for(int i = 0; i <= MAP_TILES; ++i){

			if(i == MAP_TILES)
			{
				break;
			}

			if((i == 20 || i == 21 || i == 39)){
				continue;
			}

			if(Map[i] == 1){
				continue;
			}
			else
			{ 
				randValue = rand()%10;

				if(randValue < 3 && randBlock >= 0)
				{
					Map[i] = 2;
					randBlock --;
				}

			}
			
			initalized = true;
		}

	int x = 0;
	int y = 1;

	int SCREEN_WIDTH = 21;
					
	//int tile = -1;
	int blockCounter = 0;
	int breakBlockCounter = 0;

	for(int i = 0; i <= MAP_TILES; ++i){
		if(Map[i]==2){
			blocks.push_back(new Block(tileTexture2, x*GRID_SIZE, y*GRID_SIZE, 2));		
		}

		if(Map[i] ==1){
			blocks.push_back(new Block(tileTexture3, x*GRID_SIZE, y*GRID_SIZE, 1));
		}

		x++;

		if(x >= SCREEN_WIDTH )
		{
			x = 0;
			y += 1;
		}					
	}
}

void PlayManager::updateLevel(SDL_Renderer* nRenderer, Window nWindow, bool &guitarFlag)
{

	//Clear screen
	//SDL_SetRenderDrawColor( nRenderer, 0, 120, 0, 0);
	//SDL_RenderClear(nRenderer);
	

	drawHud(nRenderer);
	hudTimer.render(nRenderer);

	//Show solid blocks
	for( signed int i = 0; i < blocks.size(); ++i)
	{
		blocks[i]->render(nRenderer, camera); 
		//blocks[i]->drawBlockCollision(nRenderer);
	}

	//pause timer to stop animation 
	//newPlayer.pauseAnimationTimer();

	//newPlayer.playerInput(keys,blocks, guitar.getCollider(), guitarFlag, guitar, explosionFlag);


	//if the player presses z create an instance of the guitar 
	createGuitar(nRenderer, guitarFlag);

	//display the enemies 
	enemies[0]->renderEnemy(nRenderer);

	//render after since the guitar should be below the player
	//newPlayer.renderPlayer(nRenderer, camera); 

	//newPlayer.drawPlayerCollision(nRenderer); 

	//move enemy and check collision 
	enemies[0]->move();
	//enemies[0]->checkCollision();

	//Update screen
	//render camera
	setCamera(nWindow, camera, newPlayer.getX(), newPlayer.getY());

	//SDL_RenderPresent( nRenderer );
}

void PlayManager::createGuitar(SDL_Renderer* nRenderer, bool &guitarFlag)
{
	//guitar.drawGuitarCollision(nRenderer);

	if(guitarFlag == false){
		
		if(explosionFlag == true){

			guitar.setColliderX(0);
			guitar.setColliderY(0);

			int curGuitarX = guitar.getX();
			int curGuitarY = guitar.getY();

			explosions[0]->setX(curGuitarX - (curGuitarX % GRID_SIZE));
			explosions[0]->setY(curGuitarY - (curGuitarY % GRID_SIZE));
			explosions[0]->resetCollision();

			explosions[1]->setX(curGuitarX - (curGuitarX % GRID_SIZE));
			explosions[1]->setY(curGuitarY - (curGuitarY % GRID_SIZE)+GRID_SIZE);
			explosions[1]->resetCollision();

			explosions[2]->setX(curGuitarX - (curGuitarX % GRID_SIZE)+GRID_SIZE);
			explosions[2]->setY(curGuitarY - (curGuitarY % GRID_SIZE));
			explosions[2]->resetCollision();

			explosions[3]->setX(curGuitarX - (curGuitarX % 64)-GRID_SIZE);
			explosions[3]->setY(curGuitarY - (curGuitarY % 64));
			explosions[3]->resetCollision();

			explosions[4]->setX(curGuitarX - (curGuitarX % 64));
			explosions[4]->setY(curGuitarY - (curGuitarY % 64)-GRID_SIZE);
			explosions[4]->resetCollision();

			for(int i = 0; i < blocks.size(); ++i)
			{
				for(int j = 0; j < explosions.size(); ++j )
				{
					if(SDL_HasIntersection(&explosions[j]->getCollider(), &newPlayer.getCollider()))
					{
			
						newPlayer.setX(64);
						newPlayer.setY(128);

					}

					if(SDL_HasIntersection(&explosions[j]->getCollider(), &blocks[i]->getCollider()))
					{
						hasCollided = true; 
						explosions[j]->setCollided(hasCollided);
					
						if(blocks[i]->getBlockType() == 2)
							blocks.erase(blocks.begin()+i);
					}
				
				}

				
			}

			    for(int i = 0; i < explosions.size(); ++i)
				{	
					explosions[i]->renderExplosion(nRenderer, explosionFlag, camera);	
					
			    }
				
		}

		Mix_HaltMusic();
	}
	else 
	{
		guitar.renderGuitar(nRenderer, guitarFlag, camera); 
		
		//Go through particles
		for( int i = 0; i < TOTAL_PARTICLES; ++i )
		{
			//Delete and replace dead particles
			if( particles[ i ]->isDead() )
			{
				delete particles[ i ];

				int posX = guitar.getX();
				int posY = guitar.getY();

				particles[ i ] = new Particle(note1,note2,note3, posX++ , posY++);
			}
		}

		musicManager();

		//Show particles
		for( int i = 0; i < TOTAL_PARTICLES; ++i )
		{
			particles[ i ]->render(nRenderer, camera);
		}
	}


}

void PlayManager::setCamera(Window window, SDL_Rect& camera, int x, int y)
{
	//Center the camera over the player
	camera.x = ( x + 64 / 2 ) - window.getHeight() / 2;
	camera.y = ( y + 64 / 2 ) - window.getHeight() / 2;

	//Keep the camera in bounds
	if( camera.x < 0 )
	{ 
		camera.x = 0;
	}
	if( camera.y < 0 )
	{
		camera.y = 0;
	}
	if( camera.x > LEVEL_WIDTH - camera.w )
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if( camera.y > LEVEL_HEIGHT - camera.h )
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}


}

void PlayManager::musicManager()
{
	if( Mix_PlayingMusic() == 0 )
	{
		//Mix_PlayMusic(gMusic, 0);
	}
}

void PlayManager::free()
{	
	//Show solid blocks
	for( signed int i = 0; i < blocks.size(); ++i)
	{
		blocks.clear();
		//blocks[i]->drawBlockCollision(nRenderer);
	}

	for(int i = 0; i < explosions.size(); ++i){
			explosions.clear();	
	}

	tileTexture.free(); 
	tileTexture2.free();
	tileTexture3.free();

	boomerTexture.free();
	note1.free();
	note2.free();
	note3.free();
	guitar.free();

	Mix_FreeMusic( gMusic );
	gMusic = NULL;
}