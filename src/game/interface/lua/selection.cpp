#include "selection.h"
#include "../selection.h"
#include "../../entity/entity.h"
#include "../../game.h"
#include "../../../engine/singleton.h"

namespace game
{
    namespace interface
    {
        namespace lua
        {

            int selectionLib(lua_State* L)
            {
                static const luaL_reg Selection_lib[] = {
                    {"getEntities", Selection_getEntities},
                    {"onChange",    Selection_onChange},
                    {NULL, NULL}
                };
                luaL_register(L, "Selection", Selection_lib);

                return 0;
            }

            int Selection_getEntities(lua_State* L)
            {
                Selection* selection = S(Game)->getSelection();
                int numSelectedEntities;
                entity::Entity** selectedEntities = selection->getEntities(&numSelectedEntities);
                lua_createtable(L, numSelectedEntities, 0);
                for (int i = 0; i < numSelectedEntities; i++)
                {
                    lua_pushlightuserdata(L, selectedEntities[i]);
                    lua_rawseti(L, -2, i + 1);
                }
                return 1;
            }
            
            int Selection_onChange(lua_State* L)
            {
                Selection* selection = S(Game)->getSelection();
                selection->setChangeListener(L);
                return 0;
            }
            
        }
    }
}
