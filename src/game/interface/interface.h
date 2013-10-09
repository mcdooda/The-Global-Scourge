#ifndef GAME_INTERFACE_INTERFACE_H
 #define GAME_INTERFACE_INTERFACE_H

#include "widget.h"

namespace game
{
    namespace interface
    {

        class Interface : public Widget
        {
            public:
                Interface();

                virtual bool isVisible();
                virtual engine::Vector2d getDimensions() const;
                virtual bool isMouseOver();
        };

    }
}

#endif
