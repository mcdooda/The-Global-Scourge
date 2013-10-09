#include <iostream>
#include "gameendstate.h"
#include "game.h"
#include "camera/camera.h"
#include "input/input.h"
#include "time/timer.h"

namespace game
{
    
    void GameEndState::enter(engine::state::Agent* agent)
    {
        Game* game = (Game*) agent;
        interface::Selection* selection = game->getSelection();
        selection->setHidden(true);
        selection->clearInside();
        selection->clearSelection();
        selection->clearListeners();
        ::game::input::input::clearListeners();
        //time::Timer::clearTimers();
    }
    
    void GameEndState::execute(engine::state::Agent* agent)
    {
        time::Timer::clearTimers();
        
        Game* game = (Game*) agent;
        
        // moving camera
        camera::move();
        //camera::zoom(0.5, 2);
        camera::setGameView();
        
        map::Map* map = game->getMap();
        map->show();

        camera::setInterfaceView();
        game->getInterface()->show();
        game->getInterface()->destroyIfDestroyed();
    }
    
    void GameEndState::exit(engine::state::Agent* agent)
    {
        
    }
    
}
