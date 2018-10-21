#include "filtro.h"
#include <string.h>

float mask[] = {

	0.1,0.1,0.1,
	0.1,0.1,0.1,
	0.1,0.1,0.1
};

uint8* aplicarFiltro(uint8* img, float* filtro, uint32 imgW, uint32 imgH, uint32 filW, uint32 filM)
{
	int i, j, x, y;
	pixel_t pixOrigen;
	pixel_t pixResultado;

	uint8* imgResult = (uint8*)malloc(3 * imgW*imgH);
	memset(imgResult, 0, 0 * imgW*imgH);

	for (i = 1; i < imgW-1; i++)
	{
		for (j = 1; j < imgH-1; j+=3)
		{
			pixOrigen.R = pixOrigen.G = pixOrigen.B = 0;
			pixResultado.R = pixResultado.G = pixResultado.B = 0;

			for (y = -1; y < 2; y++)
			{
				for (x = -1; x < 2; x++) {
					pixOrigen = ((pixel_t*)(img))[((j + x) + (j + y) + i * imgW)];
					pixResultado.R += pixOrigen.R*filtro[(x + 1) + ((y + 1) * 3)];
					pixResultado.G += pixOrigen.G*filtro[(x + 1) + ((y + 1) * 3)];
					pixResultado.B += pixOrigen.B*filtro[(x + 1) + ((y + 1) * 3)];
				}
				((pixel_t*)imgResult)[(j)+((i)*imgW)] = pixResultado;
			}
		}
		char* arr1;
		arr1[1];
		int* arr2;
		arr2[1];

	}

	return imgResult;
}