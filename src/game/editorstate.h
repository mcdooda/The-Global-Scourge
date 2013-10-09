#ifndef GAME_EDITORSTATE_H
 #define GAME_EDITORSTATE_H

#include "../engine/state/state.h"

namespace game
{

    class EditorState : public engine::state::State
    {
        public:

            virtual void enter(engine::state::Agent* agent);
            virtual void execute(engine::state::Agent* agent);
            virtual void exit(engine::state::Agent* agent);
    };

}

#endif
