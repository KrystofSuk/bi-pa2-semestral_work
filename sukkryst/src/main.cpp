#include <iostream>
#include <unistd.h>
#include <iomanip>

#include "game/game.h"


int main ( void ) {
    system("stty sane"); 

    std::cout << "\033c" << "Tower  Defence" << std::endl << " --sukkryst-- " << std::endl;
    usleep(2*(1000000));
    std::cout << "\033c";
    GameLogic::GameManager game;

    system("stty sane"); 
    
    std::cout << std::endl;
    return 0;
}