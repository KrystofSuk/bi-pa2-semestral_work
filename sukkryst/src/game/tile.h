#ifndef TILE_H
#define TILE_H

#include "enums.h"

namespace GameLogic
{
/**
 * @brief Tile class which represents one tile in map
 * 
 */
class Tile
{
public:
    /**
     * @brief Construct a new Tile
     * 
     */
    Tile();
    /**
     * @brief Construct a new Tile object
     * 
     * @param c
     * @param x 
     * @param y 
     * @param c 
     * @param p 
     */
    Tile(const char & c, const Color & col, const bool & p);

    /**
     * @brief Set the Char object
     * 
     * @param n 
     */
    void SetChar(const char & n);
    /**
     * @brief Set the Pass object
     * 
     * @param t 
     */
    void SetPass(const bool & t);

    /**
     * @brief Get the Char object
     * 
     * @return char 
     */
    const char & GetChar() const;
    /**
     * @brief Get the Color object
     * 
     * @return Color 
     */
    const Color & GetColor() const;
    /**
     * @brief Get the Passable object
     * 
     * @return true 
     * @return false 
     */
    const bool & GetPassable() const;

private:
    Color _color = White;
    bool _passable = true;
    char _char = ' ';
};

} // namespace GameLogic
#endif