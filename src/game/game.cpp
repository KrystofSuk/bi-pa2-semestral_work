#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <math.h>

#include "game.h"
#include "input.h"
#include "maps.h"
#include "unit.h"
#include "units.h"
#include "tower.h"

#include "../extras/const.h"
#include "../extras/file.h"

using namespace std;

namespace GameLogic
{


    GameManager::GameManager()
    {
        _state = InGame;
        _run = false;

        //Loading from consts
        _input.Set(_consts.GetUpKey(), _consts.GetDownKey(), _consts.GetLeftKey(), _consts.GetRightKey(), _consts.GetCancelKey(), _consts.GetConfirmKey(), _consts.GetNextKey());

        LoadScreens();

        //Loading Towers        
        Tower * bas;
        bas = new BasicTower(make_pair(_cY, _cX));
        _towerPref.push_back(bas);
    }

    void GameManager::LoadScreens()
    {
        currentMap = Map("lvl2");
        Resize(currentMap.GetW(), currentMap.GetH());
    }

    void GameManager::SwitchState(const GameState &nextState)
    {
        _state = nextState;
    }

    void GameManager::ProcessInput()
    {
        Key key = _input.Process();
        if (key == Key::End)
        {
            _run = false;
            return;
        }
        switch (_state)
        {
            case InGame:
                switch (key)
                {
                case Key::Left:
                    if (_cX > 0)
                        _cX -= 1;
                    break;
                case Key::Right:
                    if (_cX < _w - 1)
                        _cX += 1;
                    break;
                case Key::Up:
                    if (_cY > 0)
                        _cY -= 1;
                    break;
                case Key::Down:
                    if (_cY < _h - 1)
                        _cY += 1;
                    break;
                case Key::Confirm:
                    Tower * bas;
                    bas = new BasicTower(make_pair(_cY, _cX));
                    bool tmp;
                    tmp =  currentMap.PlaceTower(make_pair(_cY, _cX));
                    if(tmp)
                        _towers.push_back(bas);
                    else
                        delete bas;
                    break;
                case Key::End:
                    _run = false;
                    break;
                case Key::Next:
                    GameStep();
                    break;

                default:
                    break;
                }
                break;

            default:
                break;
        }
    }

    void GameManager::GameLoop()
    {
        system("stty sane");
        //_canvas -> Draw();
        switch (_state)
        {
        case MainMenu:
            break;
        case Help:
            break;
        case InGame:
            DrawInGame();
            break;
        default:
            break;
        }
        ProcessInput();
        system("stty sane");

        Clear();

        if (_state == GameState::Exit)
            _run = false;
        if (_run)
            GameLoop();
    }

    void GameManager::Resize(int x, int y)
    {
        for (int i = 0; i < _h; i++)
        {
            if (_display[i] != nullptr)
                delete[] _display[i];
            if (_colors[i] != nullptr)
                delete[] _colors[i];
        }
        if (_display != nullptr)
            delete[] _display;
        if (_colors != nullptr)
            delete[] _colors;

        _colors = new Color *[y];
        _display = new char *[y];
        for (int i = 0; i < y; i++)
        {
            _colors[i] = new Color[x];
            _display[i] = new char[x];
            for (int t = 0; t < x; t++){
                _display[i][t] = ' ';
                _colors[i][t] = White;
            }
        }
        _w = x;
        _h = y;
    }

    void GameManager::Start()
    {
        _run = true;
        GameLoop();
    }

    void GameManager::Clear() 
    {
        cout << "\033c";
        for (int i = 0; i < _h; i++)
            for (int t = 0; t < _w; t++)
                _colors[i][t] = White;
    }

    void GameManager::DrawInGame() const
    {
        //Displaying Map
        currentMap.GetChars(_display);
        currentMap.GetColors(_colors);
        //Displaying Enemies
        for(auto i = _enemies.begin(); i < _enemies.end(); i++){
            (*i)->GetChar(_display);
            (*i)->GetColor(_colors);
        }
        //Displaying Towers
        for(auto i = _towers.begin(); i < _towers.end(); i++){
            (*i)->GetChar(_display);
            (*i)->GetColor(_colors);
        }
        //Displays Cursor
        if(_display[_cY][_cX] == ' ' || _display[_cY][_cX] == '#' || _display[_cY][_cX] == 's' || _display[_cY][_cX] == 'e'){
            _display[_cY][_cX] = 'x';
            _colors[_cY][_cX] = Green;
        }

        if(_currentTower != -1){
            for(int r = _towerPref[_currentTower]->GetDistance(); r >= 1; r--){
                for(int ang = 0; ang < 360; ang += 1){
                    int tY = round(_cY + r * sin(ang));
                    int tX = round(_cX + r * cos(ang));
                    if(tY < 0 || tX < 0 || tX >= _w || tY >= _h)
                        continue;
                    if(_display[tY][tX] == ' '){
                        _display[tY][tX] = '+';
                        _colors[tY][tX] = Red;
                    }
                }
            }
        }

        string col;
        for (int i = 0; i < _h; i++)
        {
            for (int t = 0; t < _w; t++)
            {
                switch (_colors[i][t])
                {
                case White:
                    col = "\033[0;37m";
                    break;
                case Black:
                    col = "\033[0;30m";
                    break;
                case Blue:
                    col = "\033[0;34m";
                    break;
                case Red:
                    col = "\033[0;31m";
                    break;
                case Green:
                    col = "\033[0;32m";
                    break;
                case Yellow:
                    col = "\033[0;33m";
                    break;
                default:
                    col = "\033[0;37m";
                    break;
                }
                
                cout << col << _display[i][t];
            }
            cout << endl;
        }

        //Display Main
        cout << " ------------------------ " << endl;
        cout << "|        Lives: " << setw(2) << setfill(' ') << _lives << "       |" << endl;
        cout << " ------------------------ " << endl;
        cout << "| Wave: " << setw(2) << setfill('0') << _currentWave << "/" << setw(2) << setfill('0') << _maxWave << " Money: " << setw(3) << setfill('0') << _currentMoney << " |" << endl;
        cout << " ------------------------ " << endl;
        if(_currentTower != -1){
            cout << *_towerPref[_currentTower] << endl;
        }else{
            cout << "|         cursor         |" << endl;
        }
        cout << " ------------------------ " << endl;
    }

    void GameManager::GameStep(){

        if(_enemies.size() > 0){
            if(_towers.size() > 0){
                for(auto i = _towers.begin(); i < _towers.end(); i++){
                    (*i)->ProcessAttack(_enemies);
                }
            }

            for(auto i = _enemies.end()-1; i >= _enemies.begin(); i--){
                if(!(*i)->IsAlive()){
                    delete *i;
                    _enemies.erase(i);
                }
            }
            
            for(auto i = _enemies.begin(); i < _enemies.end(); i++){
                (*i)->Move(currentMap);
            }
        }

        
        Unit * slime;
        slime = new Slime(currentMap.GetS());
        _enemies.push_back(slime);
    }

    void GameManager::Reset()
    {
    }

    void GameManager::End()
    {
    }

    GameManager::~GameManager()
    {
        for (int i = 0; i < _h; i++)
        {
            delete[] _colors[i];
            delete[] _display[i];
        }
        delete[] _colors;
        delete[] _display;

        for(auto i = _enemies.begin(); i < _enemies.end(); i++)
            delete *i;
        for(auto i = _towers.begin(); i < _towers.end(); i++)
            delete *i;
    }
} // namespace GameLogic