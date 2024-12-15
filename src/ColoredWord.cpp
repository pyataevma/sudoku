#include "ColoredWord.h"
#include <iostream>
#include <windows.h>

ColoredWord::ColoredWord()
{
    //ctor
}

ColoredWord::~ColoredWord()
{
    //dtor
}

std::string ColoredWord::getWord() const
{
    return word;
}

void ColoredWord::print(HANDLE outputConsole) const
{
    SetConsoleTextAttribute(outputConsole, colorCode);
    std::cout << word;
};

ColoredWord& ColoredWord::operator= (const ColoredWord& aColoredWord)
{
    if (this!=&aColoredWord)
    {
        word = aColoredWord.word;
        colorCode = aColoredWord.colorCode;
    }
    return *this;
};
