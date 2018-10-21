#include <stdio.h>
#include <stdlib.h>
#include "BMPImageLoader.h"
#include "filtro.h"





//Signature	2 bytes	0000h	'BM'
//FileSize	4 bytes	0002h	File size in bytes
//reserved	4 bytes	0006h	unused(= 0)
//DataOffset	4 bytes	000Ah	Offset from beginning of file to the beginning of the bitmap data





int main(int argc, char** argv) {
	BMPImage_t* image = loadBMP("FLAG_B24.bmp");
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

	uint8* imgFilter; // deberia estar declarado arriba
	BMPImage_t imageResult;

	imgFilter = aplicarFiltro(image->pixels, mask, image->infoHeader.width, image->infoHeader.height, 3, 3);

	imageResult.header.signature[0] = "B";
	imageResult.header.signature[1] = "M";
	imageResult.header.fileSize = image->infoHeader.width * image->infoHeader.height * 3 + 14 + 40 + 0;
	imageResult.header.reserved = "0";
	imageResult.header.dataOffset = 14 + 40 + 0;
	
	imageResult.infoHeader.size = image->infoHeader.width * image->infoHeader.height * 3;
	imageResult.infoHeader.width = image->infoHeader.width;
	imageResult.infoHeader.height = image->infoHeader.height;
	imageResult.infoHeader.planes = 1;
	imageResult.infoHeader.bpp = 24;
	imageResult.infoHeader.compresion=0;
	imageResult.infoHeader.imagenSize = image->infoHeader.width + image->infoHeader.height*3;
	imageResult.infoHeader.xPixelPerM=0;
	imageResult.infoHeader.yPixelPerM=0;
	imageResult.infoHeader.colorsUsed=0;
	imageResult.infoHeader.importantColors=0;


	imageResult.pixels = imgFilter;
	imageResult.palette = NULL;

	writeBMP(image, "prueba.bmp");
	/*	FILE* fichero;
	int numBytesRead = 0;
	int actualFileSize = 0;
	long readPosition = 0;
	char* buffer = (char*)malloc(3);
	int* fileSize = (int*)malloc(sizeof(int));
	int* dataOffset = (int*)malloc(sizeof(int));
	//short* buffer2 = (short*)malloc(sizeof(short));
	fichero = fopen("FLAG_B24.bmp", "r");
	if (fichero == NULL) {
	printf("ERROR: Fichero no encontrado");
	getc(stdin);
	exit(1);
	}
	if (buffer != NULL) {

	numBytesRead = fread(buffer, 1, 2, fichero);
	if (numBytesRead != 2) {
	printf("ERROR: Lectura de datos erronea");
	}
	}
	buffer[2] = '\0';
	printf("Firma: %s\n",buffer);

	if (!strncmp(buffer, "BM", 2)) {
	printf("Fichero BMP correcto\n");
	}
	else {
	printf("Fichero BMP mal formado");
	getc(stdin);
	exit(1);
	}
	if (fileSize != NULL) {
	numBytesRead = fread(fileSize, 1, 4, fichero);
	if (numBytesRead != 4) {
	printf("ERROR: Lectura de datos erronea");
	getc(stdin);
	exit(1);
	}
	else {
	printf("Tamaño Fichero: %d\n", *fileSize);
	}
	readPosition = (int)ftell(fichero);
	fseek(fichero, 0, SEEK_END);
	actualFileSize = (int)ftell(fichero);
	fseek(fichero, readPosition, SEEK_SET);

	if (actualFileSize != *fileSize) {
	printf("ERROR: Tamaño Fichero real %d \n", actualFileSize);
	getc(stdin);
	exit(1);
	}
	}
	fseek(fichero, 4, SEEK_CUR);
	if (dataOffset != NULL) {
	numBytesRead = fread(dataOffset, 1, 4, fichero);
	if (numBytesRead != 4) {
	printf("ERROR: Lectura de datos erronea");
	getc(stdin);
	exit(1);
	}
	else {
	printf("DataOffset:  %d\n", *dataOffset);
	}
	}

	//fread(buffer, 1, 2, fichero);
	//fwrite("HolaMundo ficheros\n", 1, 19, fichero);
	//fread();
	//fwrite();
	buffer[19] = '\0';
	//printf(buffer);
	getc(stdin);
	fclose(fichero);
	free(buffer);
	free(fileSize);
	//free(buffer2);*/
	return 0;
}