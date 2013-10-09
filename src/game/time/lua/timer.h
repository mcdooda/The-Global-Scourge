#ifndef GAME_TIME_LUA_TIMER_H
 #define GAME_TIME_LUA_TIMER_H

#include "../../lua/lua.h"

namespace game
{
    namespace time
    {
        namespace lua
        {

            int timerLib(lua_State* L);
            
            int Timer_new(lua_State* L);
            int Timer_stop(lua_State* L);
            int Timer_setLoops(lua_State* L);

        }
    }
}

#endif
