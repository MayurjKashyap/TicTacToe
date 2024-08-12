#include <raylib.h>
#include <string>

#include "game.h"

int main()
{

    const int screenWidth = 800;
    const int screenHeight = 600;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Tic Tac Toe");
    SetWindowMinSize(450,450);
    Game Game;
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Game.updateFrame();
    }

    CloseWindow();
    return 0;
}