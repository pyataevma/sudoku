#include "SudocuField.h"
#include "SudokuCell.h"
#include <string.h>

SudocuField::SudocuField()
{
    //ctor
}

SudocuField::~SudocuField()
{
    //dtor
}

// Binary operations

int SudocuField::convertToBinary(int value)
{
    // returns 2 to power value
    if (value)
    {
        int p=1;
        for (int i=1; i<value; i++)
        {
            p*=2;
        }
        return p;
    }
    return 0;
}

int SudocuField::getDecimal(int value)
{
    // returns log2 of the first nonzero bit 0001010 --> 4
    // or zero if first MAX_CELL_VALUE bits are zero
    if (value)
    {
        int p=1;
        for (int i=1; i<=MAX_CELL_VALUE; i++)
        {
            if (p&value)
            {
                return i;
            }
            p*=2;
        }
    }
    return 0;
}


int SudocuField::countBits(int value)
{
    int counter=0, p=1;
    for (int i=1; i<=MAX_CELL_VALUE; i++)
    {
        if (p&value)
        {
            counter++;
        }
        p*=2;
    }
    return counter;
};


int SudocuField::selectBit(int value, int bitNumber)
{
    // returns non-zero bit
    int counter=0, p=1;
    for (int i=1; i<=MAX_CELL_VALUE; i++)
    {
        if (p&value)
        {
            counter++;
        }
        if (counter==bitNumber)
        {
            return p;
        };
        p*=2;
    }
    return 0;
};

// Making pseudo graphic image of field

ColoredLine SudocuField::makeLine(std::string border_elements, int lineIndex, bool isDigitLine)
{
    ColoredLine aLine;
    aLine.addWord(border_elements.substr(0,1),BORDER_COLOR);
    for (int i=0; i<SQUARES_IN_LINE; i++)
    {
        for (int j=0; j<SQUARE_WIDTH; j++)
        {
            int position=i*SQUARE_WIDTH+j;
            aLine.addWord(border_elements.substr(1,1),BORDER_COLOR);
            int currentColor=cells[lineIndex][position].getColor(lineIndex==active.line && position==active.position);
            isDigitLine? aLine.addWord(cells[lineIndex][position].getCellString(), currentColor):
            aLine.addWord(border_elements.substr(1,1), BORDER_COLOR);
            aLine.addWord(border_elements.substr(1,1), BORDER_COLOR);
            if (j<SQUARE_WIDTH-1)
            {
                aLine.addWord(border_elements.substr(2,1),BORDER_COLOR);
            }
        }
        if (i<SQUARES_IN_LINE-1)
        {
            aLine.addWord(border_elements.substr(3,1),BORDER_COLOR);
        }
    }
    aLine.addWord(border_elements.substr(4,1),BORDER_COLOR);
    return aLine;
};

ColoredLine SudocuField::makeLineOfPossible(CellPosition current)
{
    ColoredLine aLine;
    aLine.addWord("Possible digits: ",BORDER_COLOR);
    int possible=getPossible(current);
    int p=1;
    for (int i=1; i<=MAX_CELL_VALUE; i++)
    {
        if (!cells[current.line][current.position].getMasterStatus())
        {
            int color= (p&possible)? POSSIBLE_COLOR : IMPOSSIBLE_COLOR;
            aLine.addWord(std::to_string(i) + " ", color);
        }
        else
        {
            aLine.addWord("  ", IMPOSSIBLE_COLOR);
        }
        p*=2;
    }
    aLine.addWord(" ",BORDER_COLOR);
    return aLine;
};

ColoredLine SudocuField::makeLineOfHints(string hintText)
{
    ColoredLine aLine;
    aLine.addWord(hintText,BORDER_COLOR);
    //aLine.addWord("ARROWS - move cursor, DEL or SPACE - remove digit, ESC - main menu. ",BORDER_COLOR);
    return aLine;
};


ColoredLine SudocuField::makeEmptyLine()
{
    ColoredLine aLine;
    aLine.addWord(" ",EMPTY_SCREEN_COLOR);
    return aLine;
};

void SudocuField::makeField()
{
    addLine(makeEmptyLine());
    addLine(makeLine(DOUBLE_TOP,0,false));
    for (int i=0; i<SQUARES_IN_ROW; i++)
    {
        for (int j=0; j<SQUARE_HEIGHT; j++)
        {
            addLine(makeLine(EMPTY_CENTER,i*SQUARE_WIDTH+j,true));
            if (j<SQUARE_WIDTH-1)
            {
                addLine(makeLine(SINGLE_CENTER,0,false));
            }
        }
        if (i<SQUARES_IN_ROW-1)
        {
            addLine(makeLine(DOUBLE_CENTER,0,false));
        }
    }
    addLine(makeLine(DOUBLE_BOTTOM,0,false));
    addLine(makeEmptyLine());
    addLine(makeLineOfHints("ARROWS - move cursor"));
    addLine(makeLineOfHints("DEL or SPACE - remove digit"));
    addLine(makeLineOfHints("ESC - main menu"));
    addLine(makeLineOfPossible(active));
};

// Game algorithms

int SudocuField::getAvailableInSquare(int value, int squareNumber)
{
    //the function determines all possible positions in a square and stores them in the form of bits in one integer variable
    int available=0, p=1;
    CellPosition leftTop = getLeftTop(squareNumber);
    for (int i=0; i<SQUARE_WIDTH; i++)
    {
        for (int j=0; j<SQUARE_HEIGHT; j++)
        {
            if (cells[leftTop.line+i][leftTop.position+j].getBinary() == 0 && (getPossible({leftTop.line+i,leftTop.position+j}) & value) )
            {
                available |= p;
            }
            p*=2;
        }
    }
    return available;
};


bool SudocuField::putValueInSquare(int value, int squareNumber)
{
    int availableCells = getAvailableInSquare(value, squareNumber);
    if (availableCells)
    {
        int maxNumber = countBits(availableCells);
        int randNumber = (maxNumber>1) ? (1 + rand() % maxNumber) : 1;
        int cellNumber=getDecimal(selectBit(availableCells,randNumber));
        CellPosition current = getCellPosition(squareNumber,cellNumber);
        cells[current.line][current.position].setFromBinary(value);
        return true;
    }
    return false;
};

bool SudocuField::putValueOnField(int value)
{
    for (int squareNumber=0; squareNumber<MAX_CELL_VALUE; squareNumber++)
    {
        if (!putValueInSquare(value,squareNumber))
        {
            return false;
        }
    }
    return true;
}

bool SudocuField::putAllValuesOnField()
{
    for (int decimalValue=1; decimalValue<=MAX_CELL_VALUE; decimalValue++)
    {
        if (!putValueOnField(convertToBinary(decimalValue)))
        {
            return false;
        }
    }
    return true;
}

void SudocuField::fillRandom(int numberOfAttempts)
{
    int attempt=0;
    bool success=false;
    while (!success && attempt<numberOfAttempts )
    {
        fillEmpty();
        success=putAllValuesOnField();
        {
            active = {4,5};
        }
        attempt++;
    }
    setAllMaster();
};



void SudocuField::fillEvident()
{
    for (int i=0; i<FIELD_WIDTH; i++)
    {
        for (int j=0; j<FIELD_WIDTH; j++)
        {
            if (cells[i][j].getBinary() == 0)
            {
                if (countBits(getPossible({i,j})) == 1)
                {
                    cells[i][j].setFromBinary(getPossible({i,j}));
                };
            }
        }
    }
}


void SudocuField::fillEmpty()
{
    for (int i=0; i<FIELD_WIDTH; i++)
    {
        for (int j=0; j<FIELD_WIDTH; j++)
        {
            cells[i][j].setFromBinary(0);
            cells[i][j].setMasterStatus(false);
        }
    }
    isChanged=false;
};

int SudocuField::getOccupiedInLine(CellPosition current)
{
    int occupied=0;
    for (int i=0; i<FIELD_WIDTH; i++)
    {
        if (i!=current.position)
        {
            occupied |= cells[current.line][i].getBinary();
        }
    }
    return occupied;
};

int SudocuField::getOccupiedInRow(CellPosition current)
{
    int occupied=0;
    for (int i=0; i<FIELD_WIDTH; i++)
    {
        if (i!=current.line)
        {
            occupied |= cells[i][current.position].getBinary();
        }
    }
    return occupied;
};

SudocuField::CellPosition SudocuField::getLeftTop(CellPosition current)
{
    return {(current.line/SQUARE_WIDTH)*SQUARE_WIDTH, (current.position/SQUARE_WIDTH)*SQUARE_WIDTH};
};

SudocuField::CellPosition SudocuField::getLeftTop(int squareNumber)
{
    return {(squareNumber/SQUARES_IN_LINE)*SQUARE_WIDTH, (squareNumber % SQUARES_IN_LINE)*SQUARE_WIDTH};
};

SudocuField::CellPosition SudocuField::getCellPosition(int squareNumber, int cellNumber)
{
    CellPosition leftTop = getLeftTop(squareNumber);
    return {leftTop.line + (cellNumber-1) / SQUARE_WIDTH, leftTop.position + (cellNumber-1) % SQUARE_WIDTH};
};


int SudocuField::getOccupiedInSquare(CellPosition current)
{
    int occupied=0;
    CellPosition leftTop=getLeftTop(current);
    for (int i=0; i<SQUARE_WIDTH; i++)
    {
        for (int j=0; j<SQUARE_WIDTH; j++)
        {
            if (i != current.line % SQUARE_WIDTH || j != current.position % SQUARE_WIDTH)
            {
                occupied |= cells[leftTop.line+i][leftTop.position+j].getBinary();
            }
        }
    }
    return occupied;
};

int SudocuField::getPossible(CellPosition current)
{
    return ALL_POSSIBLE_MASK & ~(getOccupiedInLine(current) | getOccupiedInRow(current) | getOccupiedInSquare(current));
}

int SudocuField::getMinNumberOfPossible()
{
    int minPossible = MAX_CELL_VALUE, current;
    for (int i=0; i<FIELD_WIDTH; i++)
    {
        for (int j=0; j<FIELD_HEIGHT; j++)
        {
            if (cells[i][j].getBinary()==0)
            {
                int current = countBits(getPossible({i,j}));
                //std::cout << current << "\n";
                if (current<minPossible)
                {
                    minPossible=current;
                }
            }
        }
    }
    return minPossible;
}

void SudocuField::setAllMaster()
{
    for (int i=0; i<FIELD_WIDTH; i++)
    {
        for (int j=0; j<FIELD_HEIGHT; j++)
        {
            if (cells[i][j].getBinary())
            {
                cells[i][j].setMasterStatus(true);
            }
        }
    }
}

void SudocuField::clearNotMaster()
{
    for (int i=0; i<FIELD_WIDTH; i++)
    {
        for (int j=0; j<FIELD_HEIGHT; j++)
        {
            if (!cells[i][j].getMasterStatus())
            {
                cells[i][j].setFromBinary(0);
            }
        }
    }
}

bool SudocuField::isComplete()
{
    for (int i=0; i<FIELD_WIDTH; i++)
    {
        for (int j=0; j<FIELD_HEIGHT; j++)
        {
            if (cells[i][j].getBinary()==0)
            {
                return false;
            }
        }
    }
    return true;
}


void SudocuField::tryToRemove(CellPosition current)
{
    int temp=cells[current.line][current.position].getBinary();
    cells[current.line][current.position].setFromBinary(0);
    tryToSolve();
    if (isComplete())
    {
        cells[current.line][current.position].setMasterStatus(false);
    }
    else
    {
        cells[current.line][current.position].setFromBinary(temp);
    }
    clearNotMaster();
}

void SudocuField::tryToSolve()
{
    while (getMinNumberOfPossible() == 1 && !isComplete())
    {
        fillEvident();
    }
}

void SudocuField::removeRandom(int numberOfAttempts)
{
    for (int i=0; i<numberOfAttempts; i++)
    {
        CellPosition current= {rand() % FIELD_WIDTH, rand() % FIELD_HEIGHT};
        tryToRemove(current);
    }
}

void SudocuField::setActiveCellValue(int decimalValue)
{
    if (!cells[active.line][active.position].getMasterStatus())
    {
        cells[active.line][active.position].setFromDecimal(decimalValue);
    }
};

bool SudocuField::isPossibleForActive(int decimalValue)
{
    return (getPossible(active) & convertToBinary(decimalValue));
};

//
//void SudocuField::SimplePrint()
//{
//    for (int i=0; i<FIELD_WIDTH; i++)
//    {
//        std::cout << "square: " << i << "\n";
//        for (int j=0; j<FIELD_WIDTH; j++)
//        {
//            //std::cout << countBits(getPossible({i,j})) << " ";
//            //std::cout << getDecimal(cells[i][j].value) << " ";
//            std::cout << j << "(" << getCellPosition(i, j).line << "," << getCellPosition(i, j).position << ") ";
//            if ((j+1) % 3 == 0)
//            {
//                std::cout << "\n";
//            }
//        }
//        std::cout << "\n";
//    }
//    std::cout << "\n\n";
//    for (int i=0; i<FIELD_WIDTH; i++)
//    {
//        std::cout << countBits(getAvailableInSquare(1,i)) << " ";
//    }
//    std::cout << "\n\n";
//    //  ShowPossible(active);
//};



//void SudocuField::FillRandom()
//{
//    for (int i=0; i<FIELD_WIDTH; i++)
//    {
//        for (int j=0; j<FIELD_WIDTH; j++)
//        {
//            int possible=getPossible({i,j});
//            int numberOfBits=countBits(possible);
//            if (numberOfBits > 1 && rand() % 3 == 0 )
//            {
//                //cells[i][j].value = (rand() % 3 == 0 )? 0 : convertToBinary(rand() % 10);
//                //cells[i][j].isMaster = (rand() % 3 != 0 );
//                cells[i][j].value=selectBit(possible, rand() % numberOfBits+1);
//                cells[i][j].isMaster = true;
//            }
//            else
//            {
//                cells[i][j].value=0;
//                cells[i][j].isMaster = false;
//            }
//        }
//    }
//    active = {4,4};
//};

//void SudocuField::fillRandom(int numberOfAttempts)
//{
//    fillEmpty();
//    for (int i=0; i<numberOfAttempts; i++)
//    {
//        int line = rand() % FIELD_WIDTH;
//        int position = rand() % FIELD_WIDTH;
//        if (cells[line][position].value==0)
//        {
//            int possible = getPossible({line,position});
//            int numberOfBits=countBits(possible);
//
//            if (numberOfBits > 1)
//            {
//                cells[line][position].value=selectBit(possible, rand() % numberOfBits+1);
//                cells[line][position].isMaster = true;
//                if (getMinPossible() == 0)
//                {
//                    cells[line][position].value=0;
//                    cells[line][position].isMaster = false;
//                }
//                while (getMinPossible() == 1 && isNotSolved())
//                {
//                    std::cout << getMinPossible() << "\n";
//                    fillEvident();
//                }
//            }
//        }
//    }
//    active = {4,4};
//};


//void SudocuField::ShowPossible(CellPosition current)
//{
//    int possible=getPossible(current);
//    //cells[current.line][current.position].possibleValues;
//    int p=1;
//    for (int i=1; i<=MAX_CELL_VALUE; i++)
//    {
//        if (p&possible)
//        {
//            std::cout << i << "\n";
//        }
//        p*=2;
//    }
//};
