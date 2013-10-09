#include <iostream>
#include "building.h"
#include "buildingmodel.h"
#include "buildingselection.h"
#include "../mod/mod.h"
#include "../game.h"
#include "../../engine/singleton.h"

namespace game
{
    namespace entity
    {

        Building::Building(EntityModel* model, engine::Vector2d position) :
            Entity(model, position)
        {
            setCenter(engine::Vector2d(m_model->getTexture()->getWidth() / 2, S(Mod)->getTileHeight() / 2));
            updateVertices();
            m_active = false;
            m_onTheFloor = true;
            int size = ((BuildingModel*) m_model)->getSize();
            m_selectionImage = new BuildingSelection(S(engine::TextureManager)->get(S(Mod)->getResourceFilePath("interface/selectionbuilding.png")), size);
            m_selectedImage = new BuildingSelection(S(engine::TextureManager)->get(S(Mod)->getResourceFilePath("interface/selectedbuilding.png")), size);
        }
        
        float Building::getCenterX()
        {
            return m_position.getX() - (float)(((BuildingModel*) m_model)->getSize() - 1) / 2;
        }
        
        float Building::getCenterY()
        {
            return m_position.getY() - (float)(((BuildingModel*) m_model)->getSize() - 1) / 2;
        }
        
        engine::Vector2d Building::getCenter()
        {
            float radius = (float)(((BuildingModel*) m_model)->getSize() - 1) / 2;
            return m_position - engine::Vector2d(radius, radius);
        }

        void Building::addedToMap(map::Map* map, int x, int y)
        {
            int size = ((BuildingModel*) m_model)->getSize();
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    map::Tile* tile = map->getTile(x - i, y - j);
                    tile->setAccessible(false);
                    if (!(i == 0 && j == 0))
                        tile->addEntity(this);
                }
            }
        }

        void Building::removedFromMap(map::Map* map, int x, int y)
        {
            int size = ((BuildingModel*) m_model)->getSize();
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    map::Tile* tile = map->getTile(x - i, y - j);
                    tile->setAccessible(true);
                    if (!(i == 0 && j == 0))
                        tile->removeEntity(this);
                }
            }
        }
        
        std::vector<map::Tile*> Building::getTiles(map::Map* map)
        {
            int size = ((BuildingModel*) m_model)->getSize();
            std::vector<map::Tile*> tiles;
            int x = m_position.getRoundX();
            int y = m_position.getRoundY();
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    map::Tile* tile = map->getTile(x - i, y - j);
                    tiles.push_back(tile);
                }
            }
            return tiles;
        }
        
        void Building::calcDepth(float x, float y, float radius)
        {
            // see also Doodad::calcDepth
            int size = ((BuildingModel*) m_model)->getSize();
            static const float min = 0.0001;
            static const int maxSize = 3;
            setDepth(x + y + radius + min * maxSize - min * size);
        }

    }
}
