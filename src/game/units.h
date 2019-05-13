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
    Slime(pair<int, int> s);
    virtual void ProcessAttack(const int &a, const UnitResistance::ResistanceType &atk);
    void GetChar(char **c) const;
    void GetColor(Color **c) const;
    virtual void Print(ostream &os) const;
    void Move(const Map &m);
    virtual ~Slime();
};

class SlimeKing : public Slime
{
};

class Orc : public Unit, public UnitResistance
{
};

class Golem : public Unit, public UnitResistance
{
};
} // namespace GameLogic
#endif