#include <iostream>
#include "file.h"
#include "../../../engine/file/directory.h"

using namespace engine::file;

namespace game
{
    namespace file
    {
        namespace lua
        {

            int fileLib(lua_State* L)
            {
                luaL_newmetatable(L, "GP.File");

                static const luaL_reg File_lib[] = {
                    {"new", File_new},
                    {"isFile", File_isFile},
                    {"isDir", File_isDir},
                    {"getPath", File_getPath},
                    {"read", File_read},
                    {NULL, NULL}
                };
                luaL_register(L, "File", File_lib);

                lua_setfield(L, -2, "__index");

                lua_pushcfunction(L, File_destroy);
                lua_setfield(L, -2, "__gc");

                return 0;
            }

            int File_new(lua_State* L)
            {
                std::string path = luaL_checkstring(L, 1);

                if (Directory::isFileName(path))
                {
                    File** file = (File**) lua_newuserdata(L, sizeof(File*));
                    *file = new File(path);
                }
                else
                {
                    Directory** dir = (Directory**) lua_newuserdata(L, sizeof(File*));
                    *dir = new Directory(path);
                }

                luaL_getmetatable(L, "GP.File");
                lua_setmetatable(L, -2);

                return 1;
            }

            int File_destroy(lua_State* L)
            {
                File* file = *(File**) luaL_checkudata(L, 1, "GP.File");
                delete file;
                return 0;
            }

            int File_isFile(lua_State* L)
            {
                File* file = *(File**) luaL_checkudata(L, 1, "GP.File");
                lua_pushboolean(L, file->isFile());
                return 1;
            }

            int File_isDir(lua_State* L)
            {
                File* file = *(File**) luaL_checkudata(L, 1, "GP.File");
                lua_pushboolean(L, file->isDir());
                return 1;
            }

            int File_getPath(lua_State* L)
            {
                File* file = *(File**) luaL_checkudata(L, 1, "GP.File");
                lua_pushstring(L, file->getPath().c_str());
                return 1;
            }

            static void pushFiles(lua_State* L, Directory* dir)
            {
                lua_newtable(L);

                std::vector<Directory*> dirs = dir->getDirectories();
                std::vector<Directory*>::iterator end1 = dirs.end();
                for (std::vector<Directory*>::iterator it = dirs.begin(); it != end1; it++)
                {
                    pushFiles(L, *it);
                    lua_setfield(L, -2, (*it)->getPath().c_str());
                }

                std::vector<File*> files = dir->getFiles();
                std::vector<File*>::iterator end2 = files.end();
                for (std::vector<File*>::iterator it = files.begin(); it != end2; it++)
                {
                    lua_pushboolean(L, 1);
                    lua_setfield(L, -2, (*it)->getPath().c_str());
                }
            }

            int File_read(lua_State* L)
            {
                File* file = *(File**) luaL_checkudata(L, 1, "GP.File");
                if (file->isDir())
                {
                    Directory* dir = (Directory*) file;
                    dir->read();
                    pushFiles(L, dir);
                }
                else
                    lua_pushnil(L);

                return 1;
            }

        }
    }
}
