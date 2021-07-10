#ifndef BWINDOW_H
#define BWINDOW_H

#include <SDL.h>
#include <string>
#include <sstream>

class Window
{
	public: 
		//Initialize class
		Window();

		bool init();

		//Creates render from internal window
		SDL_Renderer* createRenderer();

		//Handle window events
		void handleEvent(SDL_Renderer* gRenderer, SDL_Event& e);

		//Deallocate internals
		void free();

		//screen dimensions 
		int getWidth();
		int getHeight();

		//window focii
		bool hasMouseFocus();
		bool hasKeyboardFocus();
		bool isMinimized(); 

		//returns mWindow
		SDL_Window* getWindow();

	private:
		//Window data
		SDL_Window* mWindow;
		SDL_DisplayMode dMode;

		//screen dimensions
		int mWidth;
		int mHeight;

		//Window focus
		bool mMouseFocus;
		bool mKeyboardFocus;
		bool mFullScreen;
		bool mMinimized; 
};
#endif