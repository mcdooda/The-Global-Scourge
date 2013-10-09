#ifndef GAME_MAP_IO_READER_H
 #define GAME_MAP_IO_READER_H

#include <vector>
#include <fstream>
#include "../../../engine/singleton.h"
#include "../../../engine/types.h"
#include "../../../engine/graphics/texture.h"
#include "../../game.h"

namespace game
{
    namespace map
    {
        class Map;

        namespace io
        {

            class Reader
            {
                public:
                    Reader();
                    ~Reader();

                    template <class T> void read()
                    {
                        m_map = S(Game)->getMap();

                        readHeaders();

                        for (int x = 0; x < m_mapWidth; x++)
                        {
                            m_map->m_tiles[x] = new Tile*[m_mapHeight];
                            for (int y = 0; y < m_mapHeight; y++)
                            {
                                // tile exists?
                                bool exists = readBool();
                                if (!exists)
                                {
                                    m_map->m_tiles[x][y] = NULL;
                                }
                                else
                                {
                                    //std::cout << "----" << std::endl;
                                    float z = readFloat();
                                    Uint16 tileIndex = readUint16();
                                    engine::graphics::Texture* texture = m_tiles[tileIndex];
                                    m_map->m_tiles[x][y] = new T(texture, x, y, z);
                                    bool hasDoodad = readBool();
                                    if (hasDoodad)
                                    {
                                        Uint16 doodadIndex = readUint16();
                                        engine::graphics::Texture* texture = m_doodads[doodadIndex];
                                        m_map->m_tiles[x][y]->setDoodadTexture(texture);
                                    }
                                }
                            }
                        }
                        
                        readEntities();
                    }

                private:
                    void readHeaders();
                    void readEntities();

                    bool readBool();
                    float readFloat();
                    Uint16 readUint16();
                    std::string readString();

                    Map* m_map;
                    int m_mapWidth;
                    int m_mapHeight;
                    std::ifstream m_file;

                    engine::graphics::Texture** m_tiles;
                    engine::graphics::Texture** m_doodads;
                    entity::EntityModel** m_models;
            };

        }
    }
}

#endif
