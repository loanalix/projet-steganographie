#pragma once
#include <windows.h>
#include "BMPModifier.h"

class ImageLoader {
public:
    BMPModifier* imgOrigin;
    BMPModifier* imgModified;

    void LoadImg(const char* path, BMPModifier* bmpModifier, HWND hWnd);
    void LoadImgTxt(HWND hWnd, string text);
};