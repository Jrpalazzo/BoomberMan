#include "texture.h"
#include "game.h"
#include <stdio.h>

texture::texture()
{
 mTexture = NULL;
 mWidth = 0;
 mHeight = 0;
}

texture::~texture()
{
 free();
}

bool texture::loadFromFile(std::string path)
{
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str() );
	if(loadedSurface == NULL)
	{
		printf("Error");
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF ));

		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if(newTexture = NULL)
		{
          printf("Error");
		}
		else
		{
		  mWidth = loadedSurface->w;
		  mHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	mTexture = newTexture;
	
	return mTexture != NULL;

}

void texture::free()
{
	//Free texture if it exists
	if( texture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void texture::render( int x, int y, SDL_Rect* clip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

int texture::getWidth()
{
	return mWidth;
}

int texture::getHeight()
{
	return mHeight;
}