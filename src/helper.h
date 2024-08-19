#pragma once

#include "board.h"

typedef struct Colour {
    unsigned char r;        // Color red value
    unsigned char g;        // Color green value
    unsigned char b;        // Color blue value
    unsigned char a;        // Color alpha value
} Colour;

typedef struct Rect {
    float x;                // Rectangle top-left corner position x
    float y;                // Rectangle top-left corner position y
    float width;            // Rectangle width
    float height;           // Rectangle height
} Rect;

void init(int w,int h);
bool windowcondition();
void close();
bool isMouseClicked();
int getMouseX(Board& b);
int getMouseY(Board& b);
void startDrawing();
void endDrawing();