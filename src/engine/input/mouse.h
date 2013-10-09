#ifndef ENGINE_INPUT_MOUSE_H
 #define ENGINE_INPUT_MOUSE_H

#include <SDL/SDL.h>
#include "../vector2d.h"

#define M(m) SDL_BUTTON_##m

namespace engine
{
    namespace input
    {
        namespace mouse
        {

            bool isPressed(int button);
            bool isJustPressed(int button);
            bool isJustReleased(int button);

            bool moved();

            int getX();
            int getY();

            float getViewX();
            float getViewY();
            engine::Vector2d getViewPosition();

            /* private */
            void clearEvents();
            void addEvent(const SDL_Event& e);
            void init();
            void free();

        }
    }
}

#endif
