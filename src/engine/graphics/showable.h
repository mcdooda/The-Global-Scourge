#ifndef ENGINE_GRAPHICS_SHOWABLE_H
 #define ENGINE_GRAPHICS_SHOWABLE_H

#include "../vector2d.h"

namespace engine
{
    namespace graphics
    {

        class Showable
        {
            public:

                virtual void show() = 0;

                virtual bool isVisible() = 0;

                inline Vector2d getPosition() const { return m_position; }
                virtual void setPosition(Vector2d position);

            protected:
                Vector2d m_position;
        };

    }
}

#endif
