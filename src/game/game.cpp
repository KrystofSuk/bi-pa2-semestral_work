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
                //_canvas -> MoveCursor(UI::Left);
                break;
            case GameLogic::Right:
                //_canvas -> MoveCursor(UI::Right);
                break;
            case GameLogic::Up:
                //_canvas -> MoveCursor(UI::Up);
                break;
            case GameLogic::Down:
                //_canvas -> MoveCursor(UI::Down);
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