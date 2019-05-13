#ifndef UNITS_H
#define UNITS_H

#include <string>
#include "unit.h"
#include "units.h"
#include "maps.h"

using namespace std;

namespace GameLogic
{

class Slime : public Unit
{
public:
    Slime();
    Slime(pair<int, int> s, string n);
    virtual void ProcessAttack(const int &a, const UnitResistance::ResistanceType &atk);
    void GetChar(char **c) const;
    void GetColor(Color **c) const;
    virtual void Print(ostream &os) const;
    virtual void Move(const Map &m);
    virtual ~Slime();
};

class SlimeKing : public Slime
{
public:
    SlimeKing();
    SlimeKing(pair<int, int> s, string n);
    virtual void Move(const Map &m);
    virtual ~SlimeKing();
};

class Orc : public Unit, public UnitResistance
{
public:
};

class Golem : public Unit, public UnitResistance
{
public:
};
} // namespace GameLogic
#endif