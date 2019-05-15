#include "game.h"

namespace GameLogic
{
Map::Map() {}

Map::Map(const std::string &name)
{
    //Loading map files
    vector<char> c = Extra::File<char>::LoadFromFileClean("./examples/maps/" + name);
    vector<int> p = Extra::File<int>::LoadFromFile("./examples/maps/" + name + "info");

    _w = p.at(0);
    _h = p.at(1);

    if (c.size() != _h * _w)
    {
        _w = 0;
        _h = 0;
        _valid = false;
        return;
    }

    _tiles = new Tile *[_h];

    for (int i = 0; i < _h; i++)
    {
        _tiles[i] = new Tile[_w];
        for (int t = 0; t < _w; t++)
        {
            char tmp = c.at(t + (i)*_w);
            if (tmp == 'n')
                _tiles[i][t] = Tile(' ', White, true);

            if (tmp == 'e')
            {
                _tiles[i][t] = Tile(tmp, Yellow, true);
                _e = make_pair(i, t);
            }

            if (tmp == 's')
            {
                _tiles[i][t] = Tile(tmp, Yellow, true);
                _s = make_pair(i, t);
            }

            if (tmp == '#')
                _tiles[i][t] = Tile(tmp, White, false);
        }
    }
}

Map &Map::operator=(const Map &other)
{
    if (this != &other)
    {
        _valid = other._valid;

        if (_valid)
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
    }
    return *this;
}

const int &Map::GetH() const
{
    return _h;
}

const int &Map::GetW() const
{
    return _w;
}

const pair<int, int> &Map::GetS() const
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

const bool Map::IsReachable() const
{
    auto t = BFS(_s);
    return t.size() == 1 ? false : true;
}

const bool &Map::IsValid() const
{
    return _valid;
}

const bool Map::ReachedEnd(const pair<int, int> &pos) const
{
    return pos == _e ? true : false;
}

const bool Map::PlaceTower(const pair<int, int> &pos)
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

const vector<pair<int, int>> Map::BFS(const pair<int, int> &pos) const
{
    system("stty sane");

    queue<pair<int, int>> q;
    set<pair<int, int>> v;
    map<pair<int, int>, pair<int, int>> par;
    pair<int, int> c = pos;
    vector<pair<int, int>> path;

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
            path.push_back(c);

            while (par.at(c) != pos)
            {
                c = par.at(c);
                path.push_back(c);
            }

            return path;
        }

        y = q.front().first;
        x = q.front().second;

        if (_tiles[y][x].GetPassable())
        {
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

    path.push_back(pos);
    return path;
}

const vector<pair<int, int>> Map::DFS(const pair<int, int> &pos) const
{
    system("stty sane");

    stack<pair<int, int>> q;
    set<pair<int, int>> v;
    map<pair<int, int>, pair<int, int>> par;
    pair<int, int> c = pos;
    vector<pair<int, int>> path;

    v.insert(c);
    q.push(c);
    par[c] = c;

    int x = 0;
    int y = 0;

    while (!q.empty())
    {
        if (q.top() == _e)
        {
            c = q.top();
            path.push_back(c);

            while (par.at(c) != pos)
            {
                c = par.at(c);
                path.push_back(c);
            }

            return path;
        }

        y = q.top().first;
        x = q.top().second;
        q.pop();
        v.insert(make_pair(y, x));

        if (_tiles[y][x].GetPassable())
        {
            int r = rand() % 24;

            if (r == 0)
            {
                DFSL(x, y, q, v, par);
                DFSR(x, y, q, v, par);
                DFST(x, y, q, v, par);
                DFSB(x, y, q, v, par);
            }

            if (r == 1)
            {
                DFSR(x, y, q, v, par);
                DFSL(x, y, q, v, par);
                DFST(x, y, q, v, par);
                DFSB(x, y, q, v, par);
            }

            if (r == 2)
            {
                DFST(x, y, q, v, par);
                DFSL(x, y, q, v, par);
                DFSR(x, y, q, v, par);
                DFSB(x, y, q, v, par);
            }

            if (r == 3)
            {
                DFSL(x, y, q, v, par);
                DFST(x, y, q, v, par);
                DFSR(x, y, q, v, par);
                DFSB(x, y, q, v, par);
            }

            if (r == 4)
            {
                DFSR(x, y, q, v, par);
                DFST(x, y, q, v, par);
                DFSL(x, y, q, v, par);
                DFSB(x, y, q, v, par);
            }

            if (r == 5)
            {
                DFST(x, y, q, v, par);
                DFSR(x, y, q, v, par);
                DFSL(x, y, q, v, par);
                DFSB(x, y, q, v, par);
            }

            if (r == 6)
            {
                DFSB(x, y, q, v, par);
                DFSR(x, y, q, v, par);
                DFSL(x, y, q, v, par);
                DFST(x, y, q, v, par);
            }

            if (r == 7)
            {
                DFSR(x, y, q, v, par);
                DFSB(x, y, q, v, par);
                DFSL(x, y, q, v, par);
                DFST(x, y, q, v, par);
            }

            if (r == 8)
            {
                DFSL(x, y, q, v, par);
                DFSB(x, y, q, v, par);
                DFSR(x, y, q, v, par);
                DFST(x, y, q, v, par);
            }

            if (r == 9)
            {
                DFSB(x, y, q, v, par);
                DFSL(x, y, q, v, par);
                DFSR(x, y, q, v, par);
                DFST(x, y, q, v, par);
            }

            if (r == 10)
            {
                DFSR(x, y, q, v, par);
                DFSL(x, y, q, v, par);
                DFSB(x, y, q, v, par);
                DFST(x, y, q, v, par);
            }

            if (r == 11)
            {
                DFSL(x, y, q, v, par);
                DFSR(x, y, q, v, par);
                DFSB(x, y, q, v, par);
                DFST(x, y, q, v, par);
            }

            if (r == 12)
            {
                DFSL(x, y, q, v, par);
                DFST(x, y, q, v, par);
                DFSB(x, y, q, v, par);
                DFSR(x, y, q, v, par);
            }

            if (r == 13)
            {
                DFST(x, y, q, v, par);
                DFSL(x, y, q, v, par);
                DFSB(x, y, q, v, par);
                DFSR(x, y, q, v, par);
            }

            if (r == 14)
            {
                DFSB(x, y, q, v, par);
                DFSL(x, y, q, v, par);
                DFST(x, y, q, v, par);
                DFSR(x, y, q, v, par);
            }

            if (r == 15)
            {
                DFSL(x, y, q, v, par);
                DFSB(x, y, q, v, par);
                DFST(x, y, q, v, par);
                DFSR(x, y, q, v, par);
            }

            if (r == 16)
            {
                DFST(x, y, q, v, par);
                DFSB(x, y, q, v, par);
                DFSL(x, y, q, v, par);
                DFSR(x, y, q, v, par);
            }

            if (r == 17)
            {
                DFSB(x, y, q, v, par);
                DFST(x, y, q, v, par);
                DFSL(x, y, q, v, par);
                DFSR(x, y, q, v, par);
            }

            if (r == 18)
            {
                DFSB(x, y, q, v, par);
                DFST(x, y, q, v, par);
                DFSR(x, y, q, v, par);
                DFSL(x, y, q, v, par);
            }

            if (r == 19)
            {
                DFST(x, y, q, v, par);
                DFSB(x, y, q, v, par);
                DFSR(x, y, q, v, par);
                DFSL(x, y, q, v, par);
            }

            if (r == 20)
            {
                DFSR(x, y, q, v, par);
                DFST(x, y, q, v, par);
                DFSB(x, y, q, v, par);
                DFSL(x, y, q, v, par);
            }

            if (r == 21)
            {
                DFSB(x, y, q, v, par);
                DFSR(x, y, q, v, par);
                DFST(x, y, q, v, par);
                DFSL(x, y, q, v, par);
            }

            if (r == 22)
            {
                DFST(x, y, q, v, par);
                DFSR(x, y, q, v, par);
                DFSB(x, y, q, v, par);
                DFSL(x, y, q, v, par);
            }

            if (r == 23)
            {
                DFSR(x, y, q, v, par);
                DFST(x, y, q, v, par);
                DFSB(x, y, q, v, par);
                DFSL(x, y, q, v, par);
            }
        }
    }

    path.push_back(pos);
    return path;
}

void Map::DFSL(const int &x, const int &y, std::stack<std::pair<int, int>> &q, std::set<std::pair<int, int>> &v, std::map<std::pair<int, int>, std::pair<int, int>> &par) const
{
    if (v.find(make_pair(y, x - 1)) == v.end() && x - 1 >= 0)
    {
        q.push(make_pair(y, x - 1));
        par[make_pair(y, x - 1)] = make_pair(y, x);
    }
}

void Map::DFSR(const int &x, const int &y, std::stack<std::pair<int, int>> &q, std::set<std::pair<int, int>> &v, std::map<std::pair<int, int>, std::pair<int, int>> &par) const
{
    if (v.find(make_pair(y, x + 1)) == v.end() && x + 1 < _w)
    {
        q.push(make_pair(y, x + 1));
        par[make_pair(y, x + 1)] = make_pair(y, x);
    }
}

void Map::DFST(const int &x, const int &y, std::stack<std::pair<int, int>> &q, std::set<std::pair<int, int>> &v, std::map<std::pair<int, int>, std::pair<int, int>> &par) const
{
    if (v.find(make_pair(y - 1, x)) == v.end() && y - 1 >= 0)
    {
        q.push(make_pair(y - 1, x));
        par[make_pair(y - 1, x)] = make_pair(y, x);
    }
}

void Map::DFSB(const int &x, const int &y, std::stack<std::pair<int, int>> &q, std::set<std::pair<int, int>> &v, std::map<std::pair<int, int>, std::pair<int, int>> &par) const
{
    if (v.find(make_pair(y + 1, x)) == v.end() && y + 1 < _h)
    {
        q.push(make_pair(y + 1, x));
        par[make_pair(y + 1, x)] = make_pair(y, x);
    }
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