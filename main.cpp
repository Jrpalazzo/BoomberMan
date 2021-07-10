#include "bEngine.h"
//uncheck for memory leaks !!
//#include "vld.h" 

//include arguments to get rid of error LNK2019 
int main(int argc, char *args[])
{
	Engine engine;
	bool run = engine.getRunState();
	bool reset = engine.getResetState();

	if(!engine.initSDL()){
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	}
	else
	{
		engine.initWindow();
		
		while(engine.running(run)){
				engine.update();
		}
	}

	return 0;
}