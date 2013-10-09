#ifndef GAME_MOD_H
 #define GAME_MOD_H

#include "../../engine/resourcemanager.h"

namespace game
{

    class Mod
    {
        public:

            void setPath(std::string path);

            inline std::string getPath() const { return m_path; }
            inline std::string getResourcePath() const { return m_resourcePath; }
            
            std::string getFilePath(std::string file);
            std::string getResourceFilePath(std::string file);

            inline int getMapWidth() const { return m_mapWidth; }
            inline int getMapHeight() const { return m_mapHeight; }
            
            inline const std::string& getDefaultTile() const { return m_defaultTile; }
            inline const std::string& getForestDoodad() const { return m_forestDoodad; }
            
            inline std::string getDefaultTilesGroupPath() { return getResourceFilePath("tiles/" + m_defaultTile); }
            inline std::string getForestDoodadsGroupPath() { return getResourceFilePath("doodads/" + m_forestDoodad); }
            
            inline int getTileWidth() const { return m_tileWidth; }
            inline int getTileHeight() const { return m_tileHeight; }

            engine::graphics::Texture* getTexture(std::string filename);

            void readConfig();

        private:

            std::string m_path;
            std::string m_resourcePath;

            int m_mapWidth;
            int m_mapHeight;
            
            int m_tileWidth;
            int m_tileHeight;
            
            std::string m_defaultTile;
            std::string m_forestDoodad;
    };

}

#endif
