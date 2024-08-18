#include "raylib.h"
#include "board.h"
using namespace board;

Board::Board(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            board[i][j].xcoordinate=i;
            board[i][j].ycoordinate=j;
            board[i][j].value=EMPTY;
        }
    }
    emptyCellCount=9;
    result=ONGOING;
}

void Board::reset(){
    emptyCellCount=9;
    result=ONGOING;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            board[i][j].value=EMPTY;
}

void Board::drawBoard(){
    ClearBackground(RAYWHITE);
        for(int i=0;i<N;i++) {
            for(int j=0;j<N;j++) {
                drawCell(i,j);
            }
        }
}

void Board::drawCell(int xpos,int ypos){
    if(board[xpos][ypos].value==CROSS)
        DrawRectangle(xpos * cellWidth, ypos * cellHeight, cellWidth, cellHeight, RED);
    else if(board[xpos][ypos].value==NOUGHT)
        DrawRectangle(xpos * cellWidth, ypos * cellHeight, cellWidth, cellHeight, GREEN);
    DrawRectangleLines(xpos * cellWidth, ypos * cellHeight, cellWidth, cellHeight, BLACK);
}

void Board::update(){
    if(result!=ONGOING) return;
    bool end=false;
    for(int i=0;i<N;i++){
        if(!end && board[i][0].value!=EMPTY 
            && board[i][0].value==board[i][1].value
            && board[i][0].value==board[i][2].value) {
                result = (board[i][0].value==CROSS)? PLAYER1 : PLAYER2;
                end=true;
                break;
        }
    }

    if(!end)for(int i=0;i<N;i++){
        if(board[0][i].value!=EMPTY 
            && board[0][i].value==board[1][i].value
            && board[0][i].value==board[2][i].value) {
                result = (board[0][i].value==CROSS)? PLAYER1 : PLAYER2;
                end=true;
                break;
        }
    }

    if(!end && board[1][1].value!=EMPTY){
        if(board[0][0].value==board[1][1].value && board[0][0].value==board[2][2].value){
                result = (board[1][1].value==CROSS)? PLAYER1 : PLAYER2;
                end=true;
        }
        if(!end && board[0][2].value==board[1][1].value && board[2][0].value==board[0][2].value){
                result = (board[1][1].value==CROSS)? PLAYER1 : PLAYER2;
                end=true;
        }
    }

    if(!end && !emptyCellCount) result = DRAW;
}

void Board::setCellDimensions(){
    cellWidth = GetScreenWidth()/N;
    cellHeight = GetScreenHeight()/N;
}

void Board::setCell(int xcoordinate,int ycoordinate,cellValue value){
    board[xcoordinate][ycoordinate].value=value;
    --emptyCellCount;
}

int Board::getCellWidth(){
    return cellWidth;
}

int Board::getCellHeight(){
    return cellHeight;
}

bool Board::isValidIndex(int x,int y){
    return x>=0 && x<N && y>=0 && y<N;
}

bool Board::isEmpty(int x,int y){
    return board[x][y].value==EMPTY;
}

result Board::getResult(){
    return result;
}