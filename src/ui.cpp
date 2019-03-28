#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <math.h>
#include "ui.h"

namespace UI{

    Pixel::Pixel(){
        _c = ' ';
        _col = black;
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

    Canvas::Canvas(const int & w, const int & h){
        _w = w;
        _h = h;
        _count = 0;
        _canvas = new Pixel*[h];

        for(int i = 0; i < h; i++){
            _canvas[i] = new Pixel[w];
            for(int t = 0; t < w; t++){
                _canvas[i][t] = Pixel(' ', black);
            }
        }
    }

    void Canvas::Clear(){
        cout << "\033c";
        for(int y = 0; y < _h; y++){
            for(int x = 0; x < _w; x++){
                _canvas[y][x] = Pixel(' ', black);
            }
        }
    }
    
    void Canvas::Draw() const{  
        string col = "";      
        for(int y = 0; y < _h; y++){
            for(int x = 0; x < _w; x++){
                switch (_canvas[y][x].GetCol())
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
                cout << _canvas[y][x].GetChar();
                //cout << "\033[0;30m";
            }
            cout << endl;
        }
    }

    void Canvas::AddElement(const Element & a){
        a.Draw(_canvas, _w, _h);
            /*
            int x = element.at(i).GetX();
            int y = element.at(i).GetY();
            
            if(element.at(i).GetType() == rect){

                int w = element.at(i).GetW();
                int h = element.at(i).GetH();

                for(int width = w; width >= 0; width--){
                    for(int height = h; height >= 0; height--){
                        int tY = y+height;
                        int tX = x+width;
                        if(tY < 0 || tX < 0 || tX >= _w || tY >= _h)
                            continue;
                        _canvas[tY][tX] = element.at(i).GetChar();
                        _col[tY][tX] = element.at(i).GetFG();
                    }
                }

            }
            else if(element.at(i).GetType() == circle){

            }
        }
        */
    }

    Canvas::~Canvas(){
        for(int i = 0; i < _h; i++){
            delete[] _canvas[i];
        }
        delete[] _canvas;
    }

    Element::Element(){
        _x = 0;
        _y = 0;
        _px = Pixel(' ', black);
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