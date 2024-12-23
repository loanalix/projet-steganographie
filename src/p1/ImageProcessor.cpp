#include "pch.h"
#include "ImageProcessor.h"



HBITMAP ImageProcessor::CreateBitmapFromBuffer(BYTE* buffer, int width, int height, int bitsPerPixel) {
    // Prépare la structure BITMAPINFO pour définir les informations du bitmap
    BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(BITMAPINFO));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height; // Hauteur négative pour créer un bitmap en haut vers le bas
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = bitsPerPixel;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = 0;
    // Création d'un contexte de périphérique (HDC) pour gérer les opérations graphiques
    HDC hdc = GetDC(NULL);

    // Crée une section DIB et retourner un HBITMAP
    void* pBits;
    HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pBits, NULL, 0);

    // Copie les données du buffer dans le bitmap
    memcpy(pBits, buffer, width * height * (bitsPerPixel / 8));

    ReleaseDC(NULL, hdc);

    return hBitmap;
}


void ImageProcessor::SetText(string text, BITMAPINFOHEADER bitmapInfoHeaderData, BYTE* bgr) {
    int width = bitmapInfoHeaderData.biWidth;
    int height = bitmapInfoHeaderData.biHeight;
    int rowSize = (width * 3 + 3) & ~3; 

    BYTE* buffer;

    text = SIGNATURE + text;
    
    int size = text.size();
    int xTemp = 0;
    int yTemp = 0;

    // Parcours de chaque ligne de pixels
    for (int y = 0; y < height; ++y) {
        if (size <= 0)
        {
            break;
        }
        // Parcours de chaque ligne de pixels
        for (int x = 0; x < width; ++x) {
            if (size <= 0)
            {
                break;
            }

            // Récupère un caractère du texte à cacher
            char* letter = &text[text.size() - size];
            // Convertit le caractère en sa représentation binaire
            int value = CharToBits(letter);

            std::bitset<8> bits(value);

            vector<int> color;

            // Récupère les valeurs RGB du pixel actuel
            for (int i = 0; i < 9; i++)
            {
                color.push_back(bgr[y * rowSize + x * 3 * 3 + i]);
            }

            vector<int> color2;
            size--;

            // Modifie les valeurs du pixel en fonction des bits du texte
            if (size <= 0)
            {
                color2 = ChangePixel(color, value, true);
            }
            else {
                color2 = ChangePixel(color, value, false);
            }

            // Applique les nouvelles valeurs RGB au pixel
            for (int i = 0; i < 9; i++)
            {
                bgr[y * rowSize + x * 3 * 3 + i] = color2[i];
            }
        }
    }
}


vector<int> ImageProcessor::ChangePixel(vector<int> color, int bit, bool isLast) {
    unsigned int bit2 = static_cast<unsigned int>(bit);
    int temp = 0;

    BitCalculator cal = BitCalculator();

    // Modifie chaque composant couleur d'un pixel (9 composantes)
    for (int i = 0; i < 9; i++)
    {
        if (i == 8)
        {
            if (isLast)
            {
                color[i] = cal.SetLastBits(color[i]);
            }
            else {
                color[i] = cal.ResetLastBits(color[i]);
            }
            break;
        }

        // Vérifie si le bit est 1 ou 0 et modifie le pixel en conséquence
        if (bit2 & (1 << (i + temp)))
        {
            //color[i] += 1;
            color[i] = cal.SetLastBits(color[i]);
        }
        else {
            color[i] = cal.ResetLastBits(color[i]);
        }
    }

    return color;
}

int ImageProcessor::CharToBits(char* letter) {
    // Convertit un caractère en sa représentation entière (valeur en bits)
    return static_cast<int>(*letter);
}
