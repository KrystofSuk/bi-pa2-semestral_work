#include "const.h"

namespace Extra
{

Consts::Consts()
{
    std::vector<int> consts = File<int>::LoadFromFile("./examples/const.txt");

    _upKey = consts.at(0);
    _downKey = consts.at(1);
    _leftKey = consts.at(2);
    _rightKey = consts.at(3);
    _cancelKey = consts.at(4);
    _confirmKey = consts.at(5);
    _nextKey = consts.at(6);
    _changeKey = consts.at(7);
}

const int &Consts::GetUpKey() const
{
    return _upKey;
}

const int &Consts::GetDownKey() const
{
    return _downKey;
}

const int &Consts::GetLeftKey() const
{
    return _leftKey;
}

const int &Consts::GetRightKey() const
{
    return _rightKey;
}

const int &Consts::GetCancelKey() const
{
    return _cancelKey;
}

const int &Consts::GetConfirmKey() const
{
    return _confirmKey;
}

const int &Consts::GetNextKey() const
{
    return _nextKey;
}

const int &Consts::GetChangeKey() const
{
    return _changeKey;
}

}