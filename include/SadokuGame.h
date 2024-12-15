#ifndef SADOKUGAME_H
#define SADOKUGAME_H

#include <SudocuField.h>


class SadokuGame : public SudocuField
{
    public:
        SadokuGame();
        virtual ~SadokuGame();
        virtual void handleEvent();

    protected:

    private:
};

#endif // SADOKUGAME_H
