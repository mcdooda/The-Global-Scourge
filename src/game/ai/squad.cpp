#include "squad.h"
#include "../../engine/time.h"

namespace game
{
    namespace ai
    {

        Squad::Squad() :
            m_leader(NULL),
            m_lastUpdate(0)
        {

        }

        Squad::~Squad()
        {
            std::vector<entity::Entity*>::iterator end = m_entities.end();
            for (std::vector<entity::Entity*>::iterator it = m_entities.begin(); it != end; it++)
                (*it)->setSquad(NULL);
        }

        void Squad::addEntity(entity::Entity* unit)
        {
            m_entities.push_back(unit);
            unit->setSquad(this);
        }

        void Squad::executeOrder(float frameTime)
        {
            bool updateOrder = false;
            float time = engine::time::getTime();
            static const float updatePeriod = 0.2;
            if (time > m_lastUpdate + updatePeriod)
            {
                m_lastUpdate = time;
                updateOrder = true;

            }
            engine::Vector2d destination = m_leader->getFuturePosition(0.5);
            std::vector<entity::Entity*>::iterator end = m_entities.end();
            for (std::vector<entity::Entity*>::iterator it = m_entities.begin(); it != end; it++)
            {
                if (updateOrder && *it != m_leader)
                {
                    (*it)->clearPath();
                    (*it)->addPath(destination);
                }
                (*it)->move(frameTime);
            }
        }

    }
}
