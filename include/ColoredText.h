#ifndef COLOREDTEXT_H
#define COLOREDTEXT_H
#include "ColoredLine.h"


class ColoredText
{
    public:
        ColoredText(): outputConsole{GetStdHandle(STD_OUTPUT_HANDLE)}, numberOfLines{0}, lines{nullptr}{};
        ColoredText(HANDLE consoleHandle): outputConsole{consoleHandle}, numberOfLines{0}, lines{nullptr}{};
        virtual ~ColoredText();
        int getNumberOfLines()
        {
            return numberOfLines;
        }
        int setOutputConsole(HANDLE aConsole)
        {
            outputConsole=aConsole;
        }
        void removeLineAt(int position);
        void removeLastLine();
        void clearText();
        void addLineAt(const ColoredLine& aLine, int position);
        void addLine(const ColoredLine& aLine);
        void addEmptyLine();
        void addWord(const std::string & aWord, int aColorCode);
        void addWordAtLine(const std::string & aWord, int aColorCode, int lineIndex);
        void addWordAtPosition(const std::string & aWord, int aColorCode, int lineIndex, int positionIndex);
        void print();

    protected:
        HANDLE outputConsole;
        int numberOfLines;
        ColoredLine * lines;

    private:

};

#endif // COLOREDTEXT_H
