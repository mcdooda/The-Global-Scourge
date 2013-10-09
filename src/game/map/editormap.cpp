#include <iostream>
#include <cmath>
#include "editormap.h"
#include "editortile.h"
#include "displaymanager.h"
#include "../entity/building.h"
#include "../entity/unit.h"
#include "../mod/mod.h"
#include "../../engine/singleton.h"
#include "../../engine/graphics/texturegroup.h"
#include "../../engine/graphics/coloralpha.h"
#include "../../engine/input/keyboard.h"
#include "../../engine/input/mouse.h"
#include "../../engine/time.h"
#include "../../engine/random.h"
#include "../brush/discbrush.h"
#include "io/writer.h"

namespace game
{
    namespace map
    {

        EditorMap::EditorMap()
        {
            m_currentTilesGroup = NULL;
            m_currentDoodadsGroup = NULL;
            m_currentBuildingModel = NULL;
            m_currentUnitModel = NULL;
            m_mode = MODE_TILES;
            m_brush = NULL;
            setBrush(new brush::DiscBrush());
        }

        void EditorMap::showTemporaries()
        {
            if (m_mode == MODE_TILES || m_mode == MODE_DOODADS)
            {
                const int minX = getBrushMinX();
                const int maxX = getBrushMaxX();
                const int minY = getBrushMinY();
                const int maxY = getBrushMaxY();
                
                if (m_mode == MODE_DOODADS)
                {
                    for (int x = minX; x <= maxX; x++)
                    {
                        for (int y = minY; y <= maxY; y++)
                        {
                            EditorTile* tile = (EditorTile*) m_tiles[x][y];
                            if (tile != NULL && (tile->isAccessible() || tile->hasDoodad()))
                            {
                                float d = tile->getBrushEffect();
                                float f = engine::random::rfloat(0, 1);
                                if (f < d)
                                {
                                    Doodad* doodad = new Doodad(m_currentDoodadsGroup->getRandomTexture(), tile);
                                    displaymanager::addTemporary(doodad);
                                }
                            }
                        }
                    }
                }
                
                engine::Vector2d pointer =  getPointerPosition();

                for (int x = minX; x <= maxX; x++)
                {
                    for (int y = minY; y <= maxY; y++)
                    {
                        if (m_tiles[x][y] == NULL)
                        {
                            float d = m_brush->getEffect(x - pointer.getX(), y - pointer.getY());
                            if (d > 0)
                            {
                                Tile* tile = new Tile(m_currentTilesGroup->getFirstTexture(), x, y, 0);
                                tile->setColor(new engine::graphics::ColorAlpha(128, 128, 128, 128));
                                displaymanager::addTemporary(tile);
                            }
                        }
                    }
                }
            }
            else if (m_mode == MODE_BUILDINGS)
            {
                if (m_currentBuildingModel != NULL)
                {
                    engine::Vector2d pointerPosition = getPointerPosition();
                    int x = pointerPosition.getRoundX();
                    int y = pointerPosition.getRoundY();
                    if (m_currentBuildingModel->canBeBuilt(this, x, y))
                    {
                        pointerPosition.setX(x);
                        pointerPosition.setY(y);
                        entity::Building* building = new entity::Building(m_currentBuildingModel, pointerPosition);
                        building->setColor(new engine::graphics::ColorAlpha(255, 255, 255, 128));
                        building->setZ(getTile(x, y)->getZ());
                        displaymanager::addTemporary(building);
                    }
                }
            }
            else if (m_mode == MODE_UNITS)
            {
                if (m_currentUnitModel != NULL)
                {
                    engine::Vector2d pointerPosition = getPointerPosition();
                    int x = pointerPosition.getRoundX();
                    int y = pointerPosition.getRoundY();
                    Tile* tile = getTile(x, y);
                    if (tile != NULL && tile->isAccessible())
                    {
                        entity::Unit* unit = new entity::Unit(m_currentUnitModel, pointerPosition);
                        unit->setColor(new engine::graphics::ColorAlpha(255, 255, 255, 128));
                        unit->setZ(tile->getZ());
                        displaymanager::addTemporary(unit);
                    }
                }
            }
        }

        void EditorMap::randomMap(int width, int height)
        {
            engine::graphics::TextureGroup* defaultTiles = getTilesGroup(S(Mod)->getDefaultTilesGroupPath());

            m_width = width;
            m_height = height;

            m_tiles = new Tile**[m_width];
            for (int x = 0; x < m_width; x++)
            {
                m_tiles[x] = new Tile*[m_height];
                for (int y = 0; y < m_height; y++)
                    m_tiles[x][y] = new EditorTile(defaultTiles->getRandomTexture(), x, y, 0);
            }

            generateForests();
        }

        void EditorMap::generateForests()
        {
            engine::graphics::TextureGroup* trees = getDoodadsGroup(S(Mod)->getForestDoodadsGroupPath());

            int numForests = m_width * m_height / 1000;

            engine::Vector2d forests[numForests];
            float forestsSizeSq[numForests];

            for (int i = 0; i < numForests; i++)
            {
                forests[i].setX(engine::random::rfloat(0, m_width));
                forests[i].setY(engine::random::rfloat(0, m_height));
                forestsSizeSq[i] = engine::random::rfloat(150, 450);
            }

            for (int x = 0; x < m_width; x++)
            {
                for (int y = 0; y < m_height; y++)
                {
                    float nearestForestDistanceSq = 10000000;
                    for (int i = 0; i < numForests; i++)
                    {
                        float distanceSq = (forests[i].getX() - x) * (forests[i].getX() - x) + (forests[i].getY() - y) * (forests[i].getY() - y) - forestsSizeSq[i];
                        if (distanceSq < nearestForestDistanceSq)
                            nearestForestDistanceSq = distanceSq;
                    }

                    Tile* tile = m_tiles[x][y];
                    if (tile != NULL && tile->getBuilding() == NULL)
                    {
                        if (nearestForestDistanceSq / 250 < engine::random::rfloat(-1, 1))
                            tile->setDoodadTexture(trees->getRandomTexture());

                        else
                            tile->setDoodadTexture(NULL);
                    }
                }
            }
        }

        void EditorMap::wave()
        {
            for (int x = 0; x < m_width; x++)
            {
                for (int y = 0; y < m_height; y++)
                {
                    Tile* tile = m_tiles[x][y];
                    if (tile != NULL)
                    {
                        float dist = sqrt((m_width / 2 - 0.5 - x) * (m_width / 2 - 0.5 - x) + (m_height / 2 - 0.5 - y) * (m_height / 2 - 0.5 - y));
                        tile->setZ(sin(dist + engine::time::getTime() * -5));
                    }
                }
            }
        }

        void EditorMap::flatten()
        {
            for (int x = 0; x < m_width; x++)
            {
                for (int y = 0; y < m_height; y++)
                {
                    Tile* tile = m_tiles[x][y];
                    if (tile != NULL)
                        tile->setZ(0);
                }
            }
        }

        void EditorMap::zUp()
        {
            const float frameTime = engine::time::getFrameTime();
            const int minX = getBrushMinX();
            const int maxX = getBrushMaxX();
            const int minY = getBrushMinY();
            const int maxY = getBrushMaxY();
            for (int x = minX; x <= maxX; x++)
            {
                for (int y = minY; y <= maxY; y++)
                {
                    EditorTile* tile = (EditorTile*) m_tiles[x][y];
                    if (tile != NULL)
                    {
                        float d = tile->getBrushEffect();
                        if (d > 0 && d <= 1)
                        {
                            float z = tile->getZ();
                            tile->setZ(z + d * frameTime * 20);
                        }
                    }
                }
            }
        }

        void EditorMap::zDown()
        {
            const float frameTime = engine::time::getFrameTime();
            const int minX = getBrushMinX();
            const int maxX = getBrushMaxX();
            const int minY = getBrushMinY();
            const int maxY = getBrushMaxY();
            for (int x = minX; x <= maxX; x++)
            {
                for (int y = minY; y <= maxY; y++)
                {
                    EditorTile* tile = (EditorTile*) m_tiles[x][y];
                    if (tile != NULL)
                    {
                        float d = tile->getBrushEffect();
                        if (d > 0 && d <= 1)
                        {
                            float z = tile->getZ();
                            tile->setZ(z - d * frameTime * 20);
                        }
                    }
                }
            }
        }

        void EditorMap::zMean()
        {
            const float frameTime = engine::time::getFrameTime();
            const int minX = getBrushMinX();
            const int maxX = getBrushMaxX();
            const int minY = getBrushMinY();
            const int maxY = getBrushMaxY();
            float mean = 0;
            float n = 0;
            for (int x = minX; x <= maxX; x++)
            {
                for (int y = minY; y <= maxY; y++)
                {
                    EditorTile* tile = (EditorTile*) m_tiles[x][y];
                    if (tile != NULL)
                    {
                        float d = tile->getBrushEffect();
                        if (d > 0 && d <= 1)
                        {
                            mean += tile->getZ() * d;
                            n += d;
                        }
                    }
                }
            }
            mean /= n;
            for (int x = minX; x <= maxX; x++)
            {
                for (int y = minY; y <= maxY; y++)
                {
                    EditorTile* tile = (EditorTile*) m_tiles[x][y];
                    if (tile != NULL)
                    {
                        float d = tile->getBrushEffect();
                        if (d > 0 && d <= 1)
                        {
                            float z = tile->getZ();
                            tile->setZ(z + (mean - z) * d * frameTime * 5);
                        }
                    }
                }
            }
        }

        void EditorMap::deleteTiles()
        {
            const int minX = getBrushMinX();
            const int maxX = getBrushMaxX();
            const int minY = getBrushMinY();
            const int maxY = getBrushMaxY();
            for (int x = minX; x <= maxX; x++)
            {
                for (int y = minY; y <= maxY; y++)
                {
                    EditorTile* tile = (EditorTile*) m_tiles[x][y];
                    if (tile != NULL)
                    {
                        float d = tile->getBrushEffect();
                        if (d > 0)
                        {
                            std::vector<entity::Entity*> entities = tile->getEntities();
                            std::vector<entity::Entity*>::iterator end = entities.end();
                            for (std::vector<entity::Entity*>::iterator it = entities.begin(); it != end; it++)
                            {
                                removeEntity(*it);

                                if (!(*it)->isBuilding() || ((*it)->getTileX() == x && (*it)->getTileY() == y))
                                    delete *it;
                            }

                            delete tile;
                            m_tiles[x][y] = NULL;
                        }
                    }
                }
            }
        }

        void EditorMap::insertTiles()
        {
            const int minX = getBrushMinX();
            const int maxX = getBrushMaxX();
            const int minY = getBrushMinY();
            const int maxY = getBrushMaxY();

            engine::Vector2d pointer =  getPointerPosition();

            for (int x = minX; x <= maxX; x++)
            {
                for (int y = minY; y <= maxY; y++)
                {
                    if (m_tiles[x][y] == NULL)
                    {
                        float d = m_brush->getEffect(x - pointer.getX(), y - pointer.getY());
                        if (d > 0)
                        {
                            EditorTile* tile = new EditorTile(m_currentTilesGroup->getRandomTexture(), x, y, 0);
                            m_tiles[x][y] = tile;
                        }
                    }
                }
            }
        }

        void EditorMap::save()
        {
            io::Writer w(this);
            w.write();
        }

        void EditorMap::applyGroup()
        {
            if (m_mode == MODE_TILES)
                applyTiles();

            else if (m_mode == MODE_DOODADS)
                applyDoodads();

            else if (m_mode == MODE_BUILDINGS)
                putBuilding();

            else if (m_mode == MODE_UNITS)
                putUnit();

            else // m_mode == MODE_ZONES
                selectZone();
        }

        void EditorMap::removeGroup()
        {
            if (m_mode == MODE_TILES)
                removeTiles();

            else if (m_mode == MODE_DOODADS)
                removeDoodads();

            else if (m_mode == MODE_BUILDINGS)
                removeBuilding();

            else if (m_mode == MODE_UNITS)
                removeUnit();

            else // m_mode == MODE_ZONES
                removeZone();
        }

        int EditorMap::getBrushMinX() const
        {
            int minX = ceil(getPointerPosition().getX() - m_brush->getSize());

            if (minX < 0)
                minX = 0;

            else if (minX > m_width - 1)
                minX = m_width - 1;

            return minX;
        }

        int EditorMap::getBrushMaxX() const
        {
            int maxX = floor(getPointerPosition().getX() + m_brush->getSize());

            if (maxX < 0)
                maxX = 0;

            else if (maxX > m_width - 1)
                maxX = m_width - 1;

            return maxX;
        }

        int EditorMap::getBrushMinY() const
        {
            int minY = ceil(getPointerPosition().getY() - m_brush->getSize());

            if (minY < 0)
                minY = 0;

            else if (minY > m_height - 1)
                minY = m_height - 1;

            return minY;
        }

        int EditorMap::getBrushMaxY() const
        {
            int maxY = floor(getPointerPosition().getY() + m_brush->getSize());

            if (maxY < 0)
                maxY = 0;

            else if (maxY > m_height - 1)
                maxY = m_height - 1;

            return maxY;
        }

        engine::Vector2d EditorMap::getPointerPosition() const
        {
            engine::Vector2d pointer = Map::getPointerPosition();
            if (engine::input::keyboard::isPressed(K(LSHIFT)))
            {
                pointer.setX(pointer.getRoundX());
                pointer.setY(pointer.getRoundY());
            }
            return pointer;
        }

        void EditorMap::setBrush(brush::Brush* brush)
        {
            if (m_brush != NULL)
            {
                brush->setSize(m_brush->getSize());
                delete m_brush;
            }

            m_brush = brush;
        }

        void EditorMap::setTilesGroup(std::string tilesGroup)
        {
            m_currentTilesGroup = getTilesGroup(tilesGroup);
        }

        void EditorMap::setDoodadsGroup(std::string doodadsGroup)
        {
            m_currentDoodadsGroup = getDoodadsGroup(doodadsGroup);
        }

        engine::graphics::TextureGroup* EditorMap::getTilesGroup(std::string tilesGroup)
        {
            std::map<std::string, engine::graphics::TextureGroup>::iterator it = m_tilesGroups.find(tilesGroup);
            if (it == m_tilesGroups.end()) // group not found, loading...
            {
                m_tilesGroups[tilesGroup] = engine::graphics::TextureGroup();
                m_tilesGroups[tilesGroup].addDir(tilesGroup);
                return &m_tilesGroups[tilesGroup];
            }
            else
                return &it->second;
        }

        engine::graphics::TextureGroup* EditorMap::getDoodadsGroup(std::string doodadsGroup)
        {
            std::map<std::string, engine::graphics::TextureGroup>::iterator it = m_doodadsGroups.find(doodadsGroup);
            if (it == m_doodadsGroups.end()) // group not found, loading...
            {
                m_doodadsGroups[doodadsGroup] = engine::graphics::TextureGroup();
                m_doodadsGroups[doodadsGroup].addDir(doodadsGroup);
                return &m_doodadsGroups[doodadsGroup];
            }
            else
                return &it->second;
        }

        void EditorMap::applyTiles()
        {
            const int minX = getBrushMinX();
            const int maxX = getBrushMaxX();
            const int minY = getBrushMinY();
            const int maxY = getBrushMaxY();
            for (int x = minX; x <= maxX; x++)
            {
                for (int y = minY; y <= maxY; y++)
                {
                    EditorTile* tile = (EditorTile*) m_tiles[x][y];
                    if (tile != NULL)
                    {
                        float d = tile->getBrushEffect();
                        float f = engine::random::rfloat(0, 1);

                        if (f < d)
                            tile->setTile(m_currentTilesGroup->getRandomTexture());
                    }
                }
            }
        }

        void EditorMap::applyDoodads()
        {
            const int minX = getBrushMinX();
            const int maxX = getBrushMaxX();
            const int minY = getBrushMinY();
            const int maxY = getBrushMaxY();
            for (int x = minX; x <= maxX; x++)
            {
                for (int y = minY; y <= maxY; y++)
                {
                    EditorTile* tile = (EditorTile*) m_tiles[x][y];
                    if (tile != NULL && (tile->isAccessible() || tile->hasDoodad()))
                    {
                        float d = tile->getBrushEffect();
                        float f = engine::random::rfloat(0, 1);
                        if (f < d)
                            tile->setDoodadTexture(m_currentDoodadsGroup->getRandomTexture());
                    }
                }
            }
        }

        void EditorMap::putBuilding()
        {
            if (m_currentBuildingModel != NULL && engine::input::mouse::isJustPressed(M(LEFT)))
            {
                engine::Vector2d pointerPosition = getPointerPosition();
                int x = pointerPosition.getRoundX();
                int y = pointerPosition.getRoundY();
                if (m_currentBuildingModel->canBeBuilt(this, x, y))
                {
                    pointerPosition.setX(x);
                    pointerPosition.setY(y);
                    entity::Building* building = new entity::Building(m_currentBuildingModel, pointerPosition);
                    building->setZ(getTile(x, y)->getZ());
                    addEntity(building);
                }
            }
        }

        void EditorMap::putUnit()
        {
            if (m_currentUnitModel != NULL && engine::input::mouse::isJustPressed(M(LEFT)))
            {
                engine::Vector2d pointerPosition = getPointerPosition();
                int x = pointerPosition.getRoundX();
                int y = pointerPosition.getRoundY();
                Tile* tile = getTile(x, y);
                if (tile != NULL && tile->isAccessible())
                {
                    entity::Unit* unit = new entity::Unit(m_currentUnitModel, pointerPosition);
                    unit->setZ(tile->getZ());
                    addEntity(unit);
                }
            }
        }

        void EditorMap::selectZone()
        {

        }

        void EditorMap::removeTiles()
        {
            engine::graphics::TextureGroup* currentTilesGroup = m_currentTilesGroup;
            setTilesGroup(S(Mod)->getDefaultTilesGroupPath());
            applyTiles();
            m_currentTilesGroup = currentTilesGroup;
        }

        void EditorMap::removeDoodads()
        {
            const int minX = getBrushMinX();
            const int maxX = getBrushMaxX();
            const int minY = getBrushMinY();
            const int maxY = getBrushMaxY();
            for (int x = minX; x <= maxX; x++)
            {
                for (int y = minY; y <= maxY; y++)
                {
                    EditorTile* tile = (EditorTile*) m_tiles[x][y];
                    if (tile != NULL)
                    {
                        float d = tile->getBrushEffect();
                        float f = engine::random::rfloat(0, 1);

                        if (f < d)
                            tile->setDoodadTexture(NULL);
                    }
                }
            }
        }

        void EditorMap::removeBuilding()
        {
            if (engine::input::mouse::isJustPressed(M(RIGHT)))
            {
                engine::Vector2d pointerPosition = getPointerPosition();
                int x = pointerPosition.getRoundX();
                int y = pointerPosition.getRoundY();
                EditorTile* tile = (EditorTile*) getTile(x, y);
                if (tile != NULL)
                {
                    entity::Entity* building = tile->getBuilding();
                    if (building != NULL)
                        removeEntity(building);
                }
            }
        }

        void EditorMap::removeUnit()
        {

        }

        void EditorMap::removeZone()
        {

        }

    }
}
