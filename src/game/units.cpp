
#include "units.h"
#include "unit.h"
#include "maps.h"
#include <iostream>

#include "../extras/file.h"

namespace GameLogic
{
    Slime::Slime() : Unit(){

    }
    Slime::Slime(pair<int, int> s) : Unit(){
        _hp = stoi(Extra::File<string>::LoadFromFile("res/units/slime", "HP"));
        _c = Extra::File<string>::LoadFromFile("res/units/slime", "Char")[0];
        string _name = Extra::File<string>::LoadFromFile("res/units/slime", "Name");
        _atk = stoi(Extra::File<string>::LoadFromFile("res/units/slime", "ATK"));
        string col = Extra::File<string>::LoadFromFile("res/units/slime", "Color");
        string pth = Extra::File<string>::LoadFromFile("res/units/slime", "MOV");
        if(pth == "PTH"){
            _movType = 0;
        }
        if(pth == "BFS"){
            _movType = 1;
        }
        if(col == "B")
            _col = Blue;
        if(col == "G")
            _col = Green;
        if(col == "Y")
            _col = Yellow;
        if(col == "R")
            _col = Red;
        if(col == "W")
            _col = White;

        //cout << "Loaded: " << _name << " " << _hp << "," << _atk << endl;

        _pos.first = s.first;
        _pos.second = s.second;
    }
    void Slime::Move(const Map & m){
        _pos = m.BFS(_pos);
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