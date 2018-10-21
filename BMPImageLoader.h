#pragma once
#include <stdio.h>
#include <stdlib.h>
#ifndef BMP_IMAGE_LOADER
#define BMP_IMAGE_LOADER


//InfoHeader
//40bytes
//Windows Structure :BITMAPINFOHEADER
#define uint32 unsigned int
#define uint16 unsigned short
#define uint8  unsigned char

typedef struct header_t
{
	uint8 signature[2];
	uint32 fileSize;
	uint32 reserved;
	uint32 dataOffset;

}header_t;
typedef struct infoHeader_t
{
	uint32 size;
	uint32 width;
	uint32 height;
	uint16 planes;
	uint16 bpp;
	uint32 compresion;
	uint32 imagenSize;
	uint32 xPixelPerM;
	uint32 yPixelPerM;
	uint32 colorsUsed;
	uint32 importantColors;
}infoHeader_t;

typedef struct BMPImage_t
{
	header_t header;
	infoHeader_t infoHeader;
	uint32* palette;
	uint8* pixels;
}BMPImage_t;


BMPImage_t* loadBMP(const char* path);
void writeBMP(BMPImage_t* image, const char* path);
uint8* load_pixels(FILE* file, uint16 bpp, uint32 width, uint32 heigth);
uint32* load_palette(FILE* file, uint16 bpp);
void write_infoHeader(FILE* fout, infoHeader_t infoHeader);
void write_header(FILE* fout, header_t header);
#endif
