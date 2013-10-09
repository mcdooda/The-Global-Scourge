#ifndef GAME_AI_SQUAD_H
 #define GAME_AI_SQUAD_H

#include "../entity/entity.h"

namespace game
{

    namespace entity
    {
        class Entity;
    }

    namespace ai
    {

        class Squad
        {
            public:
                Squad();
                ~Squad();

                inline void setLeader(entity::Entity* leader) { m_leader = leader; }
                inline entity::Entity* getLeader() const { return m_leader; }

                void addEntity(entity::Entity* unit);

                void executeOrder(float frameTime);

            private:

                entity::Entity* m_leader;
                std::vector<entity::Entity*> m_entities;

                float m_lastUpdate;
        };

    }
}

#endif
