#include "bTexture.h"
#include <iostream>

bTexture::bTexture()
{
	//Initialize
	nTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

bTexture::~bTexture()
{
	//Deallocate
	free();
}

bool bTexture::loadFromFile(SDL_Renderer* gRenderer, std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		//SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 255, 0xFF, 255 ) );

		std::cout << gRenderer << std::endl;

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
			
			std::cout << "background_width " << mWidth << std::endl;
			std::cout << "background_height " << mHeight << std::endl;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	nTexture = newTexture;
	return nTexture != NULL;
}

void bTexture::free()
{
	//Free texture if it exists
	if( nTexture != NULL )
	{
		SDL_DestroyTexture( nTexture );
		nTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void bTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( nTexture, red, green, blue );
}

void bTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( nTexture, blending );
}
		
void bTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( nTexture, alpha );
}

void bTexture::render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
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
	SDL_RenderCopyEx( gRenderer, nTexture, clip, &renderQuad, angle, center, flip );
}

int bTexture::getWidth()
{
	return mWidth;
}

int bTexture::getHeight()
{
	return mHeight;
}
