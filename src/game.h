#pragma once
#include <memory>
#include "board.h"
#include "button.h"
#include "network.h"

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
    void handleRestartClick();
    void reset();
    void setGameState(gameState s);
    void setServer(bool flag);
    void setNetwork(bool f);

private:
    Board board;
    gameState gameState;
    TextBox banner;
    Button restart;
    bool isServer;
    bool turn;
    std::unique_ptr<Network> network;
};
