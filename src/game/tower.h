#ifndef TOWER_H
#define TOWER_H

#include <string>
#include "tower.h"

using namespace std;

namespace GameLogic
{
    enum AttackTypes{ Fire, Ice };

    class TowerStats{

    };

    struct TowerAttack{

    };

    class FireAttack : public TowerAttack{

    };

    class BasicTower : public TowerStats, public TowerAttack{

    };

    class FireTower : public TowerStats, public FireAttack{

    };
}
#endif