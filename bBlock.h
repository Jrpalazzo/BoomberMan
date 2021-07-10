#pragma once
#include "bEntity.h"
class Block :
	public Entity
{
public:
	Block();
	Block(Texture &text1, int x, int y, int type);
	virtual ~Block();

	//Shows the block
	void render(SDL_Renderer* nRenderer, SDL_Rect& camera);

	void drawBlockCollision(SDL_Renderer* nRenderer);
	int getBlockType();

private:
	//Type of particle
	Texture *mTexture;
	int blockType;



};

