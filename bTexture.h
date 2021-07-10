#ifndef BTEXTURE_H
#define BTEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <sstream>

/*

Textures do not provide direct access to pixels Totally false! Just create a texture with access type
SDL_TEXTUREACCESS_STREAMING and then call SDL_LockTexture(), which updates the user-supplied &pixels 
pointer and &pitch value with information about the texture, thereby allowing direct, albeit officially
"write-only", access to the texture's pixels. Once finished, unlock, and then render as normal
*/

//Texture wrapper class
class Texture
{
	public:
		//Initializes variables
		Texture();  

		//Deallocates memory
		~Texture();

		//Loads image at specified path
	    bool loadFromFile(SDL_Renderer* gRenderer, std::string path );
		
		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* nTexture;
	
		//Image dimensions
		int mWidth;
		int mHeight;
};
#endif