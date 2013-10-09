#include "luatimer.h"
#include "../../engine/time.h"

namespace game
{
    namespace time
    {
        LuaTimer::LuaTimer(float timeOut, bool loops) :
            Timer(timeOut, loops)
        {
            
        }
        
        void LuaTimer::setOnTimeOut(lua_State* L)
        {
            m_onTimeOut = luaL_ref(L, LUA_REGISTRYINDEX);
        }
        
        bool LuaTimer::execute()
        {
            lua_State* L = lua::getState();
            lua_rawgeti(L, LUA_REGISTRYINDEX, m_onTimeOut);
            lua_pushlightuserdata(L, this);
            lua_pushnumber(L, engine::time::getTime() - m_initTime);
            lua_call(L, 2, 0);
            return !m_loops;
        }
    }
}


