#include <string>
#include <iostream>
#include "game.h"
#include "helper.h"
#include <thread>
#include <chrono>

int main()
{
    // int i=0;
    // std::cin>>i;

    const int screenWidth = 800;
    const int screenHeight = 600;

    init(screenWidth,screenHeight);
    Game Game;
    // if(i) 
    // Game.setNetwork(true);
    // else 
    Game.setNetwork(false);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    while (windowcondition())
    {
        Game.updateFrame();
    }

    close();
    return 0;
}