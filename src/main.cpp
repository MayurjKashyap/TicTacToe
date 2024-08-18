#include <string>
#include "game.h"
#include "helper.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    init(screenWidth,screenHeight);
    Game Game;

    while (windowcondition())
    {
        Game.updateFrame();
    }

    close();
    return 0;
}