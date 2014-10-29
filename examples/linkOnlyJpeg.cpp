#define PICTURE_USE_JPEG
#include "../include/Picture.h"

int main(){
	Picture pic;
	pic.newPic(100,100,3);
	pic.saveJpeg("square.jpg");
	return 0;
}
