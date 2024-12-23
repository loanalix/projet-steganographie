#pragma once
#include "FileHandler.h"
#include "BitCalculator.h"
#include "ImageProcessor.h"
#include <windows.h>

class BMPReader : public FileHandler, public ImageProcessor {
public:

    BMPReader();

	string ReadText(BITMAPINFOHEADER bitmapInfoHeaderData, BYTE* bgr);

	char ReadPixel(vector<int> color);
};
