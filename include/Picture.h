#include <string>
#include <stdint.h>

#define PICTURE_SDL//TODO fix

#ifdef PICTURE_SDL
#include "SDL2/SDL.h"
#endif

using namespace std;

enum Colorspace{
	greyscale = 1,
	rgb = 2,
	unknown = 3//is this right? is unknown 3 in libjpeg?
};

class Picture{
	#ifdef PICTURE_SDL
	struct WindowData;
	WindowData* mWindowData = NULL;
	#endif
	uint8_t* mData;
	int mHeight;
	int mWidth;
	int mChannels;
	int mTotalBytes;

public:
	Picture();
	~Picture();
	uint8_t* data();
	int height();
	int width();
	int channels();
	int totalBytes();
	void newPic(int height, int width, int channels, uint8_t value = 0);
	uint8_t& get(int x, int y, int channel);
	inline uint8_t& byte(int index);
	void loadJpeg(const char* fileName);
	void loadJpeg(string fileName);
	void saveJpeg(const char* fileName, int quality = 100, Colorspace colorSpace = rgb);
	void saveJpeg(string fileName, int quality = 100,  Colorspace colorSpace = rgb);
	void display();
};

inline uint8_t& Picture::byte(int index){
	return mData[index];
}

#ifdef PICTURE_SDL
struct Picture::WindowData{
		SDL_Window* mWindow = NULL;
		SDL_Surface* mSurface = NULL;
		~WindowData();
};

#endif

/*
* NOTE: 1 = greyscale, 2 = rgb. make enum later.
*/
