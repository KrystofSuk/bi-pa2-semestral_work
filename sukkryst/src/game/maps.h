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

using namespace std;

namespace GameLogic
{
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

class Tile
{
public:
    Tile();
    Tile(char t, int x, int y, Color c, bool p);
    
    Tile &operator=(const Tile &other);
    void SetChar(char n);
    void SetPass(bool t);
    char GetChar() const;
    Color GetColor() const;
    bool GetPassable() const;

private:
    Color _color = White;
    bool _passable = true;
    char _char = ' ';
};

class Map
{
private:
    Tile **_tiles = nullptr;

    pair<int, int> _s;
    pair<int, int> _e;

    int _h = 0;
    int _w = 0;

    bool _valid = true;

    void DFSL(int x, int y, stack<pair<int, int>> & q, set<pair<int, int>> & v, map<pair<int, int>, pair<int, int>> & par) const;
    void DFSR(int x, int y, stack<pair<int, int>> & q, set<pair<int, int>> & v, map<pair<int, int>, pair<int, int>> & par) const;
    void DFST(int x, int y, stack<pair<int, int>> & q, set<pair<int, int>> & v, map<pair<int, int>, pair<int, int>> & par) const;
    void DFSB(int x, int y, stack<pair<int, int>> & q, set<pair<int, int>> & v, map<pair<int, int>, pair<int, int>> & par) const;

public:
    Map();
    Map(string name);
    int GetH() const;
    int GetW() const;

    bool IsReachable() const;
    bool ReachedEnd(const pair<int, int> &pos) const;
    bool IsValid() const;
    bool PlaceTower(const pair<int, int> &pos);
    bool IsValidPlace(const pair<int, int> &pos) const;

    vector<pair<int, int>> BFS(const pair<int, int> &pos) const;
    vector<pair<int, int>> DFS(const pair<int, int> &pos) const;

    Map &operator=(const Map &other);

    void GetChars(char **c) const;
    void GetColors(Color **c) const;

    pair<int, int> GetS() const;
    ~Map();
};
} // namespace GameLogic
#endif