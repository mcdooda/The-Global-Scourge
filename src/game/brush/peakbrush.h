#ifndef GAME_BRUSH_PEAKBRUSH_H
 #define GAME_BRUSH_PEAKBRUSH_H

#include "discbrush.h"

namespace game
{
    namespace brush
    {

        class PeakBrush : public DiscBrush
        {
            public:

                float getEffect(float dx, float dy) const;
        };

    }
}

#endif



