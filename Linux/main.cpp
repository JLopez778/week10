/*
    Getting started with SDL2 - Just project setup and includes.  
*/

//For exit()
#include <cstdlib>
#include <memory>

#include "Game.hpp"

int main( int argc, char* args[] )
{
    std::shared_ptr<Game> game = Game::instance();
    game->init();
    game->runGameLoop();
    
    exit(EXIT_SUCCESS);
}
