#include <stdio.h>
#include <stdlib.h>
#include "BMPImageLoader.h"
#include "Filtro.h"
#include <Windows.h>

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif



NUM_THREAD = 10;

//Signature	2 bytes	0000h	'BM'
//FileSize	4 bytes	0002h	File size in bytes
//reserved	4 bytes	0006h	unused(= 0)
//DataOffset	4 bytes	000Ah	Offset from beginning of file to the beginning of the bitmap data



int main(int argc, char** argv) {
	BMPImage_t* image = loadBMP("FLAG_B24.bmp");
	BMPImage_t imageResult;
	uint8* imgFilter = (uint8*)malloc(sizeof(uint8)*image->infoHeader.width *image->infoHeader.height);
	printf("Tamño fichero: %d \n", image->header.fileSize);
	printf("Data Offset: %d \n", image->header.dataOffset);
	printf("size %d\n"
		"width %d\n"
		"height %\n"
		"planes %\n"
		"bpp %\n"
		"compression %d\n"
		"imageSize %d\n"
		"xPixelsPerM %d\n"
		"yPixelsPerM %d\n"
		"colorUsed %d\n"
		"importantColors%d\n",
		image->infoHeader.size,
		image->infoHeader.width,
		image->infoHeader.height,
		image->infoHeader.planes,
		image->infoHeader.bpp,
		image->infoHeader.compresion,
		image->infoHeader.imagenSize,
		image->infoHeader.xPixelPerM,
		image->infoHeader.yPixelPerM,
		image->infoHeader.colorsUsed,
		image->infoHeader.importantColors);
	/*
	imgFilter = aplicarFiltro(image->pixels, mask,
							  image->infoHeader.width,
							  image->infoHeader.height,
							  3, 3);
	*/

	int filas_por_thread = image->infoHeader.height / NUM_THREAD;
	int bytes_por_fila = image->infoHeader.width * 3;

	/*unsigned char* res[2];


	for (int i = 0; i < NUM_THREAD; i++) {
		res[i] = aplicarFiltro(image->pixels + (i * bytes_por_fila * (filas_por_thread - 1)), mask,
			image->infoHeader.width,
			filas_por_thread + 1,
			3, 3);
	}*/

	unsigned char* data = (unsigned char*)malloc(sizeof(unsigned char) * image->infoHeader.width * image->infoHeader.height * 3);

	params* hParams = (params*)malloc(sizeof(params)*NUM_THREAD);
	HANDLE* hThread = (HANDLE*)malloc(sizeof(HANDLE)*NUM_THREAD);

	for (int i = 0; i < NUM_THREAD; i++) {
		hParams[i].threadID = i;
		hParams[i].imgW = image->infoHeader.width;
		hParams[i].imgH = image->infoHeader.height / NUM_THREAD;
		hParams[i].imgResult = data;
		hParams[i].img = image->pixels;
		hParams[i].filtro = mask;

		hThread[i] = _beginthread(&aplicarFiltroConThreads, 0, &hParams[i]);
	}

	for (int i = 0; i < NUM_THREAD; i++) {
		WaitForSingleObject(hThread[i], INFINITE);
	}


	imageResult.header.signature[0] = 'B';
	imageResult.header.signature[1] = 'M';
	imageResult.header.fileSize = image->infoHeader.width * image->infoHeader.height * 3 + 14 + 40 + 0; // +0 porque no tenemos paleta pero hay que tenerlo en cuenta
	imageResult.header.reserved = 0;
	imageResult.header.dataOffset = 14 + 40 + 0; // +0 porque no tenemos paleta pero hay que tenerlo en cuenta

	imageResult.infoHeader.size = 40;
	imageResult.infoHeader.width = image->infoHeader.width;
	imageResult.infoHeader.height = image->infoHeader.height;
	imageResult.infoHeader.planes = 1;
	imageResult.infoHeader.bpp = 24;
	imageResult.infoHeader.compresion = 0;
	imageResult.infoHeader.imagenSize = image->infoHeader.width* image->infoHeader.height * 3;
	imageResult.infoHeader.xPixelPerM = 0;
	imageResult.infoHeader.yPixelPerM = 0;
	imageResult.infoHeader.colorsUsed = 0;
	imageResult.infoHeader.importantColors = 0;

	

	imageResult.pixels = data;
	imageResult.palette = NULL;

	writeBMP(&imageResult, "asdf.bmp");
	return 0;
}