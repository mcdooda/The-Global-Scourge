#include <cmath>
#include "discbrush.h"

namespace game
{
    namespace brush
    {

        float DiscBrush::getEffect(float dx, float dy) const
        {
            float max = sqrt(dx * dx + dy * dy);
            float limitWidth = getLimitWidth();

            if (max >= m_size)
                return 0;

            else if (m_size - max <= limitWidth)
                return (m_size - max) / limitWidth;

            else
                return 1;
        }

    }
}

