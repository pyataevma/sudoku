#ifndef MAINMENU_H
#define MAINMENU_H
#include <MenuBlock.h>


class MainMenu : public MenuBlock
{
    public:
        MainMenu();
        void fillMenu();
        virtual void handleEventAction(Event& anEvent);

    protected:

    private:
};

#endif // MAINMENU_H
