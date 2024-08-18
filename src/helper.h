#pragma once
#include "board.h"

void init(int w,int h);
bool windowcondition();
void close();
bool isMouseClicked();
int getMouseX(Board& b);
int getMouseY(Board& b);
void startDrawing();
void endDrawing();