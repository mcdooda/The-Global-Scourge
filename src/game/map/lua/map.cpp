#include "map.h"
#include "../map.h"
#include "../../entity/entitymodel.h"
#include "../../../engine/singleton.h"
#include "../../game.h"

namespace game
{
    namespace map
    {
        namespace lua
        {

            int mapLib(lua_State* L)
            {
                static const luaL_reg Map_lib[] = {
                    {"getDimensions",     Map_getDimensions},
                    {"getTiles",          Map_getTiles},
                    {"getTile",           Map_getTile},
                    {"getPointer",        Map_getPointer},
                    {"getEntities",       Map_getEntities},
                    {"setGhostModel",     Map_setGhostModel},
                    {"getGhostModel",     Map_getGhostModel},
                    {"onBuild",           Map_onBuild},
                    {"onGhostModelClear", Map_onGhostModelClear},
                    {"enableOverlay",     Map_enableOverlay},
                    {"disableOverlay",    Map_disableOverlay},
                    {"getOverlay",        Map_getOverlay},
                    {NULL, NULL}
                };
                luaL_register(L, "Map", Map_lib);

                return 0;
            }

            int Map_getDimensions(lua_State* L)
            {
                Map* map = S(Game)->getMap();
                lua_pushinteger(L, map->getWidth());
                lua_pushinteger(L, map->getHeight());
                return 2;
            }
            
            int Map_getTiles(lua_State* L)
            {
                Map* map = S(Game)->getMap();
                lua_createtable(L, map->getWidth() * map->getHeight(), 0);
                int n = 1;
                for (int x = 0; x < map->getWidth(); x++)
                {
                    for (int y = 0; y < map->getHeight(); y++)
                    {
                        Tile* tile = map->getTile(x, y);
                        if (tile != NULL)
                        {
                            lua_pushlightuserdata(L, tile);
                            lua_rawseti(L, -2, n);
                            n++;
                        }
                    }
                }
                return 1;
            }
            
            int Map_getTile(lua_State* L)
            {
                Map* map = S(Game)->getMap();
                int x = luaL_checkint(L, 1) - 1;
                int y = luaL_checkint(L, 2) - 1;
                lua_pushlightuserdata(L, map->getTile(x, y));
                return 1;
            }
            
            int Map_getPointer(lua_State* L)
            {
                Map* map = S(Game)->getMap();
                engine::Vector2d pointer = map->getPointerPosition();
                lua_pushnumber(L, pointer.getX() + 1);
                lua_pushnumber(L, pointer.getY() + 1);
                return 2;
            }
            
            int Map_getEntities(lua_State* L)
            {
                Map* map = S(Game)->getMap();
                int n = 1;
                if (lua_isstring(L, 1))
                {
                    const char* modelName = lua_tostring(L, 1);
                    entity::EntityModel* model = entity::EntityModel::getModelByName(modelName);
                    if (model == NULL)
                        return luaL_error(L, "no entity model named %s", modelName);
                        
                    lua_newtable(L);
                    const std::vector<entity::Entity*>& entities = map->getEntities();
                    std::vector<entity::Entity*>::const_iterator end = entities.end();
                    for (std::vector<entity::Entity*>::const_iterator it = entities.begin(); it != end; it++)
                    {
                        if ((*it)->getModel() == model)
                        {
                            lua_pushlightuserdata(L, *it);
                            lua_rawseti(L, -2, n);
                            n++;
                        }
                    }
                }
                else
                {
                    const std::vector<entity::Entity*>& entities = map->getEntities();
                    lua_createtable(L, entities.size(), 0);
                    std::vector<entity::Entity*>::const_iterator end = entities.end();
                    for (std::vector<entity::Entity*>::const_iterator it = entities.begin(); it != end; it++)
                    {
                        lua_pushlightuserdata(L, *it);
                        lua_rawseti(L, -2, n);
                        n++;
                    }
                }
                return 1;
            }
            
            int Map_setGhostModel(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                entity::EntityModel* ghostModel = (entity::EntityModel*) lua_touserdata(L, 1);
                S(Game)->getMap()->setGhostModel(ghostModel);
                return 0;
            }
            
            int Map_getGhostModel(lua_State* L)
            {
                lua_pushlightuserdata(L, S(Game)->getMap()->getGhostModel());
                return 1;
            }
            
            int Map_onBuild(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TFUNCTION);
                S(Game)->getMap()->setBuildListener(L);
                return 0;
            }
            
            int Map_onGhostModelClear(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TFUNCTION);
                S(Game)->getMap()->setGhostModelClearListener(L);
                return 0;
            }
            
            int Map_enableOverlay(lua_State* L)
            {
                Map* map = S(Game)->getMap();
                map->enableOverlay();
                lua_pushlightuserdata(L, map->getOverlay());
                return 1;
            }
            
            int Map_disableOverlay(lua_State* L)
            {
                S(Game)->getMap()->disableOverlay();
                return 0;
            }
            
            int Map_getOverlay(lua_State *L)
            {
                lua_pushlightuserdata(L, S(Game)->getMap()->getOverlay());
                return 1;
            }

        }
    }
}
