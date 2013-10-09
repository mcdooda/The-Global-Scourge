#include "input.h"
#include "../input.h"
#include "../../../engine/singleton.h"
#include "../../interface/interface.h"
#include "../../game.h"

namespace game
{
    namespace input
    {
        namespace lua
        {

            int inputLib(lua_State* L)
            {
                static const luaL_reg Input_lib[] = {
                    {"onKeyDown",            Input_onKeyDown},
                    {"isMouseOverInterface", Input_isMouseOverInterface},
                    {NULL, NULL}
                };
                luaL_register(L, "Input", Input_lib);
                
                static const struct
                {
                    const char* key;
                    int value;
                } Widget_constants[] = {
                    {"ESCAPE", K(ESCAPE)},
                    {"LEFT",   K(LEFT)},
                    {"RIGHT",  K(RIGHT)},
                    {"UP",     K(UP)},
                    {"DOWN",   K(DOWN)},
                    {NULL, 0}
                };
                for (int i = 0; Widget_constants[i].key != NULL; i++)
                {
                    lua_pushinteger(L, Widget_constants[i].value);
                    lua_setfield(L, -2, Widget_constants[i].key);
                }

                return 0;
            }

            int Input_onKeyDown(lua_State* L)
            {
                engine::input::keyboard::Key key;
                
                if (lua_type(L, 1) == LUA_TSTRING)
                    key = (engine::input::keyboard::Key) lua_tostring(L, 1)[0];
                    
                else
                    key = (engine::input::keyboard::Key) luaL_checkint(L, 1);
                
                if (lua_isnil(L, 2))
                    input::removeKeyDownListener(key);
                    
                else
                {
                    luaL_checktype(L, 2, LUA_TFUNCTION);
                    input::setKeyDownListener(key, L);
                }
                
                return 0;
            }
            
            int Input_isMouseOverInterface(lua_State* L)
            {
                lua_pushboolean(L, S(Game)->getInterface()->isMouseOver());
                return 1;
            }
            
        }
    }
}
