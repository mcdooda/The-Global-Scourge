#ifndef GAME_BRUSH_SQUAREBRUSH_H
 #define GAME_BRUSH_SQUAREBRUSH_H

#include "brush.h"

namespace game
{
    namespace brush
    {

        class SquareBrush : public Brush
        {
            public:

                float getEffect(float dx, float dy) const;
        };

    }
}

#endif
