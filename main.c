#include <stdio.h>
#include <stdlib.h>
#include "BMPImageLoader.h"
#include "Filtro.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif



NUM_THREAD = 2;

//Signature	2 bytes	0000h	'BM'
//FileSize	4 bytes	0002h	File size in bytes
//reserved	4 bytes	0006h	unused(= 0)
//DataOffset	4 bytes	000Ah	Offset from beginning of file to the beginning of the bitmap data

typedef struct hParams_t {
	int threadID;
	int* contador;
	int size;
	int width;
	int height;
	HANDLE* lock;
}hParams_t;

void threadFunction(void *params){
	hParams_t hparams = *((hParams_t*)params);
	
	int n = image->infoHeader.height / NUM_THREAD;
	unsigned char* res[2];
	
	res[i] = aplicarFiltro(image->pixels + (i * image->infoHeader.width * 3 * (n-1)), mask,
			image->infoHeader.width ,
			n + 1,
			3, 3);
			
	HANDLE* lock = hparams.lock;
			
	WaitForSingleObject(*lock,
		INFINITE);
	(*(hparams.contador))++;
	ReleaseMutex(*lock);
	_endthread();
}


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

	
	
	int* contador = 0;
	HANDLE* hThread = (HANDLE*)malloc(sizeof(HANDLE)*NUMTHREADS);
	hParams_t* hParams = (hParams_t*)malloc(sizeof(hParams_t)*NUMTHREADS);
	HANDLE* lock = (HANDLE*)malloc(sizeof(HANDLE));
	*lock = CreateMutex(NULL, FALSE, NULL);
	
	for (int i = 0; i < NUM_THREAD; i++) {
		hParams[i].threadID = i;
		hParams[i].contador = contador;
		hParams[i].lock = lock;
		
		hThread = _beginthread(&threadFunction, 0, &hParams[i]);
	}
	
	for (i = 0; i < NUMTHREADS; i++) {
		WaitForSingleObject(hThread[i], INFINITE);
	}

	printf("contador: %d\n", *contador);

	imageResult.header.signature[0] = 'B';
	imageResult.header.signature[1] = 'M';
	imageResult.header.fileSize = image->infoHeader.width * image->infoHeader.height * 3 + 14 + 40 + 0; // +0 porque no tenemos paleta pero hay que tenerlo en cuenta
	imageResult.header.reserved = 0;
	imageResult.header.dataOffset = 14 + 40 + 0; // +0 porque no tenemos paleta pero hay que tenerlo en cuenta

	imageResult.infoHeader.size = 40;
	imageResult.infoHeader.width = image->infoHeader.width ;
	imageResult.infoHeader.height = image->infoHeader.height;
	imageResult.infoHeader.planes = 1;
	imageResult.infoHeader.bpp = 24;
	imageResult.infoHeader.compresion = 0;
	imageResult.infoHeader.imagenSize = image->infoHeader.width* image->infoHeader.height * 3;
	imageResult.infoHeader.xPixelPerM = 0;
	imageResult.infoHeader.yPixelPerM = 0;
	imageResult.infoHeader.colorsUsed = 0;
	imageResult.infoHeader.importantColors = 0;

	unsigned char* data = (unsigned char*)malloc(sizeof(unsigned char) * image->infoHeader.width * image->infoHeader.height*3);
	for (int i = 0; i < NUM_THREAD; i++) {
		
		memcpy(data + (i * image->infoHeader.width * 3 *(n - 1)), res[i] + i *image->infoHeader.width * 3, image->infoHeader.width * (n + 1) * 3);
	}
	
	//memcpy(data + (image->infoHeader.width * (image->infoHeader.height / 2) * 3), res[1], image->infoHeader.width * (image->infoHeader.height / 2) * 3);
	imageResult.pixels = data;
	imageResult.palette = NULL;
	
	writeBMP(&imageResult, "asdf.bmp");
	
	
	free(contador);
	free(lock);
	free(hThread);
	free(hParams);
	
	
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