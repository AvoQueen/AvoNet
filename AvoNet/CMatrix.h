#pragma once
#include <cstdint>

typedef union color
{
	int32_t val;
	struct
	{
		unsigned char blue : 8;
		unsigned char green : 8;
		unsigned char red : 8;
		unsigned char alpha : 8;
	};
};

class CMatrix //Color Matrix
{
public:
	CMatrix(unsigned char* pixelData_BGR, int32_t width, int32_t height);

	/*
		Operator overloading for ease of use
	*/
	color* operator[](unsigned int row);

protected:
	color** data;
	int32_t width;
	int32_t height;
private:
};

