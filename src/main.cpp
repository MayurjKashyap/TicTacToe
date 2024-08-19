#include <iostream>
#include <string>

#include "game.h"
#include "helper.h"

bool quitGame=false;

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    std::cout<<"Enter 1 to host a Server else to join"<<std::endl;
    int x;
    std::cin>>x;
    init(screenWidth,screenHeight);
    Game Game;

    if(x==1) Game.setNetwork(true);
    else Game.setNetwork(false);
    std::cout<<std::endl;

    while (windowcondition())
    {
        if(quitGame) break;
        Game.updateFrame();
    }

    close();
    return 0;
}