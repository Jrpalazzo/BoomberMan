#ifndef BPARTICLE_H
#define BPARTICLE_H

#include <iostream>
#include "bTexture.h"

class Particle
{
	//the & in constructor allows for textures to be passed as non-null 
	public:
		//Initialize position and animation
		Particle(Texture &text1, Texture &text2, Texture &text3, int x, int y );

		//Shows the particle
		void render(SDL_Renderer* nRenderer, SDL_Rect& camera);

		//Checks i f particle is dead
		bool isDead();

		int getX();

		int getY();

	private:
		//Offsets
		int X, Y;

		//Current frame of animation
		int mFrame;

		//Type of particle
		Texture *mTexture;
};
#endif