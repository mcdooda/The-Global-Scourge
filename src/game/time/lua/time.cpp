#include "../../../engine/time.h"
#include "time.h"

namespace game
{
    namespace time
    {
        namespace lua
        {
            
            int timeLib(lua_State* L)
            {
                static const luaL_reg Time_lib[] = {
                    {"getTime",      Time_getTime},
                    {"getFrameRate", Time_getFrameRate},
                    {NULL, NULL}
                };
                luaL_register(L, "Time", Time_lib);
                
                return 0;
            }
            
            int Time_getTime(lua_State* L)
            {
                lua_pushnumber(L, engine::time::getTime());
                return 1;
            }
            
            int Time_getFrameRate(lua_State* L)
            {
                lua_pushnumber(L, 1 / engine::time::getFrameTime());
                return 1;
            }
            
        }
    }
}
