#include "pch.h"
#include"ImageLoader.h"

void ImageLoader::LoadImg(const char* path, BMPModifier* bmpModifier, HWND hWnd)
{
    // Déclaration de la structure pour stocker l'en-tête du fichier bitmap
    tagBITMAPFILEHEADER bitmapFileHeaderData;

    // Déclaration de la structure pour stocker l'en-tête de l'information du bitmap
    bmpModifier->bitmapInfoHeaderData;

    // Appelle la méthode pour lire le fichier BMP et stocker les données dans bmpBuffer
    bmpModifier->bmpBuffer = bmpModifier->ReadBMP(path);

    // Crée un bitmap personnalisé à partir des données lues (les pixels de l'image) et stocke le résultat dans 'bgr'
    bmpModifier->bgr = bmpModifier->CreateBitmapCustom(bmpModifier->bmpBuffer, &bitmapFileHeaderData, &bmpModifier->bitmapInfoHeaderData);


    HDC hdcGet = GetDC(hWnd); // Get the device context for the window

    // Initialiser le BITMAPINFOHEADER
    bmpModifier->info = (BITMAPINFOHEADER)bmpModifier->bitmapInfoHeaderData;

    // Crée un bitmap à partir du tampon de pixels
    bmpModifier->hBitmap = CreateDIBitmap(hdcGet, &bmpModifier->info, CBM_INIT, bmpModifier->bgr, (BITMAPINFO*)&bmpModifier->info, DIB_RGB_COLORS);

    if (bmpModifier->hBitmap) {
        // Crée un contexte de périphérique compatible (DC) pour stocker le bitmap
        bmpModifier->hdcBit = CreateCompatibleDC(hdcGet);
       
        // Sélectionne le bitmap dans le DC compatible
        bmpModifier->hWndDc = GetDC(hWnd);
    }

    ReleaseDC(hWnd, hdcGet);
}

void ImageLoader::LoadImgTxt(HWND hWnd, string text)
{
    // Crée une copie de l'image originale
    imgModified->bmpBuffer = imgOrigin->bmpBuffer;

    // Crée une copie de l'en-tête de l'image originale
    imgModified->bgr = imgOrigin->bgr;

    // Appelle la méthode 'SetText' pour insérer du texte dans l'image 
    imgModified->SetText(text,imgModified->bitmapInfoHeaderData , imgModified->bgr);

    HDC hdcGet = GetDC(hWnd); 

    // Initialiser le BITMAPINFOHEADER
    imgModified->info = (BITMAPINFOHEADER)imgModified->bitmapInfoHeaderData;

    // Crée un bitmap à partir du tampon de pixels
    imgModified->hBitmap = CreateDIBitmap(hdcGet, &imgModified->info, CBM_INIT, imgModified->bgr, (BITMAPINFO*)&imgModified->info, DIB_RGB_COLORS);

    if (imgModified->hBitmap) {
        // Crée un contexte de périphérique compatible (DC) pour stocker le bitmap
        imgModified->hdcBit = CreateCompatibleDC(hdcGet);
        
        // Sélectionne le bitmap dans le DC compatible
        imgModified->hWndDc = GetDC(hWnd);
    }

    ReleaseDC(hWnd, hdcGet);

}