#ifndef MAP_H
#define MAP_H

#include <string>
#include "map.h"
#include "../extras/file.h"

using namespace std;

namespace GameLogic
{
    class Tile{
        public:
            Tile();
            Tile(char t, int x, int y);
            void SetState(char n);
            char GetState() const;
        private:
            char _state;
    };

    class Map{
        private:
            Tile ** _tiles = nullptr;
            int _h = 0;
            int _w = 0;
        public:
            Map();
            Map(string name);
            int GetH() const;
            int GetW() const;
            Map & operator=(const Map& other);
            void GetChars(char ** c) const;
            ~Map();
    };
}
#endif