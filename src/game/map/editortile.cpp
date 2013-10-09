#include "editortile.h"
#include "editormap.h"
#include "displaymanager.h"
#include "../entity/building.h"
#include "../../engine/graphics/color.h"
#include "../../engine/singleton.h"
#include "../../engine/input/keyboard.h"
#include "../game.h"

namespace game
{
    namespace map
    {

        EditorTile::EditorTile(engine::graphics::Texture* texture, int x, int y, float z) :
            Tile(texture, x, y, z),
            m_tileTexture(texture),
            m_doodadTexture(NULL)
        {

        }

        void EditorTile::show()
        {
            if (!S(Game)->getInterface()->isMouseOver())
            {
                EditorMap* map = (EditorMap*) S(Game)->getMap();
                if (map->usingBrush())
                {
                    float d = getBrushEffect();
                    if (d > 0 && d <= 1)
                        showColored(engine::graphics::Color((1 - d) * 127 + 128, (1 - d) * 127 + 128, (1 - d) * 127 + 128));
                    
                    else
                        Tile::show();
                }
                else if (map->puttingBuilding())
                {
                    engine::Vector2d pointerPosition = map->getPointerPosition();
                    int x = pointerPosition.getRoundX();
                    int y = pointerPosition.getRoundY();
                    entity::BuildingModel* buildingModel = map->getBuildingModel();
                    if (x - buildingModel->getSize() < (int)m_x && (int)m_x <= x && y - buildingModel->getSize() < (int)m_y && (int)m_y <= y)
                    {
                        if (buildingModel->canBeBuilt(map, x, y))
                        {
                            showColored(engine::graphics::Color(128, 128, 128));
                        }
                        else
                        {
                            Tile* tile = map->getTile(x, y);
                            if (!isAccessible() || (tile != NULL && tile->getZ() != getZ()))
                                showColored(engine::graphics::Color(255, 0, 0));
                                
                            else
                                showColored(engine::graphics::Color(128, 128, 128));
                        }
                    }
                    else
                        Tile::show();
                }
                else if (map->puttingUnit())
                {
                    m_color->use();
                    
                    MapObject::show();
                    
                    if (m_doodad != NULL)
                        m_doodad->show();
                }
                else
                    Tile::show();
            }
            else
                Tile::show();
        }
        
        void EditorTile::showColored(engine::graphics::Color color)
        {
            color.use();
            
            MapObject::show();
            
            if (m_doodad != NULL)
                m_doodad->show();
        }

        float EditorTile::getBrushEffect() const
        {
            EditorMap* map = (EditorMap*) S(Game)->getMap();
            engine::Vector2d pointer =  map->getPointerPosition();
            return  map->getBrush()->getEffect(m_x - pointer.getX(), m_y - pointer.getY());
        }

        void EditorTile::setDoodadTexture(engine::graphics::Texture* texture)
        {
            Tile::setDoodadTexture(texture);
            m_doodadTexture = texture;
        }

    }
}
