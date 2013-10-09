#include "writer.h"
#include "../editortile.h"
#include "../../mod/mod.h"
#include "../../../engine/singleton.h"

namespace game
{
    namespace map
    {
        namespace io
        {

            Writer::Writer(EditorMap* map) :
                m_map(map),
                m_file(S(Mod)->getFilePath("map.gpmap").c_str(), std::ofstream::binary)
            {

            }

            void Writer::write()
            {
                int mapWidth = m_map->getWidth();
                int mapHeight = m_map->getHeight();
                
                // collecting all types of tiles and doodads
                for (int x = 0; x < mapWidth; x++)
                {
                    for (int y = 0; y < mapHeight; y++)
                    {
                        EditorTile* tile = (EditorTile*) m_map->getTile(x, y);
                        
                        if (tile != NULL)
                        {
                            m_tiles.insert(tile->getTileTexturePath());

                            if (tile->hasDoodad())
                                m_doodads.insert(tile->getDoodadTexturePath());
                        }
                    }
                }
                
                // writing tile types
                int i = 0;
                // number of tile types
                writeUint16(m_tiles.size());
                for (std::set<std::string>::iterator it = m_tiles.begin(); it != m_tiles.end(); it++)
                {
                    // tile path
                    writeString(getRelativePath(S(Mod)->getResourceFilePath("tiles/"), *it));
                    m_tilesIndices[*it] = i;
                    i++;
                }

                // writing doodad types
                i = 0;
                // number of doodad types
                writeUint16(m_doodads.size());
                for (std::set<std::string>::iterator it = m_doodads.begin(); it != m_doodads.end(); it++)
                {
                    // doodad path
                    writeString(getRelativePath(S(Mod)->getResourceFilePath("doodads/"), *it));
                    m_doodadsIndices[*it] = i;
                    i++;
                }

                // writing map
                // map width
                writeUint16(mapWidth);
                // map height
                writeUint16(mapHeight);

                for (int x = 0; x < mapWidth; x++)
                {
                    for (int y = 0; y < mapHeight; y++)
                    {
                        EditorTile* tile = (EditorTile*) m_map->getTile(x, y);
                        if (tile == NULL)
                        {
                            // no tile
                            writeBool(false);
                        }
                        else
                        {
                            // tile exists!
                            writeBool(true);
                            // z
                            writeFloat(tile->getZ());
                            // tile type
                            writeUint16(m_tilesIndices[tile->getTileTexturePath()]);
                            bool hasDoodad = tile->hasDoodad();
                            // has doodad?
                            writeBool(hasDoodad);
                            if (hasDoodad)
                            {
                                // doodad type
                                writeUint16(m_doodadsIndices[tile->getDoodadTexturePath()]);
                            }
                        }
                    }
                }
                
                // collecting all sorts of entities
                for (std::vector<entity::Entity*>::iterator it = m_map->m_entities.begin(); it != m_map->m_entities.end(); it++)
                {
                    entity::EntityModel* model = (*it)->getModel();
                    m_entities.insert(model->getName());
                }
                
                // writing entity models
                i = 0;
                // number of entity models
                writeUint16(m_entities.size());
                for (std::set<std::string>::iterator it = m_entities.begin(); it != m_entities.end(); it++)
                {
                    // entity model name
                    writeString(*it);
                    m_entitiesIndices[*it] = i;
                    i++;
                }
                
                // writing entities
                // number of entities
                writeUint16(m_map->m_entities.size());
                for (std::vector<entity::Entity*>::iterator it = m_map->m_entities.begin(); it != m_map->m_entities.end(); it++)
                {
                    entity::Entity* entity = *it;
                    // entity model
                    writeUint16(m_entitiesIndices[entity->getModel()->getName()]);
                    // x
                    writeFloat(entity->getPosition().getX());
                    // y
                    writeFloat(entity->getPosition().getY());
                }
                
                m_file.close();
            }

            std::string Writer::getRelativePath(std::string root, std::string path)
            {
                int size = root.size();
                int i;
                for (i = 0; root[i] == path[i] && i < size; i++);
                return path.substr(i);
            }

            void Writer::writeBool(bool boolean)
            {
                //std::cout << "bool   " << boolean << std::endl;
                m_file.write((char*) &boolean, sizeof(bool));
            }

            void Writer::writeFloat(float f)
            {
                //std::cout << "float  " << f << std::endl;
                m_file.write((char*) &f, sizeof(float));
            }

            void Writer::writeUint16(Uint16 integer)
            {
                //std::cout << "int    " << integer << std::endl;
                m_file.write((char*) &integer, sizeof(Uint16));
            }

            void Writer::writeString(std::string string)
            {
                writeUint16(string.size());
                //std::cout << "string " << string << std::endl;
                m_file.write(string.c_str(), string.size());
            }

        }
    }
}


