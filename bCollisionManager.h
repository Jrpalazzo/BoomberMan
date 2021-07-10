#ifndef BCOLLISIONMANAGER_h
#define BCOLLISIONMANAGER_h

#include <SDL.h>
#include <iostream>
#include "bEntity.h"
#include "bPlayer.h"
#include "bWindow.h"

class CollisionManager 
{
	public:
		CollisionManager();

		~CollisionManager();

		void getCollision(Player &newPlayer, std::vector<Block*> blocks);

		bool checkCollision(SDL_Rect a, SDL_Rect b);

	private:
		SDL_Rect curBlock;
	
};
#endif 