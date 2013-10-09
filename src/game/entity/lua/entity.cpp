#include <iostream>
#include <string>
#include "entity.h"
#include "../unit.h"
#include "../building.h"
#include "../abstractentity.h"
#include "../../../engine/singleton.h"
#include "../../map/map.h"
#include "../../game.h"
#include "../../lua/util/color.h"

namespace game
{
    namespace entity
    {
        namespace lua
        {

            int entityLib(lua_State* L)
            {
                static const luaL_reg Entity_lib[] = {
                    {"newUnit",             Entity_newUnit},
                    {"newBuilding",         Entity_newBuilding},
                    {"newAbstract",         Entity_newAbstract},
                    {"isUnit",              Entity_isUnit},
                    {"isBuilding",          Entity_isBuilding},
                    {"isAbstract",          Entity_newAbstract},
                    {"getModel",            Entity_getModel},
                    {"getPosition",         Entity_getPosition},
                    {"getCenter",           Entity_getCenter},
                    {"getAbsolutePosition", Entity_getAbsolutePosition},
                    {"getTile",             Entity_getTile},
                    {"canMove",             Entity_canMove},
                    {"isMoving",            Entity_isMoving},
                    {"clearPath",           Entity_clearPath},
                    {"addPath",             Entity_addPath},
                    {"jump",                Entity_jump},
                    {"setZ",                Entity_setZ},
                    {"setPosition",         Entity_setPosition},
                    {"setColor",            Entity_setColor},
                    {"destroy",             Entity_destroy},
                    {"enableOverlay",       Entity_enableOverlay},
                    {"disableOverlay",      Entity_disableOverlay},
                    {"getOverlay",          Entity_getOverlay},
                    {"onTileChange",        Entity_onTileChange},
                    {"isOnTheFloor",        Entity_isOnTheFloor},
                    {NULL, NULL}
                };
                luaL_register(L, "Entity", Entity_lib);

                return 0;
            }

            int Entity_newUnit(lua_State* L)
            {
                std::string modelName = luaL_checkstring(L, 1);
                float x = luaL_checknumber(L, 2) - 1;
                float y = luaL_checknumber(L, 3) - 1;
                EntityModel* model = EntityModel::getModelByName(modelName);
                Unit* unit = new Unit(model, engine::Vector2d(x, y));
                S(Game)->getMap()->addEntity(unit);
                lua_pushlightuserdata(L, unit);
                return 1;
            }

            int Entity_newBuilding(lua_State* L)
            {
                std::string modelName = luaL_checkstring(L, 1);
                float x = luaL_checknumber(L, 2) - 1;
                float y = luaL_checknumber(L, 3) - 1;
                EntityModel* model = EntityModel::getModelByName(modelName);
                Building* building = new Building(model, engine::Vector2d(x, y));
                S(Game)->getMap()->addEntity(building);
                lua_pushlightuserdata(L, building);
                return 1;
            }
            
            int Entity_newAbstract(lua_State* L)
            {
                std::string modelName = luaL_checkstring(L, 1);
                float x = luaL_checknumber(L, 2) - 1;
                float y = luaL_checknumber(L, 3) - 1;
                EntityModel* model = EntityModel::getModelByName(modelName);
                AbstractEntity* abstract = new AbstractEntity(model, engine::Vector2d(x, y));
                S(Game)->getMap()->addEntity(abstract);
                lua_pushlightuserdata(L, abstract);
                return 1;
            }
            
            int Entity_isUnit(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                lua_pushboolean(L, entity->isUnit());
                return 1;
            }
            
            int Entity_isBuilding(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                lua_pushboolean(L, entity->isBuilding());
                return 1;
            }
            
            int Entity_isAbstract(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                lua_pushboolean(L, entity->isAbstract());
                return 1;
            }
            
            int Entity_getModel(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                lua_pushlightuserdata(L, entity->getModel());
                return 1;
            }
            
            int Entity_getPosition(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                lua_pushnumber(L, entity->getX() + 1);
                lua_pushnumber(L, entity->getY() + 1);
                lua_pushnumber(L, entity->getZ());
                return 3;
            }
            
            int Entity_getCenter(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                lua_pushnumber(L, entity->getCenterX() + 1);
                lua_pushnumber(L, entity->getCenterY() + 1);
                lua_pushnumber(L, entity->getZ());
                return 3;
            }
            
            int Entity_getAbsolutePosition(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                engine::Vector2d absolutePosition = entity->getAbsolutePosition();
                lua_pushnumber(L, absolutePosition.getX());
                lua_pushnumber(L, absolutePosition.getY());
                return 2;
            }
            
            int Entity_getTile(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                lua_pushlightuserdata(L, entity->getTile());
                return 1;
            }
            
            int Entity_canMove(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                lua_pushboolean(L, entity->canMove());
                return 1;
            }
            
            int Entity_isMoving(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                lua_pushboolean(L, entity->isMoving());
                return 1;
            }
            
            int Entity_clearPath(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                entity->clearPath();
                return 0;
            }
            
            int Entity_addPath(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                float x = luaL_checknumber(L, 2) - 1;
                float y = luaL_checknumber(L, 3) - 1;
                entity->addPath(engine::Vector2d(x, y));
                return 0;
            }
            
            int Entity_jump(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                float jumpForce = luaL_checknumber(L, 2);
                entity->jump(jumpForce);
                return 0;
            }
            
            int Entity_setZ(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                float z = luaL_checknumber(L, 2);
                entity->setZ(z);
                return 0;
            }
            
            int Entity_setPosition(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                float x = luaL_checknumber(L, 2) - 1;
                float y = luaL_checknumber(L, 3) - 1;
                entity->setEntityPosition(engine::Vector2d(x, y));
                return 0;
            }
            
            int Entity_setColor(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                engine::graphics::Color* color = game::lua::util::readColor(L, 2);
                entity->setColor(color);
                return 0;
            }
            
            int Entity_destroy(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                S(Game)->getMap()->removeEntity(entity);
                delete entity;
                return 0;
            }
            
            int Entity_enableOverlay(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                entity->enableOverlay();
                lua_pushlightuserdata(L, entity->getOverlay());
                return 1;
            }
            
            int Entity_disableOverlay(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                entity->disableOverlay();
                return 0;
            }
            
            int Entity_getOverlay(lua_State *L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                lua_pushlightuserdata(L, entity->getOverlay());
                return 1;
            }
            
            int Entity_onTileChange(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                entity->setTileChangeListener(L);
                return 0;
            }
            
            int Entity_isOnTheFloor(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Entity* entity = (Entity*) lua_touserdata(L, 1);
                lua_pushboolean(L, entity->isOnTheFloor());
                return 1;
            }

        }
    }
}


