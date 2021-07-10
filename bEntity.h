#ifndef BENTITY_H
#define BENTITY_H

#include <SDL.h>
#include "bTexture.h"
#include <vector>
#include <iostream>

class Entity : public Texture
{
  
    public:
		static const int Width = 64;;
		static const int Height = 64;

        Entity();
 
        virtual ~Entity();
 
		//Gets entity location
		int getX();
		int getY();
		
		void setX(int x);

		void setY(int y);

		void setColliderX(int x);

		void setColliderY(int y);

		SDL_Rect getCollider();

		Entity* entityA;
		Entity* entityB;

	protected:
		SDL_Rect curBlock;
		int lastBlockPos;

		int X;
        int Y;
 
        SDL_Rect mCollider; 
};
#endif