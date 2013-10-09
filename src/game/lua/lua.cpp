#include <iostream>
#include "lua.h"

namespace game
{
    namespace lua
    {

        static lua_State* L = NULL;

        void init()
        {
            if (L != NULL)
                lua_close(L);
                
            L = luaL_newstate();
            luaL_openlibs(L);
            lua_atpanic(L, atPanic);
        }

        int atPanic(lua_State* L)
        {
            std::cout << std::endl
                << "Lua error:" << std::endl << lua_tostring(L, -1) << std::endl
                << std::endl;
            return 0;
        }

        lua_State* getState()
        {
            return L;
        }

        void debugStack(lua_State* L1)
        {
            std::cout << std::endl << "--- Lua Debug (" << L1 << ") ==========" << std::endl;
            int top = lua_gettop(L1);
            std::cout << "top = " << top << std::endl;
            for (int i = 1; i <= top; i++)
            {
                std::cout << "#" << i << " : ";
                switch(lua_type(L1, i))
                {
                    case LUA_TLIGHTUSERDATA:
                    std::cout << "lightuserdata : " << lua_touserdata(L1, i);
                    break;

                    case LUA_TUSERDATA:
                    std::cout << "userdata .... : " << lua_touserdata(L1, i);
                    break;

                    case LUA_TTABLE:
                    std::cout << "table ....... : " << lua_topointer(L1, i) << (lua_topointer(L1, i) == lua_topointer(L1, LUA_REGISTRYINDEX)? " (REGISTRY)" : "");
                    break;

                    case LUA_TNIL:
                    std::cout << "nil";
                    break;

                    case LUA_TFUNCTION:
                    std::cout << "function .... : " << lua_topointer(L1, i);
                    break;

                    case LUA_TNUMBER:
                    std::cout << "number ...... : " << lua_tonumber(L1, i);
                    break;

                    case LUA_TBOOLEAN:
                    std::cout << "boolean ..... : " << (lua_toboolean(L1, i) ? "true" : "false");
                    break;

                    case LUA_TSTRING:
                    std::cout << "string ...... : " << lua_tostring(L1, i);
                    break;

                    case LUA_TTHREAD:
                    std::cout << "thread ...... : " << lua_topointer(L1, i);
                    break;

                    case LUA_TNONE:
                    std::cout << "none ........ : " << lua_topointer(L1, i);
                    break;

                    default:
                    std::cout << "unknown type  : " << lua_topointer(L1, i) << " (" << lua_typename(L1, i) << " ?)";
                    break;
                }
                std::cout << std::endl;
            }
            std::cout << "--- Lua Debug ======" << std::endl << std::endl;
        }

    }
}
