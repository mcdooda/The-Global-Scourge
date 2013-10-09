#include <sstream>
#include "editorstate.h"
#include "game.h"
#include "mod/mod.h"
#include "lua/lua.h"
#include "interface/imagewidget.h"
#include "map/displaymanager.h"
#include "map/editormap.h"
#include "map/editortile.h"
#include "map/io/reader.h"
#include "time/timer.h"
#include "camera/camera.h"
#include "../engine/graphics/window.h"
#include "../engine/input/keyboard.h"
#include "../engine/input/mouse.h"
#include "../engine/time.h"
#include "../engine/file/directory.h"
#include "../engine/singleton.h"

namespace game
{

    void EditorState::enter(engine::state::Agent* agent)
    {
        Game* game = (Game*) agent;
        
        map::Map* map = new map::EditorMap();
        game->setMap(map);

        engine::file::File f(S(Mod)->getFilePath("map.gpmap"));
        if (f.isReadable())
        {
            map::io::Reader reader;
            reader.read<map::EditorTile>();
        }
        else
            ((map::EditorMap*) game->getMap())->randomMap(S(Mod)->getMapWidth(), S(Mod)->getMapHeight());
        
        lua_State* L = lua::getState();
        
        if (luaL_dofile(L, "data/editor/scripts/interface.lua") != 0)
            lua_error(L);
    }

    void EditorState::execute(engine::state::Agent* agent)
    {
        Game* game = (Game*) agent;
        
        // moving camera
        camera::move();
        camera::zoom(0.2, 5);
        camera::setGameView();
        
        map::EditorMap* map = (map::EditorMap*) game->getMap();
        map->calcPointerPosition();
        map->moveEntities();

        if (!game->getInterface()->isMouseOver() && !engine::input::keyboard::isPressed(K(LCTRL)))
        {
            if (engine::input::mouse::isPressed(M(LEFT)))
                map->applyGroup();

            else if (engine::input::mouse::isPressed(M(RIGHT)))
                map->removeGroup();
                
            else if (map->usingBrush())
            {
                if ((engine::input::mouse::isJustPressed(M(WHEELUP)) && !engine::input::keyboard::isPressed(K(SPACE))) || engine::input::keyboard::isPressed(K(t)))
                    map->zUp();

                else if ((engine::input::mouse::isJustPressed(M(WHEELDOWN)) && !engine::input::keyboard::isPressed(K(SPACE))) || engine::input::keyboard::isPressed(K(g)))
                    map->zDown();
                    
                else if (engine::input::mouse::isJustPressed(M(WHEELUP)) && engine::input::keyboard::isPressed(K(SPACE)))
                    map->getBrush()->incrementSize();
                
                else if (engine::input::mouse::isJustPressed(M(WHEELDOWN)) && engine::input::keyboard::isPressed(K(SPACE)))
                    map->getBrush()->decrementSize();

                else if (engine::input::keyboard::isPressed(K(f)))
                    map->zMean();
                    
                else if (engine::input::keyboard::isPressed(K(DELETE)))
                    map->deleteTiles();
                    
                else if (engine::input::keyboard::isPressed(K(INSERT)))
                    map->insertTiles();
            }
        }

        if (engine::input::keyboard::isJustPressed(K(a)))
            map->generateForests();

        if (engine::input::keyboard::isPressed(K(q)))
            map->wave();

        if (engine::input::keyboard::isJustPressed(K(e)))
            map->flatten();

        map->show();

        camera::setInterfaceView();

        game->getInterface()->show();
        game->getInterface()->destroyIfDestroyed();
    }

    void EditorState::exit(engine::state::Agent* agent)
    {
        
    }

}



