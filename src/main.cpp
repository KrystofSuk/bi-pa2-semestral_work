#include <iostream>
#include <string>
#include <iomanip>
#include "game/game.h"

using namespace std;

int main ( void ) {
    GameLogic::GameManager game;
    game.Start();
    system("stty sane"); 
    cout << endl;
    return 0;
}