#include "bBlock.h"

Block::Block() 
{
	X = 0;
	Y = 0;

	mCollider.x = 0;
	mCollider.y = 0;
}

Block::Block(Texture &text1, int x, int y, int type ) : Entity()
{
	X = x;
	Y = y;

	mCollider.x = x;
	mCollider.y = y;
	mCollider.w = Width;
	mCollider.h = Height;
	mTexture = &text1;

	blockType = type; 
}


Block::~Block()
{
}

void Block::render(SDL_Renderer* nRenderer, SDL_Rect& camera)
{
	mTexture->render(nRenderer, X - camera.x , Y - camera.y);

}

void Block::drawBlockCollision(SDL_Renderer* nRenderer)
{
	SDL_SetRenderDrawColor(nRenderer, 0,0,255,255);
	SDL_RenderDrawRect(nRenderer, &mCollider);  

}

int Block::getBlockType()
{
	return blockType;
}

