#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "window.h"

namespace engine
{
    namespace input
    {

        void poll()
        {
            SDL_Event e;
            keyboard::clearEvents();
            mouse::clearEvents();
            window::clearEvents();
            while (SDL_PollEvent(&e))
            {
                keyboard::addEvent(e);
                mouse::addEvent(e);
                window::addEvent(e);
            }
        }

        void clearAll()
        {
            SDL_Event e;
            while (SDL_PollEvent(&e));
            keyboard::clearEvents();
            mouse::clearEvents();
            window::clearEvents();
        }

        void init()
        {
            keyboard::init();
            mouse::init();
            window::init();
        }

        void free()
        {
            keyboard::free();
            mouse::free();
            window::free();
        }

    }
}
