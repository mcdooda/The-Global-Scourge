#include "camera.h"
#include "../camera.h"

namespace game
{
    namespace camera
    {
        namespace lua
        {
            
            int cameraLib(lua_State* L)
            {
                static const luaL_reg Camera_lib[] = {
                    {"lookAt",   Camera_lookAt},
                    {"lock",     Camera_lock},
                    {"unlock",   Camera_unlock},
                    {"isLocked", Camera_isLocked},
                    {"setZoom",  Camera_setZoom},
                    {NULL, NULL}
                };
                luaL_register(L, "Camera", Camera_lib);
                
                return 0;
            }
            
            int Camera_lookAt(lua_State* L)
            {
                float x = luaL_checknumber(L, 1);
                float y = luaL_checknumber(L, 2);
                lookAt(engine::Vector2d(x, y));
                return 0;
            }
            
            int Camera_lock(lua_State* L)
            {
                lock();
                return 0;
            }
            
            int Camera_unlock(lua_State* L)
            {
                unlock();
                return 0;
            }
            
            int Camera_isLocked(lua_State* L)
            {
                lua_pushboolean(L, isLocked());
                return 1;
            }
            
            int Camera_setZoom(lua_State* L)
            {
                float zoom = luaL_checknumber(L, 1);
                setZoom(zoom);
                return 0;
            }
            
        }
    }
}
