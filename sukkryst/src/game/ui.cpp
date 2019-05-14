#include <iostream>
#include <string>
#include <iomanip>
#include <dirent.h>

#include "game.h"
#include "ui.h"
#include "../extras/file.h"

using namespace std;

namespace GameLogic
{

GameUI::GameUI(){

}

GameUI::~GameUI(){

}

GameMainMenuUI::GameMainMenuUI(){

}

void GameMainMenuUI::Draw() const{
    cout << "\033c";
    cout << " ------------------------ " << endl;
    cout << " Welcome to Tower Defence " << endl;
    cout << "    -Game By sukkryst-    " << endl;
    cout << " ------------------------ " << endl;
    if(current == 0)
        cout << "       \033[0;36m> \033[0;37mPlay Game        " << endl;
    else
        cout << "         Play Game        " << endl;
    if(current == 1)
        cout << "         \033[0;36m> \033[0;37mHelp           " << endl;
    else
        cout << "           Help           " << endl;
    if(current == 2)
        cout << "         \033[0;36m> \033[0;37mExit           " << endl;
    else
        cout << "           Exit           " << endl;
}

void GameMainMenuUI::Move(int x, int y){
    current += y;
    if(current >= 3)
        current = 0;
    if(current < 0)
        current = 2;
}

void GameMainMenuUI::Continue(){

}

int GameMainMenuUI::GetState() const{
    return current == 0 ? 2 : current == 1 ? 3 : 0;
}

string GameMainMenuUI::GetMsg() const{
    return "";
}

GameMainMenuUI::~GameMainMenuUI(){
    
}

GameHelpUI::GameHelpUI(){

}

void GameHelpUI::Draw() const{
    cout << "\033c";
    cout << " ------------------------ " << endl;
    cout << " If not modified controls " << endl;
    cout << "  Arrows - movement       " << endl;
    cout << "   Enter - confirmation   " << endl;
    cout << "         - build tower    " << endl;
    cout << "   Space - next turn      " << endl;
    cout << "       Q - next cursor    " << endl;
    cout << "         - next tower     " << endl;
    cout << " ------------------------ " << endl << endl;
    cout << "   Press Enter to close   " << endl;
}

void GameHelpUI::Move(int x, int y){
}

void GameHelpUI::Continue(){
}

int GameHelpUI::GetState() const{
    return 0;
}

string GameHelpUI::GetMsg() const{
    return "";
}

GameHelpUI::~GameHelpUI(){
    
}

GameLevelSelectUI::GameLevelSelectUI(){
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("./examples/maps")) != NULL) {
    while ((ent = readdir (dir)) != NULL) {
        if(string(ent->d_name).find("info") == string::npos && string(ent->d_name).find("lvl") != string::npos){
            _lvls.push_back(ent->d_name);
            }
        }
        closedir (dir);
    }
    for(auto i = _lvls.begin(); i < _lvls.end(); i++)
        _valid.push_back(Map(*i).IsValid());
}

void GameLevelSelectUI::Draw() const{
    cout << "\033c";
    cout << " ------------------------ " << endl;
    cout << "     Select Game Level    " << endl;
    cout << " ------------------------ " << endl;

    int i = 0;
    for(auto t = _lvls.begin(); t < _lvls.end(); t++){
        if(_valid[i])
            cout << "         " ;
        else
            cout << "   " ;
        if(i == current)
            cout << "\033[0;36m> ";
        else
            cout << "  ";
        if(_valid[i])
            cout << "\033[0;37m" << *t << endl;
        else
            cout << "\033[0;33m" << "Not Valid: " << *t << "!\033[0;37m" << endl;
        i++;
    }

    if(current == _lvls.size())
        cout << "         \033[0;36m> \033[0;37mExit           " << endl;
    else
        cout << "           Exit           " << endl;
}

void GameLevelSelectUI::Move(int x, int y){
    current += y;
    if(current < 0){
        current = _lvls.size();
    }
    if(current > _lvls.size()){
        current = 0;
    }
}

void GameLevelSelectUI::Continue(){

}

int GameLevelSelectUI::GetState() const{
    return current != _lvls.size() ? current : -1;
}

string GameLevelSelectUI::GetMsg() const{
    if(GetState() != -1)
        return _lvls[current];
    return "";
}

GameLevelSelectUI::~GameLevelSelectUI(){
    
}
}