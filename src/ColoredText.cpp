#include "ColoredText.h"
#include <iostream>

//ColoredText::ColoredText()
//{
//    //ctor
//}

ColoredText::~ColoredText()
{
    if (lines)
    {
        //std::cout << "Destructor for text\n";
        delete[] lines;
    }
}

void ColoredText::addLineAt(const ColoredLine& aLine, int position)
{
    ColoredLine * newLines = new ColoredLine[numberOfLines+1];
    if (position > numberOfLines)
    {
        position = numberOfLines;
    }
    for (int i=0; i<=numberOfLines; i++)
    {
        if (i<position)
        {
            newLines[i] = lines[i];
        }
        else if (i==position)
        {
            newLines[i] = aLine;
        }
        else
        {
            newLines[i] = lines[i-1];
        }
    }
    if (lines)
    {
        delete[] lines;
    }
    lines = newLines;
    numberOfLines++;
};

void ColoredText::removeLineAt(int position)
{
    if (position >=0 && position < numberOfLines)
    {
        ColoredLine * newLines = new ColoredLine[numberOfLines - 1];
        for (int i=0; i<numberOfLines-1; i++)
        {
            if (i<position)
            {
                newLines[i] = lines[i];
            }
            else
            {
                newLines[i] = lines[i+1];
            }
        }
        delete[] lines;
        lines=newLines;
        numberOfLines--;
    }
};

void ColoredText::removeLastLine()
{
    removeLineAt(numberOfLines-1);
};

void ColoredText::clearText()
{
    delete[] lines;
    lines=nullptr;
    numberOfLines=0;
}

void ColoredText::addLine(const ColoredLine& aLine)
{
    addLineAt(aLine, numberOfLines);
};

void ColoredText::addEmptyLine()
{
    addLine(*(new ColoredLine));
};

void ColoredText::addWordAtLine(const std::string & aWord, int aColorCode, int lineIndex)
{
    if (lineIndex<numberOfLines)
    {
        lines[lineIndex].addWord(aWord,aColorCode);
    }
}

void ColoredText::addWord(const std::string & aWord, int aColorCode)
{
    if (numberOfLines==0)
    {
        addEmptyLine();
    }
    addWordAtLine(aWord, aColorCode, numberOfLines-1);
}


void ColoredText::print()
{
    if (numberOfLines)
    {
        for (int i=0; i<numberOfLines; i++)
        {
            lines[i].print(outputConsole);
        }
    }
};

