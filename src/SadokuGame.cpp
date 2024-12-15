#include "SadokuGame.h"

SadokuGame::SadokuGame()
{
    //ctor
}

SadokuGame::~SadokuGame()
{
    //dtor
}

void SadokuGame::handleEvent()
{
    //EV->text_changed = true; //
    switch (eventCode)
    {
    case 72:
        if (active.line > 0)
        {
            active.line--;
        }
        break;
    case 80:
        if (active.line < FIELD_HEIGHT - 1)
        {
            active.line++;
        }
        break;
    case 77:
        if (active.position < FIELD_HEIGHT - 1)
        {
            active.position++;
        }
        break;
    case 75:
        if (active.position > 0)
        {
            active.position--;
        }
        break;
////    case 32:
//        toggle_cross(B->map, B->board_size, B->active);
//        B->steps_done++;
//        break;

}

};
