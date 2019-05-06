#ifndef UNIT_H
#define UNIT_H

#include <string>
#include "unit.h"
#include "map.h"
#include "tower.h"

using namespace std;

namespace GameLogic
{
    struct UnitResistance{
        protected:
            int _resistance;
        public:
            UnitResistance(int res);
            virtual void ProcessResistance(int & attack, const AttackTypes & type) const = 0;
            virtual ~UnitResistance();
    };

    class Unit{
        protected:
            pair<int, int> _pos = make_pair<int,int>(0,0);
            int _hp = 0;
            int _atk = 0;
            char _c = 'u';
            Color _col = White;
            string _name = "";
        public:
            Unit();
            Unit(int hp, int atk, string name);
            bool IsAlive() const;
            int GetAtk() const;
            virtual void Move() = 0;
            virtual void GetChar(char ** c) const = 0;
            virtual void GetColor(Color ** c) const = 0;
            virtual ~Unit();
    };

}
#endif