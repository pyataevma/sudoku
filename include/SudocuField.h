#include <ColoredText.h>
#include <string.h>
#include "SudokuCell.h"
#include "ScreenBlock.h"
using std::string;


const int FIELD_WIDTH=9;
const int FIELD_HEIGHT=FIELD_WIDTH;
const int SQUARES_IN_LINE=3;
const int SQUARES_IN_ROW=3;
const int SQUARE_WIDTH=FIELD_WIDTH/SQUARES_IN_LINE;
const int SQUARE_HEIGHT=FIELD_HEIGHT/SQUARES_IN_ROW;
const int ALL_POSSIBLE_MASK=512-1;

const string DOUBLE_TOP= {char(201),char(205),char(209),char(203),char(187)};
const string EMPTY_CENTER= {char(186),' ',char(179),char(186),char(186)};
const string SINGLE_CENTER= {char(199),char(196),char(197),char(215),char(182)};
const string DOUBLE_CENTER= {char(204),char(205),char(216),char(206),char(185)};
const string DOUBLE_BOTTOM= {char(200),char(205),char(207),char(202),char(188)};


class SudocuField : public ScreenBlock
{
public:
    SudocuField();
    virtual ~SudocuField();
    void makeField();
    void fillEmpty();
    void fillRandom(int numberOfAttempts);
    void tryToSolve();
    void clearNotMaster();
    void removeRandom(int numberOfAttempts);
    void setActiveCellValue(int decimalValue);
    bool isPossibleForActive(int decimalValue);
    void SimplePrint();

protected:
    struct CellPosition
    {
        int line;
        int position;
    };
    SudokuCell cells[FIELD_WIDTH][FIELD_WIDTH];
    CellPosition active;
    bool isChanged;

private:

    CellPosition getLeftTop(CellPosition current);
    CellPosition getLeftTop(int squareNumber);
    CellPosition getCellPosition(int squareNumber, int cellNumber);
    void fillEvident();
    int getOccupiedInSquare(CellPosition current);
    int getOccupiedInLine(CellPosition current);
    int getOccupiedInRow(CellPosition current);
    int getPossible(CellPosition current);
    int getMinNumberOfPossible();
    void tryToRemove(CellPosition current);
    void setAllMaster();
    bool isComplete();
    int convertToBinary(int value);
    int countBits(int value);
    int getDecimal(int value);
    int selectBit(int value, int bitNumber);
    int getAvailableInSquare(int value, int squareNumber);
    bool putValueInSquare(int value, int squareNumber);
    bool putValueOnField(int value);
    bool putAllValuesOnField();
    ColoredLine makeLine(string border_elements, int lineIndex, bool isDigitLine);
    ColoredLine makeLineOfPossible(CellPosition current);
    ColoredLine makeLineOfHints(string hintText);
    ColoredLine makeEmptyLine();
};
