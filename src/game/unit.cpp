#include <iostream>
#include <string>
#include <limits>
#include <math.h>
#include "unit.h"

namespace GameLogic
{
    UnitResistance::UnitResistance(int res = 0){
        if(res < 0){
            std::cerr << "Wrong res" << endl;
            res = 0;
        }
        _resistance = res;
    }
    UnitResistance::~UnitResistance(){}
    Unit::Unit(){
        
    }
    Unit::Unit(int hp = 0, int atk = 0, string name = ""){
        _hp = hp;
        _atk = atk;
        _name = name;
    }
    int Unit::GetDistance(pair<int, int> pos) const{
        int y = abs(_pos.first - pos.first);
        int x = abs(_pos.second - pos.second);
        double d = sqrt(x*x + y*y);
        return round(d);
    }
    bool Unit::IsAlive() const{
        return _hp >= 1 ? true : false;
    }
    int Unit::GetAtk() const{
        return _atk;
    }
    Unit::~Unit(){}
}