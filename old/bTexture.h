#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <sstream>

//Texture wrapper class
class bTexture
{
	public:
		//Initializes variables
		bTexture();  

		//Deallocates memory
		~bTexture();

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