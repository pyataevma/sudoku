#ifndef COLOREDLINE_H
#define COLOREDLINE_H
#include <string>
#include <iostream>
#include "ColoredWord.h"


class ColoredLine
{
    public:
        ColoredLine(): words{nullptr}, numberOfWords{0} {};
        virtual ~ColoredLine();
        void addWord(std::string aWord, int aColorCode);
        void addWordAt(std::string aWord, int aColorCode, int position);
        void removeLastWord();
        void removeWordAt(int position);
        void print(HANDLE outputConsole) const;
        void copyAllFields(const ColoredLine& aColoredLine);
        ColoredLine& operator= (const ColoredLine& aColoredLine);

    protected:
        int numberOfWords;
        ColoredWord* words;
    private:

};

#endif // COLOREDLINE_H
