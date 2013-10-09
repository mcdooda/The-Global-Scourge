#include <iostream>
#include <string>
#include "mod.h"
#include "../lua/lua.h"
#include "../../engine/singleton.h"
#include "../../engine/graphics/texturegroup.h"

namespace game
{

    void Mod::setPath(std::string path)
    {
        m_path = path;
        m_resourcePath = path;
    }

    std::string Mod::getFilePath(std::string file)
    {
        return m_path + "/" + file;
    }

    std::string Mod::getResourceFilePath(std::string file)
    {
        return m_resourcePath + "/" + file;
    }

    engine::graphics::Texture* Mod::getTexture(std::string filename)
    {
        return S(engine::TextureManager)->get(getResourceFilePath(filename));
    }

    void Mod::readConfig()
    {
        lua_State* L = lua::getState();

        int top = lua_gettop(L);

        luaL_loadfile(L, getFilePath("scripts/config.lua").c_str());
        lua_call(L, 0, 1);

        lua_getfield(L, -1, "mapWidth");
        m_mapWidth = luaL_checkint(L, -1);

        lua_getfield(L, -2, "mapHeight");
        m_mapHeight = luaL_checkint(L, -1);

        lua_getfield(L, -3, "defaultTile");
        m_defaultTile = luaL_checkstring(L, -1);

        lua_getfield(L, -4, "forestDoodad");
        m_forestDoodad = luaL_checkstring(L, -1);

        lua_getfield(L, -5, "resourcePath");
        if (lua_isstring(L, -1))
            m_resourcePath = luaL_checkstring(L, -1);

        engine::graphics::TextureGroup defaultTiles;
        defaultTiles.addDir(getResourceFilePath(std::string("tiles/") + m_defaultTile));
        
        m_tileWidth = defaultTiles.getRandomTexture()->getWidth();
        m_tileHeight = m_tileWidth / 2;

        lua_settop(L, top);
    }

}
