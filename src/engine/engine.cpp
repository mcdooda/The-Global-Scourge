#include <SDL/SDL.h>
#include "engine.h"
#include "input/input.h"
#include "graphics/graphics.h"
#include "sound/sound.h"
#include "time.h"
#include "random.h"

namespace engine
{

    void init()
    {
        initSDL();
        input::init();
        time::init();
        graphics::init();
        sound::init();
        random::init();
    }

    void free()
    {
        quitSDL();
        input::free();
        time::free();
        graphics::free();
        sound::free();
        random::free();
    }

    /* private */
    void initSDL()
    {
        SDL_Init(SDL_INIT_VIDEO);
    }

    void quitSDL()
    {
        SDL_Quit();
    }

}
