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
    
    Arc::Arc(const int & x, const int & y, const double & r, const Color & fg, const string & c) : Circle(x, y, r, fg, c){
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
    
    UIInteraction::UIInteraction(const Color & fg){
        _active = fg;
    }


    UIInteraction::~UIInteraction(){
    } 

    Button::Button(const int & x, const int & y, const Color & fg, const string & text, const Color & activeFg, const int & index) : UIInteraction(activeFg), Text(x,y,fg,text){
        _deActive = fg;
        _stateIndex = index;
    }

    void Button::SetNextElements(Button * l, Button * r, Button * t, Button * b){
        _l = l;
        _r = r;
        _t = t;
        _b = b;
    }

    void Button::Active(){
        for(int i = 0; i < _pixels.size(); i++)
            _pixels.at(i).SetColor(_active);
    }

    void Button::Deactivate(){
        for(int i = 0; i < _pixels.size(); i++)
            _pixels.at(i).SetColor(_deActive);
    }

    Button * Button::GetNext(Direction dir){
        switch (dir)
        {
            case Left:
                if(_l != NULL){
                    Deactivate();
                    _l -> Active();
                    return _l;
                }
                return this;
            case Up:
                if(_t != NULL){
                    Deactivate();
                    _t -> Active();
                    return _t;
                }
                return this;
            case Down:
                if(_b != NULL){
                    Deactivate();
                    _b -> Active();
                    return _b;
                }
                return this;
            case Right:
                if(_r != NULL){
                    Deactivate();
                    _r -> Active();
                    return _r;
                }
                return this;
            case Zero:
                Active();
                return this;
        }
    }
    
    const int & Button::GetIndex() const{
        return _stateIndex;
    }

    Button::~Button(){
    }
}