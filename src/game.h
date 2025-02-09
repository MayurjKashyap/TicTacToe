#pragma once
#include <memory>
#include <thread>

#include "board.h"
#include "button.h"
#include "network.h"

extern bool quitGame;

typedef enum gameState{
    END,
    PLAYER1,
    PLAYER2
} gameState;

class Game{
public:
    Game();
    void updateFrame();
    void drawFrame();
    void updateGameState();
    void setDimensions();
    void handleClick();
    void handleBoardClick();
    void handleEndClick();
    void reset();
    void setGameState(gameState s);
    void setServer(bool flag);
    void setNetwork(bool f);
    void receiveDataLoop();
    void sendData();

private:
    Board board;
    gameState gameState;
    TextBox banner;
    Button restart;
    Button quit;
    bool isServer;
    bool turn;
    bool threadFlag;
    std::unique_ptr<Network> network;
    std::thread receiveThread;
    std::thread tempThread;
};
