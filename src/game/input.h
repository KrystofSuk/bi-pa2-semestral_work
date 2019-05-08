#ifndef INPUT_H
#define INPUT_H

#include <string>
#include "input.h"

using namespace std;

namespace GameLogic
{
//Specific actions
enum Key
{
    Left,
    Right,
    Up,
    Down,
    Confirm,
    Cancel,
    Unknown,
    End,
    Next,
    Change
};
/**
     * @brief It processes information from keyboard and manages it.
     * 
     */
class InputProcesser
{
private:
    int _upKey;
    int _downKey;
    int _leftKey;
    int _rightKey;
    int _cancelKey;
    int _confirmKey;
    int _nextKey;
    int _changeKey;
    Key _last;
    Key _pressed;

public:
    InputProcesser();
    InputProcesser(const int &upKey, const int &downKey, const int &leftKey, const int &rightKey, const int &cancelKey, const int &confirmKey, const int &nextKey, const int &changeKey);
    void Set(const int &upKey, const int &downKey, const int &leftKey, const int &rightKey, const int &cancelKey, const int &confirmKey, const int &nextKey, const int &changeKey);
    /**
             * @brief Key processing method for getting currently pressed key.
             * 
             * @return const Key which was pressed
             */
    const Key Process();
};
} // namespace GameLogic
#endif