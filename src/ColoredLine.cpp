#include "ColoredLine.h"
#include "ColoredWord.h"

//ColoredLine::ColoredLine()
//{
//    //ctor
//}

ColoredLine::~ColoredLine()
{
    if (words)
    {
        delete[] words;
    }
}

void ColoredLine::addWordAt(std::string aWord, int aColorCode, int position)
{
    ColoredWord * newWords = new ColoredWord[numberOfWords+1];
    ColoredWord insertedWord{aWord, aColorCode};
    if (position > numberOfWords)
    {
        position = numberOfWords;
    }
    for (int i=0; i<=numberOfWords; i++)
    {
        if (i<position)
        {
            newWords[i] = words[i];
        }
        else if (i==position)
        {
            newWords[i] = insertedWord;
        }
        else
        {
            newWords[i] = words[i-1];
        }
    }
    if (words)
    {
        delete[] words;
    }
    words=newWords;
    numberOfWords++;
};

void ColoredLine::removeWordAt(int position)
{
    if (position >=0 && position < numberOfWords)
    {
        ColoredWord * newWords = new ColoredWord[numberOfWords - 1];
        for (int i=0; i<numberOfWords-1; i++)
        {
            if (i<position)
            {
                newWords[i] = words[i];
            }
            else
            {
                newWords[i] = words[i+1];
            }
        }
        delete[] words;
        words=newWords;
        numberOfWords--;
    }
};

void ColoredLine::removeLastWord()
{
    removeWordAt(numberOfWords-1);
};


void ColoredLine::addWord(std::string aWord, int aColorCode)
{
    addWordAt(aWord, aColorCode, numberOfWords);
};

void ColoredLine::print(HANDLE outputConsole) const
{
    if (numberOfWords)
    {
        for (int i=0; i<numberOfWords; i++)
        {
            words[i].print(outputConsole);
        }
        std::cout << "\n";
    }
};


void ColoredLine::copyAllFields(const ColoredLine& aColoredLine)
{
    if (numberOfWords != aColoredLine.numberOfWords)
    {
        if (words)
        {
            delete[] words;
        }
        numberOfWords = aColoredLine.numberOfWords;
        words = (numberOfWords? new ColoredWord[numberOfWords] : nullptr);
    }
    for (int i=0; i<numberOfWords; i++)
    {
        words[i]=aColoredLine.words[i];
    }
}


ColoredLine& ColoredLine::operator= (const ColoredLine& aColoredLine)
{
    if (this!=&aColoredLine)
    {
        copyAllFields(aColoredLine);
    }
    return *this;
};
