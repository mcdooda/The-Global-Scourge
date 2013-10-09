#ifndef ENGINE_ENGINE_H
 #define ENGINE_ENGINE_H

namespace engine
{

    void init();
    void free();

    /* private */
    void initSDL();
    void quitSDL();

}

#endif
