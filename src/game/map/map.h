#ifndef GAME_MAP_MAP_H
 #define GAME_MAP_MAP_H

#include "tile.h"
#include "../entity/entitymodel.h"
#include "../ai/squad.h"
#include "../lua/lua.h"
#include "../interface/mapoverlay.h"

namespace game
{
    namespace entity
    {
        class Entity;
    }

    namespace ai
    {
        class Squad;
    }

    namespace map
    {
        class Tile;

        namespace io
        {
            class Reader;
            class Writer;
        }

        class Map
        {
            public:
                Map();
                virtual ~Map();

                void calcPointerPosition();
                
                virtual void showTemporaries();
                virtual void show();

                void addEntity(int x, int y, entity::Entity* entity);
                void removeEntity(int x, int y, entity::Entity* entity);
                void moveEntity(int x, int y, int newX, int newY, entity::Entity* entity);
                void addEntity(entity::Entity* entity);
                void removeEntity(entity::Entity* entity);

                Tile* getTile(int x, int y);

                engine::Vector2d getMapPosition(engine::Vector2d screenPosition) const;
                virtual engine::Vector2d getPointerPosition() const;

                inline int getWidth() const { return m_width; }
                inline int getHeight() const { return m_height; }
                
                inline const std::vector<entity::Entity*>& getEntities() const { return m_entities; }

                void moveEntities();
                
                inline entity::EntityModel* getGhostModel() const { return m_ghostModel; }
                inline void setGhostModel(entity::EntityModel* ghostModel) { m_ghostModel = ghostModel; }
                void clearGhostModel();
                
                void setGhostModelClearListener(lua_State* L);
                void triggerGhostModelClearListener();
                
                void setBuildListener(lua_State* L);
                void triggerBuildListener(entity::Entity* entity);
                
                void enableOverlay();
                void disableOverlay();
                inline interface::MapOverlay* getOverlay() const { return m_overlay; }

            protected:
                friend class io::Reader;
                friend class io::Writer;

                Tile*** m_tiles;

                int m_width;
                int m_height;

                std::vector<entity::Entity*> m_entities;
                std::vector<ai::Squad*> m_squads;

                engine::Vector2d m_pointerPosition;
                
                entity::EntityModel* m_ghostModel;
                int m_onGhostModelClear;
                int m_onBuild;
                
                interface::MapOverlay* m_overlay;
        };

    }
}

#endif
