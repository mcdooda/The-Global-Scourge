#include "squarebrush.h"

namespace game
{
    namespace brush
    {

        float SquareBrush::getEffect(float dx, float dy) const
        {
            if (dx < 0)
                dx *= -1;

            if (dy < 0)
                dy *= -1;

            float max = dx;

            if (dy > max)
                max = dy;
                
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
