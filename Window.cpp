#include "Window.h"
#include <iostream>

using namespace std;

Window::Window(void *data, int width, int height){
	mWindow = NULL;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )//TODO check if already init
    {
        cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
    }else{
        mWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
        if( mWindow == NULL )
        {
            cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        }else{
        	SDL_GetWindowSurface(mWindow)->pixels = data;
        }
    }
}

Window::~Window(){
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Window::update(){
	SDL_UpdateWindowSurface( mWindow );
}