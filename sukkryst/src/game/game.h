#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <queue>
#include <deque>
#include "ui.h"
#include "input.h"
#include "unit.h"
#include "units.h"
#include "../extras/const.h"
#include "maps.h"
#include "tower.h"

using namespace std;

/**
 * @brief Namespace for key game logic components.
 * 
 */
namespace GameLogic
{

//Possible states of game
enum GameState
{
    Exit,
    MainMenu,
    MapSelect,
    Help,
    InGame
};

/**
     * @brief Class for storing info about current game and global operations with other components.
     * This class is like "root" component. It contains current state of game, drawing canvas, references to defined consts and methods for managing the game.
     */
class GameManager
{
private:
    GameState _state;
    Extra::Consts _consts;
    InputProcesser _input;

    Map currentMap;
    string _name;

    char **_display = nullptr;
    Color **_colors = nullptr;

    vector<Unit *> _enemies;
    vector<Tower *> _towers;

    bool _run;
    int _w = 0;
    int _h = 0;
    int _cX = 0;
    int _cY = 0;

    int _currentTower = 0;
    vector<Tower *> _towerPref;

    int _currentWave = 0;
    int _maxWave = 4;
    int _currentMoney = 0;
    int _income = 0;

    int _turn = 0;
    queue<int> _waveQueue;

    int _lives = 0;

    vector<GameUI*> _ui;

    /**
     * @brief Switches the state of current game.
     * 
     * @param nextState Next state of game
     */
    void SwitchState(const GameState &nextState);
    /**
     * @brief Process input method for checking keys which asks input component for informations.
     * 
     */
    void ProcessInput();
    /**
     * @brief Main game loop where main game logic takes the place, like drawing on canvas, clearing, processing inputs and so on.
     * 
     */
    void Resize(int x, int y);
    void GameLoop();
    void LoadLevel(string num);
    void Clear();
    void DrawInGame() const;
    void PlaceTower();
    void GameStep();
    void NextCursor();

    void Save() const;
    void Load();

    GameState GetGameState(int i) const;
public:
    /**
     * @brief Construct a new Game Manager object.
     * 
     */
    GameManager();
    /**
     * @brief Starts the game manager.
     * This method switches gamestate to running, calls for loading ui objects and than display main menu.
     */
    void Start();
    /**
     * @brief 
     * 
     */
    void End();
    /**
     * @brief Destroy the Game Manager object.
     * 
     */
    ~GameManager();
};

} // namespace GameLogic
#endif