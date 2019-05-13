
#include "units.h"
#include "unit.h"
#include "maps.h"
#include <iostream>
#include <limits>
#include <math.h>

#include "../extras/file.h"

namespace GameLogic
{
Slime::Slime() : Unit()
{
}
Slime::Slime(pair<int, int> s, string n) : Unit()
{
    _hp = stoi(Extra::File<string>::LoadFromFile("./examples/units/" + n, "HP"));
    _c = Extra::File<string>::LoadFromFile("./examples/units/" + n, "Char")[0];
    _name = Extra::File<string>::LoadFromFile("./examples/units/" + n, "Name");
    _atk = stoi(Extra::File<string>::LoadFromFile("./examples/units/" + n, "ATK"));
    string col = Extra::File<string>::LoadFromFile("./examples/units/" + n, "Color");
    string pth = Extra::File<string>::LoadFromFile("./examples/units/" + n, "MOV");
    if (pth == "PTH")
    {
        _movType = 0;
    }
    if (pth == "BFS")
    {
        _movType = 1;
    }
    if (col == "B")
        _col = Blue;
    if (col == "G")
        _col = Green;
    if (col == "Y")
        _col = Yellow;
    if (col == "R")
        _col = Red;
    if (col == "W")
        _col = White;

    _pos.first = s.first;
    _pos.second = s.second;
}
void Slime::ProcessAttack(const int &a, const UnitResistance::ResistanceType &atk)
{
    _hp -= a;
    if(atk == UnitResistance::ResistanceType::Ice){
        _hp -= a;
    }
    if(atk == UnitResistance::ResistanceType::Fire){
        _hp -= a;
    }
    if (_hp < 0)
    {
        _hp = 0;
    }
}
void Slime::Move(const Map &m)
{
    _pos = m.BFS(_pos);
}
void Slime::GetChar(char **c) const
{
    c[_pos.first][_pos.second] = _c;
}
void Slime::GetColor(Color **c) const
{
    c[_pos.first][_pos.second] = _col;
}
void Slime::Print(ostream &os) const
{
    os << "| " << setw(22) << left << setfill(' ') << _name << " |" << endl;
    os << " ------------------------ " << endl;
    os << "|     ATK    |     HP    |" << endl;
    os << "| " << setw(10) << left << setfill(' ') << _atk << " | " << setw(9) << left << setfill(' ') << _hp << " |";
}
Slime::~Slime()
{
}


SlimeKing::SlimeKing() : Slime(){

}
SlimeKing::SlimeKing(pair<int, int> s, string n) : Slime(s, n){

}
void SlimeKing::Move(const Map &m){
    _pos = m.BFS(_pos);
}
SlimeKing::~SlimeKing(){

}
}