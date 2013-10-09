#ifndef GAME_BRUSH_DISCBRUSH_H
 #define GAME_BRUSH_DISCBRUSH_H

#include "brush.h"

namespace game
{
    namespace brush
    {

        class DiscBrush : public Brush
        {
            public:

                virtual float getEffect(float dx, float dy) const;
        };

    }
}

#endif

