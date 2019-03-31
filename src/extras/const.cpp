#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include "const.h"
#include "file.h"

namespace Extra{
    
    Consts::Consts(){
        vector<int> consts = File<int>::LoadFromFile("res/const.txt");

        _canvasWidth = consts.at(0);
        _canvasHeight = consts.at(1);
        
        _upKey = consts.at(2);
        _downKey = consts.at(3);
        _leftKey = consts.at(4);
        _rightKey = consts.at(5);
        _cancelKey = consts.at(6);
        _confirmKey = consts.at(7);
        
    }

    const int & Consts::GetCanvasWidth() const{
        return _canvasWidth;
    }
    const int & Consts::GetCanvasHeight() const{
        return _canvasHeight;
    }
    const int & Consts::GetUpKey() const{
        return _upKey;
    }
    const int & Consts::GetDownKey() const{
        return _downKey;
    }
    const int & Consts::GetLeftKey() const{
        return _leftKey;
    }
    const int & Consts::GetRightKey() const{
        return _rightKey;
    }
    const int & Consts::GetCancelKey() const{
        return _cancelKey;
    }
    const int & Consts::GetConfirmKey() const{
        return _confirmKey;
    }
}