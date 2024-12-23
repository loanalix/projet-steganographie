#include "pch.h"
#include "FileHandler.h"

FILE* FileHandler::LoadImageCustom(const char* path)
{
    FILE* image;

    errno_t err = fopen_s(&image, path, "rb");
    if (err != 0)
    {
        std::cout << "Error opening the file\n";
        return nullptr;
    }

    return image;
}

//Créer un buffer pour stocker les données de l'image
BYTE* FileHandler::CreateBuffer(FILE* image, int* returnCode, long* lSize)
{
    *returnCode = fseek(image, 0, SEEK_END);
    *lSize = ftell(image);
    *returnCode = fseek(image, 0, SEEK_SET);

    BYTE* buffer = new BYTE[*lSize];

    size_t result = fread(buffer, sizeof(BYTE), *lSize, image);

    return buffer;
}

//Ecrire un fichier BMP
void FileHandler::WriteBMP(string path, BYTE* buffer, long size)
{
    // Crée une copie de la chaîne 'path' pour la modifier
    std::string originalPath(path);

    // Recherche la dernière occurrence du caractère '.' dans le chemin
    size_t pos = originalPath.find_last_of('.');


    if (pos != std::string::npos) {
        originalPath.insert(pos, "_modified");
    }
    else {
        // If no extension is found, append "_modified" to the filename
        originalPath.append("_modified");
    }

    // Convertit la chaîne en const char* pour l'utiliser dans la fonction fopen_s
    const char* modifiedPath = originalPath.c_str();

    FILE* image;
    fopen_s(&image, modifiedPath, "wb");

    if (image != NULL) {
        fwrite(buffer, sizeof(BYTE), size, image);
        fclose(image);
        std::cout << "File saved as " << modifiedPath << "\n";
    }
    else {
        std::cout << "Error writing the file\n";
    }
}
