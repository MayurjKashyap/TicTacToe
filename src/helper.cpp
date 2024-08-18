#include "raylib.h"
#include "helper.h"
#include "board.h"

void init(int w,int h){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(w, h, "Tic Tac Toe");
    SetWindowMinSize(450,450);
    // SetTargetFPS(60);
}

bool windowcondition(){
    return !WindowShouldClose();
}

void close(){
    CloseWindow();
}

bool isMouseClicked(){
    return IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
}

int getMouseX(Board& b){
    Vector2 mPos = GetMousePosition();
	return mPos.x / b.getCellWidth();
}

int getMouseY(Board& b){
    Vector2 mPos = GetMousePosition();
	return mPos.y / b.getCellHeight();
}

void startDrawing(){
    BeginDrawing();
}

void endDrawing(){
    EndDrawing();
}