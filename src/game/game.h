#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "../ui/ui.h"

using namespace std;
using namespace UI;

/**
 * @brief Namespace for key game logic components.
 * 
 */
namespace GameLogic{

    //Possible states of game
    enum GameState { MainMenu, MapChooseMenu, Encyclopedia, Loading, InGame }; 

    /**
     * @brief Class for storing info about current game and global operations with other components.
     * This class is like "root" component. It contains current state of game, drawing canvas, references to defined consts and methods for managing the game.
     */
    class GameManager{
        private:
            GameState _state;
            Canvas * _canvas;
            bool _run;

            /**
             * @brief Switches the state of current game.
             * 
             * @param nextState Next state of game
             */
            void SwitchState(GameState nextState);
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