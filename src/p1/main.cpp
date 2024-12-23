#include "pch.h"

#include "Window.h"
#include "main.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Initialiser la fenêtre
    if (!Window::InitWindow(hInstance, nCmdShow)) {
        return FALSE;
    }

    //boucle de messages principal 
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) { 
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}