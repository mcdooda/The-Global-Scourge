#ifndef GAME_INPUT_INPUT_H
 #define GAME_INPUT_INPUT_H

#include "../../engine/input/keyboard.h"
#include "../lua/lua.h"

namespace game
{
    namespace input
    {
        namespace input
        {
            
            void triggerListeners();
            void setKeyDownListener(engine::input::keyboard::Key key, lua_State* L);
            void removeKeyDownListener(engine::input::keyboard::Key key);
            void clearListeners();
            
            /* private */
            
            
        }
    }
}

#endif
