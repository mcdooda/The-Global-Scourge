#include "selection.h"
#include "../game.h"
#include "../mod/mod.h"
#include "../../engine/singleton.h"
#include "../../engine/resourcemanager.h"

namespace game
{
    namespace interface
    {

        Selection::Selection(interface::Interface* interface) :
            ImageWidget(interface, engine::Vector2d(10, -10), Widget::LEFT | Widget::TOP, S(Mod)->getTexture("interface/selection.png"), false)
        {
            setHidden(true);
            m_numInsideEntities = 0;
            m_numSelectedEntities = 0;
            m_onChange = LUA_NOREF;
        }

        bool Selection::isMouseOver()
        {
            return false;
        }

        void Selection::setDimensions(engine::Vector2d dimensions)
        {
            ImageWidget::setDimensions(dimensions);
            engine::Vector2d position = getPosition();
            if (dimensions.getX() < 0)
            {
                m_left = position.getX() + dimensions.getX();
                m_right = position.getX();
            }
            else
            {
                m_left = position.getX();
                m_right = position.getX() + dimensions.getX();
            }

            if (dimensions.getY() < 0)
            {
                m_top = position.getY() - dimensions.getY();
                m_bottom = position.getY();
            }
            else
            {
                m_top = position.getY();
                m_bottom = position.getY() - dimensions.getY();
            }
        }

        bool Selection::isInside(engine::Vector2d screenPosition) const
        {
            return screenPosition.getX() >= m_left
                && screenPosition.getX() <= m_right
                && screenPosition.getY() >= m_bottom
                && screenPosition.getY() <= m_top;
        }

        void Selection::addInside(entity::Entity* entity)
        {
            if (m_numInsideEntities < MAX_INSIDE_ENTITIES)
            {
                m_insideEntities[m_numInsideEntities] = entity;
                m_numInsideEntities++;
                entity->setInsideOfSelection(true);
            }
        }
        
        void Selection::removeInside(entity::Entity* entity)
        {
            entity->setInsideOfSelection(false);
            for (int i = 0; i < m_numInsideEntities; i++)
            {
                if (m_insideEntities[i] == entity)
                {
                    m_insideEntities[i] = m_insideEntities[m_numInsideEntities - 1];
                    m_numInsideEntities--;
                    break;
                }
            }
        }

        void Selection::clearInside()
        {
            for (int i = 0; i < m_numInsideEntities; i++)
                m_insideEntities[i]->setInsideOfSelection(false);

            m_numInsideEntities = 0;
        }

        void Selection::selectEntities()
        {
            clearSelection();
            for (int i = 0; i < m_numInsideEntities; i++)
                m_insideEntities[i]->setSelected(true);

            memcpy(m_selectedEntities, m_insideEntities, m_numInsideEntities * sizeof(entity::Entity*));
            m_numSelectedEntities = m_numInsideEntities;
            
            triggerListeners();
        }

        void Selection::addEntities()
        {
            int oldNumSelectedEntities = m_numSelectedEntities;
            for (int i = 0; i < m_numInsideEntities; i++)
            {
                entity::Entity* entity = m_insideEntities[i];
                if (!entity->isSelected() && m_numSelectedEntities < MAX_INSIDE_ENTITIES)
                {
                    m_selectedEntities[m_numSelectedEntities] = entity;
                    entity->setSelected(true);
                    m_numSelectedEntities++;
                }
            }
            if (m_numSelectedEntities > oldNumSelectedEntities)
                triggerListeners();
        }
        
        void Selection::toggleEntity()
        {
            if (m_insideEntities[0]->isSelected())
                unselectEntity(m_insideEntities[0]);
                
            else
                addEntities();
        }
        
        void Selection::unselectEntity(entity::Entity* entity)
        {
            entity->setSelected(false);
            for (int i = 0; i < m_numSelectedEntities; i++)
            {
                if (m_selectedEntities[i] == entity)
                {
                    m_selectedEntities[i] = m_selectedEntities[m_numSelectedEntities - 1];
                    m_numSelectedEntities--;
                    triggerListeners();
                    break;
                }
            }
        }

        void Selection::clearSelection()
        {
            for (int i = 0; i < m_numSelectedEntities; i++)
                m_selectedEntities[i]->setSelected(false);

            m_numSelectedEntities = 0;
        }

        void Selection::moveOrder(bool add)
        {
            map::Map* map = S(Game)->getMap();
            engine::Vector2d mapPointer = map->getPointerPosition();

            if (mapPointer.getX() < 0)
                mapPointer.setX(0);

            else if (mapPointer.getX() > map->getWidth() - 1)
                mapPointer.setX(map->getWidth() - 1);

            if (mapPointer.getY() < 0)
                mapPointer.setY(0);

            else if (mapPointer.getY() > map->getHeight() - 1)
                mapPointer.setY(map->getHeight() - 1);


            for (int i = 0; i < m_numSelectedEntities; i++)
            {
                entity::Entity* entity = m_selectedEntities[i];

                if (!add)
                    entity->clearPath();

                entity->addPath(mapPointer);
            }
        }
        
        entity::Entity** Selection::getEntities(int* numEntities)
        {
            *numEntities = m_numSelectedEntities;
            return m_selectedEntities;
        }
        
        void Selection::setChangeListener(lua_State* L)
        {
            clearListeners();
            if (!lua_isnil(L, 1))
            {
                luaL_checktype(L, 1, LUA_TFUNCTION);
                m_onChange = luaL_ref(L, LUA_REGISTRYINDEX);
            }
        }
        
        void Selection::triggerListeners()
        {
            if (m_onChange != LUA_NOREF)
            {
                lua_State* L = lua::getState();
                lua_rawgeti(L, LUA_REGISTRYINDEX, m_onChange);
                lua_createtable(L, m_numSelectedEntities, 0);
                for (int i = 0; i < m_numSelectedEntities; i++)
                {
                    lua_pushlightuserdata(L, m_selectedEntities[i]);
                    lua_rawseti(L, -2, i + 1);
                }
                lua_call(L, 1, 0);
            }
        }
        
        void Selection::clearListeners()
        {
            if (m_onChange != LUA_NOREF)
            {
                lua_State* L = lua::getState();
                luaL_unref(L, LUA_REGISTRYINDEX, m_onChange);
                m_onChange = LUA_NOREF;
            }
        }

    }
}
