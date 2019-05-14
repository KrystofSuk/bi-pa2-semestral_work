#include <iostream>

#include "input.h"

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
    _nextKey = 32;
    _changeKey = 81;
    _last = Unknown;
}

InputProcesser::InputProcesser(const int &upKey, const int &downKey, const int &leftKey, const int &rightKey, const int &cancelKey, const int &confirmKey, const int &nextKey, const int &changeKey)
{
    _upKey = upKey;
    _downKey = downKey;
    _leftKey = leftKey;
    _rightKey = rightKey;
    _cancelKey = cancelKey;
    _confirmKey = confirmKey;
    _nextKey = nextKey;
    _changeKey = changeKey;
    _last = Unknown;
}

void InputProcesser::Set(const int &upKey, const int &downKey, const int &leftKey, const int &rightKey, const int &cancelKey, const int &confirmKey, const int &nextKey, const int &changeKey)
{
    _upKey = upKey;
    _downKey = downKey;
    _leftKey = leftKey;
    _rightKey = rightKey;
    _cancelKey = cancelKey;
    _confirmKey = confirmKey;
    _changeKey = changeKey;
    _nextKey = nextKey;
}

const Key InputProcesser::Process()
{
    system("stty raw -echo");
    int key;
    key = std::cin.get();

    if (key == 27)
    {
        key = std::cin.get();

        if (key == 91)
        {
            key = std::cin.get();
        }
    }

    _pressed = Unknown;

    if (key == _leftKey)
        _pressed = Left;

    if (key == _rightKey)
        _pressed = Right;

    if (key == _downKey)
        _pressed = Down;

    if (key == _upKey)
        _pressed = Up;

    if (key == _cancelKey)
        _pressed = Cancel;

    if (key == _confirmKey)
        _pressed = Confirm;

    if (key == _nextKey)
        _pressed = Next;

    if (key == _changeKey)
        _pressed = Change;

    if (key == 3 || key == 4 || key == 25)
        return End;

    return _pressed;
}

} // namespace GameLogic