#ifndef GAME_LUA_LUA_H
 #define GAME_LUA_LUA_H

#include <lua5.1/lua.hpp>

namespace game
{
    namespace lua
    {

        void init();
        int atPanic(lua_State* L);
        lua_State* getState();
        void debugStack(lua_State* L);

    }
}

#endif
