#include "../include/Picture.h"

int main(){
	Picture pic;
	pic.newPic(100,100,3);
	pic.saveJpeg("square.jpg");
	pic.display();
	return 0;
}
