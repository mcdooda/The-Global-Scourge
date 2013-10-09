#ifndef GAME_ENTITY_UNITMODEL_H
 #define GAME_ENTITY_UNITMODEL_H

#include "entitymodel.h"

namespace game
{
    namespace entity
    {

        class UnitModel : public EntityModel
        {
            public:
                UnitModel(std::string name, float radius, float speed, float weight, float jumpForce);
                
                virtual bool isUnitModel() const { return true; }
                virtual bool isBuildingModel() const { return false; }
                virtual bool isAbstractModel() const { return false; }
        };

    }
}

#endif
