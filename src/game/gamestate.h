#ifndef GAME_GAMESTATE_H
 #define GAME_GAMESTATE_H

#include "../engine/state/state.h"

namespace game
{

    class GameState : public engine::state::State
    {
        public:

            virtual void enter(engine::state::Agent* agent);
            virtual void execute(engine::state::Agent* agent);
            virtual void exit(engine::state::Agent* agent);
    };

}

#endif

