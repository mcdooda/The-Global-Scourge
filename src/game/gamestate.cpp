#include <sstream>
#include "gamestate.h"
#include "game.h"
#include "map/io/reader.h"
#include "mod/mod.h"
#include "entity/unit.h"
#include "entity/unitmodel.h"
#include "time/timer.h"
#include "camera/camera.h"
#include "../engine/file/file.h"
#include "../engine/graphics/text.h"
#include "../engine/graphics/window.h"
#include "../engine/input/mouse.h"
#include "../engine/input/keyboard.h"
#include "../engine/singleton.h"
#include "../engine/time.h"

namespace game
{

    void GameState::enter(engine::state::Agent* agent)
    {
        Game* game = (Game*) agent;
        
        map::Map* map = new map::Map();
        game->setMap(map);
        
        engine::file::File f(S(Mod)->getFilePath("map.gpmap"));
        if (f.isReadable())
        {
            map::io::Reader reader;
            reader.read<map::Tile>();
        }
        else
            ::exit(0);
        
        lua_State* L = lua::getState();
        
        if (luaL_dofile(L, S(Mod)->getFilePath("scripts/game.lua").c_str()) != 0)
            lua_error(L);
    }

    void GameState::execute(engine::state::Agent* agent)
    {
        Game* game = (Game*) agent;
        
        map::Map* map = game->getMap();
        
        if (engine::input::mouse::isJustPressed(M(RIGHT)))
            map->clearGhostModel();
        
        interface::Interface* interface = game->getInterface();
        
        // selecting entities
        interface::Selection* selection = game->getSelection();
        
        engine::Vector2d mouse(engine::input::mouse::getX(), engine::input::mouse::getY() - engine::graphics::window::getHeight());
        
        if (engine::input::mouse::isJustReleased(M(LEFT)) && selection->isSelecting() && selection->isAreaEmpty())
        {
            if (selection->getNumInsideEntities() > 0)
                map->clearGhostModel();
            
            if (engine::input::keyboard::isPressed(K(LSHIFT)))
                selection->addEntities();

            else
                selection->selectEntities();
        }
        else if (!interface->isMouseOver() && engine::input::mouse::isJustPressed(M(LEFT)))
        {
            selection->setHidden(false);
            selection->setRelativePosition(mouse);
            selection->setDimensions(engine::Vector2d(0, 0));
        }
        else if (map->getGhostModel() == NULL && engine::input::mouse::isPressed(M(LEFT)))
        {
            engine::Vector2d dimensions(mouse.getX() - selection->getRelativePosition().getX(), -mouse.getY() + selection->getRelativePosition().getY());
            selection->setDimensions(dimensions);
        }
        
        // moving camera
        if (!selection->isSelecting())
        {
            camera::move();
            //camera::zoom(0.5, 2);
        }
        camera::setGameView();

        selection->clearInside();
        
        map->calcPointerPosition();
        map->moveEntities();
        map->show();

        if (selection->isSelecting() && engine::input::mouse::isJustReleased(M(LEFT)))
        {
            selection->setHidden(true);

            if (engine::input::keyboard::isPressed(K(LSHIFT)))
                selection->addEntities();

            else if (!selection->isAreaEmpty())
                selection->selectEntities();
        }
        else if (engine::input::mouse::isJustPressed(M(RIGHT)))
            selection->moveOrder(engine::input::keyboard::isPressed(K(LSHIFT)));

        camera::setInterfaceView();

        game->getInterface()->show();
        game->getInterface()->destroyIfDestroyed();
    }

    void GameState::exit(engine::state::Agent* agent)
    {
        
    }

}


