
#include "units.h"
#include "unit.h"
#include <iostream>

namespace GameLogic
{
    Slime::Slime() : Unit(){

    }
    Slime::Slime(pair<int, int> s) : Unit(){
        _pos.first = s.first;
        _pos.second = s.second;
    }
    void Slime::Move(){
        std::cout << "Slime M" << endl;
    }
    void Slime::GetChar(char ** c) const{
        c[_pos.first][_pos.second] = _c;
    }
    void Slime::GetColor(Color ** c) const{
        c[_pos.first][_pos.second] = _col;
    }
    Slime::~Slime(){

    }
}