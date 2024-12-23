#pragma once
#include <windows.h>

class BitCalculator {
public:

    BitCalculator();

    int ResetLastBits(int bit);
    int SetLastBits(int bit);
    bool IsSet(int bit);
};
