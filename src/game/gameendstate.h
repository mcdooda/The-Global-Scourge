#ifndef GAME_GAMEENDSTATE_H
 #define GAME_GAMEENDSTATE_H

#include "../engine/state/state.h"

namespace game
{
    
    class GameEndState : public engine::state::State
    {
        public:

            virtual void enter(engine::state::Agent* agent);
            virtual void execute(engine::state::Agent* agent);
            virtual void exit(engine::state::Agent* agent);
    };
    
}

#endif


