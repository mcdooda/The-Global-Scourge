#ifndef GAME_MAP_LUA_MAP_H
 #define GAME_MAP_LUA_MAP_H

#include "../../lua/lua.h"

namespace game
{
    namespace map
    {
        namespace lua
        {

            int mapLib(lua_State* L);

            int Map_getDimensions(lua_State* L);
            int Map_getTiles(lua_State* L);
            int Map_getTile(lua_State* L);
            int Map_getPointer(lua_State* L);
            int Map_getEntities(lua_State* L);
            int Map_setGhostModel(lua_State* L);
            int Map_getGhostModel(lua_State* L);
            int Map_onBuild(lua_State* L);
            int Map_onGhostModelClear(lua_State* L);
            int Map_enableOverlay(lua_State* L);
            int Map_disableOverlay(lua_State* L);
            int Map_getOverlay(lua_State* L);

        }
    }
}

#endif
