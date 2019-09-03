#include "Raster.h"
#include <string>


int main()
{
	rs::iRaster r1 = rs::iRaster::Identity(3, 3);
	rs::iRaster v1 = rs::iRaster::Random(3, 1);

	r1.print();
	std::cout << std::endl;
	v1.print();

	return 0;
}