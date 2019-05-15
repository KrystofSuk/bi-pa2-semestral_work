#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <set>
#include <iostream>
#include <map>
#include <stack>
#include <utility>

#include "enums.h"
#include "tile.h"
#include "../extras/file.h"

namespace GameLogic
{
/**
 * @brief Map class which is responsible for pathfinding and holding map information
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

    /**
     * @brief DFS calculation to left side
     * 
     * @param x pos
     * @param y pos
     * @param q queue of positions
     * @param v visited positions
     * @param par parent map to backtrack path
     */
    void DFSL(const int &x, const int &y, std::stack<std::pair<int, int>> &q, std::set<std::pair<int, int>> &v, std::map<std::pair<int, int>, std::pair<int, int>> &par) const;
    /**
     * @brief DFS calculation to right side
     * 
     * @param x pos
     * @param y pos
     * @param q queue of positions
     * @param v visited positions
     * @param par parent map to backtrack path
     */
    void DFSR(const int &x, const int &y, std::stack<std::pair<int, int>> &q, std::set<std::pair<int, int>> &v, std::map<std::pair<int, int>, std::pair<int, int>> &par) const;
    /**
     * @brief DFS calculation to up side
     * 
     * @param x pos
     * @param y pos
     * @param q queue of positions
     * @param v visited positions
     * @param par parent map to backtrack path
     */
    void DFST(const int &x, const int &y, std::stack<std::pair<int, int>> &q, std::set<std::pair<int, int>> &v, std::map<std::pair<int, int>, std::pair<int, int>> &par) const;
    /**
     * @brief DFS calculation to down side
     * 
     * @param x pos
     * @param y pos
     * @param q queue of positions
     * @param v visited positions
     * @param par parent map to backtrack path
     */
    void DFSB(const int &x, const int &y, std::stack<std::pair<int, int>> &q, std::set<std::pair<int, int>> &v, std::map<std::pair<int, int>, std::pair<int, int>> &par) const;

public:
    /**
     * @brief Construct a new empty Map
     * 
     */
    Map();
    /**
     * @brief Construct a new Map and loads level information
     * 
     * @param name Level name in examples directory
     */
    Map(const std::string &name);
    /**
     * @brief Getter for height of map
     * 
     * @return int height
     */
    const int &GetH() const;
    /**
     * @brief Getter for width of map
     * 
     * @return int width
     */
    const int &GetW() const;

    /**
     * @brief Check if end is reachable from start
     * 
     * @return true end is reachable
     * @return false end is not reachable
     */
    const bool IsReachable() const;
    /**
     * @brief Checks if pos is at the end
     * 
     * @param pos position to check
     * @return true position is at the end
     * @return false position is not at the end
     */
    const bool ReachedEnd(const std::pair<int, int> &pos) const;
    /**
     * @brief Checks if map is valid
     * 
     * @return true map is valid
     * @return false map is not valid
     */
    const bool &IsValid() const;
    /**
     * @brief Tries to place the tower and if it is possible it saves it
     * 
     * @param pos wanted position of tower
     * @return true tower was placed
     * @return false tower cannot be placed
     */
    const bool PlaceTower(const std::pair<int, int> &pos);

    /**
     * @brief BFS pathfinding
     * 
     * @param pos starting position
     * @return const std::vector<std::pair<int, int>> path to end 
     */
    const std::vector<std::pair<int, int>> BFS(const std::pair<int, int> &pos) const;
    /**
     * @brief DFS pathfinding
     * 
     * @param pos starting position
     * @return const std::vector<std::pair<int, int>> path to end 
     */
    const std::vector<std::pair<int, int>> DFS(const std::pair<int, int> &pos) const;

    /**
     * @brief Overloaded operator for =
     * 
     * @param other other map object
     * @return Map& new copied map
     */
    Map &operator=(const Map &other);

    /**
     * @brief Sets the char array which will be drawn
     * 
     * @param c drawing array
     */
    void GetChars(char **c) const;
    /**
     * @brief Sets the color array which will be drawn
     * 
     * @param c coloring array
     */
    void GetColors(Color **c) const;

    /**
     * @brief Getter for start position
     * 
     * @return const std::pair<int, int>& start position
     */
    const std::pair<int, int> &GetS() const;
    /**
     * @brief Destroy the Map
     * 
     */
    ~Map();
};

} // namespace GameLogic
#endif