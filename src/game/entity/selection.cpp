#include "selection.h"

namespace game
{
    namespace entity
    {
        
        Selection::Selection(engine::graphics::Texture* texture, float radius) :
            TexturedShowable(texture->getDimensions() * radius, texture->getDimensions() * radius / 2)
        {
            setTexture(texture);
        }
        
        Selection::Selection(engine::graphics::Texture* texture, int size) :
            TexturedShowable(texture->getDimensions() * size, engine::Vector2d(texture->getDimensions().getX() * size / 2, texture->getDimensions().getY() / 2))
        {
            setTexture(texture);
        }
        
    }
}


