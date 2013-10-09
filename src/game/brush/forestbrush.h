#ifndef GAME_BRUSH_FORESTBRUSH_H
 #define GAME_BRUSH_FORESTBRUSH_H

#include "discbrush.h"

namespace game
{
    namespace brush
    {

        class ForestBrush : public DiscBrush
        {
            public:

                virtual float getEffect(float dx, float dy) const;
        };

    }
}

#endif



