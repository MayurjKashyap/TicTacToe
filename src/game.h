#pragma once

#include "board.h"
#include "button.h"

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
    void handleClick();
    void handleBoardClick();
    void handleRestartClick();
    void reset();

private:
    Board board;
    gameState gameState;
    TextBox banner;
    Button restart;
};
