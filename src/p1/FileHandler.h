#pragma once
#include <stdio.h>
#include <iostream>

using namespace std;

class FileHandler {
public:
    FILE* LoadImageCustom(const char* path);
    BYTE* CreateBuffer(FILE* image, int* returnCode, long* size);
    void WriteBMP(string path, BYTE* buffer, long size);
};
