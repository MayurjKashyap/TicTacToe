#include <string>

#include "raylib.h"
#include "button.h"
#include "helper.h"

Color convert(Colour c){
    return Color{c.r,c.g,c.b,c.a};
}

Rectangle convert(Rect r){
    return Rectangle{r.x,r.y,r.width,r.height};
}

TextBox::TextBox(std::string str,int fontsize,int x,int y,Colour c){
    text=str;
    xpercent=x;
    ypercent=y;
    fontSize=fontsize;
    color=c;
    setDimensions();
}

void TextBox::setString(std::string str){
    text=str;
}

void TextBox::draw(){
    DrawRectangle(rect.x,rect.y,rect.width,rect.height,convert(color));
    DrawText(text.basic_string::c_str(),offset,rect.y+((float)rect.height*0.25),fontSize,BLACK);
}

void TextBox::setDimensions(){
    int w=GetScreenWidth();
    int h=GetScreenHeight();
    
    Rect r;
        r.x=(w*xpercent)/100;
        r.y=(h*ypercent)/100;
        r.width=(w*(100-2*xpercent))/100;
        r.height=(h*(100-2*ypercent))/100;
    rect=r;

    if(w<600) {
        fontSize=16;
    } else if (w<1000){
        fontSize=24;
    } else{
        fontSize=36;
    } 
    
    offset=(w-MeasureText(text.basic_string::c_str(),fontSize))/2;
}

bool Button::isClicked(){
    Vector2 mousePos = GetMousePosition();
    if (CheckCollisionPointRec(mousePos, convert(rect))) {
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) return true;
        }
    return false;
}

Button::Button(std::string str,int fontsize,int x,int y,int yb,Colour c)
    : TextBox(str,fontSize,x,y,c) {
        ybottom=yb;
        setButtonDimensions();
}

void Button::setButtonDimensions(){
    setDimensions();
    rect.height=(GetScreenHeight()*(100-ypercent-ybottom))/100;
    int s=MeasureText(text.basic_string::c_str(),fontSize);
    rect.width=(s*140)/100;
    rect.x=offset-(s*20)/100;
}