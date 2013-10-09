#include <cstdlib>
#include <algorithm>
#include "tile.h"
#include "displaymanager.h"
#include "../mod/mod.h"
#include "../game.h"
#include "../../engine/graphics/window.h"
#include "../../engine/graphics/texturedshowable.h"
#include "../../engine/input/mouse.h"
#include "../../engine/singleton.h"

namespace game
{
    namespace map
    {

        Tile::Tile(engine::graphics::Texture* texture, int x, int y, float z)
        {
            resetTextureCoords();
            m_doodad = NULL;
            m_topLayer = NULL;
            m_x = x;
            m_y = y;
            m_z = z;
            m_accessible = true;
            m_building = NULL;
            calcDepth(x, y, 0);
            int textureWidthQuartered = S(Mod)->getTileWidth() / 4;
            m_texturePosition = (engine::Vector2d(-2, -1) * m_x + engine::Vector2d(2, -1) * m_y) * textureWidthQuartered;
            setCenter(engine::Vector2d(texture->getWidth() / 2, texture->getHeight() - textureWidthQuartered));
            setDimensions(texture->getDimensions());
            updatePosition();
            setTexture(texture);
        }

        Tile::~Tile()
        {
            if (m_doodad != NULL)
                delete m_doodad;
                
            if (m_topLayer != NULL)
                delete m_topLayer;
        }

        void Tile::setZ(float z)
        {
            m_z = z;
            updatePosition();
            entity::Entity* building = getBuilding();
            if (building != NULL && m_x == building->getX() && m_y == building->getY())
                building->setZ(z);
        }

        void Tile::show()
        {
            m_color->use();

            MapObject::show();
            
            if (m_topLayer != NULL)
                m_topLayer->show();
        }

        void Tile::showEntities()
        {
            interface::Selection* selection = S(Game)->getSelection();
            engine::Vector2d viewPosition = engine::graphics::window::getView().getCenter() - engine::Vector2d(engine::graphics::window::getWidth() / 2, engine::graphics::window::getHeight() / 2);

            std::vector<entity::Entity*>::iterator end = m_entities.end();
            for (std::vector<entity::Entity*>::iterator it = m_entities.begin(); it != end; it++)
            {
                entity::Entity* entity = *it;

                // we do not want to show the same building for each tile it is on
                if (entity->isBuilding() && (entity->getTileX() != m_x || entity->getTileY() != m_y))
                    continue;
                
                if (displaymanager::add(entity) && entity->isSelectable())
                {
                    if (!S(Game)->getInterface()->isMouseOver() && (!selection->isSelecting() || selection->isAreaEmpty()))
                    {
                        int mouseX = engine::input::mouse::getX();
                        int mouseY = engine::input::mouse::getY();
                        
                        engine::Vector2d topLeft = entity->engine::graphics::TexturedShowable::getAbsolutePosition() - viewPosition;
                        engine::Vector2d bottomRight = topLeft + entity->getDimensions();

                        if (topLeft.getX() < mouseX && mouseX < bottomRight.getX() && topLeft.getY() < mouseY && mouseY < bottomRight.getY())
                        {
                            int x = mouseX - topLeft.getX();
                            int y = mouseY - topLeft.getY();
                            if (entity->getPixel(x, y).getA() > 128)
                            {
                                selection->clearInside();
                                selection->addInside(entity);
                            }
                        }
                    }
                    else if (selection->isSelecting())
                    {
                        engine::Vector2d screenPosition = entity->engine::graphics::TexturedShowable::getAbsolutePosition() - viewPosition + entity->getDimensions() / 2;
                        if (selection->isInside(screenPosition))
                            selection->addInside(entity);
                    }
                }
            }
        }

        void Tile::setDoodadTexture(engine::graphics::Texture* texture)
        {
            if (m_doodad != NULL)
                delete m_doodad;

            if (texture != NULL)
            {
                m_doodad = new Doodad(texture, this);
                m_accessible = false;
            }
            else
            {
                m_doodad = NULL;
                m_accessible = true;
            }
        }
        
        void Tile::setTopLayerTexture(engine::graphics::Texture* texture)
        {
            if (m_topLayer != NULL)
                delete m_topLayer;

            if (texture != NULL)
                m_topLayer = new TopLayer(texture, this);
            
            else
                m_topLayer = NULL;
        }

        void Tile::addEntity(entity::Entity* entity)
        {
            m_entities.push_back(entity);
            //entity->setZ(m_z);
            if (entity->isBuilding())
                m_building = entity;
        }

        void Tile::removeEntity(entity::Entity* entity)
        {
            //std::remove(m_entities.begin(), m_entities.end(), entity);
            std::vector<entity::Entity*>::iterator end = m_entities.end();
            std::vector<entity::Entity*>::iterator it = find(m_entities.begin(), end, entity);
            if (it != end)
            {
                m_entities.erase(it);
                if (entity->isBuilding())
                    m_building = NULL;
            }
        }
        
        int Tile::getNumAbstractEntities()
        {
            int numAbstractEntities = 0;
            std::vector<entity::Entity*>::iterator end = m_entities.end();
            for (std::vector<entity::Entity*>::iterator it = m_entities.begin(); it != end; it++)
                if ((*it)->isAbstract())
                    numAbstractEntities++;
                    
            return numAbstractEntities;
        }

        void Tile::updatePosition()
        {
            engine::Vector2d position = m_texturePosition + engine::Vector2d(0, 1) * m_z * S(Mod)->getTileWidth() / 4;
            setPosition(position);

            if (m_doodad != NULL)
                m_doodad->setPosition(position);
                
            if (m_topLayer != NULL)
                m_topLayer->setPosition(position);
        }

    }
}

