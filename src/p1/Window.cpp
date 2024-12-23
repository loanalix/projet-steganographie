#include "pch.h"
#include "Window.h"

#include <windows.h>
#include <commdlg.h>

// D�finition des constantes pour les diff�rents boutons et actions
#define ID_OPEN_FILE             100
#define ID_OPEN_FILE_MODIFIED    101
#define ID_SUBMIT                102
#define ID_DOWNLOAD              103
#define ID_DECRYPT               104

// D�claration des objets pour la manipulation des images BMP
BMPModifier imgOrigin;
BMPModifier imgModified;
ImageLoader imageloader;

// Dimensions de l'espace pour afficher les images
int leftSpaceWidth = 400;
int leftSpaceHeight = 400;
bool isOrigineInit = false;
int screenWidth;
int screenHeight;

HWND hImageWnd;
HWND hImageWnd2;
HWND hImageWnd3;
HWND hEdit;
HWND hStatic;

WCHAR textToHide[256];// Texte � cacher dans l'image

// Fonction d'initialisation de la fen�tre
bool Window::InitWindow(HINSTANCE hInstance, int nCmdShow) {
    imgOrigin = BMPModifier();
    imgModified = BMPModifier();

    imageloader.imgModified = &imgModified;
    imageloader.imgOrigin = &imgOrigin;

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"MainWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        return false;
    }

    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);

    HWND hWnd = CreateWindow(L"MainWindowClass", L"Sample Window", WS_OVERLAPPEDWINDOW,
        0, 0, screenWidth, screenHeight, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd) {
        return false;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return true;
}

// Fonction de gestion des messages de la fen�tre
LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        // Gestion du bouton "Ouvrir un fichier" pour s�lectionner une image BMP
        if (wmId == ID_OPEN_FILE) {
            OPENFILENAME ofn; // Structure pour la bo�te de dialogue de s�lection de fichier
            wchar_t szFile[260] = { 0 };// Variable pour stocker le chemin du fichier s�lectionn�

            // Initialisation de la structure de la bo�te de dialogue
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hWnd;
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrFilter = L"BMP Files\0*.bmp\0All Files\0*.*\0";// Filtre pour les fichiers BMP
            ofn.nFilterIndex = 1;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetOpenFileName(&ofn) == TRUE) {
                // Convertir wchar_t* en std::string avec l'encodage UTF-8
                int size_needed = WideCharToMultiByte(CP_UTF8, 0, ofn.lpstrFile, -1, NULL, 0, NULL, NULL);
                std::string strFile(size_needed, 0);
                WideCharToMultiByte(CP_UTF8, 0, ofn.lpstrFile, -1, &strFile[0], size_needed, NULL, NULL);
                const char* filePath = strFile.c_str();

                // Charger l'image BMP s�lectionn�e
                imageloader.LoadImg(filePath, &imgOrigin, hWnd);

                HDC hdcSubWindow = GetDC(hImageWnd);

                SelectObject(imgOrigin.hdcBit, imgOrigin.hBitmap); 

                //Ajustement de l'image � la taille de l'espace d'affichage
                StretchBlt(hdcSubWindow, 0, 0, leftSpaceWidth, leftSpaceHeight, imgOrigin.hdcBit, 0, 0, imgOrigin.info.biWidth, imgOrigin.info.biHeight, SRCCOPY); 


                ReleaseDC(hImageWnd, hdcSubWindow);

                isOrigineInit = true;
            }
        }else if (wmId == ID_OPEN_FILE_MODIFIED) {
            // Open file dialog to select BMP file
            OPENFILENAME ofn;
            wchar_t szFile[260] = { 0 };

            // Initialisation de la structure de la bo�te de dialogue
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hWnd;
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrFilter = L"BMP Files\0*.bmp\0All Files\0*.*\0";// Filtre pour les fichiers BMP
            ofn.nFilterIndex = 1;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetOpenFileName(&ofn) == TRUE) {
                // Convertir wchar_t* en std::string avec l'encodage UTF-8
                int size_needed = WideCharToMultiByte(CP_UTF8, 0, ofn.lpstrFile, -1, NULL, 0, NULL, NULL);
                std::string strFile(size_needed, 0);
                WideCharToMultiByte(CP_UTF8, 0, ofn.lpstrFile, -1, &strFile[0], size_needed, NULL, NULL);
                const char* filePath = strFile.c_str();

                // Charger l'image BMP s�lectionn�e
                imageloader.LoadImg(filePath, &imgModified, hWnd);

                HDC hdcSubWindow = GetDC(hImageWnd3);

                SelectObject(imgModified.hdcBit, imgModified.hBitmap);

                //Ajustement de l'image � la taille de l'espace d'affichage
                StretchBlt(hdcSubWindow, 0, 0, leftSpaceWidth, leftSpaceHeight, imgModified.hdcBit, 0, 0, imgModified.info.biWidth, imgModified.info.biHeight, SRCCOPY);


                ReleaseDC(hImageWnd3, hdcSubWindow);

                isOrigineInit = true;
            }
        }
        else if (wmId == ID_SUBMIT) {
            if (!isOrigineInit)
            {
                break;
            }

            imgModified = imgOrigin;

            HDC hdcSubWindow = GetDC(hImageWnd2);
            GetWindowText(hEdit, textToHide, 256);


            wstring ws(textToHide);
            string str(ws.begin(), ws.end());

            imageloader.LoadImgTxt(hWnd, str);

            HDC hdcSubWindow2 = GetDC(hImageWnd2);

            // Load and display the selected BMP file
            SelectObject(imgModified.hdcBit, imgModified.hBitmap);
            StretchBlt(hdcSubWindow2, 0, 0, leftSpaceWidth, leftSpaceHeight, imgModified.hdcBit, 0, 0, imgModified.info.biWidth, imgModified.info.biHeight, SRCCOPY);
        }
        else if (wmId == ID_DOWNLOAD) {
            FileHandler handler = FileHandler();

            handler.WriteBMP(imgModified.pathImg, imgModified.bmpBuffer, imgModified.lSize);
        }
        else if (wmId == ID_DECRYPT) {
            BMPReader bmpReader = BMPReader();

            string str = bmpReader.ReadText(imgModified.bitmapInfoHeaderData, imgModified.bgr);

            std::wstring stemp = std::wstring(str.begin(), str.end());
            LPCWSTR sw = stemp.c_str();

            SetWindowText(hStatic, sw);
        }
        break;
    }
    case WM_CREATE:
    {

        //Interface en haut � gauche 
        CreateWindow(L"BUTTON", L"OPEN FILE", WS_VISIBLE | WS_CHILD,
            60, 110, 100, 50, hWnd, (HMENU)ID_OPEN_FILE,
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

        CreateWindow(L"BUTTON", L"SUBMIT", WS_VISIBLE | WS_CHILD,
            570, 200, 100, 50, hWnd, (HMENU)ID_SUBMIT,
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

        hEdit = CreateWindow(L"EDIT", L"test", WS_VISIBLE | WS_CHILD | WS_DLGFRAME | ES_LEFT | ES_AUTOVSCROLL | ES_MULTILINE,
            60, 200, 500, 100, hWnd, nullptr,
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

		//Rendu de l'image et appercus de l'image modifier 

        hImageWnd = CreateWindow(L"Static", L"", WS_VISIBLE | WS_CHILD,
            850, 50, leftSpaceWidth, leftSpaceHeight, hWnd, nullptr,
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

        hImageWnd2 = CreateWindow(L"Static", L"", WS_VISIBLE | WS_CHILD,
            1450, 50, leftSpaceWidth, leftSpaceHeight, hWnd, nullptr,
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

        //bouton de t�lechargement 
        CreateWindow(L"BUTTON", L"DOWNLOAD", WS_VISIBLE | WS_CHILD,
            1300, 200, 100, 50, hWnd, (HMENU)ID_DOWNLOAD,
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);


        //Interface en bas � gauche
        CreateWindow(L"BUTTON", L"OPEN FILE", WS_VISIBLE | WS_CHILD,
            60, 550, 100, 50, hWnd, (HMENU)ID_OPEN_FILE_MODIFIED,
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

        hStatic = CreateWindow(L"Static", L"", WS_VISIBLE | WS_CHILD | WS_DLGFRAME | ES_LEFT,
            60, 650, 500, 100, hWnd, nullptr,
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

        CreateWindow(L"BUTTON", L"DECRYPTE", WS_VISIBLE | WS_CHILD,
            200, 550, 100, 50, hWnd, (HMENU)ID_DECRYPT,
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

        //appercu de l'image modifier 
        hImageWnd3 = CreateWindow(L"Static", L"", WS_VISIBLE | WS_CHILD,
            850, 550, leftSpaceWidth, leftSpaceHeight, hWnd, nullptr,
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

        break;
    }
    case WM_SIZE:
    {


    }
    case WM_PAINT:
	    {
	        PAINTSTRUCT ps;
	        HDC hdc = BeginPaint(hWnd, &ps);

	        // Set the pen and brush for drawing
	        HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // Black pen
	        HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0)); // Red brush

	        // Select the pen and brush into the device context
	        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	        // Draw the rectangle
	        Rectangle(hdc, 0, 500, screenWidth, 505);

	        // Restore the old pen and brush
	        SelectObject(hdc, hOldPen);
	        SelectObject(hdc, hOldBrush);

	        // Clean up
	        DeleteObject(hPen);
	        DeleteObject(hBrush);

	        EndPaint(hWnd, &ps);
	        break;
	    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

