#include "Filtro.h"
#include <string.h>

float mask[] = {
	0.1,0.1,0.1,
	0.1,0.1,0.1,
	0.1,0.1,0.1,
};

uint8* aplicarFiltro(uint8* img, float* filtro, uint32 imgW, uint32 imgH, uint32 filW, uint32 filH)
{
	int i, j, x, y;
	pixel_t pixOrig;
	pixel_t pixResult;

	uint8* imgResult = (uint8*)malloc(3 * imgW*imgH);
	memset(imgResult, 0, 3 * imgW*imgH); //inicializa todo a cero

	for (i = 1; i < imgH-1; i++)
	{
		for (j = 1; j < imgW-1; j++)
		{
			pixResult.R = pixResult.G = pixResult.B = 0;
			for (y=-1; y < 2 ; y++)
			{
				for (x = -1; x<2; x++)
				{
					pixOrig = ((pixel_t*)(img))[(j+x) + (i+y) * imgW];
					pixResult.R += pixOrig.R*filtro[(x + 1) + (y + 1) * 3];
					pixResult.G += pixOrig.G*filtro[(x + 1) + (y + 1) * 3];
					pixResult.B += pixOrig.B*filtro[(x + 1) + (y + 1) * 3];
				}
			}
			((pixel_t*)imgResult)[j + i * imgW] = pixResult;
		}
	}
	return imgResult;
}
