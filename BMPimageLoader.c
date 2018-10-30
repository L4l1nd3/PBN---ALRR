#include <stdio.h>
#include <stdlib.h>
#include "BMPImageLoader.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

header_t loadHeader(FILE* f_bmp) {
	header_t header = {
		.signature = { 0,0 },
		.fileSize = 0,
		.reserved = 0,
		.dataOffset = 0
	};
	int numBytesRead = 0;
	//leer signature
	numBytesRead = fread(&(header.signature[0]), 1, 2, f_bmp);
	//testear signature
	if (numBytesRead != 2) exit(1);
	if (strncmp(&(header.signature[0]), "BM", 2) != 0) exit(1);
	//leer file size
	numBytesRead = fread(&(header.fileSize), 1, 4, f_bmp);
	//testear filesize
	if (numBytesRead != 4)exit(1);
	//testear tamaño(mirar main)

	//leer reserved
	numBytesRead = fread(&(header.reserved), 1, 4, f_bmp);
	//leer dataoffset
	numBytesRead = fread(&(header.dataOffset), 1, 4, f_bmp);
	if (numBytesRead != 4)exit(1);

	return header;
};

infoHeader_t loadInfoHeader(FILE* f_bmp) {
	infoHeader_t infoHeader = {
		.size = 0,
		.width = 0,
		.height = 0,
		.planes = 0,
		.bpp = 0,
		.compresion = 0,
		.imagenSize = 0,
		.xPixelPerM = 0,
		.yPixelPerM = 0,
		.colorsUsed = 0,
		.importantColors = 0
	};

	int numBytesRead = 0;
	//leer size
	numBytesRead = fread(&(infoHeader.size), 1, 4, f_bmp);
	//testear size
	if (numBytesRead != 4) exit(1);
	//leer width
	numBytesRead = fread(&(infoHeader.width), 1, 4, f_bmp);
	//testear wisth
	if (numBytesRead != 4) exit(1);
	//leer heigth
	numBytesRead = fread(&(infoHeader.height), 1, 4, f_bmp);
	//testear heigth
	if (numBytesRead != 4) exit(1);
	//leer planes
	numBytesRead = fread(&(infoHeader.planes), 1, 2, f_bmp);
	//testear planes
	if (numBytesRead != 2) exit(1);
	//leer bits per pixel
	numBytesRead = fread(&(infoHeader.bpp), 1, 2, f_bmp);
	//testear bits per pixel
	if (numBytesRead != 2) exit(1);
	//leer compression
	numBytesRead = fread(&(infoHeader.compresion), 1, 4, f_bmp);
	//testear compression
	if (numBytesRead != 4) exit(1);
	//leer image size
	numBytesRead = fread(&(infoHeader.imagenSize), 1, 4, f_bmp);
	//testear image size
	if (numBytesRead != 4) exit(1);
	//leer x pixels per m
	numBytesRead = fread(&(infoHeader.xPixelPerM), 1, 4, f_bmp);
	//testear x pixels per m
	if (numBytesRead != 4) exit(1);
	//leer y pixels per m
	numBytesRead = fread(&(infoHeader.yPixelPerM), 1, 4, f_bmp);
	//testear y pixels per m
	if (numBytesRead != 4) exit(1);
	//leer colors used
	numBytesRead = fread(&(infoHeader.colorsUsed), 1, 4, f_bmp);
	//testear colorls used
	if (numBytesRead != 4) exit(1);
	//leer important colors
	numBytesRead = fread(&(infoHeader.importantColors), 1, 4, f_bmp);
	//testear important colors
	if (numBytesRead != 4) exit(1);


	return infoHeader;
}
uint32* load_palette(FILE* file, uint16 bpp)
{
	uint32* palette = NULL;
	int numColors = 0x01 << bpp;
	int i = 0;
	if (bpp >= 8)
		return NULL;

	palette = (uint32*)malloc(sizeof(uint32)*numColors);

	for (i = 0; i < numColors; i++)
	{
		fread(&(palette[i]), 1, 4, file);
	}
	return palette;
}
uint8* load_pixels(FILE* file, uint16 bpp, uint32 width, uint32 heigth)
{
	uint8* pixels = NULL;
	int pixelArraySize = 0;
	switch (bpp)
	{
	case 1:
		break;
	case 4:
		break;
	case 8:
		break;
	case 16:
		break;
	case 24:
		pixelArraySize = 3 * width * heigth;
		pixels = (uint8*)malloc(pixelArraySize);
		for (int i = 0; i < pixelArraySize; i++)
		{
			fread(&(pixels[i]), 1, 1, file);
		}

		break;
	default:
		break;


	}
	return pixels;
}

BMPImage_t* loadBMP(const char* path) {
	FILE* file = NULL;
	BMPImage_t* BMPImage = (BMPImage_t*)malloc(sizeof(BMPImage_t));
	//comprobar variables cabecera(path)
	if (path == NULL) return NULL;
	else {
		//abrir fichero
		file = fopen(path, "r");
		//si no existe:
		if (file == NULL)return NULL;
	}
	//load header
	BMPImage->header = loadHeader(file);
	//load info header
	BMPImage->infoHeader = loadInfoHeader(file);
	//load data
	BMPImage->palette = load_palette(file, BMPImage->infoHeader.bpp);
	//return imagen
	BMPImage->pixels = load_pixels(file, BMPImage->infoHeader.bpp, BMPImage->infoHeader.width, BMPImage->infoHeader.height);

	fclose(file);
	return BMPImage;
}
void write_header(FILE* fout, header_t header)
{
	//control de errores
	fwrite(&(header.signature[0]),1,2,fout);
	fwrite(&(header.fileSize), 1, 4, fout);
	fwrite(&(header.reserved), 1, 4, fout);
	fwrite(&(header.dataOffset), 1, 4, fout);
}
void write_infoHeader(FILE* fout, infoHeader_t infoHeader)
{
	fwrite(&(infoHeader.size), 1, 4, fout);
	fwrite(&(infoHeader.width), 1, 4, fout);
	fwrite(&(infoHeader.height), 1, 4, fout);
	fwrite(&(infoHeader.planes), 1, 2, fout);
	fwrite(&(infoHeader.bpp), 1, 2, fout);
	fwrite(&(infoHeader.compresion), 1, 4, fout);
	fwrite(&(infoHeader.imagenSize), 1, 4, fout);
	fwrite(&(infoHeader.xPixelPerM), 1, 4, fout);
	fwrite(&(infoHeader.yPixelPerM), 1, 4, fout);
	fwrite(&(infoHeader.colorsUsed), 1, 4, fout);
	fwrite(&(infoHeader.importantColors), 1, 4, fout);
}

void write_palette(FILE* file, infoHeader_t infoHeader, uint32* palette)
{
	int paletteArraySize = 0x01 << infoHeader.bpp;
	if (infoHeader.bpp >= 8)
		return;

	fwrite(palette, 1, paletteArraySize * sizeof(uint32), file);
}

void write_pixels(FILE* file, infoHeader_t infoHeader, uint8* pixels)
{
	int paletteArraySize = 0;
	switch (infoHeader.bpp)
	{
	case 1:
		break;
	case 4:
		break;
	case 8:
		break;
	case 16:
		break;
	case 24:
		paletteArraySize = 3 * infoHeader.height * infoHeader.width;
		fwrite(pixels, 1, paletteArraySize, file);
		break;
	default:
		break;
	}
}

void writeBMP(BMPImage_t* image, const char* path)
{
	FILE* fout = NULL;
	//comprobar cabecera
	if ((image == NULL) || (path == NULL))//no tiene nada
		return;


	//abrir fichero
	fout = fopen(path, "w");
	//escribir cabecera
	write_header(fout,image->header);
	//escribir infoHeader
	write_infoHeader(fout,image->infoHeader);
	//escribir paleta
	write_palette(fout,image->infoHeader,image->palette);
	//escribir pixels
	write_pixels(fout,image->infoHeader,image->pixels);
	//cerrar fichero
	fclose(fout);
}

