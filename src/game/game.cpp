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

        _canvas = new Canvas(_consts.GetCanvasWidth(), _consts.GetCanvasHeight());
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
        _canvas -> Draw();
        ProcessInput();
        _canvas -> Clear(); 
        if(_run)
            GameLoop();
    }
    /**
     * @brief 
     * 
     */
    void GameManager::Start(){
        _run = true;
        Text * txt = new Text(1, 1, White, "HelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHello");
        _canvas -> AddElement(txt);
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
        delete _canvas;
    }
}