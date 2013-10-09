#ifndef GAME_TIME_LUATIMER_H
 #define GAME_TIME_LUATIMER_H

#include <vector>
#include "../lua/lua.h"
#include "timer.h"

namespace game
{
    namespace time
    {
    
        class LuaTimer : public Timer
        {
            public:
                LuaTimer(float timeOut, bool loops);
                
                void setOnTimeOut(lua_State* L);
                
            protected:
                int m_onTimeOut;
                
                virtual bool execute();
        };
        
    }
}

#endif
