#include <sstream>
#include "widget.h"
#include "../widget.h"
#include "../imagewidget.h"
#include "../textwidget.h"
#include "../../../engine/resourcemanager.h"
#include "../../../engine/singleton.h"
#include "../../../engine/graphics/color.h"
#include "../../../engine/graphics/text.h"
#include "../../game.h"
#include "../../lua/util/color.h"

namespace game
{
    namespace interface
    {
        namespace lua
        {

            int widgetLib(lua_State* L)
            {
                static const luaL_reg Widget_lib[] = {
                    {"getInterface",              Widget_getInterface},
                    {"new",                       Widget_new},
                    {"setPosition",               Widget_setPosition},
                    {"setDimensions",             Widget_setDimensions},
                    {"getPosition",               Widget_getPosition},
                    {"getDimensions",             Widget_getDimensions},
                    {"setTexture",                Widget_setTexture},
                    {"setTextureCoords",          Widget_setTextureCoords},
                    {"resetTextureCoords",        Widget_resetTextureCoords},
                    {"setAngle",                  Widget_setAngle},
                    {"add",                       Widget_add},
                    {"destroy",                   Widget_destroy},
                    {"clear",                     Widget_clear},
                    {"hide",                      Widget_hide},
                    {"setOpacity",                Widget_setOpacity},
                    {"show",                      Widget_show},
                    {"onClick",                   Widget_onClick},
                    {"setText",                   Widget_setText},
                    {"setColor",                  Widget_setColor},
                    {"getParent",                 Widget_getParent},
                    {"getChildren",               Widget_getChildren},
                    {"getAnchor",                 Widget_getAnchor},
                    {"setAnchor",                 Widget_setAnchor},
                    {"setRequireMouseOverParent", Widget_setRequireMouseOverParent},
                    {NULL, NULL}
                };
                luaL_register(L, "Widget", Widget_lib);

                static const struct
                {
                    const char* key;
                    int value;
                } Widget_constants[] = {
                    {"LEFT",    Widget::LEFT},
                    {"RIGHT",   Widget::RIGHT},
                    {"CENTERX", Widget::CENTERX},
                    {"TOP",     Widget::TOP},
                    {"BOTTOM",  Widget::BOTTOM},
                    {"CENTERY", Widget::CENTERY},
                    {NULL, 0}
                };
                for (int i = 0; Widget_constants[i].key != NULL; i++)
                {
                    lua_pushinteger(L, Widget_constants[i].value);
                    lua_setfield(L, -2, Widget_constants[i].key);
                }

                return 0;
            }

            int Widget_getInterface(lua_State* L)
            {
                lua_pushlightuserdata(L, S(Game)->getInterface());
                return 1;
            }

            int Widget_new(lua_State* L)
            {
                lua_getfield(L, 1, "parent");
                Widget* parent = (Widget*) lua_touserdata(L, -1);
                if (parent == NULL)
                    parent = S(Game)->getInterface();

                lua_getfield(L, 1, "position");
                engine::Vector2d position;
                if (lua_istable(L, -1))
                {
                    lua_getfield(L, -1, "x");
                    lua_getfield(L, -2, "y");
                    position.setX(luaL_optnumber(L, -2, 0));
                    position.setY(luaL_optnumber(L, -1, 0));
                }

                lua_getfield(L, 1, "dimensions");
                engine::Vector2d dimensions;
                bool dimensionsGiven = false;
                if (lua_istable(L, -1))
                {
                    lua_getfield(L, -1, "width");
                    lua_getfield(L, -2, "height");
                    dimensions.setX(luaL_optnumber(L, -2, 0));
                    dimensions.setY(luaL_optnumber(L, -1, 0));
                    dimensionsGiven = true;
                }

                lua_getfield(L, 1, "anchor");
                int anchor = luaL_checkint(L, -1);
                
                engine::graphics::Texture* image = NULL;
                engine::graphics::Text* text = NULL;
                
                lua_getfield(L, 1, "image");
                if (lua_isstring(L, -1))
                    image = S(engine::TextureManager)->get(lua_tostring(L, -1));
                
                lua_getfield(L, 1, "pixelPerfect");
                bool pixelPerfect = lua_toboolean(L, -1);
                    
                // text widget
                if (image == NULL)
                {
                    lua_getfield(L, 1, "text");
                    if (lua_isstring(L, -1))
                    {
                        std::string str = lua_tostring(L, -1);
                        
                        // these fields must be given: fontfile, size, color
                        lua_getfield(L, 1, "font");
                        std::string fontname = luaL_checkstring(L, -1);
                        
                        lua_getfield(L, 1, "color");
                        luaL_checktype(L, -1, LUA_TTABLE);
                        
                        // reading color
                        // red
                        lua_rawgeti(L, -1, 1);
                        unsigned char red = luaL_checkint(L, -1);
                        
                        // green
                        lua_rawgeti(L, -2, 2);
                        unsigned char green = luaL_checkint(L, -1);
                        
                        // blue
                        lua_rawgeti(L, -3, 3);
                        unsigned char blue = luaL_checkint(L, -1);
                        
                        engine::graphics::Color color(red, green, blue);
                        
                        engine::graphics::Font* font = S(engine::FontManager)->get(fontname);
                        text = new engine::graphics::Text(str, font, color);
                    }
                }

                Widget* widget;

                if (image != NULL)
                {
                    widget = new ImageWidget(parent, position, anchor, image, pixelPerfect);
                }
                else if (text != NULL)
                {
                    widget = new TextWidget(parent, position, anchor, text);
                }
                else
                {
                    widget = new Widget(parent, position, dimensions, anchor);
                }
                
                if (dimensionsGiven)
                    widget->setDimensions(dimensions);

                lua_pushlightuserdata(L, widget);

                return 1;
            }

            int Widget_setPosition(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Widget* widget = (Widget*) lua_touserdata(L, 1);
                luaL_checktype(L, 2, LUA_TTABLE);
                lua_getfield(L, 2, "x");
                lua_getfield(L, 2, "y");
                engine::Vector2d position(luaL_checknumber(L, -2), luaL_checknumber(L, -1));
                widget->setRelativePosition(position);
                return 0;
            }

            int Widget_setDimensions(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Widget* widget = (Widget*) lua_touserdata(L, 1);
                luaL_checktype(L, 2, LUA_TTABLE);
                lua_getfield(L, 2, "width");
                lua_getfield(L, 2, "height");
                engine::Vector2d dimensions(luaL_checknumber(L, -2), luaL_checknumber(L, -1));
                widget->setDimensions(dimensions);
                return 0;
            }

            int Widget_getPosition(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Widget* widget = (Widget*) lua_touserdata(L, 1);
                engine::Vector2d position = widget->getRelativePosition();
                lua_pushnumber(L, position.getX());
                lua_pushnumber(L, position.getY());
                return 2;
            }

            int Widget_getDimensions(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Widget* widget = (Widget*) lua_touserdata(L, 1);
                engine::Vector2d dimensions = widget->getDimensions();
                lua_pushnumber(L, dimensions.getX());
                lua_pushnumber(L, dimensions.getY());
                return 2;
            }
            
            int Widget_setTexture(lua_State* L) // must be an ImageWidget
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                ImageWidget* widget = (ImageWidget*) lua_touserdata(L, 1);
                std::string filename = luaL_checkstring(L, 2);
                engine::graphics::Texture* texture = S(engine::TextureManager)->get(filename);
                widget->setTexture(texture);
                return 0;
            }
            
            int Widget_setTextureCoords(lua_State* L) // must be an ImageWidget
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                ImageWidget* widget = (ImageWidget*) lua_touserdata(L, 1);
                float lX = luaL_checknumber(L, 2);
                float bY = luaL_checknumber(L, 3);
                float rX = luaL_checknumber(L, 4);
                float tY = luaL_checknumber(L, 5);
                widget->setTextureCoords(lX, bY, rX, tY);
                return 0;
            }
            
            int Widget_resetTextureCoords(lua_State* L) // must be an ImageWidget
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                ImageWidget* widget = (ImageWidget*) lua_touserdata(L, 1);
                widget->resetTextureCoords();
                return 0;
            }
            
            int Widget_setAngle(lua_State* L) // must be an ImageWidget
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                ImageWidget* widget = (ImageWidget*) lua_touserdata(L, 1);
                float angle = luaL_checknumber(L, 2);
                widget->setAngle(angle);
                return 0;
            }

            int Widget_add(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Widget* widget = (Widget*) lua_touserdata(L, 1);
                luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
                Widget* widget2 = (Widget*) lua_touserdata(L, 2);
                widget->add(widget2);
                return 0;
            }

            int Widget_destroy(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Widget* widget = (Widget*) lua_touserdata(L, 1);
                widget->setDestroyed();
                return 0;
            }
            
            int Widget_clear(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Widget* widget = (Widget*) lua_touserdata(L, 1);
                widget->clear();
                return 0;
            }

            int Widget_show(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Widget* widget = (Widget*) lua_touserdata(L, 1);
                widget->setHidden(false);
                return 0;
            }

            int Widget_hide(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Widget* widget = (Widget*) lua_touserdata(L, 1);
                widget->setHidden(true);
                return 0;
            }
            
            int Widget_setOpacity(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Widget* widget = (Widget*) lua_touserdata(L, 1);
                float opacity = luaL_checknumber(L, 2);
                widget->setOpacity(opacity);
                return 0;
            }

            int Widget_onClick(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Widget* widget = (Widget*) lua_touserdata(L, 1);
                
                if (!lua_isnil(L, 2))
                    luaL_checktype(L, 2, LUA_TFUNCTION);
                    
                widget->setOnClick(L);
                return 0;
            }
            
            int Widget_setText(lua_State* L) // must be a text widget!
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                TextWidget* widget = (TextWidget*) lua_touserdata(L, 1);
                const char* string = luaL_checkstring(L, 2);
                widget->setText(string);
                return 0;
            }
            
            int Widget_setColor(lua_State* L) // must be a text widget!
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                TextWidget* widget = (TextWidget*) lua_touserdata(L, 1);
                //const char* text = luaL_checkstring(L, 2);
                //widget->setText(text);
                engine::graphics::Color* color = game::lua::util::readColor(L, 2);
                widget->setColor(*color);
                delete color;
                return 0;
            }
            
            int Widget_getParent(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Widget* widget = (Widget*) lua_touserdata(L, 1);
                lua_pushlightuserdata(L, widget->getParent());
                return 1;
            }
            
            int Widget_getChildren(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Widget* widget = (Widget*) lua_touserdata(L, 1);
                const std::vector<Widget*>& children = widget->getChildren();
                lua_createtable(L, children.size(), 0);
                int i = 1;
                std::vector<Widget*>::const_iterator end = children.end();
                for (std::vector<Widget*>::const_iterator it = children.begin(); it != end; it++)
                {
                    lua_pushlightuserdata(L, *it);
                    lua_rawseti(L, -2, i);
                    i++;
                }
                return 1;
            }
            
            int Widget_getAnchor(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Widget* widget = (Widget*) lua_touserdata(L, 1);
                lua_pushinteger(L, widget->getAnchor());
                return 1;
            }
            
            int Widget_setAnchor(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Widget* widget = (Widget*) lua_touserdata(L, 1);
                int anchor = luaL_checkint(L, 2);
                widget->setAnchor(anchor);
                return 0;
            }
            
            int Widget_setRequireMouseOverParent(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                Widget* widget = (Widget*) lua_touserdata(L, 1);
                bool requireMouseOverParent = lua_toboolean(L, 2);
                widget->setRequireMouseOverParent(requireMouseOverParent);
                return 0;
            }
            
        }
    }
}
