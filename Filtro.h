#ifndef _FILTRO_H_
#define _FILTRO_H_
#include "BMPImageLoader.h"

typedef struct pixel
{
	uint8 R;
	uint8 G;
	uint8 B;
}pixel_t;

extern float mask[];

uint8* aplicarFiltro(uint8* img, float* filtro, uint32 imgW, uint32 imgH, uint32 filW, uint32 filM);

#endif
