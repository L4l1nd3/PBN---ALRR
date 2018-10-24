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

	for (i = 0; i < imgH; i++)
	{
		
		for (j = 0; j < imgW; j++)
		{
			pixResult.R = pixResult.G = pixResult.B = 0;

			//ESQUINA INFERIOR IZQUIERDA
			if (j == 0 && i == 0  )	
			{

				for (y = 0; y < 2; y++)
				{
					for (x = 0; x < 2; x++)
					{
						pixOrig = ((pixel_t*)(img))[(j + x) + (i + y) * imgW];
						pixResult.R += pixOrig.R*filtro[(x + 1) + (y + 1) * 3];
						pixResult.G += pixOrig.G*filtro[(x + 1) + (y + 1) * 3];
						pixResult.B += pixOrig.B*filtro[(x + 1) + (y + 1) * 3];
					}
				}
			}
			////////////////////////////

			//ESQUINA INFERIOR DERECHA
			else if (j == imgW && i == 0)
			{
				for (y = 0; y < 2; y++)
				{
					for (x = -1; x < 1; x++)
					{
						pixOrig = ((pixel_t*)(img))[(j + x) + (i + y) * imgW];
						pixResult.R += pixOrig.R*filtro[(x + 1) + (y + 1) * 3];
						pixResult.G += pixOrig.G*filtro[(x + 1) + (y + 1) * 3];
						pixResult.B += pixOrig.B*filtro[(x + 1) + (y + 1) * 3];
					}
				}
			}
			/////////////////////////////

			//ESQUINA SUPERIOR IZQUIERDA
			else if (j == 0 && i == imgH)
			{
				for (y = -1; y < 1; y++)
				{
					for (x = 0; x < 2; x++)
					{
						pixOrig = ((pixel_t*)(img))[(j + x) + (i + y) * imgW];
						pixResult.R += pixOrig.R*filtro[(x + 1) + (y + 1) * 3];
						pixResult.G += pixOrig.G*filtro[(x + 1) + (y + 1) * 3];
						pixResult.B += pixOrig.B*filtro[(x + 1) + (y + 1) * 3];
					}
				}
			}
			////////////////////////////

			//ESQUINA SUPERIOR DERECHA
			else if (j == imgW && i == imgH)
			{
				for (y = -1; y < 1; y++)
				{
					for (x = -1; x < 1; x++)
					{
						pixOrig = ((pixel_t*)(img))[(j + x) + (i + y) * imgW];
						pixResult.R += pixOrig.R*filtro[(x + 1) + (y + 1) * 3];
						pixResult.G += pixOrig.G*filtro[(x + 1) + (y + 1) * 3];
						pixResult.B += pixOrig.B*filtro[(x + 1) + (y + 1) * 3];
					}
				}
			}
			/////////////////////////////

			//LADO INFERIOR
			else if (i == 0 /*&& j != 0 && j!= imgH*/)		
			{
				for (y = 0; y < 2; y++)
				{
					for (x = -1; x < 2; x++)
					{
						pixOrig = ((pixel_t*)(img))[(j + x) + (i + y) * imgW];
						pixResult.R += pixOrig.R*filtro[(x + 1) + (y + 1) * 3];
						pixResult.G += pixOrig.G*filtro[(x + 1) + (y + 1) * 3];
						pixResult.B += pixOrig.B*filtro[(x + 1) + (y + 1) * 3];
					}
				}
			}
			////////////////////////////

			//LADO SUPERIOR
			else if (i == imgH /*&& j != 0 && j != imgH*/)		
			{

				for (y = -1; y < 1; y++)
				{
					for (x = -1; x < 2; x++)
					{
						pixOrig = ((pixel_t*)(img))[(j + x) + (i + y) * imgW];
						pixResult.R += pixOrig.R*filtro[(x + 1) + (y + 1) * 3];
						pixResult.G += pixOrig.G*filtro[(x + 1) + (y + 1) * 3];
						pixResult.B += pixOrig.B*filtro[(x + 1) + (y + 1) * 3];
					}
				}
				
			}
			////////////////////////////

			//LADO DERECHO
			else if (j == imgW-1 /*&& i != 0 && i != imgH*/)
			{
				for (y = -1; y < 2; y++)
				{
					for (x = -1; x < 1; x++)
					{
						pixOrig = ((pixel_t*)(img))[(j + x) + (i + y) * imgW];
						pixResult.R += pixOrig.R*filtro[(x + 1) + (y + 1) * 3];
						pixResult.G += pixOrig.G*filtro[(x + 1) + (y + 1) * 3];
						pixResult.B += pixOrig.B*filtro[(x + 1) + (y + 1) * 3];
					}
				}
			}
			////////////////////////////

			//LADO IZQUIERDO
			else if (j == 0 /*&& j != 0 && j != imgH*/)
			{
				for (y = -1; y < 2; y++)
				{
					for (x = 0; x < 2; x++)
					{
						pixOrig = ((pixel_t*)(img))[(j + x) + (i + y) * imgW];
						pixResult.R += pixOrig.R*filtro[(x + 1) + (y + 1) * 3];
						pixResult.G += pixOrig.G*filtro[(x + 1) + (y + 1) * 3];
						pixResult.B += pixOrig.B*filtro[(x + 1) + (y + 1) * 3];
					}
				}
			}
			////////////////////////////

			else
			{
				for (y = -1; y < 2; y++)
				{
					for (x = -1; x < 2; x++)
					{
						pixOrig = ((pixel_t*)(img))[(j + x) + (i + y) * imgW];
						pixResult.R += pixOrig.R*filtro[(x + 1) + (y + 1) * 3];
						pixResult.G += pixOrig.G*filtro[(x + 1) + (y + 1) * 3];
						pixResult.B += pixOrig.B*filtro[(x + 1) + (y + 1) * 3];
					}
				}
			}
			
			((pixel_t*)imgResult)[j + i * imgW] = pixResult; ////////////////////////
		}
	}
	return imgResult;
}

void aplicarFiltroConThreads(void* parameters)
{
	params*datos = (params*)parameters;
	
	uint32 imgW = datos->imgW;
	uint32 imgH = datos->imgH;
	float* filtro = datos->filtro;
	uint8* img = datos->img;

	int i, j, x, y;
	pixel_t pixOrig;
	pixel_t pixResult;

	uint8* imgResult = /*Datos->imgResult + Datos->threadID*/ (uint8*)malloc(3 * imgW*imgH);
	memset(imgResult, 0, 3 * imgW*imgH); //inicializa todo a cero

	for (i = 0; i < imgH; i++)
	{
		for (j = 0; j < imgW; j++)
		{
			pixResult.R = pixResult.G = pixResult.B = 0;

			//ESQUINA INFERIOR IZQUIERDA
			if (j == 0 && i == 0 && datos->threadID == 0)
			{

				for (y = 0; y < 2; y++)
				{
					for (x = 0; x < 2; x++)
					{
						pixOrig = ((pixel_t*)(img))[(j + x) + (i + y) * imgW];
						pixResult.R += pixOrig.R*filtro[(x + 1) + (y + 1) * 3];
						pixResult.G += pixOrig.G*filtro[(x + 1) + (y + 1) * 3];
						pixResult.B += pixOrig.B*filtro[(x + 1) + (y + 1) * 3];
					}
				}
			}
			////////////////////////////

			//ESQUINA INFERIOR DERECHA
			else if (j == imgW && i == 0 && datos->threadID == 0)
			{
				for (y = 0; y < 2; y++)
				{
					for (x = -1; x < 1; x++)
					{
						pixOrig = ((pixel_t*)(img))[(j + x) + (i + y) * imgW];
						pixResult.R += pixOrig.R*filtro[(x + 1) + (y + 1) * 3];
						pixResult.G += pixOrig.G*filtro[(x + 1) + (y + 1) * 3];
						pixResult.B += pixOrig.B*filtro[(x + 1) + (y + 1) * 3];
					}
				}
			}
			/////////////////////////////

			//ESQUINA SUPERIOR IZQUIERDA
			else if (j == 0 && i == imgH && datos->threadID == datos->num_total_threads)
			{
				for (y = -1; y < 1; y++)
				{
					for (x = 0; x < 2; x++)
					{
						pixOrig = ((pixel_t*)(img))[(j + x) + (i + y) * imgW];
						pixResult.R += pixOrig.R*filtro[(x + 1) + (y + 1) * 3];
						pixResult.G += pixOrig.G*filtro[(x + 1) + (y + 1) * 3];
						pixResult.B += pixOrig.B*filtro[(x + 1) + (y + 1) * 3];
					}
				}
			}
			////////////////////////////

			//ESQUINA SUPERIOR DERECHA
			else if (j == imgW && i == imgH && datos->threadID == datos->num_total_threads)
			{
				for (y = -1; y < 1; y++)
				{
					for (x = -1; x < 1; x++)
					{
						pixOrig = ((pixel_t*)(img))[(j + x) + (i + y) * imgW];
						pixResult.R += pixOrig.R*filtro[(x + 1) + (y + 1) * 3];
						pixResult.G += pixOrig.G*filtro[(x + 1) + (y + 1) * 3];
						pixResult.B += pixOrig.B*filtro[(x + 1) + (y + 1) * 3];
					}
				}
			}
			/////////////////////////////

			//LADO INFERIOR
			else if (i == 0 && datos->threadID == 0 /*&& j != 0 && j!= imgH*/)
			{
				for (y = 0; y < 2; y++)
				{
					for (x = -1; x < 2; x++)
					{
						pixOrig = ((pixel_t*)(img))[(j + x) + (i + y) * imgW];
						pixResult.R += pixOrig.R*filtro[(x + 1) + (y + 1) * 3];
						pixResult.G += pixOrig.G*filtro[(x + 1) + (y + 1) * 3];
						pixResult.B += pixOrig.B*filtro[(x + 1) + (y + 1) * 3];
					}
				}
			}
			////////////////////////////

			//LADO SUPERIOR
			else if (i == imgH && datos->threadID == datos->num_total_threads/*&& j != 0 && j != imgH*/)
			{

				for (y = -1; y < 1; y++)
				{
					for (x = -1; x < 2; x++)
					{
						pixOrig = ((pixel_t*)(img))[(j + x) + (i + y) * imgW];
						pixResult.R += pixOrig.R*filtro[(x + 1) + (y + 1) * 3];
						pixResult.G += pixOrig.G*filtro[(x + 1) + (y + 1) * 3];
						pixResult.B += pixOrig.B*filtro[(x + 1) + (y + 1) * 3];
					}
				}

			}
			////////////////////////////

			//LADO DERECHO
			else if (j == imgW - 1 /*&& i != 0 && i != imgH*/)
			{
				for (y = -1; y < 2; y++)
				{
					for (x = -1; x < 1; x++)
					{
						pixOrig = ((pixel_t*)(img))[(j + x) + (i + y) * imgW];
						pixResult.R += pixOrig.R*filtro[(x + 1) + (y + 1) * 3];
						pixResult.G += pixOrig.G*filtro[(x + 1) + (y + 1) * 3];
						pixResult.B += pixOrig.B*filtro[(x + 1) + (y + 1) * 3];
					}
				}
			}
			////////////////////////////

			//LADO IZQUIERDO
			else if (j == 0 /*&& j != 0 && j != imgH*/)
			{
				for (y = -1; y < 2; y++)
				{
					for (x = 0; x < 2; x++)
					{
						pixOrig = ((pixel_t*)(img))[(j + x) + (i + y) * imgW];
						pixResult.R += pixOrig.R*filtro[(x + 1) + (y + 1) * 3];
						pixResult.G += pixOrig.G*filtro[(x + 1) + (y + 1) * 3];
						pixResult.B += pixOrig.B*filtro[(x + 1) + (y + 1) * 3];
					}
				}
			}
			////////////////////////////

			else
			{
				for (y = -1; y < 2; y++)
				{
					for (x = -1; x < 2; x++)
					{
						pixOrig = ((pixel_t*)(img))[(j + x) + (i + y) * imgW];
						pixResult.R += pixOrig.R*filtro[(x + 1) + (y + 1) * 3];
						pixResult.G += pixOrig.G*filtro[(x + 1) + (y + 1) * 3];
						pixResult.B += pixOrig.B*filtro[(x + 1) + (y + 1) * 3];
					}
				}
			}

			((pixel_t*)imgResult)[j + i * imgW] = pixResult; ////////////////////////
		}
	}
	datos->imgResult = imgResult; 
}
