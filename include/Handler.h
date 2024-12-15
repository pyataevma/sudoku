#ifndef HANDLER_H
#define HANDLER_H

const int KEY_LEFT=75;
const int KEY_RIGHT=77;
const int KEY_UP=72;
const int KEY_DOWN=80;
const int KEY_SPACE=32;
const int KEY_ESC=27;
const int KEY_DELETE=83;
const int KEY_ENTER=13;
const int KEY_EXTRA=-32;
const int NO_EVENT=0;

const int ACTION_NOTHING=0;
const int ACTION_PLAY=1;
const int ACTION_EXIT=2;
const int ACTION_AUTOPLAY=4;
const int ACTION_REFRESH_SCREEN=8;
const int ACTION_CLEAR_SCREEN=16;
const int ACTION_RESTART=32;

const int TARGET_NOBODY=-1;
const int TARGET_MAIN_MENU=1;
const int TARGET_SUDOKU_GAME=2;

class Event{
    protected:
int code;
int action;
int target;
    public:
      Event(): code{NO_EVENT}, action{ACTION_NOTHING}, target{TARGET_NOBODY}{};
      int getCode()
      {
          return code;
      }

      void setCode(int aCode)
      {
          code=aCode;
      }


      int addAction(int anAction)
      {
          action |= anAction;
      }

      int clearAction()
      {
          action = ACTION_NOTHING;
      }

      void removeAction(int anAction)
      {
          action &= ~anAction;
      }

      bool isAction(int anAction)
      {
          return action & anAction;
      }

      int getTarget()
      {
          return target;
      }

      void setTarget(int aTarget)
      {
          target=aTarget;
      }
};

class Handler
{
    public:
        Handler();
        virtual ~Handler();
        virtual void handleEvent(Event& anEvent){};
    protected:

    private:

};

#endif // HANDLER_H
