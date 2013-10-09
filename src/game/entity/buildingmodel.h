#ifndef GAME_ENTITY_BUILDINGMODEL_H
 #define GAME_ENTITY_BUILDINGMODEL_H

#include "entitymodel.h"
#include "../map/map.h"

namespace game
{
    namespace entity
    {

        class BuildingModel : public EntityModel
        {
            public:
                BuildingModel(std::string name);
                
                virtual bool isUnitModel() const { return false; }
                virtual bool isBuildingModel() const { return true; }
                virtual bool isAbstractModel() const { return false; }
                
                inline int getSize() const { return m_size; }
                
                bool canBeBuilt(map::Map* map, int x, int y);

            private:
                int m_size;
        };

    }
}

#endif
