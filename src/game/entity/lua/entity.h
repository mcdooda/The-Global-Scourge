#ifndef GAME_ENTITY_LUA_ENTITY_H
 #define GAME_ENTITY_LUA_ENTITY_H

#include "../../lua/lua.h"

namespace game
{
    namespace entity
    {
        namespace lua
        {

            int entityLib(lua_State* L);

            int Entity_newUnit(lua_State* L);
            int Entity_newBuilding(lua_State* L);
            int Entity_newAbstract(lua_State* L);
            int Entity_isUnit(lua_State* L);
            int Entity_isBuilding(lua_State* L);
            int Entity_isAbstract(lua_State* L);
            int Entity_getModel(lua_State* L);
            int Entity_getPosition(lua_State* L);
            int Entity_getCenter(lua_State* L);
            int Entity_getAbsolutePosition(lua_State* L);
            int Entity_getTile(lua_State* L);
            int Entity_canMove(lua_State* L);
            int Entity_isMoving(lua_State* L);
            int Entity_clearPath(lua_State* L);
            int Entity_addPath(lua_State* L);
            int Entity_jump(lua_State* L);
            int Entity_setZ(lua_State* L);
            int Entity_setPosition(lua_State* L);
            int Entity_setColor(lua_State* L);
            int Entity_destroy(lua_State* L);
            int Entity_enableOverlay(lua_State* L);
            int Entity_disableOverlay(lua_State* L);
            int Entity_getOverlay(lua_State* L);
            int Entity_onTileChange(lua_State* L);
            int Entity_isOnTheFloor(lua_State* L);

        }
    }
}

#endif
