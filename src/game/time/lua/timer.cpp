#include "timer.h"
#include "../luatimer.h"

namespace game
{
    namespace time
    {
        namespace lua
        {
            
            int timerLib(lua_State* L)
            {
                static const luaL_reg Timer_lib[] = {
                    {"new",      Timer_new},
                    {"stop",     Timer_stop},
                    {"setLoops", Timer_setLoops},
                    {NULL, NULL}
                };
                luaL_register(L, "Timer", Timer_lib);
                
                return 0;
            }
            
            int Timer_new(lua_State* L)
            {
                float timeOut = 0;
                bool loops = true;
                if (lua_gettop(L) == 1)
                {
                    luaL_checktype(L, 1, LUA_TFUNCTION);
                }
                else
                {
                    timeOut = luaL_checknumber(L, 1);
                    loops = lua_toboolean(L, 2);
                    luaL_checktype(L, 3, LUA_TFUNCTION);
                }
                LuaTimer* timer = new LuaTimer(timeOut, loops);
                timer->setOnTimeOut(L);
                lua_pushlightuserdata(L, timer);
                return 1;
            }
            
            int Timer_stop(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                LuaTimer* timer = (LuaTimer*) lua_touserdata(L, 1);
                timer->stop();
                return 0;
            }
            
            int Timer_setLoops(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                LuaTimer* timer = (LuaTimer*) lua_touserdata(L, 1);
                bool loops = lua_toboolean(L, 2);
                timer->setLoops(loops);
                return 0;
            }
            
        }
    }
}
