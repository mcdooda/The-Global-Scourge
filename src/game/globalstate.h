#ifndef GAME_GLOBALSTATE_H
 #define GAME_GLOBALSTATE_H

#include "../engine/state/state.h"

namespace game
{

    class GlobalState : public engine::state::State
    {
        public:

            virtual void enter(engine::state::Agent* agent);
            virtual void execute(engine::state::Agent* agent);
            virtual void exit(engine::state::Agent* agent);

    };

}

#endif
