#include "game.h"
#include "../../gameendstate.h"
#include "../../game.h"
#include "../../mod/mod.h"
#include "../../../engine/time.h"
#include "../../../engine/singleton.h"
#include "../../../engine/sound/music.h"

namespace game
{
    namespace game
    {
        namespace lua
        {
            
            int gameLib(lua_State* L)
            {
                static const luaL_reg Game_lib[] = {
                    {"pause",    Game_pause},
                    {"resume",   Game_resume},
                    {"isPaused", Game_isPaused},
                    {"over",     Game_over},
                    {"exit",     Game_exit},
                    {"load",     Game_load},
                    {"reload",   Game_reload},
                    {NULL, NULL}
                };
                luaL_register(L, "Game", Game_lib);
                
                return 0;
            }
            
            int Game_pause(lua_State* L)
            {
                engine::time::pause();
                return 0;
            }
            
            int Game_resume(lua_State* L)
            {
                engine::time::resume();
                return 0;
            }
            
            int Game_isPaused(lua_State* L)
            {
                lua_pushboolean(L, engine::time::isPaused());
                return 1;
            }
            
            int Game_over(lua_State* L)
            {
                S(Game)->getStateMachine()->setState(new GameEndState());
                return 0;
            }
            
            int Game_exit(lua_State* L)
            {
                S(Game)->getSelection()->clearSelection();
                exit(0);
                return 0;
            }
            
            int Game_load(lua_State* L)
            {
                if (engine::time::isPaused())
                    engine::time::resume();
                    
                engine::sound::Music::rewind();
                engine::sound::Music::stop();
                    
                const char* modPath = luaL_checkstring(L, 1);
                S(Game)->stop();
                S(Game)->setNextMod(modPath);
                return 0;
            }
            
            int Game_reload(lua_State* L)
            {
                if (engine::time::isPaused())
                    engine::time::resume();
                
                S(Game)->stop();
                S(Game)->setNextMod(S(Mod)->getPath());
                return 0;
            }
            
        }
    }
}


