#include "doodad.h"

namespace game
{
    namespace map
    {

        Doodad::Doodad(engine::graphics::Texture* texture, Tile* tile) :
            m_tile(tile)
        {
            resetTextureCoords();
            setTexture(texture);
            setCenter(engine::Vector2d(texture->getWidth() / 2, texture->getWidth() / 4));
            setDimensions(texture->getDimensions());
            setPosition(tile->getPosition());
            static const float min = 0.0001;
            static const int maxSize = 3;
            static const int size = 1;
            setDepth(tile->getDepth() + min * maxSize - min * size);
        }
        
        void Doodad::show()
        {
            m_tile->getColor()->use();
            MapObject::show();
        }

    }
}

