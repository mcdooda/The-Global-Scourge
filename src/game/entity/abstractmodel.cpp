#include "abstractmodel.h"
#include "../mod/mod.h"
#include "../../engine/singleton.h"

namespace game
{
    namespace entity
    {
        
        AbstractModel::AbstractModel(std::string name) :
            EntityModel(name, S(Mod)->getResourceFilePath("abstracts/"+name+"/sprite.png"), 0, 0, 0, 0)
        {
            
        }
        
    }
}


