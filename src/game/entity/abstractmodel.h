#ifndef GAME_ENTITY_ABSTRACTMODEL_H
 #define GAME_ENTITY_ABSTRACTMODEL_H

#include "entitymodel.h"

namespace game
{
    namespace entity
    {
    
        class AbstractModel : EntityModel
        {
            public:
                AbstractModel(std::string name);
                
                virtual bool isUnitModel() const { return false; }
                virtual bool isBuildingModel() const { return false; }
                virtual bool isAbstractModel() const { return true; }
        };
    
    }
}

#endif


