#ifndef GAME_MOD_LUA_MOD_H
 #define GAME_MOD_LUA_MOD_H

#include "../../lua/lua.h"

namespace game
{
    namespace mod
    {
        namespace lua
        {

            int modLib(lua_State* L);

            int Mod_getPath(lua_State* L);
            int Mod_getResourcePath(lua_State* L);

        }
    }
}

#endif
