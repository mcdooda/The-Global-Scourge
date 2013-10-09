#ifndef GAME_SOUND_LUA_H
 #define GAME_SOUND_LUA_H

#include "../../lua/lua.h"

namespace game
{
    namespace sound
    {
        namespace lua
        {
            
            int soundLib(lua_State* L);
            
            /* music */
            int Sound_preloadMusic(lua_State* L);
            int Sound_playMusic(lua_State* L);
            int Sound_fadeInMusic(lua_State* L);
            int Sound_setMusicVolume(lua_State* L);
            int Sound_fadeOutMusic(lua_State* L);
            int Sound_isMusicPaused(lua_State* L);
            int Sound_pauseMusic(lua_State* L);
            int Sound_resumeMusic(lua_State* L);
            int Sound_rewindMusic(lua_State* L);
            int Sound_stopMusic(lua_State* L);
            
            /* sample */
            int Sound_preloadSample(lua_State* L);
            int Sound_playSample(lua_State* L);
            int Sound_stopChannel(lua_State* L);
            int Sound_setChannelVolume(lua_State* L);
            int Sound_fadeOutChannel(lua_State* L);
            
        }
    }
}

#endif


