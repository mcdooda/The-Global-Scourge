#ifndef GAME_ENTITY_UNIT_H
 #define GAME_ENTITY_UNIT_H

#include "entity.h"
#include "../ai/squad.h"

namespace game
{
    namespace ai
    {
        class Squad;
    }

    namespace entity
    {

        class Unit : public Entity
        {
            public:
                Unit(EntityModel* model, engine::Vector2d position);

                static void init();

                virtual bool isUnit() const { return true; }
                virtual bool isBuilding() const { return false; }
                virtual bool isAbstract() const { return false; }

                virtual void setActive(bool active);

            protected:
                virtual void calcDepth(float x, float y, float radius);

            private:
                virtual void followPath(float frameTime);
                virtual void setDirection(float direction);

                int m_textureCoordX;
                int m_textureCoordY;
        };

    }
}

#endif
