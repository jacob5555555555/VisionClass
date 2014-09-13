#include "SDL2/SDL.h"

class Window{
	SDL_Window* mWindow = NULL;
    void* data;
public:
	Window(void *data, int width, int height);
	~Window();
	void update();
};