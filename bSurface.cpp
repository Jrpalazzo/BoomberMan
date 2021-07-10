#include "bSurface.h"
 
Surface::Surface() {
}
 
SDL_Surface* Surface::loadFromFile(char* File, SDL_Surface* surface) {
    SDL_Surface* surfaceTemp = NULL;
    SDL_Surface* surfaceReturn = NULL;
 
    if((surfaceTemp = SDL_LoadBMP(File)) == NULL) {
        return NULL;
    }
 
	//Surface is null.
	std::cout<<"Surface " << surface <<std::endl;

	if(surface == NULL)
	{
		std::cout<<"That's a raspberry " << surface <<std::endl;
	}
	else
	{
		surfaceReturn = SDL_ConvertSurface( surfaceTemp, surface->format, 0 );
	}

    SDL_FreeSurface(surfaceTemp);

	std::cout<<"Success2"<<std::endl;
 
    return surfaceReturn;
}

bool Surface::Draw(SDL_Surface* SurfaceDest, SDL_Surface* SurfaceSrc, int X, int Y, int W, int H) {
    if(SurfaceDest == NULL || SurfaceSrc == NULL) {
        return false;
    }
 
    SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;
	DestR.w = W;
	DestR.h = H;

	SDL_BlitSurface(SurfaceSrc, NULL, SurfaceDest, &DestR);

 
    return true;
}