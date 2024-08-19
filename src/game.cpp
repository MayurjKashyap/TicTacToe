#include <string>
#include <memory>
#include <thread>

#include "game.h"
#include "button.h"
#include "network.h"
#include "helper.h"

#define LIGHTGRAY Colour{200,200,200,255}
#define GREEN Colour{0,228,48,255}
#define RED Colour{230, 41, 55, 255}
#define RAYWHITE Colour{245,245,245,255}

Game::Game(): 
            board(),
            banner("",36,10,20,LIGHTGRAY),
            restart("RESTART",36,40,40,50,GREEN),
            quit("QUIT",36,40,50,40,RED) {
    setGameState(PLAYER1);
    setServer(false);
    threadFlag=true;
}

void Game::updateFrame(){
    handleClick();
    if(gameState!=END){
        board.update();
        updateGameState();
    }
    if(gameState==END){
        setDimensions();
    }
    drawFrame();
}

void Game::drawFrame(){
    board.setCellDimensions();
    startDrawing();
    
    board.drawBoard();
    if(gameState==END) {
        banner.draw();
        restart.draw();
        quit.draw();
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
    board.setCellDimensions();
    if(gameState==END){
        handleEndClick();
    } else {
        handleBoardClick();
    }
}

void Game::handleBoardClick(){
    if (isMouseClicked()&&turn)
	{
		int xIndex = getMouseX(board);
		int yIndex = getMouseY(board);
		if(board.isValidIndex(xIndex,yIndex) && gameState!=END && board.isEmpty(xIndex,yIndex)){
            cellValue value = (gameState==PLAYER1)? CROSS : NOUGHT;
            board.setCell(xIndex,yIndex,value);
            std::string str="MV"+std::to_string(xIndex)+std::to_string(yIndex);
            strcpy(Sbuffer,str.basic_string::c_str());
            
            tempThread = std::thread(&Game::sendData, this);
            tempThread.detach();
            
            gameState = (gameState==PLAYER1)? PLAYER2 : PLAYER1;
            turn=false;
        }
	}
}

void Game::handleEndClick(){
    if(isServer && restart.isClicked()){
        strcpy(Sbuffer,"RESTART");
        tempThread = std::thread(&Game::sendData, this);
        tempThread.detach();
        reset();
    }
    else if (quit.isClicked()){
        strcpy(Sbuffer,"QUIT");
        tempThread = std::thread(&Game::sendData, this);
        tempThread.detach();
        quitGame=true;
    }
}

void Game::reset(){
    gameState=PLAYER1;
    turn=isServer;
    board.reset();
}

void Game::setGameState(enum gameState s){
    gameState=s;
}

void Game::setDimensions(){
    if(gameState==END){
        banner.setDimensions();
        restart.setButtonDimensions();
        quit.setButtonDimensions();
    }
}

void Game::setServer(bool flag){
    isServer=flag;
}

void Game::setNetwork(bool flag){
    if(flag){
        setServer(true);
        turn=true;
        network = std::make_unique<Server>();
    }
    else {
        setServer(false);
        turn=false;
        network = std::make_unique<Client>();
    }
    network->initialization();
    if(!flag) network->IPaddress="127.0.0.1";
    network->connectNetwork();
    receiveThread = std::thread(&Game::receiveDataLoop, this);
    receiveThread.detach();
}

void Game::receiveDataLoop() {
    while (threadFlag) {
        if(network->receiveData()) break;
        if (!turn && Rbuffer[0] == 'M' && Rbuffer[1] == 'V') {
            int xIndex = Rbuffer[2] - '0';
            int yIndex = Rbuffer[3] - '0';
            cellValue value = (gameState == PLAYER1) ? CROSS : NOUGHT;
            board.setCell(xIndex, yIndex, value);
            gameState = (gameState == PLAYER1) ? PLAYER2 : PLAYER1;
            turn = true;
        } else if (strcmp(Rbuffer, "RESTART") == 0) {
            reset();
        } else if (strcmp(Rbuffer, "QUIT") == 0) {
            network->close();
            threadFlag=false;
            quitGame=true;
        }
    }
}

void Game::sendData(){
    network->sendData();
}