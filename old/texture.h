#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <SDL_image.h>
#include <SDL.h>

class texture
{
	public:
		texture();

		~texture();

		bool loadFromFile(std::string path);

		void free();

		void render(int x, int y, SDL_Rect* clip = NULL);

		int getWidth();
		int getHeight();

	private:
		SDL_Texture* mTexture;
	
		int mWidth;
		int mHeight;
};

#endif 