#include "bParticle.h"
#include <math.h>
#include "bTimer.h"

Particle::Particle(Texture &text1, Texture &text2, Texture &text3, int x, int y )
{
    //Set offsets
    X = (x - 15 + ( rand() % 150 ));
    Y = y - 15 + ( rand() % 150 );

    //Initialize animation
    mFrame = rand() % 3;

    //Set type
    switch( rand() % 3 )
    {
        case 0: mTexture = &text1; break;
        case 1: mTexture = &text2; break;
        case 2: mTexture = &text3; break;
    }

}

int Particle::getX()
{
	return X;
}

int Particle::getY()
{
	return Y;
}

void Particle::render(SDL_Renderer* nRenderer, SDL_Rect& camera)
{

	mTexture->render(nRenderer, X-camera.x, Y-camera.y);

    //Animate
    mFrame+=2;
}

bool Particle::isDead()
{
    return mFrame > 35;
}