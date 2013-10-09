#ifndef GAME_BRUSH_LUA_BRUSH_H
 #define GAME_BRUSH_LUA_BRUSH_H

#include "../../lua/lua.h"

namespace game
{
    namespace brush
    {
        namespace lua
        {
            
            int brushLib(lua_State* L);
            
            int Brush_new(lua_State* L);
            int Brush_destroy(lua_State* L);
            int Brush_getSize(lua_State* L);
            int Brush_setSize(lua_State* L);
            int Brush_growSize(lua_State* L);
            int Brush_getLimitWidth(lua_State* L);
            int Brush_setLimitWidth(lua_State* L);
            int Brush_growLimitWidth(lua_State* L);
            int Brush_getTiles(lua_State* L);
            int Brush_getEntities(lua_State* L);
            
        }
    }
}

#endif


