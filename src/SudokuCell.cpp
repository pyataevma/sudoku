#include "SudokuCell.h"
#include <string>
#include <iostream>

using std::string;


SudokuCell::SudokuCell()
{
    //ctor
}

SudokuCell::~SudokuCell()
{
    //dtor
}

void  SudokuCell::setFromDecimal(int decimalValue)
{
    if (decimalValue)
    {
        int p=1;
        for (int i=1; i<decimalValue; i++)
        {
            p*=2;
        }
        binaryValue=p;
    }
    else
    {
       binaryValue=0;
    }
}

int SudokuCell::getDecimal()
{
    // returns log2 of the first nonzero bit 0001010 --> 4
    // or zero if first MAX_CELL_VALUE bits are zero
    if (binaryValue)
    {
        int p=1;
        for (int i=1; i<=MAX_CELL_VALUE; i++)
        {
            if (p&binaryValue)
            {
                return i;
            }
            p*=2;
        }
    }
    return 0;
}

string SudokuCell::getCellString()
{
    return binaryValue? std::to_string(getDecimal()) : " ";
}

int SudokuCell::getColor(bool isActive)
{
    int color=masterStatus? MASTER_COLOR : PLAYER_COLOR;
    color+= isActive ? ACTIVE_BACK_COLOR : STANDARD_BACK_COLOR;
    return color;
}

void SudokuCell::printAllBits(int value)
{
    int counter=0, p=1;
    for (int i=1; i<=MAX_CELL_VALUE; i++)
    {
        if (p&value)
        {
            std::cout << i << " ";
        }
        p*=2;
    }
};
