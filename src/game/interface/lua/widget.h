#ifndef GAME_INTERFACE_LUA_WIDGET_H
 #define GAME_INTERFACE_LUA_WIDGET_H

#include "../../lua/lua.h"

namespace game
{
    namespace interface
    {
        namespace lua
        {

            int widgetLib(lua_State* L);

            int Widget_getInterface(lua_State* L);
            int Widget_new(lua_State* L);
            int Widget_setPosition(lua_State* L);
            int Widget_setDimensions(lua_State* L);
            int Widget_getPosition(lua_State* L);
            int Widget_getDimensions(lua_State* L);
            int Widget_setTexture(lua_State* L);
            int Widget_setTextureCoords(lua_State* L);
            int Widget_resetTextureCoords(lua_State* L);
            int Widget_setAngle(lua_State* L);
            int Widget_add(lua_State* L);
            int Widget_destroy(lua_State* L);
            int Widget_clear(lua_State* L);
            int Widget_show(lua_State* L);
            int Widget_hide(lua_State* L);
            int Widget_setOpacity(lua_State* L);
            int Widget_onClick(lua_State* L);
            int Widget_setText(lua_State* L);
            int Widget_setColor(lua_State* L);
            int Widget_getParent(lua_State* L);
            int Widget_getChildren(lua_State* L);
            int Widget_getAnchor(lua_State* L);
            int Widget_setAnchor(lua_State* L);
            int Widget_setRequireMouseOverParent(lua_State* L);

        }
    }
}

#endif
