#ifndef SUDOKUGAME_H
#define SUDOKUGAME_H

#include <SudocuField.h>


class SudokuGame : public SudocuField
{
    public:
        SudokuGame()
        {
            blockTarget=TARGET_SUDOKU_GAME;
        };
        virtual ~SudokuGame();
        virtual void handleEvent(Event& anEvent);
        virtual void refresh(Event& event);

    protected:

    private:
        void handleEventAction(Event& anEvent);
        void handleEventCode(Event& anEvent);
};

#endif // SUDOKUGAME_H
