#ifndef UNIT_H
#define UNIT_H

#include <string>
#include "unit.h"
#include "maps.h"

using namespace std;

namespace GameLogic
{
    struct UnitResistance{
        protected:
            int _resistance;
        public:
            enum ResistanceType{ Fire, Ice, Default };
            UnitResistance(int res);
            virtual void ProcessResistance(int & attack, const ResistanceType & type) const = 0;
            virtual ~UnitResistance();
    };

    struct Unit{
        protected:
            pair<int, int> _pos = make_pair<int,int>(0,0);
            int _hp = 0;
            int _atk = 0;
            char _c = 'u';
            Color _col = White;
            string _name = "";
            int _movType = 0;
        public:
            Unit();
            Unit(int hp, int atk, string name);
            bool IsAlive() const;
            int GetAtk() const;
            int GetDistance(pair<int, int> pos) const;
            pair<int, int> GetPos() const;
            virtual void ProcessAttack(const int & a, const UnitResistance::ResistanceType & atk) = 0;
            virtual void Move(const Map & m) = 0;
            virtual void GetChar(char ** c) const = 0;
            virtual void GetColor(Color ** c) const = 0;
            virtual void Print(ostream& os) const  = 0;
            friend ostream& operator<<(ostream& os, const Unit& obj){
                obj.Print(os);
                return os;
            }
            virtual ~Unit();
    };

}
#endif