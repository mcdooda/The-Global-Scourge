#ifndef GAME_FILE_LUA_FILE_H
 #define GAME_FILE_LUA_FILE_H

#include "../../lua/lua.h"

namespace game
{
    namespace file
    {
        namespace lua
        {

            int fileLib(lua_State* L);

            int File_new(lua_State* L);
            int File_destroy(lua_State* L);
            int File_isFile(lua_State* L);
            int File_isDir(lua_State* L);
            int File_getPath(lua_State* L);
            int File_read(lua_State* L);

        }
    }
}

#endif
