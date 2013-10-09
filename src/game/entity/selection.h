#ifndef GAME_ENTITY_SELECTION_H
 #define GAME_ENTITY_SELECTION_H

#include "../../engine/graphics/texturedshowable.h"

namespace game
{
    namespace entity
    {
        
        class Selection : public engine::graphics::TexturedShowable
        {
            public:
                Selection(engine::graphics::Texture* texture, float radius);
                
            protected:
                Selection(engine::graphics::Texture* texture, int size);
        };
        
    }
}

#endif


