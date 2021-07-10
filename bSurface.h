#ifndef BSURFACE_H
#define BSURFACE_H

#include <SDL.h>
#include <iostream>

class Surface {
    public:
        Surface();
 
    public:
        static SDL_Surface* loadFromFile(char* File, SDL_Surface* surface);
		static bool Draw(SDL_Surface* SurfaceDest, SDL_Surface* SurfaceSrc, int X, int Y, int W, int H);
};
#endif