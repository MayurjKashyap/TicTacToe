#pragma once

#include <string>
#include "raylib.h"

class TextBox{
public:
    TextBox(std::string str,int fontsize,int x,int y,Color c);
    void setString(std::string str);
    void draw();
    void setDimensions();

protected:
    std::string text;
    Rectangle rect;
    int fontSize;
    float offset;
    int xpercent;
    int ypercent;
    Color color;
};

class Button: public TextBox{
public:
    Button(std::string str,int fontsize,int x,int y,int yb,Color c);
    void setButtonDimensions();
    bool isClicked();

private:
    int ybottom;
};