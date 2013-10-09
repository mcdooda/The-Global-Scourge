#include "tile.h"
#include "../tile.h"
#include "../../../engine/singleton.h"
#include "../../../engine/graphics/coloralpha.h"
#include "../../../engine/resourcemanager.h"
#include "../../game.h"
#include "../../lua/util/color.h"

namespace game
{
    namespace map
    {
        namespace lua
        {
        
            int tileLib(lua_State* L)
            {
                static const luaL_reg Tile_lib[] = {
                    {"getTexturePath",     Tile_getTexturePath},
                    {"getPosition",        Tile_getPosition},
                    {"getX",               Tile_getX},
                    {"getY",               Tile_getY},
                    {"getZ",               Tile_getZ},
                    {"setZ",               Tile_setZ},
                    {"isAccessible",       Tile_isAccessible},
                    {"getEntities",        Tile_getEntities},
                    {"getBuilding",        Tile_getBuilding},
                    {"setColor",           Tile_setColor},
                    {"setTopLayerTexture", Tile_setTopLayerTexture},
                    {"setTopLayerColor",   Tile_setTopLayerColor},
                    {"setTopLayerYShift",  Tile_setTopLayerYShift},
                    {NULL, NULL}
                };
                luaL_register(L, "Tile", Tile_lib);
                
                static const struct
                {
                    const char* key;
                    void* value;
                } Tile_constants[] = {
                    {"NIL", NULL},
                    {NULL, NULL}
                };
                for (int i = 0; Tile_constants[i].key != NULL; i++)
                {
                    lua_pushlightuserdata(L, Tile_constants[i].value);
                    lua_setfield(L, -2, Tile_constants[i].key);
                }

                return 0;
            }
            
            int Tile_getTexturePath(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Tile* tile = (Tile*) lua_touserdata(L, 1);
                lua_pushstring(L, tile->getTexturePath().c_str());
                return 1;
            }
            
            int Tile_getPosition(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Tile* tile = (Tile*) lua_touserdata(L, 1);
                lua_pushinteger(L, tile->getX() + 1);
                lua_pushinteger(L, tile->getY() + 1);
                lua_pushnumber(L, tile->getZ());
                return 3;
            }
            
            int Tile_getX(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Tile* tile = (Tile*) lua_touserdata(L, 1);
                lua_pushinteger(L, tile->getX() + 1);
                return 1;
            }
            
            int Tile_getY(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Tile* tile = (Tile*) lua_touserdata(L, 1);
                lua_pushinteger(L, tile->getY() + 1);
                return 1;
            }
            
            int Tile_getZ(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Tile* tile = (Tile*) lua_touserdata(L, 1);
                lua_pushnumber(L, tile->getZ());
                return 1;
            }
            
            int Tile_setZ(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Tile* tile = (Tile*) lua_touserdata(L, 1);
                tile->setZ(luaL_checknumber(L, 2));
                return 0;
            }
            
            int Tile_isAccessible(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Tile* tile = (Tile*) lua_touserdata(L, 1);
                lua_pushboolean(L, tile->isAccessible());
                return 1;
            }
            
            int Tile_getEntities(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Tile* tile = (Tile*) lua_touserdata(L, 1);
                const std::vector<entity::Entity*>& entities = tile->getEntities();
                lua_createtable(L, entities.size(), 0);
                int k = 1;
                std::vector<entity::Entity*>::const_iterator end = entities.end();
                for (std::vector<entity::Entity*>::const_iterator it = entities.begin(); it != end; it++)
                {
                    lua_pushlightuserdata(L, *it);
                    lua_rawseti(L, -2, k);
                    k++;
                }
                return 1;
            }
            
            int Tile_getBuilding(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Tile* tile = (Tile*) lua_touserdata(L, 1);
                lua_pushlightuserdata(L, tile->getBuilding());
                return 1;
            }
            
            int Tile_setColor(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Tile* tile = (Tile*) lua_touserdata(L, 1);
                engine::graphics::Color* color = game::lua::util::readColor(L, 2);
                tile->setColor(color);
                return 0;
            }
            
            int Tile_setTopLayerTexture(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Tile* tile = (Tile*) lua_touserdata(L, 1);
                
                if (lua_isstring(L, 2))
                {
                    engine::graphics::Texture* texture = S(engine::TextureManager)->get(lua_tostring(L, 2));
                    tile->setTopLayerTexture(texture);
                }
                else
                    tile->setTopLayerTexture(NULL);
                    
                return 0;
            }
            
            int Tile_setTopLayerColor(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Tile* tile = (Tile*) lua_touserdata(L, 1);
                engine::graphics::Color* color = game::lua::util::readColor(L, 2);
                tile->getTopLayer()->setColor(color);
                return 0;
            }
            
            int Tile_setTopLayerYShift(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Tile* tile = (Tile*) lua_touserdata(L, 1);
                float yShift = luaL_checknumber(L, 2);
                tile->getTopLayer()->setYShift(yShift);
                return 0;
            }
        
        }
    }
}
