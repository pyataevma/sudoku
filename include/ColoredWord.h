#ifndef COLOREDWORD_H
#define COLOREDWORD_H
#include <string>
#include <windows.h>

class ColoredWord
{
    public:
        ColoredWord();
        ColoredWord(std::string aWord, int aColorCode): word{aWord}, colorCode{aColorCode}{};
        virtual ~ColoredWord();
        void print(HANDLE outputConsole) const;
        std::string getWord() const;
        ColoredWord& operator= (const ColoredWord& aColoredWord);

    protected:

    private:
        int colorCode;
        std::string word;
};

#endif // COLOREDWORD_H
