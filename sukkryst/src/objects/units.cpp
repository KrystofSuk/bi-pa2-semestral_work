
#include "units.h"
#include "unit.h"
#include "../game/maps.h"
#include <iostream>
#include <limits>
#include <math.h>

#include "../extras/file.h"

namespace GameLogic
{
Slime::Slime() : Unit()
{
}
Slime::Slime(pair<int, int> s) : Unit("slime")
{
    _pos.first = s.first;
    _pos.second = s.second;
}
Slime::Slime(pair<int, int> s, const string & n) : Unit(n)
{
    _pos.first = s.first;
    _pos.second = s.second;
}
int Slime::GetType() const{
    return 0;
}
void Slime::ProcessAttack(const int &a, const UnitResistance::ResistanceType &atk)
{
    _hp -= a;
    if (atk == UnitResistance::ResistanceType::Ice)
    {
        _hp -= a;
    }
    if (atk == UnitResistance::ResistanceType::Fire)
    {
        _hp -= a;
    }
    if (_hp < 0)
    {
        _hp = 0;
    }
}
void Slime::Move(const Map &m)
{
    if (_movType == 0)
    {
        if (_path.size() == 0)
            _path = m.DFS(_pos);
        if (_path.size() >= 1)
        {
            _pos = _path.at(_path.size() - 1);
            _path.erase(_path.begin() + _path.size() - 1);
        }
    }
    else
    {
        if (_path.size() == 0)
            _path = m.BFS(_pos);
        if (_path.size() >= 1)
        {
            _pos = _path.at(_path.size() - 1);
            _path.erase(_path.begin() + _path.size() - 1);
        }
    }
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

SlimeKing::SlimeKing() : Slime()
{
}
SlimeKing::SlimeKing(pair<int, int> s) : Slime(s, "slimeking")
{
}
int SlimeKing::GetType() const{
    return 1;
}
SlimeKing::~SlimeKing()
{
}

Orc::Orc() : UnitResistance(0), Unit() {
    
}
Orc::Orc(pair<int, int> s) : UnitResistance(0), Unit("orc"){
    _pos.first = s.first;
    _pos.second = s.second;
}
int Orc::GetType() const{
    return 2;
}
void Orc::ProcessAttack(const int &a, const UnitResistance::ResistanceType &atk){
    _hp -= a;
    if (atk == UnitResistance::ResistanceType::Ice && ProcessResistance(atk))
    {
        _hp -= a;
    }
    if (atk == UnitResistance::ResistanceType::Fire && ProcessResistance(atk))
    {
        _hp -= a;
    }
    if (_hp < 0)
    {
        _hp = 0;
    }
}
bool Orc::ProcessResistance(const ResistanceType &type) const{
    if(type != _resistance)
        return true;
    return false;
}
void Orc::Print(ostream &os) const
{
    os << "| " << setw(22) << left << setfill(' ') << _name << " |" << endl;
    os << " ------------------------ " << endl;
    os << "|  ATK  |  RES  |   HP   |" << endl;
    os << "| " << setw(5) << left << setfill(' ') << _atk << " | ";
    if (_resistance == Fire)
        os << setw(5) << left << setfill(' ') << " FIR "
           << " | ";
    if (_resistance == Ice)
        os << setw(5) << left << setfill(' ') << " ICE "
           << " | ";
    os << setw(6) << left << setfill(' ') << _hp << " |";
}
void Orc::Move(const Map &m)
{
    if (_movType == 0)
    {
        if (_path.size() == 0)
            _path = m.DFS(_pos);
        if (_path.size() >= 1)
        {
            _pos = _path.at(_path.size() - 1);
            _path.erase(_path.begin() + _path.size() - 1);
        }
    }
    else
    {
        if (_path.size() == 0)
            _path = m.BFS(_pos);
        if (_path.size() >= 1)
        {
            _pos = _path.at(_path.size() - 1);
            _path.erase(_path.begin() + _path.size() - 1);
        }
    }
}
Orc::~Orc()
{
}

Golem::Golem() : UnitResistance(1), Unit() {
    
}
Golem::Golem(pair<int, int> s) : UnitResistance(1), Unit("golem"){
    _pos.first = s.first;
    _pos.second = s.second;
}
int Golem::GetType() const{
    return 3;
}
void Golem::ProcessAttack(const int &a, const UnitResistance::ResistanceType &atk){
    _hp -= a;
    if (atk == UnitResistance::ResistanceType::Ice && ProcessResistance(atk))
    {
        _hp -= a;
    }
    if (atk == UnitResistance::ResistanceType::Fire && ProcessResistance(atk))
    {
        _hp -= a;
    }
    if (_hp < 0)
    {
        _hp = 0;
    }
}
bool Golem::ProcessResistance(const ResistanceType &type) const{
    if(type != _resistance)
        return true;
    return false;
}
void Golem::Print(ostream &os) const
{
    os << "| " << setw(22) << left << setfill(' ') << _name << " |" << endl;
    os << " ------------------------ " << endl;
    os << "|  ATK  |  RES  |   HP   |" << endl;
    os << "| " << setw(5) << left << setfill(' ') << _atk << " | ";
    if (_resistance == Fire)
        os << setw(5) << left << setfill(' ') << " FIR "
           << " | ";
    if (_resistance == Ice)
        os << setw(5) << left << setfill(' ') << " ICE "
           << " | ";
    os << setw(6) << left << setfill(' ') << _hp << " |";
}
void Golem::Move(const Map &m)
{
    if (_movType == 0)
    {
        if (_path.size() == 0)
            _path = m.DFS(_pos);
        if (_path.size() >= 1)
        {
            _pos = _path.at(_path.size() - 1);
            _path.erase(_path.begin() + _path.size() - 1);
        }
    }
    else
    {
        if (_path.size() == 0)
            _path = m.BFS(_pos);
        if (_path.size() >= 1)
        {
            _pos = _path.at(_path.size() - 1);
            _path.erase(_path.begin() + _path.size() - 1);
        }
    }
}
Golem::~Golem()
{
}
} // namespace GameLogic