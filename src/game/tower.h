#ifndef TOWER_H
#define TOWER_H

#include <string>
#include "tower.h"
#include "../ui/ui_elements.h"

using namespace std;

namespace GameLogic
{
    enum AttackTypes{ Fire };

    class TowerStats{

    };

    class TowerAttack : public UI::Circle{

    };

    class FireAttack : public TowerAttack{

    };

    class BasicTower : public TowerStats, public TowerAttack, public UI::Rect{

    };

    class FireTower : public TowerStats, public FireAttack, public UI::Rect{

    };
}
#endif