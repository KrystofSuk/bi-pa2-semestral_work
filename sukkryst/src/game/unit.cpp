#include <iostream>
#include <string>
#include <limits>
#include <math.h>
#include "unit.h"

namespace GameLogic
{
UnitResistance::UnitResistance(int res = 2)
{
    if (res < 0)
    {
        std::cerr << "Wrong res" << endl;
        res = 0;
    }
    _resistance = res;
}
UnitResistance::~UnitResistance() {}
Unit::Unit()
{
}
Unit::Unit(const string & n = "")
{
    _hp = stoi(Extra::File<string>::LoadFromFile("./examples/units/" + n, "HP"));
    _c = Extra::File<string>::LoadFromFile("./examples/units/" + n, "Char")[0];
    _name = Extra::File<string>::LoadFromFile("./examples/units/" + n, "Name");
    _atk = stoi(Extra::File<string>::LoadFromFile("./examples/units/" + n, "ATK"));
    string col = Extra::File<string>::LoadFromFile("./examples/units/" + n, "Color");
    string pth = Extra::File<string>::LoadFromFile("./examples/units/" + n, "MOV");
    if (pth == "DFS")
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
    if (col == "C")
        _col = Cyan;
    if (col == "M")
        _col = Magenta;
}
pair<int, int> Unit::GetPos() const
{
    return _pos;
}
void Unit::ClearPath(){
    _path.clear();
}
void Unit::GetChar(char **c) const
{
    c[_pos.first][_pos.second] = _c;
}
void Unit::GetColor(Color **c) const
{
    c[_pos.first][_pos.second] = _col;
}
int Unit::GetDistance(pair<int, int> pos) const
{
    int y = abs(_pos.first - pos.first);
    int x = abs(_pos.second - pos.second);
    double d = sqrt(x * x + y * y);
    return round(d);
}
bool Unit::IsAlive() const
{
    return _hp >= 1 ? true : false;
}
int Unit::GetAtk() const
{
    return _atk;
}
Unit::~Unit() {}
} // namespace GameLogic