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

class Board {
public:
    Board();
    void draw(int xpos,int ypos);
    void update();
    void check();
    void setCellDimensions();

private:
    cell board[N][N];
    int cellWidth;
    int cellHeight;
};