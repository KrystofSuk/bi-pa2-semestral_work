#ifndef TOWER_H
#define TOWER_H

#include <string>
#include <queue>
#include <deque>
#include "tower.h"
#include "maps.h"
#include "unit.h"

using namespace std;

namespace GameLogic
{

struct Tower
{
public:
    enum AttackType
    {
        Fire,
        Ice,
        Default
    };
    Tower();
    Tower(pair<int, int> p);
    const int GetPrice() const;
    const int GetDistance() const;
    virtual void ProcessAttack(vector<Unit *> &units) = 0;
    pair<int, Tower::AttackType> GetAttack() const;
    pair<int, int> GetPos() const;
    virtual void GetChar(char **c) const = 0;
    virtual void GetColor(Color **c) const = 0;
    virtual void Print(ostream &os) const = 0;
    friend ostream &operator<<(ostream &os, const Tower &obj)
    {
        obj.Print(os);
        return os;
    }
    virtual ~Tower();

protected:
    char _c;
    Color _col;
    int _price;
    int _atk;
    int _distance;
    AttackType _type;
    string _name;

    pair<int, int> _pos;
};

class BasicTower : public Tower
{
public:
    BasicTower(pair<int, int> p, string n);
    virtual void ProcessAttack(vector<Unit *> &units);
    void GetChar(char **c) const;
    void GetColor(Color **c) const;
    void Print(ostream &os) const;
    virtual ~BasicTower();
};

class FireTower : public BasicTower
{
public:
    FireTower(pair<int, int> p, string n);
    virtual ~FireTower();
};

class IceTower : public BasicTower
{
public:
    IceTower(pair<int, int> p, string n);
    virtual ~IceTower();
};

class MortarTower : public BasicTower{
public:
    MortarTower(pair<int, int> p, string n);
    virtual void ProcessAttack(vector<Unit *> &units);
    virtual ~MortarTower();
};

}
#endif