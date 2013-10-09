#include "engine/singleton.h"
#include "game/game.h"

int main(int argc, char* argv[])
{
    //freopen("CON", "w", stdout);
    S(game::Game);
    S(game::Game)->init(argc, argv);
    S(game::Game)->loop();
    return 0;
}
