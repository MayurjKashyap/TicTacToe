#include "raylib.h"
#include "game.h"
#include "button.h"

Game::Game(): 
            board(),
            banner("",36,10,20,LIGHTGRAY),
            restart("RESTART",36,40,50,40,GREEN) {
    gameState=PLAYER1;
}

void Game::updateFrame(){
    board.setCellDimensions();
    banner.setDimensions();
    restart.setButtonDimensions();
    handleClick();
    board.update();
    updateGameState();
    drawFrame();
}

void Game::drawFrame(){
    board.setCellDimensions();
    BeginDrawing();
    
        ClearBackground(RAYWHITE);
        for(int i=0;i<N;i++) {
            for(int j=0;j<N;j++) {
                board.draw(i,j);
            }
        }

    if(gameState==END) {
        banner.draw();
        restart.draw();
    }
    EndDrawing();
}

void Game::updateGameState(){
    if(board.getResult()!=board::ONGOING) {
        gameState=END;
        switch (board.getResult())
        {
        case board::PLAYER1 :
            banner.setString("PLAYER 1 WINS");
            break;

        case board::PLAYER2 :
            banner.setString("PLAYER 2 WINS");
            break;

        case board::DRAW :
            banner.setString("IT'S A DRAW");
            break;
        }
    }
}

void Game::handleClick(){
    if(gameState==END){
        handleRestartClick();
    } else {
        handleBoardClick();
    }
}

void Game::handleBoardClick(){
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		Vector2 mPos = GetMousePosition();
		int xIndex = mPos.x / board.getCellWidth();
		int yIndex = mPos.y / board.getCellHeight();

		if(board.isValidIndex(xIndex,yIndex) && gameState!=END && board.isEmpty(xIndex,yIndex)){
            cellValue value = (gameState==PLAYER1)? CROSS : NOUGHT;
            board.setCell(xIndex,yIndex,value);
            gameState = (gameState==PLAYER1)? PLAYER2 : PLAYER1;
        }
	}
}

void Game::handleRestartClick(){
    if(restart.isClicked()){
        reset();
    }
}

void Game::reset(){
    gameState=PLAYER1;
    board.reset();
}