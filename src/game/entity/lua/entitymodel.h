#ifndef GAME_ENTITY_LUA_ENTITYMODEL_H
 #define GAME_ENTITY_LUA_ENTITYMODEL_H

#include "../../lua/lua.h"

namespace game
{
    namespace entity
    {
        namespace lua
        {

            int entityModelLib(lua_State* L);
            
            int EntityModel_getAll(lua_State* L);
            int EntityModel_getByName(lua_State* L);
            int EntityModel_newUnit(lua_State* L);
            int EntityModel_newBuilding(lua_State* L);
            int EntityModel_newAbstract(lua_State* L);
            int EntityModel_isUnit(lua_State* L);
            int EntityModel_isBuilding(lua_State* L);
            int EntityModel_isAbstract(lua_State* L);
            int EntityModel_getName(lua_State* L);
            int EntityModel_getTexturePath(lua_State* L);
            int EntityModel_getTextureDimensions(lua_State* L);

        }
    }
}

#endif
