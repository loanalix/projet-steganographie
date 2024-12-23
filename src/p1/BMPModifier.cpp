#include "pch.h"
#include "BMPModifier.h"
#include <bitset>
#include <iostream>

BMPModifier::BMPModifier()
{

}

//Charger une image
BYTE* BMPModifier::ReadBMP(const char* path) {
    pathImg = path;
    FILE* image = LoadImageCustom(path);
    if (!image) return nullptr;

    int returnCode;
    bmpBuffer = CreateBuffer(image, &returnCode, &lSize);
    fclose(image);

    bgr = bmpBuffer + sizeof(tagBITMAPFILEHEADER) + sizeof(tagBITMAPINFOHEADER);
    return bmpBuffer;
}

//Créer un bitmap à partir d'un buffer
BYTE* BMPModifier::CreateBitmapCustom(BYTE* buffer, tagBITMAPFILEHEADER* bitmapFileData, tagBITMAPINFOHEADER* bitmapInfoData)
{
    memcpy(bitmapFileData, buffer, sizeof(tagBITMAPFILEHEADER));
    memcpy(bitmapInfoData, buffer + sizeof(tagBITMAPFILEHEADER), sizeof(tagBITMAPINFOHEADER));

    return buffer + sizeof(tagBITMAPFILEHEADER) + sizeof(tagBITMAPINFOHEADER);
}