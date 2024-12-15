#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu()
{
    //ctor
}

void MainMenu::fillMenu()
{
    addItem(MenuItem{" Play ", ACTION_PLAY});
    addItem(MenuItem{" Solve ", ACTION_AUTOPLAY});
    addItem(MenuItem{" Restart ", ACTION_RESTART});
    addItem(MenuItem{" Exit ", ACTION_EXIT});
   blockTarget=TARGET_MAIN_MENU;
};

void MainMenu::handleEventAction(Event& anEvent)
{
    if (anEvent.isAction(ACTION_PLAY))
    {
        anEvent.setTarget(TARGET_SUDOKU_GAME);
        anEvent.removeAction(ACTION_PLAY);
    }
    if (anEvent.isAction(ACTION_AUTOPLAY))
    {
        anEvent.setTarget(TARGET_SUDOKU_GAME);
    }
    if (anEvent.isAction(ACTION_RESTART))
    {
        anEvent.setTarget(TARGET_SUDOKU_GAME);
    }
};
