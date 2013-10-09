#ifndef GAME_INTERFACE_IMAGEWIDGET_H
 #define GAME_INTERFACE_IMAGEWIDGET_H

#include "widget.h"
#include "../../engine/graphics/texture.h"

namespace game
{
    namespace interface
    {

        class ImageWidget : public Widget
        {
            public:
                ImageWidget(Widget* parent, engine::Vector2d relativePosition, int anchor, engine::graphics::Texture* texture, bool pixelPerfect);

                virtual void show();
                
                void setTextureCoords(float lX, float bY, float rX, float tY);
                void resetTextureCoords();
                
                virtual bool isMouseOver();
                
                inline void setTexture(engine::graphics::Texture* texture) { engine::graphics::TexturedShowable::setTexture(texture); }
                
            protected:
                void showTexture();
                
                float m_textureCoords[8]; // has to be kept here in addition to engine::graphics::TextureShowable::m_textureCoords
                bool m_pixelPerfect;
        };

    }
}

#endif
