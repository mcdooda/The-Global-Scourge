#ifndef GAME_ENTITY_ENTITY_H
 #define GAME_ENTITY_ENTITY_H

#include "../map/mapobject.h"
#include "../../engine/vector2d.h"
#include "../map/map.h"
#include "entitymodel.h"
#include "../ai/squad.h"
#include "selection.h"
#include "../interface/entityoverlay.h"

namespace game
{
    namespace map
    {
        class Map;
        class Tile;
    }

    namespace entity
    {

        class Entity : public map::MapObject
        {
            public:
                Entity(EntityModel* model, engine::Vector2d position);
                virtual ~Entity();

                virtual void show();

                void clearPath();
                void addPath(engine::Vector2d point);
                void findPath(engine::Vector2d point);

                virtual void move(float frameTime);

                void updatePosition();
                inline engine::Vector2d getPosition() const { return m_position; }
                inline float getX() const { return m_position.getX(); }
                inline float getY() const { return m_position.getY(); }
                inline float getZ() const { return m_z; }
                virtual float getCenterX() { return m_position.getX(); }
                virtual float getCenterY() { return m_position.getY(); }
                virtual engine::Vector2d getCenter() { return m_position; }

                int getTileX() const;
                int getTileY() const;

                virtual bool isBuilding() const = 0;
                virtual bool isUnit() const = 0;
                virtual bool isAbstract() const = 0;
                bool canMove() const;
                inline bool isMoving() const { return !m_path.empty(); }

                inline EntityModel* getModel() const { return m_model; }

                void setZ(float z);
                void setEntityPosition(engine::Vector2d position);

                virtual void addedToMap(map::Map* map, int x, int y);
                virtual void removedFromMap(map::Map* map, int x, int y) {}
                
                virtual bool isSelectable() const { return true; }
                inline void setInsideOfSelection(bool insideOfSelection) { m_insideOfSelection = insideOfSelection; }
                inline void setSelected(bool selected) { m_selected = selected; }
                inline bool isSelected() const { return m_selected; }
                
                engine::Vector2d getAbsolutePosition();

                virtual void setActive(bool active);
                inline bool isActive() const { return m_active; }

                map::Tile* getTile();

                engine::Vector2d getFuturePosition(float time);
                map::Tile* getFutureTile(float time);

                bool isSquadLeader();

                inline void setSquad(ai::Squad* squad) { m_squad = squad; }
                
                void jump(float force);
                
                void enableOverlay();
                void disableOverlay();
                inline interface::EntityOverlay* getOverlay() const { return m_overlay; }
                
                void setTileChangeListener(lua_State* L);
                void triggerTileChangeListener();
                
                inline bool isOnTheFloor() const { return m_onTheFloor; }

            protected:
                bool separate();
                bool separateTile();
                std::vector<Entity*> getNeighbors(float radius);
                virtual void followPath(float frameTime);
                virtual void setDirection(float direction);
                bool fall(float frameTime);

                bool m_onTheFloor;
                std::vector<engine::Vector2d> m_path;
                bool m_insideOfSelection;
                bool m_selected;
                bool m_active;
                EntityModel* m_model;
                float m_direction;
                engine::Vector2d m_speed;
                engine::Vector2d m_position;
                float m_z;
                float m_zSpeed;
                
                Selection* m_selectionImage;
                Selection* m_selectedImage;

                ai::Squad* m_squad;
                
                interface::EntityOverlay* m_overlay;
                
                int m_onTileChange;
        };

    }
}

#endif
