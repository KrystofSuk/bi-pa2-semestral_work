#include "ui_elements.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <math.h>

using namespace std;
namespace UI{
    Rect::Rect(const int & x, const int & y, const int & w, const int & h, const Color & fg, const char & c){
        _x = x;
        _y = y;
        _w = w;
        _h = h;
        _px = Pixel(c, fg);
    }

    void Rect::Draw(Pixel ** canvas, int w, int h) const{
        for(int width = _w; width >= 0; width--){
            for(int height = _h; height >= 0; height--){
                int tY = _y+height;
                int tX = _x+width;
                if(tY < 0 || tX < 0 || tX >= w || tY >= h)
                    continue;
                canvas[tY][tX] = _px;
            }
        }
    }
    
    Circle::Circle(const int & x, const int & y, const double & r, const Color & fg, const char & c){
        _x = x;
        _y = y;
        _r = r;
        _px = Pixel(c, fg);
    }

    void Circle::Draw(Pixel ** canvas, int w, int h) const{
        for(int ang = 0; ang < 360; ang += 1){
            int tY = round(_y + _r * sin(ang));
            int tX = round(_x + _r * cos(ang));
            if(tY < 0 || tX < 0 || tX >= w || tY >= h)
                continue;
            canvas[tY][tX] = _px;
        }
    }
    
    void Arc::Draw(Pixel ** canvas, int w, int h) const{
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

    Text::Text(const int & x, const int & y, const Color & fg, const string & text){
        _x = x;
        _y = y;
        _text = text;
        for(int i = 0; i< _text.size(); i++)
            _pixels.push_back(Pixel(_text[i], fg));
    }

    void Text::Draw(Pixel ** canvas, int w, int h) const{
        for(int i = 0; i < _text.size(); i++){
            int tX = round(_x + i);
            if(_y < 0 || tX < 0 || tX >= w || _y >= h)
                return;
            canvas[_y][tX] = _pixels[i];
        }
    }
}