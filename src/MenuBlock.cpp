#include "MenuBlock.h"

MenuBlock::~MenuBlock()
{
    if (items)
    {
        delete[] items;
    }
}

void MenuBlock::addItem(const MenuItem& anItem)
{
    MenuItem* newItems = new MenuItem[numberOfItems+1];
    for (int i=0; i<numberOfItems; i++)
    {
        newItems[i] = items[i];
    }
    newItems[numberOfItems]=anItem;
    if (numberOfItems)
    {
        delete[] items;
    }
    items = newItems;
    numberOfItems++;
};

void MenuBlock::makeLine()
{
    ColoredLine aLine;
    for (int i=0; i<numberOfItems; i++)
    {
        int color = (i==active? MENU_ACTIVE_COLOR : MENU_COLOR);
        aLine.addWord(items[i].getText(), color);
    }
    addLine(aLine);
};

void MenuBlock::handleEvent(Event& anEvent)
{
    if (anEvent.getTarget() == blockTarget)
    {
        handleEventCode(anEvent);
        handleEventAction(anEvent);
    }
};

void MenuBlock::handleEventAction(Event& anEvent)
{

}

void MenuBlock::handleEventCode(Event& anEvent)
{
    int currentCode=anEvent.getCode();
    switch (currentCode)
    {
    case KEY_RIGHT:
        if (active < numberOfItems - 1)
        {
            active++;
            isChanged=true;
            anEvent.setCode(NO_EVENT);
        }
        break;
    case KEY_LEFT:
        if (active > 0)
        {
            active--;
            isChanged=true;
            anEvent.setCode(NO_EVENT);
        }
        break;
    case KEY_ENTER:
        anEvent.addAction(items[active].getAction());
        break;
    }
};

void MenuBlock::refresh(Event& event)
{
    if (isChanged)
    {
        clearText();
        makeLine();
        isChanged=false;
        event.addAction(ACTION_REFRESH_SCREEN);
    }
};
