#include <string>
#include "brush.h"
#include "../discbrush.h"
#include "../forestbrush.h"
#include "../peakbrush.h"
#include "../spherebrush.h"
#include "../squarebrush.h"
#include "../../game.h"
#include "../../../engine/singleton.h"

namespace game
{
    namespace brush
    {
        namespace lua
        {
            
            int brushLib(lua_State* L)
            {
                luaL_newmetatable(L, "GP.Brush");

                static const luaL_reg Brush_lib[] = {
                    {"new",            Brush_new},
                    {"getSize",        Brush_getSize},
                    {"setSize",        Brush_setSize},
                    {"growSize",       Brush_growSize},
                    {"getLimitWidth",  Brush_getLimitWidth},
                    {"setLimitWidth",  Brush_setLimitWidth},
                    {"growLimitWidth", Brush_growLimitWidth},
                    {"getTiles",       Brush_getTiles},
                    {"getEntities",    Brush_getEntities},
                    {NULL, NULL}
                };
                luaL_register(L, "Brush", Brush_lib);

                lua_setfield(L, -2, "__index");

                lua_pushcfunction(L, Brush_destroy);
                lua_setfield(L, -2, "__gc");

                return 0;
            }
            
            int Brush_new(lua_State* L)
            {
                std::string type = luaL_checkstring(L, 1);
                
                Brush** brush = (Brush**) lua_newuserdata(L, sizeof(Brush*));
                
                if (type == "disc")
                    *brush = new DiscBrush();
                    
                else if (type == "forest")
                    *brush = new ForestBrush();
                    
                else if (type == "peak")
                    *brush = new PeakBrush();
                    
                else if (type == "sphere")
                    *brush = new SphereBrush();
                    
                else if (type == "square")
                    *brush = new SquareBrush();
                    
                else
                    return luaL_error(L, "unknown brush type %s", type.c_str());

                luaL_getmetatable(L, "GP.Brush");
                lua_setmetatable(L, -2);

                return 1;
            }
            
            int Brush_destroy(lua_State* L)
            {
                Brush* brush = *(Brush**) luaL_checkudata(L, 1, "GP.Brush");
                delete brush;
                return 0;
            }
            
            int Brush_getSize(lua_State* L)
            {
                Brush* brush = *(Brush**) luaL_checkudata(L, 1, "GP.Brush");
                lua_pushnumber(L, brush->getSize());
                return 1;
            }
            
            int Brush_setSize(lua_State* L)
            {
                Brush* brush = *(Brush**) luaL_checkudata(L, 1, "GP.Brush");
                float size = luaL_checknumber(L, 2);
                brush->setSize(size);
                return 0;
            }
            
            int Brush_growSize(lua_State* L)
            {
                Brush* brush = *(Brush**) luaL_checkudata(L, 1, "GP.Brush");
                float sizeGrowth = luaL_checknumber(L, 2);
                brush->growSize(sizeGrowth);
                return 0;
            }
            
            int Brush_getLimitWidth(lua_State* L)
            {
                Brush* brush = *(Brush**) luaL_checkudata(L, 1, "GP.Brush");
                lua_pushnumber(L, brush->getLimitWidth());
                return 1;
            }
            
            int Brush_setLimitWidth(lua_State* L)
            {
                Brush* brush = *(Brush**) luaL_checkudata(L, 1, "GP.Brush");
                float limitWidth = luaL_checknumber(L, 2);
                brush->setLimitWidth(limitWidth);
                return 0;
            }
            
            int Brush_growLimitWidth(lua_State* L)
            {
                Brush* brush = *(Brush**) luaL_checkudata(L, 1, "GP.Brush");
                float limitWidthGrowth = luaL_checknumber(L, 2);
                brush->growLimitWidth(limitWidthGrowth);
                return 0;
            }
            
            int Brush_getTiles(lua_State* L)
            {
                Brush* brush = *(Brush**) luaL_checkudata(L, 1, "GP.Brush");
                float x = luaL_checknumber(L, 2) - 1;
                float y = luaL_checknumber(L, 3) - 1;
                map::Map* map = S(Game)->getMap();
                brush->getTiles(map, x, y, L);
                return 1;
            }
            
            int Brush_getEntities(lua_State* L)
            {
                Brush* brush = *(Brush**) luaL_checkudata(L, 1, "GP.Brush");
                float x = luaL_checknumber(L, 2) - 1;
                float y = luaL_checknumber(L, 3) - 1;
                float minEffect = luaL_checknumber(L, 4);
                const char* modelName = NULL;
                if (lua_isstring(L, 5))
                    modelName = lua_tostring(L, 5);
                    
                map::Map* map = S(Game)->getMap();
                brush->getEntities(map, x, y, minEffect, modelName, L);
                return 1;
            }
            
        }
    }
}


