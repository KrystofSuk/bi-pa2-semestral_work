#include "units.h"

namespace GameLogic
{

Slime::Slime() : Unit() {}

Slime::Slime(const std::pair<int, int> & s) : Unit("slime")
{
    _pos.first = s.first;
    _pos.second = s.second;
}

Slime::Slime(const std::pair<int, int> & s, const std::string &n) : Unit(n)
{
    _pos.first = s.first;
    _pos.second = s.second;
}

const int Slime::GetType() const
{
    return 0;
}

void Slime::ProcessAttack(const int &a, const AttackType &atk)
{
    _hp -= a;

    if (atk == Ice || atk == Fire)
        _hp -= a;

    if (_hp < 0)
        _hp = 0;
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

void Slime::Print(std::ostream &os) const
{
    os << "| " << std::setw(22) << std::left << std::setfill(' ') << _name << " |" << std::endl;
    os << " ------------------------ " << std::endl;
    os << "|     ATK    |     HP    |" << std::endl;
    os << "| " << std::setw(10) << std::left << std::setfill(' ') << _atk << " | " << std::setw(9) << std::left << std::setfill(' ') << _hp << " |";
}

Slime::~Slime() {}

SlimeKing::SlimeKing() : Slime() {}

SlimeKing::SlimeKing(const std::pair<int, int> & s) : Slime(s, "slimeking") {}

const int SlimeKing::GetType() const
{
    return 1;
}

SlimeKing::~SlimeKing() {}

Orc::Orc() : UnitResistance(0), Unit() {}

Orc::Orc(const std::pair<int, int> & s) : UnitResistance(0), Unit("orc")
{
    _pos.first = s.first;
    _pos.second = s.second;
}

const int Orc::GetType() const
{
    return 2;
}

void Orc::ProcessAttack(const int &a, const AttackType &atk)
{
    _hp -= a;

    if ((atk ==Ice && ProcessResistance(atk)) || (atk == Fire && ProcessResistance(atk)))
        _hp -= a; 

    if (_hp < 0)
        _hp = 0;
}

const bool Orc::ProcessResistance(const AttackType &type) const
{
    if (type != _resistance)
        return true;

    return false;
}

void Orc::Print(std::ostream &os) const
{
    os << "| " << std::setw(22) << std::left << std::setfill(' ') << _name << " |" << std::endl;
    os << " ------------------------ " << std::endl;
    os << "|  ATK  |  RES  |   HP   |" << std::endl;
    os << "| " << std::setw(5) << std::left << std::setfill(' ') << _atk << " | ";

    if (_resistance == Fire)
        os << std::setw(5) << std::left << std::setfill(' ') << " FIR "
           << " | ";

    if (_resistance == Ice)
        os << std::setw(5) << std::left << std::setfill(' ') << " ICE "
           << " | ";

    os << std::setw(6) << std::left << std::setfill(' ') << _hp << " |";
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

Orc::~Orc(){}

Golem::Golem() : UnitResistance(1), Unit(){}

Golem::Golem(const std::pair<int, int> & s) : UnitResistance(1), Unit("golem")
{
    _pos.first = s.first;
    _pos.second = s.second;
}

const int Golem::GetType() const
{
    return 3;
}

void Golem::ProcessAttack(const int &a, const AttackType &atk)
{
    _hp -= a;

    if ((atk ==Ice && ProcessResistance(atk)) || (atk == Fire && ProcessResistance(atk)))
        _hp -= a; 

    if (_hp < 0)
        _hp = 0;
}

const bool Golem::ProcessResistance(const AttackType &type) const
{
    if (type != _resistance)
        return true;

    return false;
}

void Golem::Print(std::ostream &os) const
{
    os << "| " << std::setw(22) << std::left << std::setfill(' ') << _name << " |" << std::endl;
    os << " ------------------------ " << std::endl;
    os << "|  ATK  |  RES  |   HP   |" << std::endl;
    os << "| " << std::setw(5) << std::left << std::setfill(' ') << _atk << " | ";

    if (_resistance == Fire)
        os << std::setw(5) << std::left << std::setfill(' ') << " FIR "
           << " | ";

    if (_resistance == Ice)
        os << std::setw(5) << std::left << std::setfill(' ') << " ICE "
           << " | ";

    os << std::setw(6) << std::left << std::setfill(' ') << _hp << " |";
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

Golem::~Golem(){}

} // namespace GameLogic