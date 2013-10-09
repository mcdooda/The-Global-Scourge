#ifndef GAME_ENTITY_BUILDINGSELECTION_H
 #define GAME_ENTITY_BUILDINGSELECTION_H

#include "selection.h"

namespace game
{
    namespace entity
    {
        
        class BuildingSelection : public Selection
        {
            public:
                BuildingSelection(engine::graphics::Texture* texture, int size);
        };
        
    }
}

#endif


