
#ifndef _FILTRO_H
#define _FILTRO_H
#include "BMPimageLoader.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

typedef struct pixel_t
{
	uint8 R;
	uint8 G;
	uint8 B;
}pixel_t;

extern float mask[];
uint8* aplicarFiltro(uint8* img, float* filtro, uint32 imgW, uint32 imgH, uint32 filW, uint32 filH);
#endif
