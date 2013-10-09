#ifndef GAME_MAP_EDITORMAP_H
 #define GAME_MAP_EDITORMAP_H

#include <iostream>
#include <map>
#include "map.h"
#include "../entity/buildingmodel.h"
#include "../entity/unitmodel.h"
#include "../brush/brush.h"
#include "../../engine/graphics/texturegroup.h"

namespace game
{
    namespace map
    {

        class EditorMap : public Map
        {
            public:
                enum Mode
                {
                    MODE_TILES,
                    MODE_DOODADS,
                    MODE_BUILDINGS,
                    MODE_UNITS,
                    MODE_ZONES
                };

                EditorMap();
                
                virtual void showTemporaries();

                void randomMap(int width, int height);

                void generateForests();
                void wave();
                void flatten();

                void zUp();
                void zDown();
                void zMean();
                
                void deleteTiles();
                void insertTiles();

                void save();

                void applyGroup();
                void removeGroup();
                
                inline bool usingBrush() const { return m_mode == MODE_TILES || m_mode == MODE_DOODADS; }
                inline bool puttingBuilding() const { return m_mode == MODE_BUILDINGS && m_currentBuildingModel != NULL; }
                inline bool puttingUnit() const { return m_mode == MODE_UNITS && m_currentUnitModel != NULL; }

                int getBrushMinX() const;
                int getBrushMaxX() const;
                int getBrushMinY() const;
                int getBrushMaxY() const;

                virtual engine::Vector2d getPointerPosition() const;

                inline brush::Brush* getBrush() const { return m_brush; }
                void setBrush(brush::Brush* brush);

                void setTilesGroup(std::string tilesGroup);
                void setDoodadsGroup(std::string doodadsGroup);
                inline void setBuildingModel(entity::BuildingModel* buildingModel) { m_currentBuildingModel = buildingModel; }
                inline void setUnitModel(entity::UnitModel* unitModel) { m_currentUnitModel = unitModel; }
                
                inline entity::BuildingModel* getBuildingModel() const { return m_currentBuildingModel; }
                inline entity::UnitModel* getUnitModel() const { return m_currentUnitModel; }

                inline void setMode(Mode mode) { m_mode = mode; }
                inline int getMode() const { return m_mode; }

            private:
                friend class io::Reader;
                
                engine::graphics::TextureGroup* getTilesGroup(std::string tilesGroup);
                engine::graphics::TextureGroup* getDoodadsGroup(std::string doodadsGroup);

                void applyTiles();
                void applyDoodads();
                void putBuilding();
                void putUnit();
                void selectZone();
                
                void removeTiles();
                void removeDoodads();
                void removeBuilding();
                void removeUnit();
                void removeZone();

                brush::Brush* m_brush;

                int m_mode;

                engine::graphics::TextureGroup* m_currentTilesGroup;
                std::map<std::string, engine::graphics::TextureGroup> m_tilesGroups;

                engine::graphics::TextureGroup* m_currentDoodadsGroup;
                std::map<std::string, engine::graphics::TextureGroup> m_doodadsGroups;
                
                entity::BuildingModel* m_currentBuildingModel;
                
                entity::UnitModel* m_currentUnitModel;
        };

    }
}

#endif
