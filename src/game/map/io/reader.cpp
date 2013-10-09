#include "reader.h"
#include "../map.h"
#include "../editormap.h"
#include "../editortile.h"
#include "../../entity/entity.h"
#include "../../entity/unit.h"
#include "../../entity/building.h"
#include "../../entity/entitymodel.h"
#include "../../mod/mod.h"
#include "../../game.h"
#include "../../../engine/singleton.h"

namespace game
{
    namespace map
    {
        namespace io
        {

            Reader::Reader() :
                m_file(S(Mod)->getFilePath("map.gpmap").c_str(), std::ofstream::binary)
            {

            }

            Reader::~Reader()
            {
                delete m_tiles;
                delete m_doodads;
                delete m_models;
            }

            void Reader::readHeaders()
            {
                //std::cout << "Reading map ..." << std::endl;

                //std::cout << "==== tiles ====" << std::endl;

                int numTiles = readUint16();
                m_tiles = new engine::graphics::Texture*[numTiles];
                for (int i = 0; i < numTiles; i++)
                {
                    std::string name = readString();
                    std::string texturePath = S(Mod)->getResourceFilePath("tiles/"+name);
                    m_tiles[i] = S(engine::TextureManager)->get(texturePath);
                }

                //std::cout << "==== doodads ====" << std::endl;

                int numDoodads = readUint16();
                m_doodads = new engine::graphics::Texture*[numDoodads];
                for (int i = 0; i < numDoodads; i++)
                {
                    std::string name = readString();
                    std::string texturePath = S(Mod)->getResourceFilePath("doodads/"+name);
                    m_doodads[i] = S(engine::TextureManager)->get(texturePath);
                }

                //std::cout << "==== size ====" << std::endl;

                m_mapWidth = readUint16();
                m_mapHeight = readUint16();

                //std::cout << "==== map ====" << std::endl;

                m_map->m_width = m_mapWidth;
                m_map->m_height = m_mapHeight;

                m_map->m_tiles = new Tile**[m_mapWidth];
            }
            
            void Reader::readEntities()
            {
                int numModels = readUint16();
                m_models = new entity::EntityModel*[numModels];
                for (int i = 0; i < numModels; i++)
                {
                    std::string modelName = readString();
                    m_models[i] = entity::EntityModel::getModelByName(modelName);
                }
                
                int numEntities = readUint16();
                for (int i = 0; i < numEntities; i++)
                {
                    int modelIndex = readUint16();
                    entity::EntityModel* model = m_models[modelIndex];
                    float x = readFloat();
                    float y = readFloat();
                    
                    entity::Entity* entity;
                    
                    if (model->isUnitModel())
                        entity = new entity::Unit(model, engine::Vector2d(x, y));
                    
                    else
                        entity = new entity::Building(model, engine::Vector2d(x, y));
                        
                    m_map->addEntity(entity);
                }
            }

            bool Reader::readBool()
            {
                bool boolean;
                m_file.read((char*) &boolean, sizeof(bool));
                //std::cout << "bool   " << boolean << std::endl;
                return boolean;
            }

            float Reader::readFloat()
            {
                float f;
                m_file.read((char*) &f, sizeof(float));
                //std::cout << "float  " << f << std::endl;
                return f;
            }

            Uint16 Reader::readUint16()
            {
                Uint16 integer;
                m_file.read((char*) &integer, sizeof(Uint16));
                //std::cout << "int    " << integer << std::endl;
                return integer;
            }

            std::string Reader::readString()
            {
                Uint16 size = readUint16();
                char* s = new char[size + 1];
                m_file.read(s, size);
                s[size] = '\0';
                std::string string = s;
                //std::cout << "string " << string << std::endl;
                delete s;
                return string;
            }

        }
    }
}
