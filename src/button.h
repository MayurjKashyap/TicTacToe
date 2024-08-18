#pragma once

#include <string>

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