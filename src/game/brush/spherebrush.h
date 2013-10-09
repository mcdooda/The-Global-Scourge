#ifndef GAME_BRUSH_SPHEREBRUSH_H
 #define GAME_BRUSH_SPHEREBRUSH_H

#include "discbrush.h"

namespace game
{
    namespace brush
    {

        class SphereBrush : public DiscBrush
        {
            public:

                float getEffect(float dx, float dy) const;
        };

    }
}

#endif


