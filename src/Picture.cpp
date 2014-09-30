#include "include/Picture.h"
#include <stdio.h>
#include <jpeglib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <iostream>

Picture::Picture(){
	mData = NULL;
	mHeight = 0;
	mWidth = 0;
	mChannels = 0;
	mTotalBytes = 0;
}
Picture::~Picture(){
	if (mData != NULL)//TODO do I need to check for null?
		free(mData);
	if(mWindowData != NULL)	
		delete mWindowData;
}

void Picture::loadJpeg(const char* fileName){
	if (mData != NULL)
		free(mData);
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr err;
	FILE* infile;
	JSAMPROW rowPntr;
	int row_stride;
	cinfo.err = jpeg_std_error(&err);
	infile = fopen(fileName, "rb");
	if (infile == NULL){
		fputs("Could not open file\n", stderr);
		exit(EXIT_FAILURE);
	}
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, infile);
	jpeg_read_header(&cinfo, true);
	jpeg_start_decompress(&cinfo);
	row_stride = cinfo.output_width * cinfo.output_components;
	mData = (uint8_t*)malloc(cinfo.output_height * cinfo.output_width * cinfo.output_components);
	while (cinfo.output_scanline < cinfo.output_height){
		rowPntr = (JSAMPROW)(mData + (cinfo.output_scanline * row_stride));
		jpeg_read_scanlines(&cinfo, &rowPntr, 1);
	}
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(infile);
	mHeight = cinfo.output_height;
	mWidth = cinfo.output_width;
	mChannels = cinfo.output_components;
	mTotalBytes = mHeight * mWidth;
}

void Picture::loadJpeg(string fileName){
	loadJpeg(fileName.c_str());
}

void Picture::saveJpeg(const char* fileName, int quality, Colorspace colorSpace){
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	FILE* outfile;
	JSAMPROW row_pointer[1];
	int row_stride;
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);
	if ((outfile = fopen(fileName, "wb")) == NULL){
		fprintf(stderr, "Can't open file %s", fileName);
		exit(EXIT_FAILURE);
	}
	jpeg_stdio_dest(&cinfo, outfile);
	cinfo.image_width = mWidth;
	cinfo.image_height = mHeight;
	cinfo.input_components = mChannels;
	cinfo.in_color_space = (J_COLOR_SPACE)colorSpace;
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, quality, true);
	jpeg_start_compress(&cinfo, true);
	row_stride = cinfo.image_width * cinfo.input_components;/*mabye need 3*/
	while(cinfo.next_scanline < cinfo.image_height){
		row_pointer[0] = mData + (cinfo.next_scanline * row_stride);
		jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}
	jpeg_finish_compress(&cinfo);
	fclose(outfile);
	jpeg_destroy_compress(&cinfo);
}

void Picture::saveJpeg(string fileName, int quality, Colorspace colorSpace){
	saveJpeg(fileName.c_str(), quality, colorSpace);
}

void Picture::newPic(int height, int width, int channels, uint8_t value){
	mHeight = height;
	mWidth = width;
	mChannels = channels;
	mTotalBytes = mHeight * mWidth * mChannels;
	mData = (uint8_t*)realloc(mData,mTotalBytes);//should realloc()
	memset(mData, value, mTotalBytes);
}

int Picture::height(){
	return mHeight;
}
int Picture::width(){
	return mWidth;
}
int Picture::channels(){
	return mChannels;
}
int Picture::totalBytes(){
	return mTotalBytes;
}
uint8_t* Picture::data(){
	return mData;
}
uint8_t& Picture::get(int x, int y, int channel){
	return mData[mChannels * (x + mWidth * y) + channel];
}

#ifdef PICTURE_SDL

void Picture::display(){
	if(mWindowData == NULL){
		if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){//TODO check if already init
        	cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        	return;
    	}else{
    		mWindowData = new WindowData();
        	mWindowData->mWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWidth, mHeight, SDL_WINDOW_SHOWN );
        	if( mWindowData->mWindow == NULL )
        	{
            	cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
            	return;
        	}
    	}
    }
    //TODO check if size has changed
    SDL_Event dummy;
    while(SDL_PollEvent(&dummy));
    SDL_FreeSurface(mWindowData->mSurface);
    mWindowData->mSurface = SDL_CreateRGBSurfaceFrom(mData, mWidth, mHeight, 24, mWidth*3, 0x0000FF, 0x00FF00, 0xFF0000, 0x000000/*0,0,0,0*/);//this surface could be a local variable and not a member
    int height, width;
    SDL_GetWindowSize(mWindowData->mWindow, &height, &width);
    if (width!=mWidth || height!=mHeight)
    	SDL_SetWindowSize(mWindowData->mWindow, mWidth, mHeight);
    SDL_BlitSurface(mWindowData->mSurface, NULL, SDL_GetWindowSurface(mWindowData->mWindow), NULL);//TODO: resize
	SDL_UpdateWindowSurface(mWindowData->mWindow);
}

Picture::WindowData::~WindowData(){
	if (mWindow != NULL)
		SDL_DestroyWindow(mWindow);//TODO do I also have to free?
	if (mSurface != NULL)
		SDL_FreeSurface(mSurface);
	SDL_Quit();
}

#endif
/*
void* convertRGBtoRGBA(uint8_t* data, size_t size){
	uint8_t* newData = malloc(size*4/3);
	uint8_t* oldDataPntr = data;
	uint8_t* newDataPntr = newData;
	while (oldDataPntr - data != size){
		for (int i = 0; i < 3; i++){
			*(newDataPntr++) = *(oldDataPntr++);
		}
		*(newDataPntr++) = (uint8_t)0;
	}
}*/
