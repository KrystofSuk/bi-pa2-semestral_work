#include "input.h"
#include <iostream>
#include <string>

namespace GameLogic{
    InputProcesser::InputProcesser(){
        _upKey = 65;
        _downKey = 66;
        _leftKey = 68;
        _rightKey = 67;
        _cancelKey = 27;
        _confirmKey = 13;
    }

    InputProcesser::InputProcesser(const int & upKey, const int & downKey, const int & leftKey, const int & rightKey, const int & cancelKey, const int & confirmKey){
        _upKey = upKey;
        _downKey = downKey;
        _leftKey = leftKey;
        _rightKey = rightKey;
        _cancelKey = cancelKey;
        _confirmKey = confirmKey;
    }

    void InputProcesser::Set(const int & upKey, const int & downKey, const int & leftKey, const int & rightKey, const int & cancelKey, const int & confirmKey){
        _upKey = upKey;
        _downKey = downKey;
        _leftKey = leftKey;
        _rightKey = rightKey;
        _cancelKey = cancelKey;
        _confirmKey = confirmKey;
    }

    const Key InputProcesser::Process(){ 
        system("stty raw -echo"); 
        int key = cin.get();
        if(key == 27){
            key = cin.get();
            if(key == 91){
                key = cin.get();
            }
        }

        if(key == _leftKey)
            return Left;
        if(key == _rightKey)
            return Right;
        if(key == _downKey)
            return Down;
        if(key == _upKey)
            return Up;
        if(key == _cancelKey)
            return Cancel;
        if(key == _confirmKey)
            return Confirm;
        if(key == 3 || key == 4 || key == 25)
            return End;

        return Unknown;
    }
}