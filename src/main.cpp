#include <raylib.h>
#include <string>
#include<iostream>

#include "game.h"

int main()
{
    int i=0;
    std::cin>>i;

    const int screenWidth = 800;
    const int screenHeight = 600;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Tic Tac Toe");
    SetWindowMinSize(450,450);
    Game Game;
    if(i) Game.setNetwork(true);
    else Game.setNetwork(false);
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Game.updateFrame();
    }

    CloseWindow();
    return 0;
}