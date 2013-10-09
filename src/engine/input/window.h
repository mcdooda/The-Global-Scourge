#ifndef ENGINE_INPUT_WINDOW_H
 #define ENGINE_INPUT_WINDOW_H

#include <SDL/SDL.h>
#include "../graphics/window.h"

namespace engine
{
    namespace input
    {
        namespace window
        {

            bool closed();
            bool resized();

            inline int getWidth() { return graphics::window::getWidth(); }
            inline int getHeight() { return graphics::window::getHeight(); }

            /* private */
            void clearEvents();
            void addEvent(const SDL_Event& e);
            void init();
            void free();

        }
    }
}

#endif
