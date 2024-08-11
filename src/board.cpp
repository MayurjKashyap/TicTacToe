#include "raylib.h"
#include "board.h"

Board::Board(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            board[i][j].xcoordinate=i;
            board[i][j].ycoordinate=j;
            board[i][j].value=EMPTY;
        }
    }
    setCellDimensions();
}

void Board::draw(int xpos,int ypos){
    DrawRectangleLines(xpos * cellWidth, ypos * cellHeight, cellWidth, cellHeight, BLACK);
}

void Board::setCellDimensions(){
    cellWidth = GetScreenWidth()/N;
    cellHeight = GetScreenHeight()/N;
}