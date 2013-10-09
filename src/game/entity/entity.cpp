#include <iostream>
#include <cmath>
#include "entity.h"
#include "../mod/mod.h"
#include "../game.h"
#include "../../engine/singleton.h"
#include "../../engine/graphics/color.h"

// the unit does not jump if the altitude difference is lower than this
#define JUMP_UP_Z_THRESHOLD 0.4
#define JUMP_DOWN_Z_THRESHOLD 0.7

namespace game
{
    namespace entity
    {

        Entity::Entity(EntityModel* model, engine::Vector2d position) :
            m_position(position)
        {
            resetTextureCoords();
            m_model = model;
            engine::graphics::Texture* texture = m_model->getTexture();
            setCenter(engine::Vector2d(texture->getWidth() / 2, m_model->getRadius() * S(Mod)->getTileHeight() / 2));
            setDimensions(texture->getDimensions());
            setTexture(texture);
            updatePosition();
            setDirection(0);
            m_insideOfSelection = false;
            m_selected = false;
            m_onTheFloor = false;
            m_zSpeed = 0;
            setActive(true);
            m_selectedImage = NULL;
            m_selectionImage = NULL;
            m_overlay = NULL;
            m_onTileChange = LUA_NOREF;
        }
        
        Entity::~Entity()
        {
            if (m_insideOfSelection)
                S(Game)->getSelection()->removeInside(this);
            
            if (m_selected)
                S(Game)->getSelection()->unselectEntity(this);
            
            delete m_selectionImage;
            delete m_selectedImage;
            
            disableOverlay();
            
            if (m_onTileChange != LUA_NOREF)
            {
                lua_State* L = lua::getState();
                luaL_unref(L, LUA_REGISTRYINDEX, m_onTileChange);
            }
        }

        void Entity::show()
        {
            if (m_insideOfSelection)
            {
                engine::graphics::Color::WHITE.use();
                m_selectionImage->setPosition(engine::graphics::TexturedShowable::getPosition());
                m_selectionImage->show();
            }
            else if (m_selected)
            {
                engine::graphics::Color::WHITE.use();
                m_selectedImage->setPosition(engine::graphics::TexturedShowable::getPosition());
                m_selectedImage->show();
            }

            m_color->use();
            map::MapObject::show();
            
            if (m_overlay != NULL && !m_overlay->isHidden())
            {
                m_overlay->engine::graphics::TexturedShowable::setPosition(getAbsolutePosition());
                m_overlay->resize();
                m_overlay->show();
            }
        }

        void Entity::clearPath()
        {
            m_path.clear();
            setActive(false);
        }

        void Entity::addPath(engine::Vector2d point)
        {
            if (m_path.empty())
                setDirection((point - m_position).angle());

            m_path.push_back(point);
            setActive(true);
        }

        void Entity::findPath(engine::Vector2d point)
        {

        }

        void Entity::move(float frameTime)
        {
            if (isActive())
            {
                followPath(frameTime);

                bool b1 = isMoving();
                bool b2 = fall(frameTime);
                bool b3 = separate();
                bool b4 = separateTile();

                if (!b1 && !b2 && !b3 && !b4)
                    setActive(false);
            }
        }

        bool Entity::separate()
        {
            bool moved = false;
            float radius = m_model->getRadius();
            std::vector<Entity*> neighbors = getNeighbors(radius + 1);
            std::vector<Entity*>::iterator end = neighbors.end();
            for (std::vector<Entity*>::iterator it = neighbors.begin(); it != end; it++)
            {
                Entity* entity = *it;
                if (!entity->isAbstract() && m_onTheFloor == entity->m_onTheFloor)
                {
                    float radiusSum = radius + entity->m_model->getRadius();
                    engine::Vector2d diff = m_position - entity->m_position;
                    if (diff.distanceSquared() < radiusSum * radiusSum)
                    {
                        float distance = diff.distance() - radiusSum;
                        engine::Vector2d separation = diff.normalize() * distance / 2;

                        if (separation.distanceSquared() > 0.001)
                        {
                            //engine::Vector2d initialPosition = getPosition();
                            //engine::Vector2d entityInitialPosition = entity->getPosition();

                            if (isMoving() == entity->isMoving())
                            {
                                setEntityPosition(m_position - separation);
                                entity->setEntityPosition(entity->m_position + separation);
                            }
                            else if (entity->isMoving())
                            {
                                setEntityPosition(m_position - separation * 2);
                            }
                            else if (isMoving())
                            {
                                entity->setEntityPosition(entity->m_position - separation * 2);
                            }

                            if (isMoving())
                                setDirection((*m_path.begin() - m_position).angle());

                            if (entity->isMoving())
                                entity->setDirection((*entity->m_path.begin() - entity->m_position).angle());

                            moved = true;
                            entity->setActive(true);

                            if (entity->m_z != entity->getTile()->getZ())
                                entity->m_onTheFloor = false;
                        }
                    }
                }
            }
            return moved;
        }

        bool Entity::separateTile()
        {
            map::Tile* tile = getTile();
            bool moved = false;
            float radius = m_model->getRadius();

            engine::Vector2d position = m_position;

            float maxZ = m_z + JUMP_UP_Z_THRESHOLD;

            if (!tile->isAccessible())
                moved = true;

            else
            {
                int tileX = tile->getX();
                int tileY = tile->getY();

                float x = m_position.getX();
                float y = m_position.getY();

                game::map::Map* map = S(Game)->getMap();

                if (x - tile->getMinX() < radius) // top right
                {
                    map::Tile* tile2 = map->getTile(tileX - 1, tileY);
                    if (tile2 == NULL || !tile2->isAccessible() || tile2->getZ() > maxZ)
                    {
                        //std::cout << "separating from top right tile" << std::endl;
                        moved = true;
                        position.setX(tile->getMinX() + radius);
                    }
                }
                else if (tile->getMaxX() - x < radius) // bottom left
                {
                    map::Tile* tile2 = map->getTile(tileX + 1, tileY);
                    if (tile2 == NULL || !tile2->isAccessible() || tile2->getZ() > maxZ)
                    {
                        //std::cout << "separating from bottom left tile" << std::endl;
                        moved = true;
                        position.setX(tile->getMaxX() - radius);
                    }
                }

                if (y - tile->getMinY() < radius) // top left
                {
                    map::Tile* tile2 = map->getTile(tileX, tileY - 1);
                    if (tile2 == NULL || !tile2->isAccessible() || tile2->getZ() > maxZ)
                    {
                        //std::cout << "separating from top left tile" << std::endl;
                        moved = true;
                        position.setY(tile->getMinY() + radius);
                    }
                }
                else if (tile->getMaxY() - y < radius) // bottom right
                {
                    map::Tile* tile2 = map->getTile(tileX, tileY + 1);
                    if (tile2 == NULL || !tile2->isAccessible() || tile2->getZ() > maxZ)
                    {
                        //std::cout << "separating from bottom right tile" << std::endl;
                        moved = true;
                        position.setY(tile->getMaxY() - radius);
                    }
                }

                if (!moved)
                {
                    if ((x - tile->getMinX()) * (x - tile->getMinX()) + (y - tile->getMinY()) * (y - tile->getMinY()) < radius * radius) // top (-1,-1)
                    {
                        map::Tile* tile2 = map->getTile(tileX - 1, tileY - 1);
                        if (tile2 == NULL || !tile2->isAccessible() || tile2->getZ() > maxZ)
                        {
                            //std::cout << "separating from top tile" << std::endl;
                            moved = true;
                            engine::Vector2d corner = engine::Vector2d(tile->getMinX(), tile->getMinY());
                            engine::Vector2d diff = m_position - corner;
                            diff = diff.normalize() * radius;
                            position = corner + diff;
                        }
                    }
                    else if ((tile->getMaxX() - x) * (tile->getMaxX() - x) + (tile->getMaxY() - y) * (tile->getMaxY() - y) < radius * radius) // bottom (+1,+1)
                    {
                        map::Tile* tile2 = map->getTile(tileX + 1, tileY + 1);
                        if (tile2 == NULL || !tile2->isAccessible() || tile2->getZ() > maxZ)
                        {
                            //std::cout << "separating from bottom tile" << std::endl;
                            moved = true;
                            engine::Vector2d corner = engine::Vector2d(tile->getMaxX(), tile->getMaxY());
                            engine::Vector2d diff = m_position - corner;
                            diff = diff.normalize() * radius;
                            position = corner + diff;
                        }
                    }
                    else if ((x - tile->getMinX()) * (x - tile->getMinX()) + (tile->getMaxY() - y) * (tile->getMaxY() - y) < radius * radius) // right (-1,+1)
                    {
                        map::Tile* tile2 = map->getTile(tileX - 1, tileY + 1);
                        if (tile2 == NULL || !tile2->isAccessible() || tile2->getZ() > maxZ)
                        {
                            //std::cout << "separating from right tile" << std::endl;
                            moved = true;
                            engine::Vector2d corner = engine::Vector2d(tile->getMinX(), tile->getMaxY());
                            engine::Vector2d diff = m_position - corner;
                            diff = diff.normalize() * radius;
                            position = corner + diff;
                        }
                    }
                    else if ((tile->getMaxX() - x) * (tile->getMaxX() - x) + (y - tile->getMinY()) * (y - tile->getMinY()) < radius * radius) // left (+1,-1)
                    {
                        map::Tile* tile2 = map->getTile(tileX + 1, tileY - 1);
                        if (tile2 == NULL || !tile2->isAccessible() || tile2->getZ() > maxZ)
                        {
                            //std::cout << "separating from left tile" << std::endl;
                            moved = true;
                            engine::Vector2d corner = engine::Vector2d(tile->getMaxX(), tile->getMinY());
                            engine::Vector2d diff = m_position - corner;
                            diff = diff.normalize() * radius;
                            position = corner + diff;
                        }
                    }
                }

                if (moved)
                {
                    setEntityPosition(position);
                    if (isMoving())
                        setDirection((*m_path.begin() - m_position).angle());
                }
            }

            return moved;
        }

        std::vector<Entity*> Entity::getNeighbors(float radius)
        {
            int tileX = getTileX();
            int tileY = getTileY();

            map::Map* map = S(Game)->getMap();

            int tileMinX = ceil(tileX - radius);
            if (tileMinX < 0)
                tileMinX = 0;

            int tileMaxX = floor(tileX + radius);
            if (tileMaxX > map->getWidth() - 1)
                tileMaxX = map->getWidth() - 1;

            int tileMinY = ceil(tileY - radius);
            if (tileMinY < 0)
                tileMinY = 0;

            int tileMaxY = floor(tileY + radius);
            if (tileMaxY > map->getHeight() - 1)
                tileMaxY = map->getHeight() - 1;

            float radiusSquared = radius * radius;
            std::vector<Entity*> neighbors;
            for (int x = tileMinX; x <= tileMaxX; x++)
            {
                for (int y = tileMinY; y <= tileMaxY; y++)
                {
                    map::Tile* tile = map->getTile(x, y);
                    if (tile != NULL && tile->isAccessible())
                    {
                        const std::vector<Entity*>& tileEntities = tile->getEntities();
                        std::vector<Entity*>::const_iterator end = tileEntities.end();
                        for (std::vector<Entity*>::const_iterator it = tileEntities.begin(); it != end; it++)
                        {
                            if ((m_position - (*it)->m_position).distanceSquared() <= radiusSquared)
                                neighbors.push_back(*it);
                        }
                    }
                }
            }

            return neighbors;
        }

        void Entity::followPath(float frameTime)
        {
            if (isMoving())
            {
                setEntityPosition(m_position + m_speed * frameTime);

                if (m_onTheFloor)
                {
                    map::Tile* futureTile = getFutureTile(m_model->getHalfJumpDuration());
                    if (futureTile != NULL)
                    {
                        if (futureTile->getZ() > m_z + JUMP_UP_Z_THRESHOLD && futureTile->getZ() < m_z + m_model->getJumpAltitude())
                            jump(1);

                        else if (futureTile->getZ() < m_z - JUMP_DOWN_Z_THRESHOLD)
                            jump(0.5);
                    }
                }

                if ((*m_path.begin() - m_position).distanceSquared() < 0.25)
                {
                    m_path.erase(m_path.begin());
                    if (isMoving())
                        setDirection((*m_path.begin() - m_position).angle());
                }
            }
        }

        void Entity::setEntityPosition(engine::Vector2d position)
        {
            map::Map* map = S(Game)->getMap();

            if (position.getX() < 0)
                position.setX(0);
            else if (position.getX() > map->getWidth() - 1)
                position.setX(map->getWidth() - 1);

            if (position.getY() < 0)
                position.setY(0);
            else if (position.getY() > map->getHeight() - 1)
                position.setY(map->getHeight() - 1);

            int tileX = getTileX();
            int tileY = getTileY();

            int newTileX = position.getRoundX();
            int newTileY = position.getRoundY();

            map::Tile* newTile = map->getTile(newTileX, newTileY);

            if (newTile == NULL || newTile->getZ() > m_z + JUMP_UP_Z_THRESHOLD || (!newTile->isAccessible() && !isAbstract()))
                return;

            m_position = position;
            updatePosition();

            if (tileX != newTileX || tileY != newTileY)
            {
                map->moveEntity(tileX, tileY, newTileX, newTileY, this);
                triggerTileChangeListener();
            }
        }

        engine::Vector2d Entity::getFuturePosition(float time)
        {
            if (isMoving())
            {
                engine::Vector2d futurePos;
                float speed = m_model->getSpeed();
                float t = time;
                engine::Vector2d lastPos = m_position;
                std::vector<engine::Vector2d>::iterator end = m_path.end();
                std::vector<engine::Vector2d>::iterator it;
                for (it = m_path.begin(); t >= 0 && it != end; it++)
                {
                    engine::Vector2d diff = *it - lastPos;
                    float duration = diff.distance() / speed;
                    t -= duration;

                    if (t < 0)
                        futurePos = lastPos + diff * (duration + t) / duration;

                    else
                        futurePos = *it;

                    lastPos = *it;
                }
                return futurePos;
            }
            else
                return m_position;
        }

        map::Tile* Entity::getFutureTile(float time)
        {
            engine::Vector2d futurePos = getFuturePosition(time);
            return S(Game)->getMap()->getTile(futurePos.getRoundX(), futurePos.getRoundY());
        }

        void Entity::setDirection(float direction)
        {
            m_direction = direction;
            m_speed = engine::Vector2d(direction) * m_model->getSpeed();
        }

        void Entity::updatePosition()
        {
            setPosition((engine::Vector2d(-2, -1) * m_position.getX() + engine::Vector2d(2, -1) * m_position.getY() + engine::Vector2d(0, 1) * m_z) * S(Mod)->getTileWidth() / 4);
            calcDepth(m_position.getX(), m_position.getY(), m_model->getRadius());
        }

        int Entity::getTileX() const
        {
            return m_position.getRoundX();
        }

        int Entity::getTileY() const
        {
            return m_position.getRoundY();
        }

        bool Entity::canMove() const
        {
            return !isBuilding() && m_model->getSpeed() > 0;
        }

        void Entity::setZ(float z)
        {
            m_z = z;
            updatePosition();
        }

        bool Entity::fall(float frameTime)
        {
            if (!m_onTheFloor)
            {
                map::Tile* tile = getTile();

                m_zSpeed -= frameTime * m_model->getWeight();
                float z = m_z + m_zSpeed * frameTime;
                if (z <= tile->getZ())
                {
                    m_onTheFloor = true;
                    m_zSpeed = 0;
                    z = tile->getZ();
                }
                setZ(z);
            }
            return !m_onTheFloor;
        }

        void Entity::jump(float force)
        {
            setActive(true);
            m_zSpeed = m_model->getJumpForce() * force;
            m_onTheFloor = false;
        }

        void Entity::addedToMap(map::Map* map, int x, int y)
        {
            float tileZ = map->getTile(x, y)->getZ();
            if (tileZ < m_z)
                m_onTheFloor = false;

            else
                setZ(tileZ);
        }
        
        engine::Vector2d Entity::getAbsolutePosition()
        {
            return engine::graphics::TexturedShowable::getAbsolutePosition() + getDimensions() / 2;
        }

        void Entity::setActive(bool active)
        {
            m_active = active;
        }

        map::Tile* Entity::getTile()
        {
            return S(Game)->getMap()->getTile(getTileX(), getTileY());
        }

        bool Entity::isSquadLeader()
        {
            if (m_squad == NULL)
                return false;

            else
                return m_squad->getLeader() == this;
        }
        
        void Entity::enableOverlay()
        {
            disableOverlay();
            m_overlay = new interface::EntityOverlay();
        }
        
        void Entity::disableOverlay()
        {
            if (m_overlay != NULL)
            {
                delete m_overlay;
                m_overlay = NULL;
            }
        }
        
        void Entity::setTileChangeListener(lua_State* L)
        {
            if (m_onTileChange != LUA_NOREF)
            {
                luaL_unref(L, LUA_REGISTRYINDEX, m_onTileChange);
                m_onTileChange = LUA_NOREF;
            }
            if (!lua_isnil(L, -1))
            {
                luaL_checktype(L, -1, LUA_TFUNCTION);
                m_onTileChange = luaL_ref(L, LUA_REGISTRYINDEX);
            }
        }
        
        void Entity::triggerTileChangeListener()
        {
            if (m_onTileChange != LUA_NOREF)
            {
                lua_State* L = lua::getState();
                lua_rawgeti(L, LUA_REGISTRYINDEX, m_onTileChange);
                lua_pushlightuserdata(L, this);
                lua_call(L, 1, 0);
            }
        }

    }
}


