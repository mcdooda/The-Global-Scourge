#ifndef GAME_INTERFACE_TEXTWIDGET_H
 #define GAME_INTERFACE_TEXTWIDGET_H

#include "imagewidget.h"
#include "../../engine/graphics/text.h"
#include "../../engine/graphics/color.h"

namespace game
{
    namespace interface
    {

        class TextWidget : public ImageWidget
        {
            public:
                TextWidget(Widget* parent, engine::Vector2d relativePosition, int anchor, engine::graphics::Text* text);
                ~TextWidget();

                void setText(std::string text);
                void setColor(engine::graphics::Color color);
                
            protected:
                engine::graphics::Text* m_text;
        };

    }
}

#endif
