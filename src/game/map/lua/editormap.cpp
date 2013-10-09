#include "editormap.h"
#include "../editormap.h"
#include "../../../engine/singleton.h"
#include "../../game.h"
#include "../../brush/discbrush.h"
#include "../../brush/squarebrush.h"
#include "../../brush/peakbrush.h"
#include "../../brush/spherebrush.h"
#include "../../brush/forestbrush.h"

namespace game
{
    namespace map
    {
        namespace lua
        {

            int editorMapLib(lua_State* L)
            {
                static const luaL_reg EditorMap_lib[] = {
                    {"brushSizeUp",       EditorMap_brushSizeUp},
                    {"brushSizeDown",     EditorMap_brushSizeDown},
                    {"brushShapeCone",    EditorMap_brushShapeCone},
                    {"brushShapeDisc",    EditorMap_brushShapeDisc},
                    {"brushShapePeak",    EditorMap_brushShapePeak},
                    {"brushShapePyramid", EditorMap_brushShapePyramid},
                    {"brushShapeSphere",  EditorMap_brushShapeSphere},
                    {"brushShapeSquare",  EditorMap_brushShapeSquare},
                    {"brushShapeForest",  EditorMap_brushShapeForest},
                    {"setTilesGroup",     EditorMap_setTilesGroup},
                    {"setDoodadsGroup",   EditorMap_setDoodadsGroup},
                    {"setBuildingModel",  EditorMap_setBuildingModel},
                    {"setUnitModel",      EditorMap_setUnitModel},
                    {"setMode",           EditorMap_setMode},
                    {"save",              EditorMap_save},
                    {NULL, NULL}
                };
                luaL_register(L, "EditorMap", EditorMap_lib);
                
                static const struct
                {
                    const char* key;
                    int value;
                } EditorMap_constants[] = {
                    {"MODE_TILES",     EditorMap::MODE_TILES},
                    {"MODE_DOODADS",   EditorMap::MODE_DOODADS},
                    {"MODE_BUILDINGS", EditorMap::MODE_BUILDINGS},
                    {"MODE_UNITS",     EditorMap::MODE_UNITS},
                    {"MODE_ZONES",     EditorMap::MODE_ZONES},
                    {NULL, 0}
                };
                for (int i = 0; EditorMap_constants[i].key != NULL; i++)
                {
                    lua_pushinteger(L, EditorMap_constants[i].value);
                    lua_setfield(L, -2, EditorMap_constants[i].key);
                }

                return 0;
            }

            int EditorMap_brushSizeUp(lua_State* L)
            {
                EditorMap* map = (EditorMap*) S(Game)->getMap();
                map->getBrush()->incrementSize();
                return 0;
            }

            int EditorMap_brushSizeDown(lua_State* L)
            {
                EditorMap* map = (EditorMap*) S(Game)->getMap();
                map->getBrush()->decrementSize();
                return 0;
            }

            int EditorMap_brushShapeCone(lua_State* L)
            {
                EditorMap* map = (EditorMap*) S(Game)->getMap();
                brush::Brush* brush = new brush::DiscBrush();
                brush->setLimitWidth(brush::Brush::MAX_SIZE);
                map->setBrush(brush);
                return 0;
            }

            int EditorMap_brushShapeDisc(lua_State* L)
            {
                EditorMap* map = (EditorMap*) S(Game)->getMap();
                map->setBrush(new brush::DiscBrush());
                return 0;
            }

            int EditorMap_brushShapePeak(lua_State* L)
            {
                EditorMap* map = (EditorMap*) S(Game)->getMap();
                map->setBrush(new brush::PeakBrush());
                return 0;
            }

            int EditorMap_brushShapePyramid(lua_State* L)
            {
                EditorMap* map = (EditorMap*) S(Game)->getMap();
                brush::Brush* brush = new brush::SquareBrush();
                brush->setLimitWidth(brush::Brush::MAX_SIZE);
                map->setBrush(brush);
                return 0;
            }

            int EditorMap_brushShapeSphere(lua_State* L)
            {
                EditorMap* map = (EditorMap*) S(Game)->getMap();
                map->setBrush(new brush::SphereBrush());
                return 0;
            }

            int EditorMap_brushShapeSquare(lua_State* L)
            {
                EditorMap* map = (EditorMap*) S(Game)->getMap();
                map->setBrush(new brush::SquareBrush());
                return 0;
            }

            int EditorMap_brushShapeForest(lua_State* L)
            {
                EditorMap* map = (EditorMap*) S(Game)->getMap();
                map->setBrush(new brush::ForestBrush());
                return 0;
            }

            int EditorMap_setTilesGroup(lua_State* L)
            {
                EditorMap* map = (EditorMap*) S(Game)->getMap();
                map->setTilesGroup(luaL_checkstring(L, 1));
                return 0;
            }

            int EditorMap_setDoodadsGroup(lua_State* L)
            {
                EditorMap* map = (EditorMap*) S(Game)->getMap();
                map->setDoodadsGroup(luaL_checkstring(L, 1));
                return 0;
            }
            
            int EditorMap_setBuildingModel(lua_State* L)
            {
                EditorMap* map = (EditorMap*) S(Game)->getMap();
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                entity::BuildingModel* buildingModel = (entity::BuildingModel*) lua_touserdata(L, 1);
                map->setBuildingModel(buildingModel);
                return 0;
            }
            
            int EditorMap_setUnitModel(lua_State* L)
            {
                EditorMap* map = (EditorMap*) S(Game)->getMap();
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                entity::UnitModel* unitModel = (entity::UnitModel*) lua_touserdata(L, 1);
                map->setUnitModel(unitModel);
                return 0;
            }

            int EditorMap_setMode(lua_State* L)
            {
                EditorMap* map = (EditorMap*) S(Game)->getMap();
                int mode = luaL_checkint(L, 1);
                map->setMode((EditorMap::Mode)mode);
                return 0;
            }

            int EditorMap_save(lua_State* L)
            {
                EditorMap* map = (EditorMap*) S(Game)->getMap();
                map->save();
                return 0;
            }

        }
    }
}
