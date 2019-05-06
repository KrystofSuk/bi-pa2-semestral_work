#ifndef MAP_H
#define MAP_H

#include <string>
#include "map.h"
#include "../extras/file.h"

using namespace std;

namespace GameLogic
{
    enum Color { White, Black, Blue, Red, Green, Yellow };

    class Tile{
        public:
            Tile();
            Tile(char t, int x, int y, Color c, bool p);
            void SetChar(char n);
            char GetChar() const;
            Color GetColor() const;
            bool GetPassable() const;
        private:
            Color _color = White;
            bool _passable = true;
            char _char = ' ';
    };

    class Map{
        private:
            Tile ** _tiles = nullptr;

            pair<int, int> _s;
            pair<int, int> _e;
            
            int _h = 0;
            int _w = 0;
        public:
            Map();
            Map(string name);
            int GetH() const;
            int GetW() const;

            bool IsReachable(const pair<int, int> & a, const pair<int, int> & b) const;

            pair<int, int> BFS(const pair<int, int> & pos) const;
            pair<int, int> PTH(const pair<int, int> & pos) const;            

            Map & operator=(const Map& other);

            void GetChars(char ** c) const;
            void GetColors(Color ** c) const;

            pair<int, int> GetS() const;
            ~Map();
    };
}
#endif