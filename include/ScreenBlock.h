#ifndef SCREENBLOCK_H
#define SCREENBLOCK_H

#include <ColoredText.h>
#include <Handler.h>


class ScreenBlock : public ColoredText, public Handler
{
    public:
        ScreenBlock();
        virtual ~ScreenBlock();
        virtual void refresh(Event& event){};
    protected:
        int blockTarget;
    private:
};

#endif // SCREENBLOCK_H
