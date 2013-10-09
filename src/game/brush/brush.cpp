#include <cmath>
#include <set>
#include "brush.h"

namespace game
{
    namespace brush
    {

        Brush::Brush() :
            m_size(1),
            m_limitWidth(1)
        {

        }

        void Brush::incrementSize()
        {
            m_size += 1;
            if (m_size > MAX_SIZE)
                m_size = MAX_SIZE;
        }

        void Brush::decrementSize()
        {
            m_size -= 1;
            if (m_size < 0)
                m_size = 0;
        }
        
        void Brush::getTiles(map::Map* map, float x, float y, lua_State* L) const
        {
            const int minX = floor(x - m_size);
            const int maxX = ceil(x + m_size);
            const int minY = floor(y - m_size);
            const int maxY = ceil(y + m_size);
            
            lua_createtable(L, (maxX - minX) * (maxY - minY), 0);
            
            for (int tx = minX; tx <= maxX; tx++)
            {
                for (int ty = minY; ty <= maxY; ty++)
                {
                    map::Tile* tile = map->getTile(tx, ty);
                    if (tile != NULL)
                    {
                        float dx = (float) tx - x;
                        float dy = (float) ty - y;
                        
                        float effect = getEffect(dx, dy);
                        if (effect > 0)
                        {
                            lua_pushlightuserdata(L, tile);
                            lua_pushnumber(L, effect);
                            lua_rawset(L, -3);
                        }
                    }
                }
            }
        }
        
        void Brush::getEntities(map::Map* map, float x, float y, float minEffect, const char* modelName, lua_State* L)
        {
            const int minX = floor(x - m_size);
            const int maxX = ceil(x + m_size);
            const int minY = floor(y - m_size);
            const int maxY = ceil(y + m_size);
            
            lua_newtable(L);
            int n = 1;
            
            entity::EntityModel* model = NULL;
            if (modelName != NULL)
                model = entity::EntityModel::getModelByName(modelName);
                
            std::set<entity::Entity*> buildings;
            
            for (int tx = minX; tx <= maxX; tx++)
            {
                for (int ty = minY; ty <= maxY; ty++)
                {
                    map::Tile* tile = map->getTile(tx, ty);
                    if (tile != NULL)
                    {
                        float dx = (float) tx - x;
                        float dy = (float) ty - y;
                        
                        float effect = getEffect(dx, dy);
                        if (effect > minEffect)
                        {
                            const std::vector<entity::Entity*>& entities = tile->getEntities();
                            std::vector<entity::Entity*>::const_iterator end = entities.end();
                            for (std::vector<entity::Entity*>::const_iterator it = entities.begin(); it != end; it++)
                            {
                                if (model == NULL || (*it)->getModel() == model)
                                {
                                    if ((*it)->isBuilding())
                                    {
                                        if (buildings.find(*it) == buildings.end())
                                        {
                                            buildings.insert(*it);
                                            lua_pushlightuserdata(L, *it);
                                            lua_rawseti(L, -2, n);
                                            n++;
                                        }
                                    }
                                    else
                                    {
                                        lua_pushlightuserdata(L, *it);
                                        lua_rawseti(L, -2, n);
                                        n++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

    }
}
