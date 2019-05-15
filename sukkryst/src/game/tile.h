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
     * @brief Construct a new Tile
     * 
     * @param c displayed char
     * @param col color of tile
     * @param p if tile is passable
     */
    Tile(const char & c, const Color & col, const bool & p);

    /**
     * @brief Set the char of tile
     * 
     * @param n new char
     */
    void SetChar(const char & n);
    /**
     * @brief Set the pass of tile
     * 
     * @param p new passable state
     */
    void SetPass(const bool & p);

    /**
     * @brief Get the char of tile
     * 
     * @return char 
     */
    const char & GetChar() const;
    /**
     * @brief Get the color of tile
     * 
     * @return Color 
     */
    const Color & GetColor() const;
    /**
     * @brief Get the passable state
     * 
     * @return true tile is passable
     * @return false tile is not passable
     */
    const bool & GetPassable() const;

private:
    Color _color = White;
    bool _passable = true;
    char _char = ' ';
};

} // namespace GameLogic
#endif