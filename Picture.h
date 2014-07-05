#include <string>
#include <stdint.h>

using namespace std;

enum Colorspace{
	greyscale = 1,
	rgb = 2,
	unknown = 3//is this right? is unknown 3 in libjpeg?
};

class Picture{
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
	uint8_t& byte(int index);
	void loadJpeg(const char* fileName);
	void loadJpeg(string fileName);
	void saveJpeg(const char* fileName, int quality = 100, Colorspace colorSpace = rgb);
	void saveJpeg(string fileName, int quality = 100,  Colorspace colorSpace = rgb);
};


/*
* NOTE: 1 = greyscale, 2 = rgb. make enum later.
*/
