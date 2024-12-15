#include "GameScreen.h"


GameScreen::~GameScreen()
{
    if (blocks)
    {
        delete[] blocks;
    }
}

void GameScreen::addBlock(ScreenBlock* pBlock)
{
    ScreenBlock** newBlocks = new ScreenBlock*[numberOfBlocks+1];
    for (int i=0; i<numberOfBlocks; i++)
    {
        newBlocks[i] = blocks[i];
    }
    newBlocks[numberOfBlocks]=pBlock;
    newBlocks[numberOfBlocks]->setOutputConsole(outputConsole);
    if (numberOfBlocks)
    {
        delete[] blocks;
    }
    blocks = newBlocks;
    numberOfBlocks++;
};

void GameScreen::listenEvent()
{
    if (_kbhit())
    {
        int key = _getch();
        if (key == KEY_EXTRA)
        {
            key = _getch();
        }
        event.setCode(key);
    }
};

void GameScreen::handleEvent()
{
    for (int i=0; i<numberOfBlocks; i++)
    {
        blocks[i]->handleEvent(event);
    }
    refresh();
};

void GameScreen::refresh()
{
    for (int i=0; i<numberOfBlocks; i++)
    {
        blocks[i]->refresh(event);
    }
    if (event.isAction(ACTION_REFRESH_SCREEN))
    {
        prepareScreen();
        print();
        event.removeAction(ACTION_REFRESH_SCREEN);
    }
};

void GameScreen::prepareScreen()
{
    if (event.isAction(ACTION_CLEAR_SCREEN))
    {
        //    system("cls");
        char fillSymbol = ' ';
        COORD topLeft = {0,0};
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(outputConsole, &info);
        DWORD written, cells = info.dwSize.X * info.dwSize.Y;
        FillConsoleOutputCharacter(outputConsole, fillSymbol, cells, topLeft, &written);
        FillConsoleOutputAttribute(outputConsole, info.wAttributes, cells, topLeft, &written);
        event.removeAction(ACTION_CLEAR_SCREEN);
    }
    SetConsoleCursorPosition(outputConsole, {0,0});
};

void GameScreen::print()
{
    for (int i=0; i<numberOfBlocks; i++)
    {
        blocks[i]->print();
    }
};

void GameScreen::run()
{
    event.setTarget(TARGET_SUDOKU_GAME);
    while (!event.isAction(ACTION_EXIT))
    {
        listenEvent();
        handleEvent();
    }
};

