#include "input.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

namespace GameLogic
{
    InputProcesser::InputProcesser()
    {
        _upKey = 65;
        _downKey = 66;
        _leftKey = 68;
        _rightKey = 67;
        _cancelKey = 27;
        _confirmKey = 13;
        _last = Unknown;
    }

    InputProcesser::InputProcesser(const int &upKey, const int &downKey, const int &leftKey, const int &rightKey, const int &cancelKey, const int &confirmKey)
    {
        _upKey = upKey;
        _downKey = downKey;
        _leftKey = leftKey;
        _rightKey = rightKey;
        _cancelKey = cancelKey;
        _confirmKey = confirmKey;
        _last = Unknown;
    }

    void InputProcesser::Set(const int &upKey, const int &downKey, const int &leftKey, const int &rightKey, const int &cancelKey, const int &confirmKey)
    {
        _upKey = upKey;
        _downKey = downKey;
        _leftKey = leftKey;
        _rightKey = rightKey;
        _cancelKey = cancelKey;
        _confirmKey = confirmKey;
    }

    const Key InputProcesser::Process(void)
    {
        /*----------------------------------------------------
                        CODE COPYIED FROM FORUM
                http://www.cplusplus.com/forum/unices/18395/
        ------------------------------------------------------*/
        int key;
        struct termios oldt;
        struct termios newt;
        tcgetattr(STDIN_FILENO, &oldt);          
        newt = oldt;                             
        newt.c_lflag &= ~(ICANON | ECHO);        
        tcsetattr(STDIN_FILENO, TCSANOW, &newt); 
        key = getchar();                         
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); 
        /*----------------------------------------------------
                        END OF COPYIED CODE
        ------------------------------------------------------*/

        if (key == _leftKey)
        {
            _pressed = Left;
        }
        if (key == _rightKey)
        {
            _pressed = Right;
        }
        if (key == _downKey)
        {
            _pressed = Down;
        }
        if (key == _upKey)
        {
            _pressed = Up;
        }
        if (key == _cancelKey)
        {
            _pressed = Cancel;
        }
        if (key == _confirmKey)
        {
            _pressed = Confirm;
        }
        if (key == 3 || key == 4 || key == 25)
            return End;

        return _pressed;
    }

} 