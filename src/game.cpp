#include <string>
#include <memory>
#include "game.h"
#include "button.h"
#include "network.h"
#include "helper.h"

int abc;

#define LIGHTGRAY Colour{200,200,200,255}
#define GREEN Colour{0,228,48,255}
#define RAYWHITE Colour{245,245,245,255}

Game::Game(): 
            board(),
            banner("",36,10,20,LIGHTGRAY),
            restart("RESTART",36,40,50,40,GREEN) {
    setGameState(PLAYER1);
    setServer(false);
}

void Game::updateFrame(){
    setDimensions();
    handleClick();
    board.update();
    updateGameState();
    drawFrame();
}

void Game::drawFrame(){
    board.setCellDimensions();
    startDrawing();
    
    board.drawBoard();

    if(gameState==END) {
        banner.draw();
        restart.draw();
    }

    endDrawing();
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

        default: break;
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
    if(turn==false) {
        abc = network->receiveData();
        if(buffer[0]=='M'&&buffer[1]=='V'){
            int xIndex=buffer[2]-'0';
            int yIndex=buffer[3]-'0';
            cellValue value = (gameState==PLAYER1)? CROSS : NOUGHT;
            board.setCell(xIndex,yIndex,value);
            gameState = (gameState==PLAYER1)? PLAYER2 : PLAYER1;
            turn=true;
        }
    }
    else {
        if (isMouseClicked())
	    {
	    	int xIndex = getMouseX(board);
	    	int yIndex = getMouseY(board);

	    	if(board.isValidIndex(xIndex,yIndex) && gameState!=END && board.isEmpty(xIndex,yIndex)){
                cellValue value = (gameState==PLAYER1)? CROSS : NOUGHT;
                board.setCell(xIndex,yIndex,value);
                std::string str="MV"+std::to_string(xIndex)+std::to_string(yIndex);
                strcpy(buffer,str.basic_string::c_str());
                abc = network->sendData();
                gameState = (gameState==PLAYER1)? PLAYER2 : PLAYER1;
                // turn=false;
            }
	    }
    }
}

void Game::handleRestartClick(){
    if(isServer && restart.isClicked()){
        strcpy(buffer,"RESTART");
        abc =network->sendData();
        reset();
    }
    else {
        abc =network->receiveData();
        if(strcmp(buffer,"RESTART")){
            reset();
        }
    }
}

void Game::reset(){
    gameState=PLAYER1;
    ZeroMemory(buffer,BUFFER_SIZE);
    board.reset();
}

void Game::setGameState(enum gameState s){
    gameState=s;
}

void Game::setDimensions(){
    board.setCellDimensions();
    banner.setDimensions();
    restart.setButtonDimensions();
}

void Game::setServer(bool flag){
    isServer=flag;
}

void Game::setNetwork(bool f){
    if(f){
        setServer(true);
        turn=true;
        network = std::make_unique<Server>();
    }
    else {
        setServer(false);
        turn=false;
        network = std::make_unique<Client>();
    }
    network->IPaddress="127.0.0.1";
    abc = network->initialization();
}