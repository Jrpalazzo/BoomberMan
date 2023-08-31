#ifndef BPLAYMANAGER_h
#define BPLAYMANAGER_h

#include <SDL.h>
#include <utility>
#include <algorithm>    // std::random_shuffle
#include "bWindow.h"
#include "bTexture.h"
#include "bPlayer.h"
#include "bParticle.h"
#include "bGuitar.h"
#include "bInputManager.h"
#include "bExplosion.h"
#include "SDL_mixer.h"
#include "bBlock.h"
#include <iostream>
#include <ctime>
#include <vector>
#include "bEnemy.h"
#include "bGameText.h"

class PlayManager 
{
	public:
		PlayManager();

		~PlayManager();

		static std::vector<Entity*> entityColList;

		void loadMedia(Window nWindow, SDL_Renderer* nRenderer);

		void updateLevel(SDL_Renderer* nRenderer, Window nWindow, bool &guitarFlag, bool &resetState);

		void generateMap(SDL_Renderer* nRenderer);

		void free(); 

		void musicManager(); 

		void drawHud(SDL_Renderer* nRenderer);

		void createGuitar(SDL_Renderer* nRenderer, bool &guitarFlag); 

		void createExplosions(int curGuitarX, int curGuitarY);

		bool checkPlayerDeath();

		//bool checkBombCollsion(SDL_Renderer* nRenderer, std::vector<Explosion*> &explosions, Block *& block, SDL_Rect playerRect, bool &hasCollided); 

		//void alignToGrid();

		void setCamera(Window window, SDL_Rect& camera, int x, int y);

	private:
		Mix_Music *gMusic;
		bool initalized;
		bool hasCollided;

		int deathTimer;

		Player newPlayer;
		Window nWindow;
		Guitar guitar; 
		InputManager input; 

		std::vector<Block*> blocks;
		std::vector<Block*> innerBlocks;

		std::vector<Explosion*> explosions;
		std::vector<Enemy*> enemies;

		Texture tileTexture; 
		Texture tileTexture2;

		Texture hudTimerTexture;

		//original 
		Texture tileTexture3;
		Texture explosionTexture; 
		Texture guitarTexture;
		Texture enemy1Texture; 
		Texture note1;
		Texture note2;
		Texture note3;

		GameText hudTimer;
		Explosion *explosion; 

		SDL_Rect camera;
};
#endif 