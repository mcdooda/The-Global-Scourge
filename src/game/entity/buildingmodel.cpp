#include "buildingmodel.h"
#include "../game.h"
#include "../mod/mod.h"
#include "../../engine/singleton.h"

namespace game
{
    namespace entity
    {

        BuildingModel::BuildingModel(std::string name) :
            EntityModel(name, S(Mod)->getResourceFilePath("buildings/"+name+"/sprite.png"), 0, 0, 0, 0)
        {
            m_size = (int)((float)getTexture()->getWidth() / S(Mod)->getTileWidth());
        }
        
        bool BuildingModel::canBeBuilt(map::Map* map, int x, int y)
        {
            bool ok = true;
            
            map::Tile* anchorTile = map->getTile(x, y);
            float z = 0;
            
            if (anchorTile != NULL)
                z = anchorTile->getZ();
                
            else
                ok = false;
                
            for (int i = 0; i < m_size && ok; i++)
            {
                for (int j = 0; j < m_size && ok; j++)
                {
                    map::Tile* tile = map->getTile(x - i, y - j);
                    
                    if (tile == NULL)
                        ok = false;
                        
                    else if (tile->getZ() != z || !tile->isAccessible() || (tile->getNumEntities() > 0 && tile->getNumEntities() - tile->getNumAbstractEntities() > 0))
                        ok = false;
                }
            }
            
            return ok;
        }

    }
}


