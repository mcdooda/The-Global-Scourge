#include "sound.h"
#include "../../mod/mod.h"
#include "../../../engine/resourcemanager.h"
#include "../../../engine/singleton.h"

namespace game
{
    namespace sound
    {
        namespace lua
        {
            
            int soundLib(lua_State* L)
            {
                static const luaL_reg Sound_lib[] = {
                    {"preloadMusic",     Sound_preloadMusic},
                    {"playMusic",        Sound_playMusic},
                    {"fadeInMusic",      Sound_fadeInMusic},
                    {"setMusicVolume",   Sound_setMusicVolume},
                    {"fadeOutMusic",     Sound_fadeOutMusic},
                    {"isMusicPaused",    Sound_isMusicPaused},
                    {"pauseMusic",       Sound_pauseMusic},
                    {"resumeMusic",      Sound_resumeMusic},
                    {"rewindMusic",      Sound_rewindMusic},
                    {"stopMusic",        Sound_stopMusic},
                    {"preloadSample",    Sound_preloadSample},
                    {"playSample",       Sound_playSample},
                    {"stopChannel",      Sound_stopChannel},
                    {"setChannelVolume", Sound_setChannelVolume},
                    {"fadeOutChannel",   Sound_fadeOutChannel},
                    {NULL, NULL}
                };
                luaL_register(L, "Sound", Sound_lib);

                return 0;
            }
            
            int Sound_preloadMusic(lua_State* L)
            {
                std::string filename = luaL_checkstring(L, 1);
                S(engine::MusicManager)->get(S(Mod)->getResourceFilePath("music/" + filename));
                return 0;
            }
            
            int Sound_playMusic(lua_State* L)
            {
                std::string filename = luaL_checkstring(L, 1);
                engine::sound::Music* music = S(engine::MusicManager)->get(S(Mod)->getResourceFilePath("music/" + filename));
                music->play();
                return 0;
            }
            
            int Sound_fadeInMusic(lua_State* L)
            {
                std::string filename = luaL_checkstring(L, 1);
                float duration = luaL_checknumber(L, 2);
                engine::sound::Music* music = S(engine::MusicManager)->get(S(Mod)->getResourceFilePath("music/" + filename));
                music->fadeIn(duration);
                return 0;
            }
            
            int Sound_setMusicVolume(lua_State* L)
            {
                float volume = luaL_checknumber(L, 1);
                engine::sound::Music::setVolume(volume);
                return 0;
            }
            
            int Sound_fadeOutMusic(lua_State* L)
            {
                float duration = luaL_checknumber(L, 1);
                engine::sound::Music::fadeOut(duration);
                return 0;
            }
            
            int Sound_isMusicPaused(lua_State* L)
            {
                lua_pushboolean(L, engine::sound::Music::isPaused());
                return 1;
            }
            
            int Sound_pauseMusic(lua_State* L)
            {
                engine::sound::Music::pause();
                return 0;
            }
            
            int Sound_resumeMusic(lua_State* L)
            {
                engine::sound::Music::resume();
                return 0;
            }
            
            int Sound_rewindMusic(lua_State* L)
            {
                engine::sound::Music::rewind();
                return 0;
            }
            
            int Sound_stopMusic(lua_State* L)
            {
                engine::sound::Music::stop();
                return 0;
            }
            
            int Sound_preloadSample(lua_State* L)
            {
                std::string filename = luaL_checkstring(L, 1);
                S(engine::SampleManager)->get(S(Mod)->getResourceFilePath("samples/" + filename));
                return 0;
            }
            
            int Sound_playSample(lua_State* L)
            {
                std::string filename = luaL_checkstring(L, 1);
                engine::sound::Sample* sample = S(engine::SampleManager)->get(S(Mod)->getResourceFilePath("samples/" + filename));
                int channel = sample->play();
                lua_pushinteger(L, channel);
                return 1;
            }
            
            int Sound_stopChannel(lua_State* L)
            {
                int channel = luaL_checkint(L, 1);
                engine::sound::Sample::stopChannel(channel);
                return 0;
            }
            
            int Sound_setChannelVolume(lua_State* L)
            {
                int channel = luaL_checkint(L, 1);
                float volume = luaL_checknumber(L, 2);
                engine::sound::Sample::setChannelVolume(channel, volume);
                return 0;
            }
            
            int Sound_fadeOutChannel(lua_State* L)
            {
                int channel = luaL_checkint(L, 1);
                float duration = luaL_checknumber(L, 2);
                engine::sound::Sample::fadeOutChannel(channel, duration);
                return 0;
            }
            
        }
    }
}


