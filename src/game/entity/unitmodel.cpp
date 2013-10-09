#include "unitmodel.h"
#include "../mod/mod.h"
#include "../../engine/singleton.h"

namespace game
{
    namespace entity
    {

        UnitModel::UnitModel(std::string name, float radius, float speed, float weight, float jumpForce) :
            EntityModel(name, S(Mod)->getResourceFilePath("units/"+name+"/sprite.png"), radius, speed, weight, jumpForce)
        {

        }

    }
}
