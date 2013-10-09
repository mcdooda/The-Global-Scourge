#ifndef ENGINE_GAME_MAP_DOODAD_H
 #define ENGINE_GAME_MAP_DOODAD_H

#include "../../engine/graphics/texture.h"
#include "tile.h"
#include "mapobject.h"

namespace game
{
    namespace map
    {
        class Tile;

        class Doodad : public MapObject
        {
            public:
                Doodad(engine::graphics::Texture* texture, Tile* tile);
                
                virtual void show();
                
            private:
                Tile* m_tile;
        };

    }
}

#endif

