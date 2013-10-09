#ifndef GAME_INPUT_LUA_INPUT_H
 #define GAME_INPUT_LUA_INPUT_H

#include "../../lua/lua.h"

namespace game
{
    namespace input
    {
        namespace lua
        {

            int inputLib(lua_State* L);
            
            int Input_onKeyDown(lua_State* L);
            int Input_isMouseOverInterface(lua_State* L);

        }
    }
}

#endif
