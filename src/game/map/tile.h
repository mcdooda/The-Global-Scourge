#ifndef GAME_MAP_TILE_H
 #define GAME_MAP_TILE_H

#include <vector>
#include "../../engine/graphics/texture.h"
#include "../../engine/graphics/texturedshowable.h"
#include "../../engine/graphics/color.h"
#include "../entity/entity.h"
#include "doodad.h"
#include "toplayer.h"
#include "mapobject.h"

namespace game
{
    namespace entity
    {
        class Entity;
    }

    namespace map
    {
        class Doodad;
        class TopLayer;

        class Tile : public MapObject
        {
            public:
                Tile(engine::graphics::Texture* texture, int x, int y, float z);
                virtual ~Tile();

                inline float getZ() const { return m_z; }
                void setZ(float z);

                virtual void show();
                void showEntities();
                
                virtual void setDoodadTexture(engine::graphics::Texture* texture);
                virtual void setTopLayerTexture(engine::graphics::Texture* texture);
                
                inline Doodad* getDoodad() const { return m_doodad; }
                inline TopLayer* getTopLayer() const { return m_topLayer; }

                void addEntity(entity::Entity* entity);
                void removeEntity(entity::Entity* entity);

                inline bool isAccessible() const { return m_accessible; }
                inline void setAccessible(bool accessible) { m_accessible = accessible; }

                inline float getMinX() const { return (float) m_x - 0.5; }
                inline float getMaxX() const { return (float) m_x + 0.5; }
                inline float getMinY() const { return (float) m_y - 0.5; }
                inline float getMaxY() const { return (float) m_y + 0.5; }

                inline int getX() const { return m_x; }
                inline int getY() const { return m_y; }

                virtual inline void setTile(engine::graphics::Texture* texture) { setTexture(texture); }

                inline const std::vector<entity::Entity*>& getEntities() { return m_entities; }
                inline entity::Entity* getBuilding() const { return m_building; } // does not return a Building* because it would make cyclic dependencies and i am too tired
                inline void setBuilding(entity::Entity* building) { m_building = building; }
                
                inline int getNumEntities() const { return m_entities.size(); }
                int getNumAbstractEntities();

            protected:
                void updatePosition();

                Doodad* m_doodad;
                TopLayer* m_topLayer;

                int m_x;
                int m_y;
                float m_z;

                std::vector<entity::Entity*> m_entities;
                entity::Entity* m_building;

                engine::Vector2d m_texturePosition;

                bool m_accessible;
        };

    }
}

#endif
