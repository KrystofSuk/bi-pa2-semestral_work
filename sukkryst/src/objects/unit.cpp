#include "unit.h"

namespace GameLogic
{
UnitResistance::UnitResistance(const int &res)
{
    if (res < 0)
    {
        _resistance = 0;
    }
    else
        _resistance = res;
}

UnitResistance::~UnitResistance() {}

Unit::Unit(){}

Unit::Unit(const std::string &n = "")
{
    _hp = stoi(Extra::File<std::string>::LoadFromFile("./examples/units/" + n, "HP"));
    _c = Extra::File<std::string>::LoadFromFile("./examples/units/" + n, "Char")[0];
    _name = Extra::File<std::string>::LoadFromFile("./examples/units/" + n, "Name");
    _atk = stoi(Extra::File<std::string>::LoadFromFile("./examples/units/" + n, "ATK"));
    std::string col = Extra::File<std::string>::LoadFromFile("./examples/units/" + n, "Color");
    std::string pth = Extra::File<std::string>::LoadFromFile("./examples/units/" + n, "MOV");

    if (pth == "DFS")
        _movType = 0;

    if (pth == "BFS")
        _movType = 1;

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

const std::pair<int, int> & Unit::GetPos() const
{
    return _pos;
}

void Unit::ClearPath()
{
    _path.clear();
}

void Unit::GetChar(char **c) const
{
    c[_pos.first][_pos.second] = _c;
}

const int & Unit::GetHP() const
{
    return _hp;
}

void Unit::SetHP(const int & hp)
{
    _hp = hp;
}

void Unit::GetColor(Color **c) const
{
    c[_pos.first][_pos.second] = _col;
}

const int Unit::GetDistance(const std::pair<int, int> & pos) const
{
    int y = abs(_pos.first - pos.first);
    int x = abs(_pos.second - pos.second);
    double d = sqrt(x * x + y * y);
    return round(d);
}

const bool Unit::IsAlive() const
{
    return _hp >= 1 ? true : false;
}

const int & Unit::GetAtk() const
{
    return _atk;
}

Unit::~Unit() {}

} // namespace GameLogic