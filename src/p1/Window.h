#pragma once

#include <windows.h>
#include "BMPModifier.h"
#include "BMPReader.h"

#include "ImageLoader.h"

class Window {
public:
    HWND hWnd;
    ImageLoader imageLoader;

    static bool InitWindow(HINSTANCE hInstance, int nCmdShow);
    static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
};