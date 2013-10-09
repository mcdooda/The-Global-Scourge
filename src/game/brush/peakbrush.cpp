#include <cmath>
#include "peakbrush.h"

namespace game
{
    namespace brush
    {

        float PeakBrush::getEffect(float dx, float dy) const
        {
            float d = sqrt(dx * dx + dy * dy);

            if (d >= m_size)
                return 0;

            else
                return (1 - d / m_size) * (1 - d / m_size) * (1 - d / m_size);
        }

    }
}



