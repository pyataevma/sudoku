#include "SudokuGame.h"

SudokuGame::~SudokuGame()
{
}

void SudokuGame::refresh(Event& event)
{
    if (isChanged)
    {
        clearText();
        makeField();
        isChanged=false;
        event.addAction(ACTION_REFRESH_SCREEN);
    }
};

void SudokuGame::handleEvent(Event& anEvent)
{
    if (anEvent.getTarget() == blockTarget)
    {
        handleEventCode(anEvent);
        handleEventAction(anEvent);
    }
}

void SudokuGame::handleEventAction(Event& anEvent)
{
    if (anEvent.isAction(ACTION_AUTOPLAY))
    {
        tryToSolve();
        isChanged=true;
        anEvent.removeAction(ACTION_AUTOPLAY);
    }
    if (anEvent.isAction(ACTION_RESTART))
    {
        clearNotMaster();
        isChanged=true;
        anEvent.removeAction(ACTION_RESTART);
    }
}


void SudokuGame::handleEventCode(Event& anEvent)
{
    int currentCode=anEvent.getCode();
    switch (currentCode)
    {
    case KEY_UP:
        if (active.line > 0)
        {
            active.line--;
            isChanged=true;
            anEvent.setCode(NO_EVENT);
        }
        break;
    case KEY_DOWN:
        if (active.line < FIELD_HEIGHT - 1)
        {
            active.line++;
            isChanged=true;
            anEvent.setCode(NO_EVENT);
        }
        break;
    case KEY_RIGHT:
        if (active.position < FIELD_HEIGHT - 1)
        {
            active.position++;
            isChanged=true;
            anEvent.setCode(NO_EVENT);
        }
        break;
    case KEY_LEFT:
        if (active.position > 0)
        {
            active.position--;
            isChanged=true;
            anEvent.setCode(NO_EVENT);
        }
        break;
    case KEY_ESC:
        isChanged=true;
        anEvent.setCode(NO_EVENT);
        anEvent.setTarget(TARGET_MAIN_MENU);
        break;
    case KEY_SPACE:
    case KEY_DELETE:
        setActiveCellValue(0);
        isChanged=true;
        anEvent.setCode(NO_EVENT);
        break;
    default:
        if (currentCode>=int('1') && currentCode<=int('9'))
        {
            int userValue=currentCode-int('1')+1;
            if  (isPossibleForActive(userValue))
            {
                setActiveCellValue(userValue);
                isChanged=true;
                anEvent.setCode(NO_EVENT);
            }
        }
    }
};
