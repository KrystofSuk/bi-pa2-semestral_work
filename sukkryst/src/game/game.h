#ifndef GAME_H
#define GAME_H

#include "ui.h"
#include "input.h"
#include "maps.h"

#include "../objects/unit.h"
#include "../objects/units.h"
#include "../objects/tower.h"

#include "../extras/const.h"

/**
 * @brief Namespace for key game logic components.
 * 
 */
namespace GameLogic
{
/**
 * @brief Possible states of game
 * 
 */
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
    std::string _name;

    char **_display = nullptr;
    Color **_colors = nullptr;

    std::vector<Unit *> _enemies;
    std::vector<Tower *> _towers;

    bool _run;
    int _w = 0;
    int _h = 0;
    int _cX = 0;
    int _cY = 0;

    int _currentTower = 0;
    std::vector<Tower *> _towerPref;

    int _currentWave = 0;
    int _maxWave = 0;
    int _currentMoney = 0;
    int _income = 0;

    int _turn = 0;
    std::queue<int> _waveQueue;

    int _lives = 0;

    std::vector<GameUI *> _ui;

    /**
     * @brief Starts the game.
     * This method restarts private variables
     */
    void Start();
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
     * @brief Switches cursor to next state like next tower or inspect state
     * 
     */
    void NextCursor();
    /**
     * @brief Main game loop where main game logic takes the place, like drawing on canvas, clearing, processing inputs and so on.
     * 
     */
    void GameLoop();
    /**
     * @brief Game step which is called once player is satisfied and pressed next turn, it resolves movement of enemies, tower firing, next wave spawns and game end system.
     * 
     */
    void GameStep();

    /**
     * @brief Loades selected level and inforamtion about level
     * 
     * @param name of level
     */
    void LoadLevel(const std::string &name);
    /**
     * @brief Resizes displaying array 
     * 
     * @param x new width
     * @param y new height
     */
    void Resize(const int &x, const int &y);

    /**
     * @brief Clears UI
     * 
     */
    void Clear();
    /**
     * @brief Draws whole game, map, towers, enemies, cursor and ingame ui;
     * 
     */
    void DrawInGame() const;

    /**
     * @brief Tries to place a tower if it doesnt block path and if player have enough money
     * 
     */
    void PlaceTower();

    /**
     * @brief Saves current game to save file
     * 
     */
    void Save() const;
    /**
     * @brief Loads saved game
     * 
     */
    void Load();

    /**
     * @brief Get the Game State from int
     * 
     * @param i wanted state number
     * @return const GameState selected state by number
     */
    const GameState GetGameState(const int &i) const;

public:
    /**
     * @brief Construct a new Game Manager object.
     * 
     */
    GameManager();
    /**
     * @brief Destroy the Game Manager object.
     * 
     */
    ~GameManager();
};

} // namespace GameLogic
#endif