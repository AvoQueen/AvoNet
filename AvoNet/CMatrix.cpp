#include "CMatrix.h"

CMatrix::CMatrix(unsigned char* d, int32_t w, int32_t h) : width(w), height(h)
{
	data = new color* [h]; // h = amount of rows
	int32_t value;

	for (int32_t i = 0; i < h; i++) // w = amount of rows
	{
		data[i] = new color[w];

		for (int32_t j = 0; j < w; j++)
		{
			int index = (i * w + j) * 3;
			data[i][j].blue = d[index];
			data[i][j].green = d[index + 1];
			data[i][j].red = d[index + 2];
			data[i][j].alpha = 0x00;
		}
	}
}

color* CMatrix::operator[](unsigned int row)
{
	return data[row];
}
