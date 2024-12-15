#include <string>

using std::string;

#ifndef SUDOKUCELL_H
#define SUDOKUCELL_H

const int MAX_CELL_VALUE=9;

const int STANDARD_BACK_COLOR=15*16;
const int ACTIVE_BACK_COLOR=12*16;
const int MASTER_COLOR=0;
const int PLAYER_COLOR=1;
const int STANDART_COLOR=0;
const int BORDER_COLOR=STANDARD_BACK_COLOR+STANDART_COLOR;
const int POSSIBLE_COLOR=STANDARD_BACK_COLOR+STANDART_COLOR;
const int IMPOSSIBLE_COLOR=STANDARD_BACK_COLOR+7;
const int EMPTY_SCREEN_COLOR=7;

class SudokuCell
{
public:
    SudokuCell();
    virtual ~SudokuCell();
    int getBinary() const
    {
        return binaryValue;
    };
    int setFromBinary(int aBinaryValue)
    {
        binaryValue=aBinaryValue;
    };
    void setMasterStatus(bool isMaster)
    {
        masterStatus=isMaster;
    };
    bool getMasterStatus()
    {
        return masterStatus;
    };

    int getDecimal();
    void setFromDecimal(int decimalValue);
    string getCellString();
    int getColor(bool isActive);
    void printAllBits(int value);

protected:

private:
    int binaryValue;
    bool masterStatus;
};
#endif // SUDOKUCELL_H
