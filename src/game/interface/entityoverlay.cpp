#include <iostream>
#include "entityoverlay.h"

namespace game
{
    namespace interface
    {
        
        EntityOverlay::EntityOverlay() :
            Widget(NULL, engine::Vector2d(0, 0), engine::Vector2d(0, 0), CENTERX | CENTERY)
        {
            
        }
        
    }
}


