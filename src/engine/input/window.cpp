#include "window.h"
#include "../graphics/window.h"

namespace engine
{
    namespace input
    {
        namespace window
        {

            static bool windowClosed;
            static bool windowResized;

            bool closed()
            {
                return windowClosed;
            }

            bool resized()
            {
                return windowResized;
            }

            /* private */
            void clearEvents()
            {
                windowClosed = false;
                windowResized = false;
            }

            void addEvent(const SDL_Event& e)
            {
                switch (e.type)
                {
                    case SDL_QUIT:
                    windowClosed = true;
                    break;

                    case SDL_VIDEORESIZE:
                    windowResized = true;
                    graphics::window::setWidth(e.resize.w);
                    graphics::window::setHeight(e.resize.h);
                    break;
                }
            }

            void init()
            {
                clearEvents();
            }

            void free()
            {

            }

        }
    }
}
