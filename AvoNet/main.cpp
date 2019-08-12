#include "CMatrix.h"
#include "BitMap.h"
#include <iostream>

using namespace std;

int main()
{
	BitMap bm("Images/db.bmp");
	CMatrix cm = bm.getColorMatrix();
	return 0;
}