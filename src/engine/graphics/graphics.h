#ifndef ENGINE_GRAPHICS_GRAPHICS_H
 #define ENGINE_GRAPHICS_GRAPHICS_H

namespace engine
{
    namespace graphics
    {

        void beginFrame();
        void endFrame();

        /* private */
        void init();
        void free();

    }
}

#endif
