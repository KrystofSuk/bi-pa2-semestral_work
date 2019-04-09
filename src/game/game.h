#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "../ui/ui.h"
#include "../ui/ui_elements.h"
#include "input.h"
#include "../extras/const.h"

using namespace std;
using namespace UI;

/**
 * @brief Namespace for key game logic components.
 * 
 */
namespace GameLogic{

    //Possible states of game
    enum GameState { Exit, MainMenu, MapSelect, Help, Loading, InGame }; 

    /**
     * @brief Class for storing info about current game and global operations with other components.
     * This class is like "root" component. It contains current state of game, drawing canvas, references to defined consts and methods for managing the game.
     */
    class GameManager{
        private:
            GameState _state;
            Extra::Consts _consts;
            InputProcesser _input;
            Canvas * _mainMenu;
            Canvas * _game;
            Canvas * _help;
            
            bool _run;
            
            Button * bt1;
            Button * bt2;
            Button * bt3;
            Button * current;

            /**
             * @brief Switches the state of current game.
             * 
             * @param nextState Next state of game
             */
            void SwitchState(const GameState & nextState);
            /**
             * @brief Process input method for checking keys which asks input component for informations.
             * 
             */
            void ProcessInput();
            /**
             * @brief Main game loop where main game logic takes the place, like drawing on canvas, clearing, processing inputs and so on.
             * 
             */
            void GameLoop();
            void LoadScreens();
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
            void Reset();
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
}
#endif