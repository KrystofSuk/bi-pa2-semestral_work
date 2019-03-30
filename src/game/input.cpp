#include "input.h"
#include <iostream>
#include <string>

namespace GameLogic{

    const Key InputProcesser::Process(){ 
        system("stty raw -echo"); 
        int key = cin.get();
        if(key == 27){
            key = cin.get();
            if(key == 91){
                key = cin.get();
            }
        }
        switch(key)
        {
            case 68: 
                return Left;
            case 67:
                return Right;
            case 66:
                return Down;
            case 65:
                return Up;
            case 27:
                return Cancel;
            case 3:
                return End;
            case 4:
                return End;
            case 25:
                return End;
            case 13: 
                return Confirm;
        } 
        return Unknown;
    }
}