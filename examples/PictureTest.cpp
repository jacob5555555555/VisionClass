#include <iostream>
#include <unistd.h>
#include "../include/Picture.h"

int main(int argc, char **argv){	
	if (argc != 2){
		cout << "usage: " << argv[0] << " [filemane.jpg]" << endl;
		return 1;
	}
	Picture myPic;
	myPic.loadJpeg(argv[1]);
	for (int time = 0; time <= 300; time++){
		myPic.display();
		usleep(5000);
	}	
}

