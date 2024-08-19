#pragma once
#include <string>

#include "helper.h"

class TextBox{
public:
    TextBox(std::string str,int fontsize,int x,int y,Colour c);
    void setString(std::string str);
    void draw();
    void setDimensions();

protected:
    std::string text;
    Rect rect;
    int fontSize;
    float offset;
    int xpercent;
    int ypercent;
    Colour color;
};

class Button: public TextBox{
public:
    Button(std::string str,int fontsize,int x,int y,int yb,Colour c);
    void setButtonDimensions();
    bool isClicked();

private:
    int ybottom;
};