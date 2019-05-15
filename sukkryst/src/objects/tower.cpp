#include "tower.h"

namespace GameLogic
{

Tower::Tower() {}

Tower::Tower(const std::pair<int, int> & p)
{
    _pos = p;
}

const std::pair<int, int> & Tower::GetPos() const
{
    return _pos;
}

const int & Tower::GetDistance() const
{
    return _distance;
}

const int & Tower::GetPrice() const
{
    return _price;
}

const std::pair<int, AttackType> Tower::GetAttack() const
{
    return std::make_pair(_atk, _type);
}

Tower::~Tower() {}

BasicTower::BasicTower(const std::pair<int, int> & p, const std::string & n) : Tower(p)
{
    _c = Extra::File<std::string>::LoadFromFile("./examples/towers/" + n, "Char")[0];
    _name = Extra::File<std::string>::LoadFromFile("./examples/towers/" + n, "Name");
    _atk = stoi(Extra::File<std::string>::LoadFromFile("./examples/towers/" + n, "ATK"));
    _distance = stoi(Extra::File<std::string>::LoadFromFile("./examples/towers/" + n, "Distance"));
    _price = stoi(Extra::File<std::string>::LoadFromFile("./examples/towers/" + n, "Price"));
    _type = Default;
    std::string col = Extra::File<std::string>::LoadFromFile("./examples/towers/" + n, "Color");

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
}

void BasicTower::ProcessAttack(std::vector<Unit *> &units)
{
    Unit *u = nullptr;
    int dist = _distance;

    for (auto i = units.end() - 1; i >= units.begin(); i--)
    {
        if ((*i)->GetDistance(_pos) <= _distance && (*i)->GetDistance(_pos) <= dist)
        {
            dist = (*i)->GetDistance(_pos);
            u = *i;
        }
    }

    if (u != nullptr)
    {
        switch (_type)
        {
        case Fire:
            u->ProcessAttack(_atk, UnitResistance::Fire);
            break;

        case Ice:
            u->ProcessAttack(_atk, UnitResistance::Ice);
            break;

        default:
            u->ProcessAttack(_atk, UnitResistance::Default);
            break;
        }
    }
}

void BasicTower::Print(std::ostream &os) const
{
    os << "| " << setw(22) << left << setfill(' ') << _name << " |" << endl;
    os << " ------------------------ " << endl;
    os << "| ATK | DIST | TYP |PRICE|" << endl;
    os << "| " << setw(3) << left << setfill(' ') << _atk << " | " << setw(4) << left << setfill(' ') << _distance << " | ";

    switch (_type)
    {
    case Fire:
        os << "Fir"
           << " | " << setw(3) << right << setfill('0') << _price << " |";
        break;

    case Ice:
        os << "Ice"
           << " | " << setw(3) << right << setfill('0') << _price << " |";
        break;

    default:
        os << " - "
           << " | " << setw(3) << right << setfill('0') << _price << " |";
        break;
    }
}

void BasicTower::GetChar(char **c) const
{
    c[_pos.first][_pos.second] = _c;
}

void BasicTower::GetColor(Color **c) const
{
    c[_pos.first][_pos.second] = _col;
}

const int BasicTower::GetType() const
{
    return -2;
}

BasicTower::~BasicTower() {}

FireTower::FireTower(const std::pair<int, int> & p, const std::string & n) : BasicTower(p, n)
{
    _type = Fire;
}

const int FireTower::GetType() const
{
    return -3;
}

FireTower::~FireTower() {}

IceTower::IceTower(const std::pair<int, int> & p, const std::string & n) : BasicTower(p, n)
{
    _type = Ice;
}

const int IceTower::GetType() const
{
    return -4;
}
IceTower::~IceTower() {}

MortarTower::MortarTower(const std::pair<int, int> & p, const std::string & n) : BasicTower(p, n) {}

void MortarTower::ProcessAttack(vector<Unit *> &units)
{
    vector<Unit *> u;

    for (auto i = units.end() - 1; i >= units.begin(); i--)
    {
        if ((*i)->GetDistance(_pos) <= _distance)
        {
            u.push_back(*i);
        }
    }

    for (auto i = u.begin(); i < u.end(); i++)
    {
        switch (_type)
        {
        case Fire:
            (*i)->ProcessAttack(_atk, UnitResistance::Fire);
            break;

        case Ice:
            (*i)->ProcessAttack(_atk, UnitResistance::Ice);
            break;

        default:
            (*i)->ProcessAttack(_atk, UnitResistance::Default);
            break;
        }
    }
}

const int MortarTower::GetType() const
{
    return -5;
}

MortarTower::~MortarTower() {}

} // namespace GameLogic