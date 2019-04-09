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
    
    GameManager::GameManager(){ 
        _state = MainMenu; 
        _run = false;

        //Loading from consts
        _input.Set(_consts.GetUpKey(), _consts.GetDownKey(),_consts.GetLeftKey(), _consts.GetRightKey(), _consts.GetCancelKey(), _consts.GetConfirmKey());

        LoadScreens();
    }
    
    void GameManager::LoadScreens(){
        _mainMenu = new Canvas(_consts.GetCanvasWidth(), _consts.GetCanvasHeight(), false);

        bt1 = new Button(8,2,White,"Play", Green,2);
        bt2 = new Button(8,3,White,"Help", Green,3);
        bt3 = new Button(8,4,White,"Exit", Green,0);
        bt1 -> Active();
        bt1 -> SetNextElements(NULL, NULL, NULL, bt2);
        bt2 -> SetNextElements(NULL, NULL, bt1, bt3);
        bt3 -> SetNextElements(NULL, NULL, bt2, NULL);
        current = bt1;
        _mainMenu -> AddElement(bt1);
        _mainMenu -> AddElement(bt2);
        _mainMenu -> AddElement(bt3);
        _help = new Canvas(_consts.GetCanvasWidth(), _consts.GetCanvasHeight(), false);
        _game = new Canvas(_consts.GetCanvasWidth(), _consts.GetCanvasHeight(), true);
    }
    
    void GameManager::SwitchState(const GameState & nextState){
        _state = nextState;
    }
    
    void GameManager::ProcessInput(){
        Key key = _input.Process();
        if(key == Key::End){
            _run = false;
            return;
        }
        switch (_state)
        {
            case MainMenu:
                switch (key)
                {
                    case Key::Left:
                        break;
                    case Key::Right:
                        break;
                    case Key::Up:
                        current = current -> GetNext(UI::Up);
                        break;
                    case Key::Down:
                        current = current -> GetNext(UI::Down);
                        break;
                    case Key::Confirm:
                        SwitchState(GameLogic::GameState(current -> GetIndex()));
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
        if(_state == GameState::Exit)
            _run = false;
        if(_run)
            GameLoop();
    }

    void GameManager::Start(){
        _run = true;
        GameLoop();
    }
    
    void GameManager::Reset(){
        
    }
    
    void GameManager::End(){
        
    }
    
    GameManager::~GameManager(){
        delete _mainMenu;
        delete _help;
        delete _game;
    }
}