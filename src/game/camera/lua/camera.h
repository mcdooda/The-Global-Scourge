#ifndef GAME_CAMERA_LUA_CAMERA_H
 #define GAME_CAMERA_LUA_CAMERA_H

#include "../../lua/lua.h"

namespace game
{
    namespace camera
    {
        namespace lua
        {

            int cameraLib(lua_State* L);

            int Camera_lookAt(lua_State* L);
            int Camera_lock(lua_State* L);
            int Camera_unlock(lua_State* L);
            int Camera_isLocked(lua_State* L);
            int Camera_setZoom(lua_State* L);

        }
    }
}

#endif
