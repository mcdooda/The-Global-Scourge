#ifndef ENGINE_INPUT_KEYBOARD_H
 #define ENGINE_INPUT_KEYBOARD_H

#include <vector>
#include <SDL/SDL.h>

#define K(k) SDLK_##k

namespace engine
{
    namespace input
    {
        namespace keyboard
        {

            typedef SDLKey Key;

            bool isPressed(Key k);
            bool isJustPressed(Key k);
            bool isJustReleased(Key k);
            
            std::vector<Key> getPressedKeys();
            std::vector<Key> getJustPressedKeys();
            std::vector<Key> getJustReleasedKeys();

            Uint16* getUnicodeText(int* length);

            /* private */
            void clearEvents();
            void addEvent(const SDL_Event& e);
            void init();
            void free();

        }
    }
}

#endif
