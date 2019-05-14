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
    Slime(pair<int, int> s, const string & n);
    virtual void ProcessAttack(const int &a, const UnitResistance::ResistanceType &atk);
    virtual void Print(ostream &os) const;
    virtual void Move(const Map &m);
    virtual ~Slime();
};

class SlimeKing : public Slime
{
public:
    SlimeKing();
    SlimeKing(pair<int, int> s);
    virtual ~SlimeKing();
};
class Orc : public Unit, public UnitResistance
{
public:
    Orc();
    Orc(pair<int, int> s);
    virtual void ProcessAttack(const int &a, const UnitResistance::ResistanceType &atk);
    bool ProcessResistance(const ResistanceType &type) const;
    virtual void Print(ostream &os) const;
    virtual void Move(const Map &m);
    virtual ~Orc();
};

class Golem : public Unit, public UnitResistance
{
public:
    Golem();
    Golem(pair<int, int> s);
    virtual void ProcessAttack(const int &a, const UnitResistance::ResistanceType &atk);
    bool ProcessResistance(const ResistanceType &type) const;
    virtual void Print(ostream &os) const;
    virtual void Move(const Map &m);
    virtual ~Golem();
};
} // namespace GameLogic
#endif