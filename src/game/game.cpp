#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <math.h>

#include "game.h"
#include "input.h"

#include "../ui/ui.h"
#include "../ui/ui_elements.h"

#include "../extras/file.h"
#include "../extras/const.h"

using namespace std;
using namespace UI;

namespace GameLogic{
    GameManager::GameManager(){ 
        _state = MainMenu; 
        _run = false;
        _canvas = new Canvas(52,12);
    }
    
    void GameManager::SwitchState(const GameState & nextState){
        _state = nextState;
    }

    void GameManager::ProcessInput(){
        Key key = InputProcesser::Process();
        switch (key)
        {
            case GameLogic::End:
                _run = false;
                break;
        
            default:
                break;
        }
    }

    void GameManager::GameLoop(){
        system("stty sane");
        _canvas -> Draw();
        ProcessInput();
        _canvas -> Clear(); 
        if(_run)
            GameLoop();
    }

    void GameManager::Start(){
        int t = Extra::File::LoadFromFile("res/const.txt", "Height");
        cout <<endl << t<< endl ;
        _run = true;
        Text * txt = new Text(1, 1, White, "HelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHello");
        _canvas -> AddElement(txt);
        GameLoop();
    }

    void GameManager::Reset(){
        
    }

    void GameManager::End(){
        
    }

    GameManager::~GameManager(){
        delete _canvas;
    }
}