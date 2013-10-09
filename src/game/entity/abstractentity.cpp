#include "abstractentity.h"

namespace game
{
    namespace entity
    {
        
        AbstractEntity::AbstractEntity(EntityModel* model, engine::Vector2d position) :
            Entity(model, position)
        {
            m_active = false;
        }
        
        void AbstractEntity::show()
        {
            m_color->use();
            map::MapObject::show();
        }
        
        void AbstractEntity::calcDepth(float x, float y, float radius)
        {
            setDepth(x + y + 0.5);
        }
        
    }
}


