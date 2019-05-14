#ifndef CONSTS_H
#define CONSTS_H

#include <string>
#include <vector>

using namespace std;

namespace Extra
{
    /**
     * @brief Const class responsible for loading and keeping consts like keybingings
     * 
     */
class Consts
{
public:
    Consts();

    const int &GetUpKey() const;
    const int &GetDownKey() const;
    const int &GetLeftKey() const;
    const int &GetRightKey() const;
    const int &GetCancelKey() const;
    const int &GetConfirmKey() const;
    const int &GetNextKey() const;
    const int &GetChangeKey() const;

private:
    int _upKey;
    int _downKey;
    int _leftKey;
    int _rightKey;
    int _cancelKey;
    int _confirmKey;
    int _nextKey;
    int _changeKey;
};
} // namespace Extra
#endif