#include "entitymodel.h"
#include "../unitmodel.h"
#include "../buildingmodel.h"
#include "../abstractmodel.h"

namespace game
{
    namespace entity
    {
        namespace lua
        {

            int entityModelLib(lua_State* L)
            {
                static const luaL_reg EntityModel_lib[] = {
                    {"getAll",               EntityModel_getAll},
                    {"getByName",            EntityModel_getByName},
                    {"newUnit",              EntityModel_newUnit},
                    {"newBuilding",          EntityModel_newBuilding},
                    {"newAbstract",          EntityModel_newAbstract},
                    {"isUnit",               EntityModel_isUnit},
                    {"isBuilding",           EntityModel_isBuilding},
                    {"isAbstract",           EntityModel_isAbstract},
                    {"getName",              EntityModel_getName},
                    {"getTexturePath",       EntityModel_getTexturePath},
                    {"getTextureDimensions", EntityModel_getTextureDimensions},
                    {NULL, NULL}
                };
                luaL_register(L, "EntityModel", EntityModel_lib);
                
                static const struct
                {
                    const char* key;
                    void* value;
                } EntityModel_constants[] = {
                    {"NIL", NULL},
                    {NULL, NULL}
                };
                for (int i = 0; EntityModel_constants[i].key != NULL; i++)
                {
                    lua_pushlightuserdata(L, EntityModel_constants[i].value);
                    lua_setfield(L, -2, EntityModel_constants[i].key);
                }
                
                return 0;
            }
            
            int EntityModel_getAll(lua_State* L)
            {
                const std::map<std::string, EntityModel*> models = EntityModel::getAll();
                lua_createtable(L, 0, models.size());
                std::map<std::string, EntityModel*>::const_iterator end = models.end();
                for (std::map<std::string, EntityModel*>::const_iterator it = models.begin(); it != end; it++)
                {
                    lua_pushstring(L, it->first.c_str());
                    lua_pushlightuserdata(L, it->second);
                    lua_rawset(L, -3);
                }
                return 1;
            }
            
            int EntityModel_getByName(lua_State* L)
            {
                std::string name = luaL_checkstring(L, 1);
                lua_pushlightuserdata(L, EntityModel::getModelByName(name));
                return 1;
            }

            int EntityModel_newUnit(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TTABLE);

                lua_getfield(L, 1, "name");
                std::string name = luaL_checkstring(L, -1);

                lua_getfield(L, 1, "radius");
                float radius = luaL_checknumber(L, -1);

                lua_getfield(L, 1, "speed");
                float speed = luaL_checknumber(L, -1);

                lua_getfield(L, 1, "weight");
                float weight = luaL_checknumber(L, -1);

                lua_getfield(L, 1, "jumpForce");
                float jumpForce = luaL_checknumber(L, -1);

                new UnitModel(name, radius, speed, weight, jumpForce);
                return 0;
            }

            int EntityModel_newBuilding(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TTABLE);

                lua_getfield(L, 1, "name");
                std::string name = luaL_checkstring(L, -1);

                new BuildingModel(name);
                return 0;
            }
            
            int EntityModel_newAbstract(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TTABLE);

                lua_getfield(L, 1, "name");
                std::string name = luaL_checkstring(L, -1);

                new AbstractModel(name);
                return 0;
            }
            
            int EntityModel_isUnit(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                EntityModel* entityModel = (EntityModel*) lua_touserdata(L, 1);
                lua_pushboolean(L, entityModel->isUnitModel());
                return 1;
            }
            
            int EntityModel_isBuilding(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                EntityModel* entityModel = (EntityModel*) lua_touserdata(L, 1);
                lua_pushboolean(L, entityModel->isBuildingModel());
                return 1;
            }
            
            int EntityModel_isAbstract(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                EntityModel* entityModel = (EntityModel*) lua_touserdata(L, 1);
                lua_pushboolean(L, entityModel->isAbstractModel());
                return 1;
            }
            
            int EntityModel_getName(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                EntityModel* entityModel = (EntityModel*) lua_touserdata(L, 1);
                lua_pushstring(L, entityModel->getName().c_str());
                return 1;
            }
            
            int EntityModel_getTexturePath(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                EntityModel* entityModel = (EntityModel*) lua_touserdata(L, 1);
                lua_pushstring(L, entityModel->getTexture()->getPath().c_str());
                return 1;
            }
            
            int EntityModel_getTextureDimensions(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                EntityModel* entityModel = (EntityModel*) lua_touserdata(L, 1);
                engine::graphics::Texture* texture = entityModel->getTexture();
                lua_pushinteger(L, texture->getWidth());
                lua_pushinteger(L, texture->getHeight());
                return 2;
            }

        }
    }
}
