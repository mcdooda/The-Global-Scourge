#ifndef GAME_TIME_LUA_TIME_H
 #define GAME_TIME_LUA_TIME_H

#include "../../lua/lua.h"

namespace game
{
    namespace time
    {
        namespace lua
        {

            int timeLib(lua_State* L);
            
            int Time_getTime(lua_State* L);
            int Time_getFrameRate(lua_State* L);

        }
    }
}

#endif
