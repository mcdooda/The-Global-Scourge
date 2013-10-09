#include "color.h"
#include "../../../engine/graphics/coloralpha.h"

namespace game
{
    namespace lua
    {
        namespace util
        {
            
            engine::graphics::Color* readColor(lua_State* L, int index)
            {
                luaL_checktype(L, index, LUA_TTABLE);
                lua_rawgeti(L, index, 1);
                unsigned int r = luaL_checkint(L, -1);
                lua_rawgeti(L, index, 2);
                unsigned int g = luaL_checkint(L, -1);
                lua_rawgeti(L, index, 3);
                unsigned int b = luaL_checkint(L, -1);
                
                engine::graphics::Color* color;
                lua_rawgeti(L, index, 4);
                
                if (lua_isnumber(L, -1))
                {
                    unsigned int a = lua_tointeger(L, -1);
                    color = new engine::graphics::ColorAlpha(r, g, b, a);
                }
                else
                    color = new engine::graphics::Color(r, g, b);
                    
                lua_pop(L, 4);
                return color;
            }
            
        }
    }
}


