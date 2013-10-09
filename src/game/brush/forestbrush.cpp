#include <cmath>
#include "forestbrush.h"
#include "../../engine/random.h"

namespace game
{
    namespace brush
    {

        float ForestBrush::getEffect(float dx, float dy) const
        {
            float max = sqrt(dx * dx + dy * dy);
            float d = max / m_size;
            float f = 1 - d * d;

            if (engine::random::rfloat(0, 1) < f)
                return f;

            else
                return 0;
        }

    }
}



