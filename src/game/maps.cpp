
#include <vector>
#include <queue>
#include <deque>
#include <set>
#include <iostream>
#include <map>
#include <utility>

#include "maps.h"
#include "game.h"

namespace GameLogic
{
Tile::Tile()
{
    _char = ' ';
}
Tile::Tile(char t, int x, int y, Color c = White, bool p = true)
{
    _char = t;
    _color = c;
    _passable = p;
}
void Tile::SetPass(bool t)
{
    _passable = t;
}
void Tile::SetChar(char n)
{
    _char = n;
}
char Tile::GetChar() const
{
    return _char;
}
Color Tile::GetColor() const
{
    return _color;
}
bool Tile::GetPassable() const
{
    return _passable;
}

Map::Map() {}
Map::Map(string name)
{
    //Loading map files
    vector<char> c = Extra::File<char>::LoadFromFileClean("res/maps/" + name);
    vector<int> p = Extra::File<int>::LoadFromFile("res/maps/" + name + "props");

    _w = p.at(0);
    _h = p.at(1);

    _tiles = new Tile *[_h];
    for (int i = 0; i < _h; i++)
    {
        _tiles[i] = new Tile[_w];
        for (int t = 0; t < _w; t++)
        {
            char tmp = c.at(t + (i)*_w);
            if (tmp == 'n')
                _tiles[i][t] = Tile(' ', t, i);
            if (tmp == 'e')
            {
                _tiles[i][t] = Tile(tmp, t, i, Yellow, true);
                _e = make_pair(i, t);
            }
            if (tmp == 's')
            {
                _tiles[i][t] = Tile(tmp, t, i, Yellow, true);
                _s = make_pair(i, t);
            }
            if (tmp == '#')
                _tiles[i][t] = Tile(tmp, t, i, White, false);
        }
    }
}
Map &Map::operator=(const Map &other)
{
    if (this != &other)
    {
        _s = other._s;
        _e = other._e;
        if (_w != other._w || _h != other._h)
        {
            for (int i = 0; i < _h; i++)
            {
                if (_tiles[i] != nullptr)
                    delete[] _tiles[i];
            }
            if (_tiles != nullptr)
                delete[] _tiles;
            _w = other._w;
            _h = other._h;

            _tiles = new Tile *[_h];
            for (int i = 0; i < _h; i++)
            {
                _tiles[i] = new Tile[_w];
                for (int t = 0; t < _w; t++)
                {
                    _tiles[i][t] = other._tiles[i][t];
                }
            }
        }
    }
    return *this;
}
int Map::GetH() const
{
    return _h;
}
int Map::GetW() const
{
    return _w;
}
pair<int, int> Map::GetS() const
{
    return _s;
}
void Map::GetChars(char **c) const
{
    for (int i = 0; i < _h; i++)
    {
        for (int t = 0; t < _w; t++)
        {
            c[i][t] = _tiles[i][t].GetChar();
        }
    }
}
void Map::GetColors(Color **c) const
{
    for (int i = 0; i < _h; i++)
    {
        for (int t = 0; t < _w; t++)
        {
            c[i][t] = _tiles[i][t].GetColor();
        }
    }
}
bool Map::IsReachable() const
{
    auto t = BFS(_s);
    return t == pair<int, int>(0, 0) ? false : true;
}
bool Map::PlaceTower(const pair<int, int> &pos)
{
    if (_tiles[pos.first][pos.second].GetPassable() && pos != _e)
    {
        _tiles[pos.first][pos.second].SetPass(false);
        if (!IsReachable())
        {
            _tiles[pos.first][pos.second].SetPass(true);
            return false;
        }
        return true;
    }
    return false;
}
pair<int, int> Map::BFS(const pair<int, int> &pos) const
{
    system("stty sane");

    queue<pair<int, int>> q;
    set<pair<int, int>> v;
    map<pair<int, int>, pair<int, int>> par;
    pair<int, int> c = pos;

    v.insert(c);
    q.push(c);
    par[c] = c;

    int x = 0;
    int y = 0;

    while (!q.empty())
    {
        if (q.front() == _e)
        {
            //cout << "Found" << endl;
            c = q.front();
            while (par.at(c) != pos)
            {
                c = par.at(c);
                //cout << "PTH: " << c.first << "/" << c.second << " - " << _s.first << "/" << _s.second << endl;
            }
            return c;
        }
        y = q.front().first;
        x = q.front().second;
        if (_tiles[y][x].GetPassable())
        {
            //cout << x << "," << y <<endl;
            if (v.find(make_pair(y, x - 1)) == v.end() && x - 1 >= 0)
            {
                q.push(make_pair(y, x - 1));
                v.insert(make_pair(y, x - 1));
                par[make_pair(y, x - 1)] = make_pair(y, x);
            }
            if (v.find(make_pair(y, x + 1)) == v.end() && x + 1 < _w)
            {
                q.push(make_pair(y, x + 1));
                v.insert(make_pair(y, x + 1));
                par[make_pair(y, x + 1)] = make_pair(y, x);
            }
            if (v.find(make_pair(y - 1, x)) == v.end() && y - 1 >= 0)
            {
                q.push(make_pair(y - 1, x));
                v.insert(make_pair(y - 1, x));
                par[make_pair(y - 1, x)] = make_pair(y, x);
            }
            if (v.find(make_pair(y + 1, x)) == v.end() && y + 1 < _h)
            {
                q.push(make_pair(y + 1, x));
                v.insert(make_pair(y + 1, x));
                par[make_pair(y + 1, x)] = make_pair(y, x);
            }
        }
        q.pop();
    }
    return make_pair<int, int>(0, 0);
}
pair<int, int> Map::PTH(const pair<int, int> &pos) const
{
    pair<int, int> p = make_pair<int, int>(0, 0);
    return p;
}
Map::~Map()
{
    for (int i = 0; i < _h; i++)
    {
        delete[] _tiles[i];
    }
    delete[] _tiles;
}
} // namespace GameLogic