#include "pch.h"
#include "BitCalculator.h"
#include <bitset>
#include <iostream>

BitCalculator::BitCalculator()
{

}

//Réinitialise les bits 
int BitCalculator::ResetLastBits(int bit) {
	unsigned int lastBit = 0b00000001;
	bit = bit & ~lastBit;
	return bit;
}

//Definir le dernier bit
int BitCalculator::SetLastBits(int bit) {
	unsigned int lastBit = 0b00000001;
	bit = bit | lastBit;
	return bit;
}

//Verifier si le dernier bit est defini à 1 
bool BitCalculator::IsSet(int bit) {
	unsigned int lastBit = 0b00000001;
	if (bit & lastBit)
	{
		return true;
	}
	return false;
}