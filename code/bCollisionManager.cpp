#include "bCollisionManager.h"

CollisionManager::CollisionManager()
{


}

CollisionManager::~CollisionManager()
{


}

void CollisionManager::getCollision(Player &newPlayer, std::vector<Block*> blocks)
{
	for(int i = 0; i < blocks.size(); ++i )
	{
		if(checkCollision(newPlayer.getCollider(), blocks[i]->getCollider()))
		{
			
			
		}
	}

}

bool CollisionManager::checkCollision(SDL_Rect a, SDL_Rect b)
{
	if(SDL_HasIntersection(&a, &b))
	{
		curBlock = b;
		return true;
	}	

	return false; 
}

