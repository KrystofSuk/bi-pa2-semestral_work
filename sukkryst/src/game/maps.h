#ifndef MAP_H
#define MAP_H

#include <string>
#include "maps.h"
#include "../extras/file.h"
#include <vector>
#include <queue>
#include <deque>
#include <set>
#include <iostream>
#include <map>
#include <stack>
#include <utility>

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
     * @param t 
     * @param x 
     * @param y 
     * @param c 
     * @param p 
     */
    Tile(char t, int x, int y, Color c, bool p);

    /**
     * @brief Set the Char object
     * 
     * @param n 
     */
    void SetChar(char n);
    /**
     * @brief Set the Pass object
     * 
     * @param t 
     */
    void SetPass(bool t);

    /**
     * @brief Get the Char object
     * 
     * @return char 
     */
    char GetChar() const;
    /**
     * @brief Get the Color object
     * 
     * @return Color 
     */
    Color GetColor() const;
    /**
     * @brief Get the Passable object
     * 
     * @return true 
     * @return false 
     */
    bool GetPassable() const;

private:
    Color _color = White;
    bool _passable = true;
    char _char = ' ';
};
/**
 * @brief 
 * 
 */
class Map
{
private:
    Tile **_tiles = nullptr;

    std::pair<int, int> _s;
    std::pair<int, int> _e;

    int _h = 0;
    int _w = 0;

    bool _valid = true;

    void DFSL(int x, int y, std::stack<std::pair<int, int>> &q, std::set<std::pair<int, int>> &v, std::map<std::pair<int, int>, std::pair<int, int>> &par) const;
    void DFSR(int x, int y, std::stack<std::pair<int, int>> &q, std::set<std::pair<int, int>> &v, std::map<std::pair<int, int>, std::pair<int, int>> &par) const;
    void DFST(int x, int y, std::stack<std::pair<int, int>> &q, std::set<std::pair<int, int>> &v, std::map<std::pair<int, int>, std::pair<int, int>> &par) const;
    void DFSB(int x, int y, std::stack<std::pair<int, int>> &q, std::set<std::pair<int, int>> &v, std::map<std::pair<int, int>, std::pair<int, int>> &par) const;

public:
    Map();
    Map(std::string name);
    int GetH() const;
    int GetW() const;

    bool IsReachable() const;
    bool ReachedEnd(const std::pair<int, int> &pos) const;
    bool IsValid() const;
    bool PlaceTower(const std::pair<int, int> &pos);
    bool IsValidPlace(const std::pair<int, int> &pos) const;

    std::vector<std::pair<int, int>> BFS(const std::pair<int, int> &pos) const;
    std::vector<std::pair<int, int>> DFS(const std::pair<int, int> &pos) const;

    Map &operator=(const Map &other);

    void GetChars(char **c) const;
    void GetColors(Color **c) const;

    std::pair<int, int> GetS() const;
    ~Map();
};

} // namespace GameLogic
#endif