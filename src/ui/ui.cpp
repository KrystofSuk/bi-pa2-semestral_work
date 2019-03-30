#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <math.h>
#include "ui.h"
#include "ui_elements.h"

namespace UI{

    Pixel::Pixel(){
        _c = ' ';
        _col = Black;
    }
    Pixel::Pixel(const char & c, const Color & col){
        _c = c;
        _col = col;
    }

    char Pixel::GetChar() const{
        return _c;
    }

    Color Pixel::GetCol() const{
        return _col;
    }

    Canvas::Canvas(){
        _w = 0;
        _h = 0;
        _count = 0;
        _canvas = NULL;
    }

    Canvas::Canvas(const int & w, const int & h){
        _w = w;
        _h = h;
        _count = 0;
        _canvas = new Pixel*[h];

        for(int i = 0; i < h; i++){
            _canvas[i] = new Pixel[w];
            for(int t = 0; t < w; t++){
                _canvas[i][t] = Pixel(' ', Black);
            }
        }
    }

    void Canvas::Clear(){
        cout << "\033c";
        /*
        string t = "\033[";
        t.append(to_string(_h+2));
        t.append("A");
        cout << t;\
        */
        for(int y = 0; y < _h; y++){
            for(int x = 0; x < _w; x++){
                _canvas[y][x] = Pixel();
            }
        }
    }
    
    void Canvas::Draw(){
        system("stty sane"); 
        for(size_t i = 0; i < _layer.size(); i++) {
            _layer .at(i) -> Draw(_canvas, _w, _h);
        }
        
        string col = "";      
        for(int y = -1; y <= _h; y++){
            for(int x = -1; x <= _w; x++){
                col = "\033[0;37m";
                if(y == -1 && x == -1){
                    cout << col << "┌";
                }
                else if(y == -1 && x == _w){
                    cout << col << "┐";
                }
                else if(y == _h && x == -1){
                    cout << col << "└";
                }
                else if(y == _h && x == _w){
                    cout << col << "┘";
                }
                else if(y == -1){
                    cout << col << "─";
                }
                else if(y == _h){
                    cout << col << "─";
                }
                else if(x == -1 || x == _w){
                    cout << col << "│";
                }
                else{
                    switch (_canvas[y][x].GetCol())
                    {
                        case White:
                            col = "\033[0;37m";
                            break;
                        case Black:
                            col = "\033[0;30m";
                            break;
                        case Blue:
                            col = "\033[0;34m";
                            break;
                        case Red:
                            col = "\033[0;31m";
                            break;
                        case Green:
                            col = "\033[0;32m";
                            break;
                        case Yellow:
                            col = "\033[0;33m";
                            break;                
                        default:
                            break;
                    }
                    cout << col << _canvas[y][x].GetChar();
                }
            }
            cout << endl;
        }
    }

    void Canvas::AddElement(Element * e){
        _layer.push_back(e);
    }

    Canvas::~Canvas(){
        for(int i = 0; i < _h; i++){
            delete[] _canvas[i];
        }
        for(size_t i = 0; i < _layer.size(); i++){
            delete _layer.at(i);
        }
        delete[] _canvas;
    }

    Element::Element(){
        _x = 0;
        _y = 0;
        _px = Pixel();
    }

    Element::Element(const int & x, const int & y, const char & c, const Color & fg){
        _x = x;
        _y = y;
        _px = Pixel(c, fg);
    }
    
    void Element::SetPos(const int & x = 0, const int & y = 0){
        _x = x;
        _y = y;
    }
    
    int Element::GetX() const{
        return _x;
    }

    int Element::GetY() const{
        return _y;
    }

    Pixel Element::GetPixel() const{
        return _px;
    }

    void Element::Draw(Pixel ** canvas, int w, int h) const{
    }
}