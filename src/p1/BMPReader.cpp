#include "pch.h"
#include "BMPReader.h"
#include <bitset>
#include <iostream>

BMPReader::BMPReader()
{

}

//Lire un texte dans une image BMP
string BMPReader::ReadText(BITMAPINFOHEADER bitmapInfoHeaderData, BYTE* bgr) {
    int width = bitmapInfoHeaderData.biWidth;
    int height = bitmapInfoHeaderData.biHeight;
    int rowSize = (width * 3 + 3) & ~3; // Row size must be a multiple of 4

    char letter = '0';
    string rep = "";
    string sign = SIGNATURE;
    bool isEnd = false;

    // Boucle sur chaque pixel de l'image
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            vector<int> color;

            // Extraction des valeurs des 9 premi�res composantes de couleur du pixel
            for (int i = 0; i < 9; i++)
            {
                int pos = y * rowSize + x * 3 * 3 + i;

                color.push_back(bgr[pos]);
            }

            // Lire un caract�re � partir de ces composantes couleur
            letter = ReadPixel(color);

            // Ajouter le caract�re extrait � la cha�ne de r�ponse
            rep += letter;

            BitCalculator cal = BitCalculator();

            if (cal.IsSet(color[color.size() - 1]))
            {
                isEnd = true;
            }

            if (rep.size() == sign.size())
            {
                if (rep != sign)
                {
                    break;
                }
            }
            if (isEnd)
            {
                break;
            }
        }

        // R�p�ter les v�rifications de correspondance et de fin apr�s chaque ligne de pixels
        if (rep.size() == sign.size())
        {
            if (rep != sign)
            {
                break;
            }
        }
        if (isEnd)
        {
            break;
        }
    }

    // Supprimer la signature de la cha�ne lue
    rep.erase(0, 2);
    return rep;
}


//Lire un pixel dans une image BMP
char BMPReader::ReadPixel(vector<int> color) {

    unsigned char result = 0; // Stocker le r�sultat final

    BitCalculator cal = BitCalculator();


    color.pop_back();


    // Parcours des composantes couleur du pixel
    for (int i = 0; i < color.size(); i++) {

        if (cal.IsSet(color[i]))
        {
            result += pow(2, i);
        }
    }

    //Conversion du r�sultat en caract�re
    return static_cast<char>(result); 
}