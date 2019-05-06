#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <math.h>

#include "game.h"
#include "input.h"
#include "map.h"

#include "../extras/const.h"

using namespace std;

namespace GameLogic
{

GameManager::GameManager()
{
    _state = InGame;
    _run = false;

    //Loading from consts
    _input.Set(_consts.GetUpKey(), _consts.GetDownKey(), _consts.GetLeftKey(), _consts.GetRightKey(), _consts.GetCancelKey(), _consts.GetConfirmKey());

    LoadScreens();
}

void GameManager::LoadScreens()
{
    currentMap = Map("lvl1");
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
            break;
        case Key::End:
            _run = false;
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
    Draw();
    switch (_state)
    {
    case MainMenu:
        break;
    case Help:
        break;
    case InGame:
        break;
    default:
        break;
    }
    ProcessInput();

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

void GameManager::Draw() const
{
    currentMap.GetChars(_display);
    _display[_cY][_cX] = 'x';
    _colors[_cY][_cX] = Blue;
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
        delete[] _display[i];
    }
    delete[] _display;
}
} // namespace GameLogic