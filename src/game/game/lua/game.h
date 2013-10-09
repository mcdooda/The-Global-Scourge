#ifndef GAME_GAME_LUA_GAME_H
 #define GAME_GAME_LUA_GAME_H

#include "../../lua/lua.h"

namespace game
{
    namespace game
    {
        namespace lua
        {
            
            int gameLib(lua_State* L);
            
            int Game_pause(lua_State* L);
            int Game_resume(lua_State* L);
            int Game_isPaused(lua_State* L);
            int Game_over(lua_State* L);
            int Game_exit(lua_State* L);
            int Game_load(lua_State* L);
            int Game_reload(lua_State* L);
            
        }
    }
}

#endif


