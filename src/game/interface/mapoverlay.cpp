#include "mapoverlay.h"

namespace game
{
    namespace interface
    {
        
        MapOverlay::MapOverlay() :
            Widget(NULL, engine::Vector2d(0, 0), engine::Vector2d(0, 0), CENTERX | CENTERY)
        {
            
        }
        
    }
}


