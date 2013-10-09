#include <cmath>
#include "globalstate.h"
#include "game.h"
#include "entity/buildingmodel.h"
#include "entity/building.h"
#include "entity/unitmodel.h"
#include "entity/unit.h"
#include "lua/lua.h"
#include "mod/mod.h"
#include "mod/lua/mod.h"
#include "file/lua/file.h"
#include "interface/lua/widget.h"
#include "interface/lua/selection.h"
#include "map/lua/editormap.h"
#include "map/lua/map.h"
#include "map/lua/tile.h"
#include "time/lua/time.h"
#include "time/lua/timer.h"
#include "time/timer.h"
#include "sound/lua/sound.h"
#include "entity/lua/entitymodel.h"
#include "entity/lua/entity.h"
#include "camera/lua/camera.h"
#include "input/lua/input.h"
#include "input/input.h"
#include "brush/lua/brush.h"
#include "game/lua/game.h"
#include "../engine/input/keyboard.h"
#include "../engine/input/window.h"
#include "../engine/input/mouse.h"
#include "../engine/input/input.h"
#include "../engine/time.h"
#include "../engine/singleton.h"

namespace game
{

    void GlobalState::enter(engine::state::Agent* agent)
    {
        Game* game = (Game*) agent;
        
        //engine::input::clearAll();

        lua::init();
        lua_State* L = lua::getState();

        lua_cpcall(L, mod::lua::modLib, NULL);
        lua_cpcall(L, file::lua::fileLib, NULL);
        lua_cpcall(L, interface::lua::widgetLib, NULL);
        lua_cpcall(L, interface::lua::selectionLib, NULL);
        lua_cpcall(L, entity::lua::entityModelLib, NULL);
        lua_cpcall(L, entity::lua::entityLib, NULL);
        lua_cpcall(L, map::lua::editorMapLib, NULL);
        lua_cpcall(L, map::lua::mapLib, NULL);
        lua_cpcall(L, map::lua::tileLib, NULL);
        lua_cpcall(L, time::lua::timeLib, NULL);
        lua_cpcall(L, time::lua::timerLib, NULL);
        lua_cpcall(L, camera::lua::cameraLib, NULL);
        lua_cpcall(L, ::game::input::lua::inputLib, NULL);
        lua_cpcall(L, brush::lua::brushLib, NULL);
        lua_cpcall(L, ::game::game::lua::gameLib, NULL);
        lua_cpcall(L, sound::lua::soundLib, NULL);
        
        S(Mod)->readConfig();
        
        entity::Unit::init();
        
        interface::Interface* interface = new interface::Interface();
        game->setInterface(interface);
        
        interface::Selection* selection = new interface::Selection(interface);
        game->setSelection(selection);
        
        if (luaL_dofile(L, S(Mod)->getFilePath("scripts/units.lua").c_str()) != 0)
            lua_error(L);

        if (luaL_dofile(L, S(Mod)->getFilePath("scripts/buildings.lua").c_str()) != 0)
            lua_error(L);
            
        if (luaL_dofile(L, S(Mod)->getFilePath("scripts/abstracts.lua").c_str()) != 0)
            lua_error(L);
    }

    void GlobalState::execute(engine::state::Agent* agent)
    {
        Game* game = (Game*) agent;

        if (engine::input::window::closed())
            game->stop();

        if (engine::input::window::resized())
        {
            engine::graphics::window::resize();
            game->getInterface()->resize();
        }
        
        time::Timer::triggerTimers();
        input::input::triggerListeners();
    }

    void GlobalState::exit(engine::state::Agent* agent)
    {
        time::Timer::clearTimers();
        input::input::clearListeners();
    }

}

