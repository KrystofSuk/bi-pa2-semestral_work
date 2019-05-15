#ifndef ENUM_H
#define ENUM_H

namespace GameLogic
{
/**
 * @brief UI colors 
 * 
 */
enum Color
{
    White,
    Black,
    Blue,
    Red,
    Green,
    Yellow,
    Magenta,
    Cyan
};
/**
 * @brief Possible states of game
 * 
 */
enum GameState
{
    Exit,
    MainMenu,
    MapSelect,
    Help,
    InGame
};
/**
 * @brief Specific key
 * 
 */
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
 * @brief AttackType
 * 
 */
enum AttackType
{
    Fire,
    Ice,
    Default
};
} // namespace GameLogic
#endif