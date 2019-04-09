#ifndef UNITS_H
#define UNITS_H

#include <string>
#include "unit.h"
#include "units.h"
#include "../ui/ui_elements.h"

using namespace std;

namespace GameLogic
{

    class Slime : public Unit, UI::Rect{

    };

    class Orc : public Unit, public UnitResistance, UI::Rect{

    };

    class Golem : public Unit, public FireResistance, UI::Rect{

    };
}
#endif