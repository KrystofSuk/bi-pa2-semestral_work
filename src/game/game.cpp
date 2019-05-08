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
    _state = MainMenu;
    _ui.push_back(new GameMainMenuUI());
    _ui.push_back(new GameHelpUI());
    _ui.push_back(new GameLevelSelectUI());

    //Loading Towers
    Tower *bas;
    bas = new BasicTower(make_pair(_cY, _cX));
    _towerPref.push_back(bas);

    GameLoop();    
}

void GameManager::LoadLevel(string num)
{
    _state = InGame;
    _run = false;

    //Loading from consts
    _input.Set(_consts.GetUpKey(), _consts.GetDownKey(), _consts.GetLeftKey(), _consts.GetRightKey(), _consts.GetCancelKey(), _consts.GetConfirmKey(), _consts.GetNextKey(), _consts.GetChangeKey());

    //loading level
    currentMap = Map(num);
    Resize(currentMap.GetW(), currentMap.GetH());

}

void GameManager::SwitchState(const GameState &nextState)
{
    _state = nextState;
    if(_state == Exit)
        _run = false;
}

void GameManager::ProcessInput()
{
    Key key = _input.Process();
    system("stty sane");
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
            PlaceTower();
            break;
        case Key::Change:
            NextCursor();
            break;
        case Key::End:
            _run = false;
            break;
        case Key::Next:
            GameStep();
            break;
        }
        break;
    case MainMenu:
        switch (key)
        {
        case Key::Up:
            _ui[0]->Move(0,-1);
            break;
        case Key::Down:
            _ui[0]->Move(0,1);
            break;
        case Key::Confirm:
            SwitchState(GetGameState(_ui[0]->GetState()));
            break;
        case Key::End:
            _run = false;
            break;
        }
        break;
    case Help:
        switch (key)
        {
        case Key::Up:
            break;
        case Key::Down:
            break;
        case Key::Confirm:
            SwitchState(MainMenu);
            break;
        case Key::End:
            _run = false;
            break;
        }
        break;
    case MapSelect:
        switch (key)
        {
        case Key::Up:
            _ui[2]->Move(0,-1);
            break;
        case Key::Down:
            _ui[2]->Move(0,1);
            break;
        case Key::Confirm:
            if(_ui[2]->GetState() == -1)
                SwitchState(MainMenu);
            else{
                SwitchState(InGame);
                LoadLevel(_ui[2]->GetMsg());
                Start();
            }
            break;
        case Key::End:
            _run = false;
            break;
        }
        break;
    }
}

GameState GameManager::GetGameState(int i) const{
    if(i == 0)
        return Exit;
    if(i == 1)
        return MainMenu;
    if(i == 2)
        return MapSelect;
    if(i == 3)
        return Help;
    if(i == 4)
        return InGame;
}

void GameManager::PlaceTower()
{
    Tower *bas;
    bas = new BasicTower(make_pair(_cY, _cX));
    bool tmp;
    tmp = currentMap.PlaceTower(make_pair(_cY, _cX));
    if (tmp)
        _towers.push_back(bas);
    else
        delete bas;
}

void GameManager::GameLoop()
{
    system("stty sane");
    switch (_state)
    {
    case MainMenu:
        _ui[0]->Draw();
        break;
    case Help:
        _ui[1]->Draw();
        break;
    case InGame:
        DrawInGame();
        break;
    case MapSelect:
        _ui[2]->Draw();
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
        for (int t = 0; t < x; t++)
        {
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

    _currentTower = 0;
    vector<Tower *> _towerPref;

    _currentWave = 0;
    _maxWave = 4;
    _currentMoney = 0;
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
    for (auto i = _enemies.begin(); i < _enemies.end(); i++)
    {
        (*i)->GetChar(_display);
        (*i)->GetColor(_colors);
    }
    char tmp = _display[_cY][_cX];
    //Cursor
    _display[_cY][_cX] = 'x';
    _colors[_cY][_cX] = Green;

    //Displaying Towers
    for (auto i = _towers.begin(); i < _towers.end(); i++)
    {
        (*i)->GetChar(_display);
        (*i)->GetColor(_colors);
    }

    //Tower Distance
    if (_currentTower != -1)
    {
        for (int r = _towerPref[_currentTower]->GetDistance(); r >= 1; r--)
        {
            for (int ang = 0; ang < 360; ang += 1)
            {
                int tY = round(_cY + r * sin(ang));
                int tX = round(_cX + r * cos(ang));
                if (tY < 0 || tX < 0 || tX >= _w || tY >= _h)
                    continue;
                if (_display[tY][tX] == ' ')
                {
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
    bool emp = true;
    if (_currentTower != -1)
    {
        cout << *_towerPref[_currentTower] << endl;
    }
    else
    {
        if (tmp == ' ')
        {
            for (auto i = _towers.begin(); i < _towers.end(); i++)
            {
                if ((*i)->GetPos().first == _cY && (*i)->GetPos().second == _cX)
                {
                    cout << (**i) << endl;
                    emp = false;
                    break;
                }
            }
            if (emp)
                cout << "|         empty          |" << endl;
        }
        else if (tmp == '#')
        {
            cout << "|          wall          |" << endl;
        }
        else
        {
            for (auto i = _enemies.begin(); i < _enemies.end(); i++)
            {
                if ((*i)->GetPos().first == _cY && (*i)->GetPos().second == _cX)
                {
                    cout << (**i) << endl;
                    emp = false;
                    break;
                }
            }
            if (emp)
                cout << "|         xxxxx          |" << endl;
        }
    }
    cout << " ------------------------ " << endl;
}

void GameManager::GameStep()
{

    if (_enemies.size() > 0)
    {
        if (_towers.size() > 0)
        {
            for (auto i = _towers.begin(); i < _towers.end(); i++)
            {
                (*i)->ProcessAttack(_enemies);
            }
        }

        for (auto i = _enemies.end() - 1; i >= _enemies.begin(); i--)
        {
            if (!(*i)->IsAlive())
            {
                delete *i;
                _enemies.erase(i);
            }
        }

        for (auto i = _enemies.begin(); i < _enemies.end(); i++)
        {
            (*i)->Move(currentMap);
        }
    }

    Unit *slime;
    slime = new Slime(currentMap.GetS());
    _enemies.push_back(slime);
}

void GameManager::End()
{
    for (auto i = _enemies.begin(); i < _enemies.end(); i++)
        delete *i;
    for (auto i = _towers.begin(); i < _towers.end(); i++)
        delete *i;
        
    _enemies.clear();
    _towers.clear();
}

void GameManager::NextCursor()
{
    _currentTower++;
    if (_currentTower >= _towerPref.size())
        _currentTower = -1;
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

    for (auto i = _enemies.begin(); i < _enemies.end(); i++)
        delete *i;
    for (auto i = _towers.begin(); i < _towers.end(); i++)
        delete *i;

    for (auto i = _towerPref.begin(); i < _towerPref.end(); i++)
        delete *i;

    for (auto i = _ui.begin(); i < _ui.end(); i++)
        delete *i;
}


}