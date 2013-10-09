#ifndef GAME_MAP_LUA_EDITORMAP_H
 #define GAME_MAP_LUA_EDITORMAP_H

#include "../../lua/lua.h"

namespace game
{
    namespace map
    {
        namespace lua
        {

            int editorMapLib(lua_State* L);

            int EditorMap_brushSizeUp(lua_State* L);
            int EditorMap_brushSizeDown(lua_State* L);

            int EditorMap_brushShapeCone(lua_State* L);
            int EditorMap_brushShapeDisc(lua_State* L);
            int EditorMap_brushShapePeak(lua_State* L);
            int EditorMap_brushShapePyramid(lua_State* L);
            int EditorMap_brushShapeSphere(lua_State* L);
            int EditorMap_brushShapeSquare(lua_State* L);
            int EditorMap_brushShapeForest(lua_State* L);

            int EditorMap_setTilesGroup(lua_State* L);
            int EditorMap_setDoodadsGroup(lua_State* L);
            int EditorMap_setBuildingModel(lua_State* L);
            int EditorMap_setUnitModel(lua_State* L);

            int EditorMap_setMode(lua_State* L);

            int EditorMap_save(lua_State* L);

        }
    }
}

#endif
