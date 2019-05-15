#ifndef CONSTS_H
#define CONSTS_H

#include "file.h"

namespace Extra
{
/**
 * @brief Consts class is responsible for loading and keeping keybingings
 * 
 */
class Consts
{
public:
    /**
     * @brief Construct a new Consts and loading keybings
     * 
     */
    Consts();

    /**
     * @brief Get the up key nubmer
     * 
     * @return const int& up keynumber
     */
    const int &GetUpKey() const;
    /**
     * @brief Get the down key nubmer
     * 
     * @return const int& down keynumber
     */
    const int &GetDownKey() const;
    /**
     * @brief Get the left key nubmer
     * 
     * @return const int& left keynumber
     */
    const int &GetLeftKey() const;
    /**
     * @brief Get the right key nubmer
     * 
     * @return const int& right keynumber
     */
    const int &GetRightKey() const;
    /**
     * @brief Get the cancel key nubmer
     * 
     * @return const int& cancel keynumber
     */
    const int &GetCancelKey() const;
    /**
     * @brief Get the confirm key nubmer
     * 
     * @return const int& confirm keynumber
     */
    const int &GetConfirmKey() const;
    /**
     * @brief Get the next key nubmer
     * 
     * @return const int& next keynumber
     */
    const int &GetNextKey() const;
    /**
     * @brief Get the change key nubmer
     * 
     * @return const int& change keynumber
     */
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