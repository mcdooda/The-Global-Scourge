#include <cmath>
#include "spherebrush.h"

namespace game
{
    namespace brush
    {

        float SphereBrush::getEffect(float dx, float dy) const
        {
            float max = sqrt(dx * dx + dy * dy);
            float d = max / m_size;
            return 1 - d * d;
        }

    }
}


