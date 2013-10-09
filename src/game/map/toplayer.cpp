#include "toplayer.h"

namespace game
{
    namespace map
    {

        TopLayer::TopLayer(engine::graphics::Texture* texture, Tile* tile) :
            m_tile(tile),
            m_yShift(0)
        {
            m_textureHalfWidth = texture->getWidth() / 2;
            m_textureThreeQuartersHeight = texture->getHeight() * 3.f / 4;
            resetTextureCoords();
            setTexture(texture);
            setCenter(engine::Vector2d(m_textureHalfWidth, m_textureThreeQuartersHeight + m_yShift));
            setDimensions(texture->getDimensions());
            setPosition(tile->getPosition());
        }
        
        void TopLayer::show()
        {
            m_color->use();
            MapObject::show();
        }
        
        void TopLayer::updateCenter()
        {
            setCenter(engine::Vector2d(m_textureHalfWidth, m_textureThreeQuartersHeight + m_yShift));
            setPosition(m_tile->getPosition());
        }

    }
}

