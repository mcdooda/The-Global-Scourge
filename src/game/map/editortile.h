#ifndef GAME_MAP_EDITORTILE_H
 #define GAME_MAP_EDITORTILE_H

#include "tile.h"

namespace game
{
    namespace map
    {

        class EditorTile : public Tile
        {
            public:
                EditorTile(engine::graphics::Texture* texture, int x, int y, float z);

                virtual void show();
                void showColored(engine::graphics::Color color);

                float getBrushEffect() const;

                virtual inline void setTile(engine::graphics::Texture* texture) { m_tileTexture = texture; setTexture(texture); }

                virtual void setDoodadTexture(engine::graphics::Texture* texture);

                inline const std::string& getTileTexturePath() const { return m_tileTexture->getPath(); }
                inline const std::string& getDoodadTexturePath() const { return m_doodadTexture->getPath(); }

                inline bool hasDoodad() const { return m_doodadTexture != NULL; }

            private:
                engine::graphics::Texture* m_tileTexture;
                engine::graphics::Texture* m_doodadTexture;
        };

    }
}

#endif
