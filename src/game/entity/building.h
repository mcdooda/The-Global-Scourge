#ifndef GAME_ENTITY_BUILDING_H
 #define GAME_ENTITY_BUILDING_H

#include "entity.h"
#include "../map/tile.h"

namespace game
{
    namespace entity
    {

        class Building : public Entity
        {
            public:
                Building(EntityModel* model, engine::Vector2d position);
                
                virtual float getCenterX();
                virtual float getCenterY();
                virtual engine::Vector2d getCenter();

                virtual void move(float frameTime) {}

                virtual bool isBuilding() const { return true; }
                virtual bool isUnit() const { return false; }
                virtual bool isAbstract() const { return false; }

                virtual void setActive(bool active) {}

                void addedToMap(map::Map* map, int x, int y);
                void removedFromMap(map::Map* map, int x, int y);
                
                std::vector<map::Tile*> getTiles(map::Map* map);
                
            protected:
                virtual void calcDepth(float x, float y, float radius);
        };

    }
}

#endif
