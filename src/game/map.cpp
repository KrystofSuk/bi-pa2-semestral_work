#include "map.h"

namespace GameLogic
{
    Tile::Tile(){
        _state = ' ';
    }
    Tile::Tile(char t, int x, int y){
        _state = t;
    }
    void Tile::SetState(char n){
        _state = n;
    }
    char Tile::GetState() const{
        return _state;
    }
    Map::Map(){
        
    }
    Map::Map(string name){
        vector<char> c = Extra::File<char>::LoadFromFileClean("res/maps/" + name); 
        vector<int> p = Extra::File<int>::LoadFromFile("res/maps/" + name + "props"); 

        _w = p.at(0);
        _h = p.at(1);

        _tiles = new Tile*[_h];
        for(int i = 0; i < _h; i++){
            _tiles[i] = new Tile[_w];
            for(int t = 0; t < _w; t++){
                char tmp = c.at(t + (i)*_w); 
                if(tmp == 'n')
                    _tiles[i][t] = Tile(' ', t, i);
                if(tmp == 'e')
                    _tiles[i][t] = Tile(tmp, t, i);
                if(tmp == 's')
                    _tiles[i][t] = Tile(tmp, t, i);
                if(tmp == '#')
                    _tiles[i][t] = Tile(tmp, t, i);
            }
        }
        cout << "Completed" << endl;
    }
    Map & Map::operator=(const Map& other) 
    {
        if (this != &other) { 
            if (_w != other._w || _h != other._h) { 
                for(int i = 0; i < _h; i++){
                    if(_tiles[i] != nullptr)
                        delete[] _tiles[i];
                }
                if(_tiles != nullptr)
                    delete[] _tiles;
                _w = other._w;
                _h = other._h;
                
                _tiles = new Tile*[_h];
                for(int i = 0; i < _h; i++){
                    _tiles[i] = new Tile[_w];
                    for(int t = 0; t < _w; t++){
                        _tiles[i][t] = other._tiles[i][t];
                    }
                }
            } 
        }
        return *this;
    }
    int Map::GetH() const{
        return _h;
    }
    int Map::GetW() const{
        return _w;
    }
    void Map::GetChars(char ** c) const{
        for(int i = 0; i < _h; i++){
            for(int t = 0; t < _w; t++){
                c[i][t] = _tiles[i][t].GetState();
            }
        }
    }
    Map::~Map(){
        for(int i = 0; i < _h; i++){
            delete[] _tiles[i];
        }
        delete[] _tiles;
    }
}