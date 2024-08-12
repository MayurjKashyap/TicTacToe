#pragma once

const int N = 3; 

typedef enum cellValue{
    EMPTY,
    CROSS,
    NOUGHT
} cellValue;

typedef struct cell{
    int xcoordinate;
    int ycoordinate;
    cellValue value;
} cell;

namespace board {
    typedef enum result{
        PLAYER1,
        PLAYER2,
        DRAW,
        ONGOING
    } result;
}


class Board {
public:
    Board();
    void draw(int xpos,int ypos);
    void update();
    void setCellDimensions();
    void setCell(int xcoordinate,int ycoordinate,cellValue value);
    void reset();
    int getCellWidth();
    int getCellHeight();
    bool isValidIndex(int x,int y);
    bool isEmpty(int x,int y);
    board::result getResult();

private:
    cell board[N][N];
    int cellWidth;
    int cellHeight;
    int emptyCellCount;
    board::result result;
};