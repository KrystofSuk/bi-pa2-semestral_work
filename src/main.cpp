#include <iostream>
#include <unistd.h>
#include <iomanip>
#include "game/game.h"

using namespace std;

int main ( void ) {
    system("stty sane"); 
    cout << "\033c" << "Tower  Defence" << endl << " --sukkryst-- " << endl;
    usleep(2*(1000000));
    cout << "\033c";
    GameLogic::GameManager game;
    game.Start();
    system("stty sane"); 
    cout << endl;
    return 0;
}