#pragma once
#include <stdio.h>
#include <iostream>
#include "CMatrix.h"


using namespace std;

constexpr int FILE_HEADER_LENGTH = 14;
constexpr int MIN_DIB_HEADER_LENGTH = 40;
constexpr int MIN_HEADER_LENGTH = 54;

constexpr int BITMAPCOREHEADER_LENGTH = 12;
constexpr int OS21XBITMAPHEADER_LENGTH	= 12;
constexpr int OS22XBITMAPHEADER_LENGTH = 16 | 64;
constexpr int BITMAPINFOHEADER_LENGTH = 40;
constexpr int BITMAPV2INFOHEADER_LENGTH = 52;
constexpr int BITMAPV3INFOHEADER_LENGTH = 56;
constexpr int BITMAPV4HEADER_LENGTH = 108;
constexpr int BITMAPV5HEADER_LENGTH = 124;


class BitMap {
public:
	BitMap(const char* filename);

	void getFileHeader(FILE* file);
	void getDIBHeader(FILE* file);
	void getPixelArray(FILE* file);

	void logBitmapInformation();
	void logPixels();
	void extractChars(FILE* pFile, int num, int bytes);

	bool hasMinHeaderLength();

	int32_t assignValue(unsigned char* data, int offset, int bytes);

	void save(const char* filename);


	//Standard functions that can be used with most bitmaps 54byte header
	int32_t getFileSize();
	int32_t getHeaderSize();
	int32_t getWidth();
	int32_t getHeight();
	int32_t getPlanes();
	int32_t getBitCount();
	int32_t getOffBits();
	int32_t getCompression();
	int32_t getImageSize();
	int32_t getPixelPerMeterX();
	int32_t getPixelPerMeterY();
	int32_t getUsedColors();
	int32_t getImportantColors();
	int32_t getPadding();
	int32_t getReserved1();
	int32_t getReserved2();
	char* getType();

	//Extra functions that can be used with bitmaps with larger headers > 54 bytes
	int32_t getBitmaskRed();
	int32_t getBitmaskGreen();
	int32_t getBitmaskBlue();

	unsigned char* getColorspaceType();
	unsigned char* getColorspaceEndpoints();

	//Yes
	CMatrix getColorMatrix()
	{
		return CMatrix(pixels, biWidth, biHeight);
	}

protected:
	bool SMALL_ENDIAN;

private:
	//general data
	unsigned char* pixels;
	unsigned char* file_header;
	unsigned char* dib_header;
	unsigned char* icc_colorprofile;
	char bfType[2];

	//padding to make the amount of columns devisable by 4
	short int padding;

	//fileheader + infoheader specific data
	int32_t filesize; //filesize
	int32_t headersize; //headersize

	int32_t bfOffBits;
	int32_t biBitCount;
	
	int32_t biWidth;
	int32_t biHeight;

	//these variables are not present in all header types
	//!!The bitmasks are not in small-endian format!!
	int32_t bitmask_red;
	int32_t bitmask_green;
	int32_t bitmask_blue;
	

	//internal functions to retrieve dibheader data
	void getBitmapInfoHeader(FILE* file);
	void getBitmapV2InfoHeader(FILE* file);
	void getBitmapV3InfoHeader(FILE* file);
	void getBitmapV4Header(FILE* file);
	void getBitmapV5Header(FILE* file);

	//internal functions to save the bitmap
	void writePixelData(FILE* file);
	void writeFileHeader(FILE* file);
	void writeDIBHeader(FILE* file);
};

