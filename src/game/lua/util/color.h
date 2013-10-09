#ifndef GAME_LUA_UTIL_COLOR_H
 #define GAME_LUA_UTIL_COLOR_H

#include "../lua.h"
#include "../../../engine/graphics/color.h"

namespace game
{
    namespace lua
    {
        namespace util
        {
            
            engine::graphics::Color* readColor(lua_State* L, int index);
            
        }
    }
}

#endif


