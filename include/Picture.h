#include <string>
#include <stdint.h>

using namespace std;

enum Colorspace{
	greyscale = 1,
	rgb = 2,
	unknown = 3//is this right? is unknown 3 in libjpeg?
};

class WindowData;

class Picture{
	WindowData* mWindowData;
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

inline int Picture::height(){
	return mHeight;
}
inline int Picture::width(){
	return mWidth;
}
inline int Picture::channels(){
	return mChannels;
}
inline int Picture::totalBytes(){
	return mTotalBytes;
}
inline uint8_t* Picture::data(){
	return mData;
}
inline uint8_t& Picture::get(int x, int y, int channel){
	return mData[mChannels * (x + mWidth * y) + channel];
}


/*
* NOTE: 1 = greyscale, 2 = rgb. make enum later.
*/
