#include "pch.h"
#include"ImageLoader.h"

void ImageLoader::LoadImg(const char* path, BMPModifier* bmpModifier, HWND hWnd)
{
    // D�claration de la structure pour stocker l'en-t�te du fichier bitmap
    tagBITMAPFILEHEADER bitmapFileHeaderData;

    // D�claration de la structure pour stocker l'en-t�te de l'information du bitmap
    bmpModifier->bitmapInfoHeaderData;

    // Appelle la m�thode pour lire le fichier BMP et stocker les donn�es dans bmpBuffer
    bmpModifier->bmpBuffer = bmpModifier->ReadBMP(path);

    // Cr�e un bitmap personnalis� � partir des donn�es lues (les pixels de l'image) et stocke le r�sultat dans 'bgr'
    bmpModifier->bgr = bmpModifier->CreateBitmapCustom(bmpModifier->bmpBuffer, &bitmapFileHeaderData, &bmpModifier->bitmapInfoHeaderData);


    HDC hdcGet = GetDC(hWnd); // Get the device context for the window

    // Initialiser le BITMAPINFOHEADER
    bmpModifier->info = (BITMAPINFOHEADER)bmpModifier->bitmapInfoHeaderData;

    // Cr�e un bitmap � partir du tampon de pixels
    bmpModifier->hBitmap = CreateDIBitmap(hdcGet, &bmpModifier->info, CBM_INIT, bmpModifier->bgr, (BITMAPINFO*)&bmpModifier->info, DIB_RGB_COLORS);

    if (bmpModifier->hBitmap) {
        // Cr�e un contexte de p�riph�rique compatible (DC) pour stocker le bitmap
        bmpModifier->hdcBit = CreateCompatibleDC(hdcGet);
       
        // S�lectionne le bitmap dans le DC compatible
        bmpModifier->hWndDc = GetDC(hWnd);
    }

    ReleaseDC(hWnd, hdcGet);
}

void ImageLoader::LoadImgTxt(HWND hWnd, string text)
{
    // Cr�e une copie de l'image originale
    imgModified->bmpBuffer = imgOrigin->bmpBuffer;

    // Cr�e une copie de l'en-t�te de l'image originale
    imgModified->bgr = imgOrigin->bgr;

    // Appelle la m�thode 'SetText' pour ins�rer du texte dans l'image 
    imgModified->SetText(text,imgModified->bitmapInfoHeaderData , imgModified->bgr);

    HDC hdcGet = GetDC(hWnd); 

    // Initialiser le BITMAPINFOHEADER
    imgModified->info = (BITMAPINFOHEADER)imgModified->bitmapInfoHeaderData;

    // Cr�e un bitmap � partir du tampon de pixels
    imgModified->hBitmap = CreateDIBitmap(hdcGet, &imgModified->info, CBM_INIT, imgModified->bgr, (BITMAPINFO*)&imgModified->info, DIB_RGB_COLORS);

    if (imgModified->hBitmap) {
        // Cr�e un contexte de p�riph�rique compatible (DC) pour stocker le bitmap
        imgModified->hdcBit = CreateCompatibleDC(hdcGet);
        
        // S�lectionne le bitmap dans le DC compatible
        imgModified->hWndDc = GetDC(hWnd);
    }

    ReleaseDC(hWnd, hdcGet);

}