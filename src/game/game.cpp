#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <math.h>

#include "game.h"
#include "input.h"

#include "../ui/ui.h"
#include "../ui/ui_elements.h"

#include "../extras/const.h"

using namespace std;
using namespace UI;

namespace GameLogic{
    /**
     * @brief Construct a new Game Manager:: Game Manager object
     * 
     */
    GameManager::GameManager(){ 
        _state = MainMenu; 
        _run = false;

        //Loading from consts
        _input.Set(_consts.GetUpKey(), _consts.GetDownKey(),_consts.GetLeftKey(), _consts.GetRightKey(), _consts.GetCancelKey(), _consts.GetConfirmKey());

        LoadScreens();
    }
    
    void GameManager::LoadScreens(){
        _mainMenu = new Canvas(_consts.GetCanvasWidth(), _consts.GetCanvasHeight());
        Button * bt = new Button(5,5,White,"Play", Green, "H");
        _mainMenu -> AddElement(bt);
        _help = new Canvas(_consts.GetCanvasWidth(), _consts.GetCanvasHeight());
        _game = new Canvas(_consts.GetCanvasWidth(), _consts.GetCanvasHeight());
    }
    /**
     * @brief 
     * 
     * @param nextState 
     */
    void GameManager::SwitchState(const GameState & nextState){
        _state = nextState;
    }
    /**
     * @brief 
     * 
     */
    void GameManager::ProcessInput(){
        Key key = _input.Process();
        switch (key)
        {
            case GameLogic::Left:
                _mainMenu -> MoveCursor(UI::Left);
                break;
            case GameLogic::Right:
                _mainMenu -> MoveCursor(UI::Right);
                break;
            case GameLogic::Up:
                _mainMenu -> MoveCursor(UI::Up);
                break;
            case GameLogic::Down:
                _mainMenu -> MoveCursor(UI::Down);
                break;
            case GameLogic::End:
                _run = false;
                break;
        
            default:
                break;
        }
    }
    /**
     * @brief 
     * 
     */
    void GameManager::GameLoop(){
        system("stty sane");
        //_canvas -> Draw();
        switch (_state)
        {
            case MainMenu:
                _mainMenu -> Draw();
                break;
            case Help:
                _help -> Draw();
                break;
            case InGame:
                _game -> Draw();
                break;
            default:
                break;
        }
        ProcessInput();
        _mainMenu -> Clear();
        _game -> Clear();
        _help -> Clear(); 
        if(_run)
            GameLoop();
    }
    /**
     * @brief 
     * 
     */
    void GameManager::Start(){
        _run = true;
        GameLoop();
    }
    /**
     * @brief 
     * 
     */
    void GameManager::Reset(){
        
    }
    /**
     * @brief 
     * 
     */
    void GameManager::End(){
        
    }
    /**
     * @brief Destroy the Game Manager:: Game Manager object
     * 
     */
    GameManager::~GameManager(){
        delete _mainMenu;
        delete _help;
        delete _game;
    }
}