#include "BitMap.h"

BitMap::BitMap(const char* fn)
{
	FILE * pFile;
	fopen_s(&pFile, fn, "rb");
	SMALL_ENDIAN = true;

	if (!pFile)
	{
		throw "The system cannot find the requested file!";
	}

	getFileHeader(pFile);

	getDIBHeader(pFile);

	getPixelArray(pFile);

	fclose(pFile);

}

void BitMap::getFileHeader(FILE* file)
{
	//set the pointer to the start
	fseek(file, 0, SEEK_SET);

	//create buffer for the file-header
	file_header = new unsigned char[FILE_HEADER_LENGTH];

	//fill the file-header
	for (int i = 0; i < FILE_HEADER_LENGTH; i++)
	{
		file_header[i] = fgetc(file);
	}

	bfType[0] = file_header[0];
	bfType[1] = file_header[1];

	filesize = assignValue(file_header, 2, 4);
	bfOffBits = assignValue(file_header, 10, 4);
}

void BitMap::getDIBHeader(FILE* file)
{
	fseek(file, FILE_HEADER_LENGTH, SEEK_SET);
	const int headerLength = bfOffBits - FILE_HEADER_LENGTH;

	dib_header = new unsigned char[headerLength];

	switch (headerLength)
	{
	case 40:
		getBitmapInfoHeader(file);
		break;
	case 52:
		getBitmapV2InfoHeader(file);
		break;
	case 56:
		getBitmapV3InfoHeader(file);
		break;
	case 108:
		getBitmapV4Header(file);
		break;
	case 124:
		getBitmapV5Header(file);
		break;
	}
}

void BitMap::getPixelArray(FILE* file)
{
	/*
	
		Currently only works for the 24bpp format
		Remember its BGR and left->right, bot->top
	
	*/

	//Go to the start of the pixel array
	fseek(file, bfOffBits, SEEK_SET);

	const int amtBytes = biWidth * (biBitCount / 8) * biHeight;

	pixels = new unsigned char[amtBytes];

	const int charsPerCol = biWidth * 3 + padding;
	for (int row = biHeight - 1; row >= 0; row--)
	{
		for (int col = 0; col < charsPerCol; col++)
		{
			if (col < biWidth * 3)
			{
				pixels[row * charsPerCol + col] = fgetc(file);
			}
		}
	}
}

void BitMap::logBitmapInformation()
{
	cout << "Identifier: " << bfType << endl;
	cout << "Filesize: " << filesize << " bytes" << endl;
	cout << "Reserved 1: " << getReserved1() << endl;
	cout << "Reserved 2: " << getReserved2() << endl;
	cout << "Offset: " << bfOffBits << " bytes" << endl;

	cout << "\nHeader size (>= 40): " << headersize << " bytes" << endl;
	cout << "Image width: " << biWidth << " px" << endl;
	cout << "Image height: " << biHeight << " px" << endl;
	cout << "Planes (Must be 1): " << getPlanes() << endl;
	cout << "Bits per pixel: " << biBitCount << endl;
	cout << "Compression type: " << getCompression() << endl;
	cout << "Image Size x3: " << getImageSize() << " bytes" << endl;
	cout << "Pref. res. in px/m (X): " << getPixelPerMeterX() << " px/m" << endl;
	cout << "Pref. res. in px/m (Y): " << getPixelPerMeterY() << " px/m" << endl;
	cout << "Used Color Map entries: " << getUsedColors() << endl;
	cout << "Significant colors: " << getImportantColors() << endl;
	cout << "Padding: " << padding << endl;
}

void BitMap::logPixels()
{
	const int amtBytes = biWidth * (biBitCount / 8) * biHeight;
	
	int colCounter = 1;
	for (int i = 0; i < amtBytes - 2; i += 3)
	{
		printf("(%d,%d,%d)",pixels[i], pixels[i + 1], pixels[i + 2]);
		if (colCounter++ == biWidth)
		{
			colCounter = 1;
			cout << endl;
		}
	}
	
	//printf("first (%d,%d,%d) \n", pixels[0], pixels[1], pixels[2]);
	//printf("last  (%d,%d,%d) \n", pixels[amtBytes - 3], pixels[amtBytes - 1], pixels[amtBytes - 1]);
}

bool BitMap::hasMinHeaderLength()
{
	return (bfOffBits >= MIN_HEADER_LENGTH);
}

int32_t BitMap::assignValue(unsigned char* data, int offset, int bytes)
{
	int32_t result;
	if (SMALL_ENDIAN)
	{
		result = data[offset + bytes - 1];
		for (int i = offset + bytes - 2; i >= offset; i--)
		{
			result = result << 8 | data[i];
		}
	}
	else {
		result = data[offset];
		for (int i = offset + 1; i < offset + bytes; i++)
		{
			result = result << 8 | data[i];
		}
	}
	return result;

}


//Save the Bitmap and export it
void BitMap::save(const char* fn)
{
	FILE* pFile;
	fopen_s(&pFile, fn, "wb");
	
	if (!pFile)
	{
		return;
	}
	
	writeFileHeader(pFile);
	writeDIBHeader(pFile);
	writePixelData(pFile);
	//didnt bother with the ICC Color Profile xD

	fclose(pFile);
}

void BitMap::extractChars(FILE* pFile, int num, int bytes)
{
	char c = num & 255;
	fputc(c, pFile);
	for (int i = 1; i < bytes; i++)
	{
		num >>= 8;
		c = num & 255;
		fputc(c, pFile);
	}
}

int32_t BitMap::getFileSize()
{
	return filesize;
}

int32_t BitMap::getHeaderSize()
{
	return headersize;
}

int32_t BitMap::getWidth()
{
	return biWidth;
}

int32_t BitMap::getHeight()
{
	return biHeight;
}

int32_t BitMap::getPlanes()
{
	return assignValue(dib_header, 12, 2);
}

int32_t BitMap::getBitCount()
{
	return biBitCount;
}

int32_t BitMap::getOffBits()
{
	return bfOffBits;
}

int32_t BitMap::getCompression()
{
	return assignValue(dib_header, 16, 4);
}

int32_t BitMap::getImageSize()
{
	return assignValue(dib_header, 20, 4);
}

int32_t BitMap::getPixelPerMeterX()
{
	return assignValue(dib_header, 24, 4);
}

int32_t BitMap::getPixelPerMeterY()
{
	return assignValue(dib_header, 28, 4);
}

int32_t BitMap::getUsedColors()
{
	return assignValue(dib_header, 32, 4);
}

int32_t BitMap::getImportantColors()
{
	return assignValue(dib_header, 36, 4);
}

int32_t BitMap::getPadding()
{
	return padding;
}

int32_t BitMap::getReserved1()
{
	return assignValue(file_header, 6, 2);
}

int32_t BitMap::getReserved2()
{
	return assignValue(file_header, 8, 2);
}

char* BitMap::getType()
{
	return bfType;
}


int32_t BitMap::getBitmaskRed()
{
	return bitmask_red;
}

int32_t BitMap::getBitmaskGreen()
{
	return bitmask_green;
}

int32_t BitMap::getBitmaskBlue()
{
	return bitmask_blue;
}

unsigned char* BitMap::getColorspaceType()
{
	//only works if the dib_header is V4 or V5
	unsigned char LCS_WINDOWS_COLOR_SPACE[4];
	LCS_WINDOWS_COLOR_SPACE[0] = dib_header[73];
	LCS_WINDOWS_COLOR_SPACE[1] = dib_header[72];
	LCS_WINDOWS_COLOR_SPACE[2] = dib_header[71];
	LCS_WINDOWS_COLOR_SPACE[3] = dib_header[70];

	return LCS_WINDOWS_COLOR_SPACE;
}

unsigned char* BitMap::getColorspaceEndpoints()
{
	//only works if the dib_header is V4 or V5
	unsigned char CSEndpoints[36];
	for (int i = 0; i < 36; i++)
	{
		CSEndpoints[i] = dib_header[74 + i];
	}
	return CSEndpoints;
}

void BitMap::getBitmapInfoHeader(FILE* file)
{
	//fill the file-header
	for (int i = 0; i < BITMAPINFOHEADER_LENGTH; i++)
	{
		dib_header[i] = fgetc(file);
		//std::cout << (int)dib_header[i] << " ";
	}

	headersize = assignValue(dib_header, 0, 4);
	biWidth = assignValue(dib_header, 4, 4);
	biHeight = assignValue(dib_header, 8, 4);
	biBitCount = assignValue(dib_header, 14, 2);
	padding = (biWidth * (biBitCount / 8)) % 4;
}

void BitMap::getBitmapV2InfoHeader(FILE* file)
{
}

void BitMap::getBitmapV3InfoHeader(FILE* file)
{
}

void BitMap::getBitmapV4Header(FILE* file)
{
}

void BitMap::getBitmapV5Header(FILE* file)
{
	//collect the data from the infoheader first because
	//the infoheader is a subset of the other headers
	getBitmapInfoHeader(file); 

	//collect the remaining data from the dib header
	//that is specific to the V5Header
	for (int i = BITMAPINFOHEADER_LENGTH; i < BITMAPV5HEADER_LENGTH; i++)
	{
		dib_header[i] = fgetc(file);
		//std::cout << (int)dib_header[i] << " ";
	}

	//the bitmasks are in big-endian
	SMALL_ENDIAN = false;
	bitmask_red = assignValue(dib_header, 54, 4);
	bitmask_red = assignValue(dib_header, 58, 4);
	bitmask_red = assignValue(dib_header, 62, 4);
	bitmask_red = assignValue(dib_header, 66, 4);
	SMALL_ENDIAN = true;

	icc_colorprofile = new unsigned char[filesize - headersize - getImageSize()];
}

void BitMap::writePixelData(FILE* file)
{
	const int charsPerCol = biWidth * 3 + padding;
	for (int row = biHeight - 1; row >= 0; row--)
	{
		for (int col = 0; col < charsPerCol; col++)
		{
			if (col < biWidth * 3)
			{
				fputc(pixels[row * charsPerCol + col], file);
			}
			else {
				fputc(0x00, file);
			}
		}
	}
}

void BitMap::writeFileHeader(FILE* file)
{
	fwrite(file_header, FILE_HEADER_LENGTH, 1, file);
}

void BitMap::writeDIBHeader(FILE* file)
{
	fwrite(dib_header, headersize, 1, file);
}

