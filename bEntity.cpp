#include "bEntity.h"

Entity::Entity() : Texture(){ 
    X = 0;
	Y = 0;
 
    mCollider.w = Width;
	mCollider.h = Height;; 

}
 
Entity::~Entity() {
}
 
int Entity::getX()
{
	return X;
}

int Entity::getY()
{
	return Y;
}

void Entity::setX(int x)
{
	X = x;
}

void Entity::setY(int y)
{
	Y = y;
}

void Entity::setColliderX(int x)
{
	mCollider.x = x;

}

void Entity::setColliderY(int y)
{
	mCollider.y = y;

}
SDL_Rect Entity::getCollider()
{
	return mCollider; 
}


