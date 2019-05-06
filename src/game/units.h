#ifndef UNITS_H
#define UNITS_H

#include <string>
#include "unit.h"
#include "units.h"
#include "maps.h"

using namespace std;

namespace GameLogic
{

    class Slime : public Unit{
        public:
            Slime();
            Slime(pair<int, int> s);
            void GetChar(char ** c) const;
            void GetColor(Color ** c) const;
            void Move(const Map & m);
            ~Slime();
    };

    class Orc : public Unit, public UnitResistance{

    };

    class Golem : public Unit, public UnitResistance{

    };
}
#endif