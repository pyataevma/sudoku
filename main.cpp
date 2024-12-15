#include <time.h>
#include "SudokuGame.h"
#include "MainMenu.h"
#include "GameScreen.h"

const int MAX_FILL_ATTEMPTS=30000;
const int REMOVE_ATTEMPTS=200;

int main()
{
    srand(time(NULL));
    SudokuGame sudokuGame;
    SudokuGame* pSudokuGame=&sudokuGame;
    sudokuGame.fillRandom(MAX_FILL_ATTEMPTS);
    sudokuGame.removeRandom(REMOVE_ATTEMPTS);
    sudokuGame.makeField();
    MainMenu mainMenu;
    mainMenu.fillMenu();
    mainMenu.makeLine();
    MainMenu* pMainMenu=&mainMenu;
    GameScreen mainScreen;
    mainScreen.addBlock(pMainMenu);
    mainScreen.addBlock(pSudokuGame);
    mainScreen.print();
    mainScreen.run();
}
