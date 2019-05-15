#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <vector>
#include "../game/maps.h"

using namespace std;

namespace GameLogic
{
struct UnitResistance
{
protected:
    int _resistance;

public:
    enum ResistanceType
    {
        Fire,
        Ice,
        Default
    };
    UnitResistance(int res);
    virtual bool ProcessResistance(const ResistanceType &type) const = 0;
    virtual ~UnitResistance();
};

struct Unit
{
protected:
    pair<int, int> _pos = make_pair<int, int>(0, 0);
    int _hp = 0;
    int _atk = 0;
    char _c = 'u';
    Color _col = White;
    string _name = "";
    int _movType = 0;
    vector<pair<int, int>> _path;
public:
    Unit();
    Unit(const string & n);
    bool IsAlive() const;
    int GetAtk() const;
    int GetHP() const;
    void SetHP(int hp);
    int GetDistance(pair<int, int> pos) const;
    pair<int, int> GetPos() const;
    void ClearPath();
    virtual int GetType() const = 0;
    virtual void GetChar(char **c) const;
    virtual void GetColor(Color **c) const;
    virtual void ProcessAttack(const int &a, const UnitResistance::ResistanceType &atk) = 0;
    virtual void Move(const Map &m) = 0;
    virtual void Print(ostream &os) const = 0;
    friend ostream &operator<<(ostream &os, const Unit &obj)
    {
        obj.Print(os);
        return os;
    }
    virtual ~Unit();
};

} // namespace GameLogic
#endif