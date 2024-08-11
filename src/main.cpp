#include <raylib.h>
#include <string>

#include "game.h"

int main()
{

    const int screenWidth = 800;
    const int screenHeight = 600;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Tic Tac Toe");
    Game Game;
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // BeginDrawing();
        // ClearBackground(darkGreen);
        // Vector2 x;
        // if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        //     x=GetMousePosition();
        //     std::string y= "X pos= "+ std::to_string(x.x) + "Y pos= "+std::to_string(x.y);
        //     DrawText(y.c_str(),200,200,16,Color{255,0,0,255});
        // }
        // EndDrawing();
        Game.updateFrame();
    }

    CloseWindow();
    return 0;
}