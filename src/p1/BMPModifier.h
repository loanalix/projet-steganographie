#pragma once
#include "FileHandler.h"
#include "ImageProcessor.h"
#include <windows.h>

class BMPModifier : public FileHandler, public ImageProcessor {
public:
    string pathImg;
    long lSize;
    BYTE* bgr;
    BYTE* bmpBuffer;
    tagBITMAPINFOHEADER bitmapInfoHeaderData;
    BITMAPINFOHEADER info;
    HBITMAP hBitmap = nullptr;
    HDC hdcBit;
    HDC hWndDc;

    BMPModifier();
    BYTE* ReadBMP(const char* path);
    BYTE* CreateBitmapCustom(BYTE* buffer, tagBITMAPFILEHEADER* fileHeader, tagBITMAPINFOHEADER* infoHeader);
};
