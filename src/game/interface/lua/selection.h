#ifndef GAME_INTERFACE_LUA_SELECTION_H
 #define GAME_INTERFACE_LUA_SELECTION_H

#include "../../lua/lua.h"

namespace game
{
    namespace interface
    {
        namespace lua
        {

            int selectionLib(lua_State* L);

            int Selection_getEntities(lua_State* L);
            
            int Selection_onChange(lua_State* L);

        }
    }
}

#endif
