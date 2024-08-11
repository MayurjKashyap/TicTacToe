#include "raylib.h"
#include "game.h"

Game::Game(): board(){
}

void Game::updateFrame(){
    board.setCellDimensions();
    BeginDrawing();

        ClearBackground(RAYWHITE);
        for(int i=0;i<N;i++) {
            for(int j=0;j<N;j++) {
                board.draw(i,j);
            }
        }
        
    EndDrawing();
}