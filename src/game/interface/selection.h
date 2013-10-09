#ifndef GAME_INTERFACE_SELECTION_H
 #define GAME_INTERFACE_SELECTION_H

#include "imagewidget.h"
#include "interface.h"
#include "../entity/entity.h"

#define MAX_INSIDE_ENTITIES 3000

namespace game
{
    namespace interface
    {

        class Selection : public ImageWidget
        {
            public:
                Selection(interface::Interface* interface);

                virtual bool isMouseOver();

                void setDimensions(engine::Vector2d dimensions);

                inline float getLeft()   const { return m_left; }
                inline float getRight()  const { return m_right; }
                inline float getTop()    const { return m_top; }
                inline float getBottom() const { return m_bottom; }

                inline bool isSelecting() const { return !isHidden(); }
                
                inline bool isAreaEmpty() const { return m_left >= m_right - 5 && m_bottom >= m_top - 5; }

                bool isInside(engine::Vector2d screenPosition) const;
                void addInside(entity::Entity* entity);
                void removeInside(entity::Entity* entity);
                void clearInside();
                inline int getNumInsideEntities() const { return m_numInsideEntities; }

                void selectEntities();
                void addEntities();
                void toggleEntity();
                void unselectEntity(entity::Entity* entity);
                void clearSelection();

                void moveOrder(bool add);
                entity::Entity** getEntities(int* numEntities);
                
                void setChangeListener(lua_State* L);
                void triggerListeners();
                void clearListeners();

            private:

                entity::Entity* m_insideEntities[MAX_INSIDE_ENTITIES];
                int m_numInsideEntities;

                entity::Entity* m_selectedEntities[MAX_INSIDE_ENTITIES];
                int m_numSelectedEntities;

                float m_left;
                float m_right;
                float m_top;
                float m_bottom;
                
                int m_onChange;
        };

    }
}

#endif
