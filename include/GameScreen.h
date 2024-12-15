#ifndef GAMESCREEN_H
#define GAMESCREEN_H
#include "ScreenBlock.h"
#include <conio.h>

class GameScreen
{
    public:
        GameScreen(): blocks{nullptr}, numberOfBlocks{0}
        {
            outputConsole=GetStdHandle(STD_OUTPUT_HANDLE);
        };
        virtual ~GameScreen();
        void addBlock(ScreenBlock* pBlock);
        void listenEvent();
        void handleEvent();
        void clearScreen();
        void prepareScreen();
        void refresh();
        void print();
        void run();

    protected:
      ScreenBlock** blocks;
      int numberOfBlocks;
      Event event;
      HANDLE outputConsole;
    private:
};

#endif // GAMESCREEN_H
