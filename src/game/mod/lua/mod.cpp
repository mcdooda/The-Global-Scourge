#include "../../../engine/singleton.h"
#include <string>
#include "mod.h"
#include "../mod.h"

namespace game
{
    namespace mod
    {
        namespace lua
        {
            
            int modLib(lua_State* L)
            {
                static const luaL_reg Mod_lib[] = {
                    {"getPath",         Mod_getPath},
                    {"getResourcePath", Mod_getResourcePath},
                    {NULL, NULL}
                };
                luaL_register(L, "Mod", Mod_lib);
                
                return 0;
            }
            
            int Mod_getPath(lua_State* L)
            {
                std::string file = luaL_checkstring(L, 1);
                std::string path = S(Mod)->getFilePath(file);
                lua_pushstring(L, path.c_str());
                return 1;
            }
            
            int Mod_getResourcePath(lua_State* L)
            {
                std::string file = luaL_checkstring(L, 1);
                std::string path = S(Mod)->getResourceFilePath(file);
                lua_pushstring(L, path.c_str());
                return 1;
            }
            
        }
    }
}
