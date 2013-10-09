#include <map>
#include "input.h"

namespace game
{
    namespace input
    {
        namespace input
        {
            static std::map<engine::input::keyboard::Key, int> keyDownListeners;
            
            void triggerListeners()
            {
                if (!keyDownListeners.empty())
                {
                    lua_State* L = lua::getState();
                    
                    std::map<engine::input::keyboard::Key, int>::iterator end = keyDownListeners.end();
                    for (std::map<engine::input::keyboard::Key, int>::iterator it = keyDownListeners.begin(); it != end; it++)
                    {
                        if (engine::input::keyboard::isJustPressed(it->first))
                        {
                            lua_rawgeti(L, LUA_REGISTRYINDEX, it->second);
                            lua_call(L, 0, 0);
                        }
                    }
                }
            }
            
            void setKeyDownListener(engine::input::keyboard::Key key, lua_State* L)
            {
                keyDownListeners[key] = luaL_ref(L, LUA_REGISTRYINDEX);
            }
            
            void removeKeyDownListener(engine::input::keyboard::Key key)
            {
                std::map<engine::input::keyboard::Key, int>::iterator it = keyDownListeners.find(key);
                if (it != keyDownListeners.end())
                {
                    lua_State* L = lua::getState();
                    luaL_unref(L, LUA_REGISTRYINDEX, it->second);
                    keyDownListeners.erase(it);
                }
            }
            
            void clearListeners()
            {
                lua_State* L = lua::getState();
                
                std::map<engine::input::keyboard::Key, int>::iterator end = keyDownListeners.end();
                for (std::map<engine::input::keyboard::Key, int>::iterator it = keyDownListeners.begin(); it != end; it++)
                    luaL_unref(L, LUA_REGISTRYINDEX, it->second);
                
                keyDownListeners.clear();
            }
            
        }
    }
}
