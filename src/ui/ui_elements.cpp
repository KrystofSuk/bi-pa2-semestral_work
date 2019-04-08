#include "ui_elements.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <math.h>

using namespace std;
namespace UI{
    Rect::Rect(const int & x, const int & y, const int & w, const int & h, const Color & fg, const string & c){
        _x = x;
        _y = y;
        _w = w;
        _h = h;
        _px = Pixel(c, fg);
    }

    void Rect::Draw(Pixel ** canvas, const int & w, const int & h) const{
        for(int width = _w-1; width >= 0; width--){
            for(int height = _h-1; height >= 0; height--){
                int tY = _y+height;
                int tX = _x+width;
                if(tY < 0 || tX < 0 || tX >= w || tY >= h)
                    continue;
                canvas[tY][tX] = _px;
            }
        }
    }

    Rect::~Rect(){

    }
    
    Circle::Circle(const int & x, const int & y, const double & r, const Color & fg, const string & c){
        _x = x;
        _y = y;
        _r = r;
        _px = Pixel(c, fg);
    }

    void Circle::Draw(Pixel ** canvas, const int & w, const int & h) const{
        for(int ang = 0; ang < 360; ang += 1){
            int tY = round(_y + _r * sin(ang));
            int tX = round(_x + _r * cos(ang));
            if(tY < 0 || tX < 0 || tX >= w || tY >= h)
                continue;
            canvas[tY][tX] = _px;
        }
    }

    Circle::~Circle(){

    }
    
    Arc::Arc(const int & x, const int & y, const double & r, const Color & fg, const string & c){
        _x = x;
        _y = y;
        _r = r;
        _px = Pixel(c, fg);
    }
    
    void Arc::Draw(Pixel ** canvas, const int & w, const int & h) const{
        for(double i = _r; i >= 0; i -= 0.5){
            for(int ang = 0; ang < 360; ang += 1){
                int tY = round(_y + i * sin(ang));
                int tX = round(_x + i * cos(ang));
                if(tY < 0 || tX < 0 || tX >= w || tY >= h)
                    continue;
                canvas[tY][tX] = _px;
            }
        }
    }

    Arc::~Arc(){

    }

    Text::Text(const int & x, const int & y, const Color & fg, const string & text){
        _x = x;
        _y = y;
        _text = text;
        for(int i = 0; i< _text.size(); i++){
            Pixel px (string(1,_text[i]), fg);
            _pixels.push_back(px);
        }
    }

    void Text::Draw(Pixel ** canvas, const int & w, const int & h) const{
        for(int i = 0; i < _text.size(); i++){
            int tX = round(_x + i);
            if(_y < 0 || tX < 0 || tX >= w || _y >= h)
                return;
            canvas[_y][tX] = _pixels[i];
        }
    }

    Text::~Text(){

    }
    
    UIInteraction::UIInteraction(const Color & fg, const string & c){
        _active = Pixel(c, fg);
    }

    void UIInteraction::SetNextElements(UIInteraction * l, UIInteraction * r, UIInteraction * t, UIInteraction * b){
        _l = l;
        _r = r;
        _t = t;
        _b = b;
    }

    UIInteraction::~UIInteraction(){
        if(_l)
            delete _l;
        if(_r)
            delete _r;
        if(_t)
            delete _t;
        if(_b)
            delete _b;
    } 

    Button::Button(const int & x, const int & y, const Color & fg, const string & text, const Color & activeFg, const string & activeC) : UIInteraction(activeFg, activeC), Text(x,y,fg,text){
    }

    Button::~Button(){
        
    }
}