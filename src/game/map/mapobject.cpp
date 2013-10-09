#include "mapobject.h"

namespace game
{
    namespace map
    {
        
        MapObject::MapObject()
        {
            m_color = engine::graphics::Color::WHITE.newCopy();
        }
        
        MapObject::~MapObject()
        {
            delete m_color;
        }

        void MapObject::calcDepth(float x, float y, float radius)
        {
            setDepth(x + y + radius);
        }

    }
}
