#ifndef GAME_MAP_LUA_TILE_H
 #define GAME_MAP_LUA_TILE_H

#include "../../lua/lua.h"

namespace game
{
    namespace map
    {
        namespace lua
        {

            int tileLib(lua_State* L);
            
            int Tile_getTexturePath(lua_State* L);
            int Tile_getPosition(lua_State* L);
            int Tile_getX(lua_State* L);
            int Tile_getY(lua_State* L);
            int Tile_getZ(lua_State* L);
            int Tile_setZ(lua_State* L);
            int Tile_isAccessible(lua_State* L);
            int Tile_getEntities(lua_State* L);
            int Tile_getBuilding(lua_State* L);
            int Tile_setColor(lua_State* L);
            int Tile_setTopLayerTexture(lua_State* L);
            int Tile_setTopLayerColor(lua_State* L);
            int Tile_setTopLayerYShift(lua_State* L);

        }
    }
}

#endif
