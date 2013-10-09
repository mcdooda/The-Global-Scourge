#ifndef GAME_ENTITY_ABSTRACTENTITY_H
 #define GAME_ENTITY_ABSTRACTENTITY_H

#include "entity.h"

namespace game
{
    namespace entity
    {
        
        class AbstractEntity : public Entity
        {
            public:
                AbstractEntity(EntityModel* model, engine::Vector2d position);
                
                virtual bool isUnit() const { return false; }
                virtual bool isBuilding() const { return false; }
                virtual bool isAbstract() const { return true; }
                
                virtual void setActive(bool active) {}
                
                virtual bool isSelectable() const { return false; }
                
                virtual void show();
                
                virtual void move(float frameTime) {}
                
            protected:
                virtual void calcDepth(float x, float y, float radius);
            
            
        };
        
    }
}

#endif


