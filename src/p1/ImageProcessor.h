#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <bitset>
#include "BitCalculator.h"

using namespace std;

class ImageProcessor {
public:
    virtual HBITMAP CreateBitmapFromBuffer(BYTE* buffer, int width, int height, int bitsPerPixel);
    virtual void SetText(string text, BITMAPINFOHEADER bitmapInfoHeaderData, BYTE* bgr);
    vector<int> ChangePixel(vector<int> color, int bit, bool isLast);
    int CharToBits(char* letter);
};




