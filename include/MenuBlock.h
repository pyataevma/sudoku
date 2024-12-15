#ifndef MENUBLOCK_H
#define MENUBLOCK_H
#include <string>
#include "ScreenBlock.h"

const int MENU_COLOR=7*16+0;
const int MENU_ACTIVE_COLOR=10*16+0;
//const int MENU_SPACE_COLOR=4*16+0;

using std::string;

class MenuItem
{
    protected:
        int action;
        string text;
    public:
        MenuItem(string itemName, int itemAction): text{itemName}, action{itemAction}{};
        MenuItem(){};
        void setAction(int anAction)
        {
            action=anAction;
        };
        void setText(string aText)
        {
            text=aText;
        };
        int getAction()
        {
            return action;
        }
        string  getText()
        {
            return text;
        }
};

class MenuBlock: public ScreenBlock
{
    public:
        MenuBlock(): items{nullptr}, numberOfItems{0}, active{0}, isChanged{false} {};
        virtual ~MenuBlock();
        void addItem(const MenuItem& anItem);
        void makeLine();
        virtual void refresh(Event& event);
        virtual void handleEvent(Event& anEvent);
        virtual void handleEventAction(Event& anEvent);
        virtual void handleEventCode(Event& anEvent);


    protected:
        MenuItem* items;
        int numberOfItems;
        int active;
        bool isChanged;

    private:
};

#endif // MENUBLOCK_H
