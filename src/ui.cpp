#include "ui.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <math.h>

namespace UI{

    Canvas::Canvas(int w, int h){
        _w = w;
        _h = h;
        _count = 0;
        _col = new Color*[h];
        _canvas = new unsigned char*[h];
        for(int i = 0; i < h; i++){
            _canvas[i] = new unsigned char[w];
            _col[i] = new Color[w];
            for(int t = 0; t < w; t++){
                _canvas[i][t] = ' ';
            }
        }
    }

    void Canvas::Clear(){
        cout << "\033c";

        for(int y = 0; y < _h; y++){
            for(int x = 0; x < _w; x++){
                _canvas[y][x] = ' ';
            }
        }
    }
    
    void Canvas::Draw() const{  
        string col = "";      
        for(int y = 0; y < _h; y++){
            for(int x = 0; x < _w; x++){
                
                switch (_col[y][x])
                {
                    case white:
                        col = "\033[0;97m";
                        break;
                    case black:
                        col = "\033[0;30m";
                        break;
                    case blue:
                        col = "\033[0;94m";
                        break;
                    case red:
                        col = "\033[0;91m";
                        break;
                    case green:
                        col = "\033[0;92m";
                        break;
                    case yellow:
                        col = "\033[0;93m";
                        break;                
                    default:
                        break;
                }
                cout << col;
                cout << _canvas[y][x];
                cout << "\033[0;30m";
            }
            cout << endl;
        }
    }

    void Canvas::SetElements(vector<Element> _elements){
        for(unsigned i = 0; i < _elements.capacity(); i++){
            
            int x = _elements.at(i).GetX();
            int y = _elements.at(i).GetY();
            
            if(_elements.at(i).GetType() == rect){

                int w = _elements.at(i).GetW();
                int h = _elements.at(i).GetH();

                for(int width = w; width >= 0; width--){
                    for(int height = h; height >= 0; height--){
                        int tY = y+height;
                        int tX = x+width;
                        if(tY < 0 || tX < 0 || tX >= _w || tY >= _h)
                            continue;
                        _canvas[tY][tX] = '*';
                        _col[tY][tX] = _elements.at(i).GetFG();
                    }
                }

            }
            else if(_elements.at(i).GetType() == circle){

                int r = _elements.at(i).GetW();

                for(int ang = 0; ang < 360; ang += 1){
                    int tY = round(y + r*sin(ang));
                    int tX = round(x + r*cos(ang));
                    if(tY < 0 || tX < 0 || tX >= _w || tY >= _h)
                        continue;
                    _col[tY][tX] = _elements.at(i).GetFG();
                    _canvas[tY][tX] = '*';
                }
            }
        }
    }

    Canvas::~Canvas(){
        for(int i = 0; i < _h; i++){
            delete[] _col[i];
            delete[] _canvas[i];
        }
        delete[] _col;
        delete[] _canvas;
    }

    Element::Element(){
        _x = 0;
        _y = 0;
        _fg = black;
        _bg = black;
        _h = 0;
        _w = 0;
        _type = none;
    }

    Element::Element(int x, int y, Color fg, Color bg){
        _x = x;
        _y = y;
        _fg = fg;
        _bg = bg;
        _h = 1;
        _w = 1;
        _type = none;
    }
    
    void Element::SetPos(int x = 0, int y = 0){
        _x = x;
        _y = y;
    }
    
    int Element::GetX() const{
        return _x;
    }

    int Element::GetY() const{
        return _y;
    }
    
    int Element::GetH() const{
        return _h;
    }

    int Element::GetW() const{
        return _w;
    }

    Color Element::GetFG() const{
        return _fg;
    }

    Color Element::GetBG() const{
        return _bg;
    }

    UI_Type Element::GetType() const{
        return _type;
    }


    void Element::Draw() const{
        cout << "\x1b[C" << "Default Draw" << endl;
    }

    Rect::Rect(int x, int y, int w, int h, Color fg, Color bg){
        _x = x;
        _y = y;
        _w = w;
        _h = h;
        _fg = fg;
        _bg = bg;
        _type = rect;
    }

    void Rect::Draw() const{
        cout << "Rect Draw" << endl;
    }
    
    Circle::Circle(int x, int y, int r, Color fg, Color bg){
        _x = x;
        _y = y;
        _w = r;
        _h = r;
        _fg = fg;
        _bg = bg;
        _type = circle;
    }
}