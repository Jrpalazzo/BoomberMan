#include "bWindow.h"

bWindow::bWindow()
{
	mWindow = NULL;
	mMouseFocus = false;
	mKeyboardFocus = false;
	mFullScreen = false;
	mMinimized = false;
	mWidth  = 0;
	mHeight = 0;
}

bool bWindow::init()
{
	SDL_GetCurrentDisplayMode(0, &dMode);

	//Screen dimension constants
	//const int SCREEN_WIDTH = dMode.w;
	//const int SCREEN_HEIGHT = dMode.h;
	
	//For testing
	int SCREEN_HEIGHT = 720;
	int SCREEN_WIDTH = 1280;

	//Create window
	mWindow = SDL_CreateWindow( "Boomerman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( mWindow != NULL )
	{
		mMouseFocus = true;
		mKeyboardFocus = true;
		mWidth = SCREEN_WIDTH;
		mHeight = SCREEN_HEIGHT;
	}

	return mWindow != NULL;
}

//Creates rendere from internal window
SDL_Renderer* bWindow::createRenderer()
{
	return SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_PRESENTVSYNC);
}

//Handle window events
void bWindow::handleEvent(SDL_Renderer* gRenderer, SDL_Event& e)
{
	//Window event occured
    if( e.type == SDL_WINDOWEVENT )
    {
        //Caption update flag
        bool updateCaption = false;

		switch( e.window.event )
        {
            //Get new dimensions and repaint on window size change
            case SDL_WINDOWEVENT_SIZE_CHANGED:
            mWidth = e.window.data1;
            mHeight = e.window.data2;
            SDL_RenderPresent( gRenderer );
            break;

            //Repaint on exposure
            case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent( gRenderer );
            break;
			 //Mouse entered window
            case SDL_WINDOWEVENT_ENTER:
            mMouseFocus = true;
            updateCaption = true;
            break;
            
            //Mouse left window
            case SDL_WINDOWEVENT_LEAVE:
            mMouseFocus = false;
            updateCaption = true;
            break;

            //Window has keyboard focus
            case SDL_WINDOWEVENT_FOCUS_GAINED:
            mKeyboardFocus = true;
            updateCaption = true;
            break;

            //Window lost keyboard focus
            case SDL_WINDOWEVENT_FOCUS_LOST:
            mKeyboardFocus = false;
            updateCaption = true;
            break;

			    //Window minimized
            case SDL_WINDOWEVENT_MINIMIZED:
            mMinimized = true;
            break;

            //Window maxized
            case SDL_WINDOWEVENT_MAXIMIZED:
            mMinimized = false;
            break;
            
            //Window restored
            case SDL_WINDOWEVENT_RESTORED:
            mMinimized = false;
            break;
        }

    }

	//Enter exit full screen on return key
    else if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN )
    {
        if( mFullScreen )
        {
            SDL_SetWindowFullscreen( mWindow, SDL_FALSE );
            mFullScreen = false;
        }
        else
        {
            SDL_SetWindowFullscreen( mWindow, SDL_TRUE );
            mFullScreen = true;
            mMinimized = false;
        }
    }
}

//Deallocate internals
void bWindow::free()
{
	if( mWindow != NULL )
	{
		SDL_DestroyWindow( mWindow );
	}

	mMouseFocus = false;
	mKeyboardFocus = false;
	mWidth = 0;
	mHeight = 0;
}


//screen dimensions 
int bWindow::getWidth()
{
	return mWidth;
}

int bWindow::getHeight()
{
	return mHeight;
}

//window focii
bool bWindow::hasMouseFocus()
{
    return mMouseFocus;
}

bool bWindow::hasKeyboardFocus()
{
    return mKeyboardFocus;
}

bool bWindow::isMinimized()
{
    return mMinimized;
}