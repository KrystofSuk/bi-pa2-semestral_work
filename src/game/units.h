#ifndef UNITS_H
#define UNITS_H

#include <string>
#include "unit.h"
#include "units.h"

using namespace std;

namespace GameLogic
{

    class Slime : public Unit{

    };

    class Orc : public Unit, public UnitResistance{

    };

    class Golem : public Unit, public UnitResistance{

    };
}
#endif