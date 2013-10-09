#ifndef GAME_MAP_TOPLAYER_H
 #define GAME_MAP_TOPLAYER_H

#include "../../engine/graphics/texture.h"
#include "tile.h"
#include "mapobject.h"

namespace game
{
    namespace map
    {
        class Tile;

        class TopLayer : public MapObject
        {
            public:
                TopLayer(engine::graphics::Texture* texture, Tile* tile);
                
                virtual void show();
                
                inline void setYShift(float yShift) { m_yShift = yShift; updateCenter(); }
                
            private:
                void updateCenter();
                
                Tile* m_tile;
                float m_yShift;
                int m_textureHalfWidth;
                int m_textureThreeQuartersHeight;
        };

    }
}

#endif

