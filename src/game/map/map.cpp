#include <iostream>
#include <cmath>
#include <algorithm>
#include "map.h"
#include "displaymanager.h"
#include "../entity/buildingmodel.h"
#include "../entity/building.h"
#include "../entity/unitmodel.h"
#include "../entity/unit.h"
#include "../game.h"
#include "../../engine/time.h"
#include "../../engine/input/keyboard.h"
#include "../../engine/input/mouse.h"
#include "../../engine/random.h"
#include "../../engine/graphics/texturegroup.h"
#include "../../engine/graphics/window.h"
#include "../../engine/time.h"
#include "../../engine/singleton.h"
#include "../mod/mod.h"

namespace game
{
    namespace map
    {

        Map::Map()
        {
            m_ghostModel = NULL;
            m_onBuild = LUA_NOREF;
            m_onGhostModelClear = LUA_NOREF;
            m_overlay = NULL;
        }

        Map::~Map()
        {
            for (int x = 0; x < m_width; x++)
            {
                for (int y = 0; y < m_height; y++)
                    delete m_tiles[x][y];

                delete m_tiles[x];
            }
            delete m_tiles;
            
            for (std::vector<entity::Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); it++)
                delete *it;
                
            for (std::vector<ai::Squad*>::iterator it = m_squads.begin(); it != m_squads.end(); it++)
                delete *it;
                
            disableOverlay();
        }

        void Map::calcPointerPosition()
        {
            m_pointerPosition = getMapPosition(engine::Vector2d(engine::input::mouse::getViewX(), engine::input::mouse::getViewY()));
        }
        
        void Map::showTemporaries()
        {
            if (m_ghostModel != NULL && S(Game)->getSelection()->getNumInsideEntities() == 0 && !S(Game)->getInterface()->isMouseOver())
            {
                if (m_ghostModel->isBuildingModel())
                {
                    engine::Vector2d pointerPosition = getPointerPosition();
                    int x = pointerPosition.getRoundX();
                    int y = pointerPosition.getRoundY();
                    if (((entity::BuildingModel*)m_ghostModel)->canBeBuilt(this, x, y))
                    {
                        pointerPosition.setX(x);
                        pointerPosition.setY(y);
                        entity::Building* building = new entity::Building(m_ghostModel, pointerPosition);
                        building->setColor(new engine::graphics::ColorAlpha(255, 255, 255, 128));
                        building->setZ(getTile(x, y)->getZ());
                        displaymanager::addTemporary(building);
                        
                        if (engine::input::mouse::isJustReleased(M(LEFT)))
                        {
                            triggerBuildListener(building);
                            if (!engine::input::keyboard::isPressed(K(LSHIFT)))
                                clearGhostModel();
                        }
                    }
                }
                else if (m_ghostModel->isUnitModel())
                {
                    engine::Vector2d pointerPosition = getPointerPosition();
                    int x = pointerPosition.getRoundX();
                    int y = pointerPosition.getRoundY();
                    Tile* tile = getTile(x, y);
                    if (tile != NULL && tile->isAccessible())
                    {
                        entity::Unit* unit = new entity::Unit(m_ghostModel, pointerPosition);
                        unit->setColor(new engine::graphics::ColorAlpha(255, 255, 255, 128));
                        unit->setZ(tile->getZ());
                        displaymanager::addTemporary(unit);
                        
                        if (engine::input::mouse::isJustReleased(M(LEFT)))
                        {
                            triggerBuildListener(unit);
                            if (!engine::input::keyboard::isPressed(K(LSHIFT)))
                                clearGhostModel();
                        }
                    }
                }
                else // abstract
                {
                
                }
            }
        }

        void Map::show()
        {
            displaymanager::clearAll();

            const engine::graphics::View& view = engine::graphics::window::getView();

            engine::Vector2d topLeft = engine::Vector2d(view.getLeft(), view.getTop());
            //engine::Vector2d bottomLeft = engine::Vector2d(view.getLeft(), view.getBottom());

            //engine::Vector2d mapBottomLeft  = getMapPosition(bottomLeft);
            engine::Vector2d mapTopLeft     = getMapPosition(topLeft);

            const int margin = 5;
            
            int tileWidth = S(Mod)->getTileWidth();
            int tileHeight = S(Mod)->getTileHeight();

            int numTilesX = view.getWidth() / tileWidth + 2;
            int numTilesY = view.getHeight() / tileHeight + margin * 2;

            int x = mapTopLeft.getRoundX() - margin;
            int y = mapTopLeft.getRoundY() - margin - 1;

            for (int j = 0; j < numTilesY; j++)
            {
                int x2 = x;
                int y2 = y;
                for (int i = 0; i < numTilesX; i++)
                {
                    Tile* tile = getTile(x2, y2);
                    if (tile != NULL)
                    {
                        if (displaymanager::add(tile) && tile->getDoodad() != NULL)
                            displaymanager::add(tile->getDoodad());
                            
                        tile->showEntities();
                    }

                    x2--;
                    y2++;
                }

                y++;

                x2 = x;
                y2 = y;
                for (int i = 0; i < numTilesX; i++)
                {
                    Tile* tile = getTile(x2, y2);
                    if (tile != NULL)
                    {
                        if (displaymanager::add(tile) && tile->getDoodad() != NULL)
                            displaymanager::add(tile->getDoodad());
                            
                        tile->showEntities();
                    }

                    x2--;
                    y2++;
                }

                x++;
            }
            
            showTemporaries();

            displaymanager::showAll();
            
            if (m_overlay != NULL && !m_overlay->isHidden())
            {
                m_overlay->resize();
                m_overlay->show();
            }
            
            engine::graphics::Color::WHITE.use();
        }

        void Map::addEntity(int x, int y, entity::Entity* entity)
        {
            m_tiles[x][y]->addEntity(entity);
            entity->addedToMap(this, x, y);
        }

        void Map::removeEntity(int x, int y, entity::Entity* entity)
        {
            m_tiles[x][y]->removeEntity(entity);
            entity->removedFromMap(this, x, y);
        }
        
        void Map::moveEntity(int x, int y, int newX, int newY, entity::Entity* entity)
        {
            m_tiles[x][y]->removeEntity(entity);
            m_tiles[newX][newY]->addEntity(entity);
        }

        void Map::addEntity(entity::Entity* entity)
        {
            m_entities.push_back(entity);
            int tileX = entity->getTileX();
            int tileY = entity->getTileY();
            addEntity(tileX, tileY, entity);
            entity->setZ(m_tiles[tileX][tileY]->getZ());
        }

        void Map::removeEntity(entity::Entity* entity)
        {
            //std::remove(m_entities.begin(), m_entities.end(), entity);
            
            std::vector<entity::Entity*>::iterator end = m_entities.end();
            std::vector<entity::Entity*>::iterator it = find(m_entities.begin(), end, entity);
            if (it != end)
                m_entities.erase(it);
            
            removeEntity(entity->getTileX(), entity->getTileY(), entity);
        }

        map::Tile* Map::getTile(int x, int y)
        {
            if (x < 0 || x >= m_width || y < 0 || y >= m_height)
                return NULL;

            return m_tiles[x][y];
        }

        engine::Vector2d Map::getMapPosition(engine::Vector2d screenPosition) const
        {
            engine::Vector2d mapPosition;
            float x = screenPosition.getX();
            float y = screenPosition.getY();
            
            int tileWidthQuartered = S(Mod)->getTileWidth() / 4;

            mapPosition.setX((x + 2 * y) / -4 / tileWidthQuartered);
            mapPosition.setY((x - 2 * y) / 4  / tileWidthQuartered);

            return mapPosition;
        }

        engine::Vector2d Map::getPointerPosition() const
        {
            return m_pointerPosition;
        }

        void Map::moveEntities()
        {
            float frameTime = engine::time::getFrameTime();
            std::vector<entity::Entity*>::iterator end = m_entities.end();
            for (std::vector<entity::Entity*>::iterator it = m_entities.begin(); it != end; it++)
                (*it)->move(frameTime);
        }
        
        void Map::clearGhostModel()
        {
            if (m_ghostModel != NULL)
            {
                m_ghostModel = NULL;
                triggerGhostModelClearListener();
            }
        }
        
        void Map::setGhostModelClearListener(lua_State* L)
        {
            if (m_onGhostModelClear != LUA_NOREF)
            {
                lua_State* L = lua::getState();
                luaL_unref(L, LUA_REGISTRYINDEX, m_onGhostModelClear);
                m_onGhostModelClear = LUA_NOREF;
            }
            if (!lua_isnil(L, 1))
            {
                luaL_checktype(L, 1, LUA_TFUNCTION);
                m_onGhostModelClear = luaL_ref(L, LUA_REGISTRYINDEX);
            }
        }
        
        void Map::triggerGhostModelClearListener()
        {
            if (m_onGhostModelClear != LUA_NOREF)
            {
                lua_State* L = lua::getState();
                lua_rawgeti(L, LUA_REGISTRYINDEX, m_onGhostModelClear);
                lua_call(L, 0, 0);
            }
        }
        
        void Map::setBuildListener(lua_State* L)
        {
            if (m_onBuild != LUA_NOREF)
            {
                luaL_unref(L, LUA_REGISTRYINDEX, m_onBuild);
                m_onBuild = LUA_NOREF;
            }
            if (!lua_isnil(L, 1))
            {
                luaL_checktype(L, 1, LUA_TFUNCTION);
                m_onBuild = luaL_ref(L, LUA_REGISTRYINDEX);
            }
        }
        
        void Map::triggerBuildListener(entity::Entity* entity)
        {
            if (m_onBuild != LUA_NOREF)
            {
                lua_State* L = lua::getState();
                lua_rawgeti(L, LUA_REGISTRYINDEX, m_onBuild);
                lua_pushlightuserdata(L, m_ghostModel);
                lua_pushnumber(L, entity->getCenterX() + 1);
                lua_pushnumber(L, entity->getCenterY() + 1);
                lua_call(L, 3, 0);
            }
        }
        
        void Map::enableOverlay()
        {
            disableOverlay();
            m_overlay = new interface::MapOverlay();
        }
        
        void Map::disableOverlay()
        {
            if (m_overlay != NULL)
            {
                delete m_overlay;
                m_overlay = NULL;
            }
        }
        
    }
}
