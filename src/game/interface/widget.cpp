#include <iostream>
#include <algorithm>
#include "../../engine/graphics/color.h"
#include "../../engine/graphics/transform.h"
#include "../../engine/input/mouse.h"
#include "widget.h"

namespace game
{
    namespace interface
    {

        Widget::Widget(Widget* parent, engine::Vector2d relativePosition, engine::Vector2d dimensions, int anchor) :
            m_parent(parent),
            m_relativePosition(relativePosition),
            m_angle(0),
            m_anchor(anchor),
            m_opacity(1),
            m_hidden(false),
            m_destroyed(false),
            m_requireMouseOverParent(false),
            m_onClick(LUA_NOREF)
        {
            engine::graphics::TexturedShowable::setDimensions(dimensions);

            if (parent != NULL)
            {
                parent->m_widgets.push_back(this);
                calcPosition();
            }
        }

        Widget::~Widget()
        {
            if (hasClickListener())
                luaL_unref(lua::getState(), LUA_REGISTRYINDEX, m_onClick);
                
            if (m_parent != NULL)
                m_parent->remove(this);
                
            std::vector<Widget*>::iterator end = m_widgets.end();
            for (std::vector<Widget*>::iterator it = m_widgets.begin(); it != end; it++)
            {
                (*it)->m_parent = NULL;
                delete *it;
            }
        }
        
        void Widget::setAnchor(int anchor)
        {
            m_anchor = anchor;
            resize();
        }

        void Widget::setRelativePosition(engine::Vector2d relativePosition)
        {
            m_relativePosition = relativePosition;
            resize();
        }

        void Widget::setDimensions(engine::Vector2d dimensions)
        {
            engine::graphics::TexturedShowable::setDimensions(dimensions);
            resize();
        }

        void Widget::setCenter(engine::Vector2d center)
        {
            engine::graphics::TexturedShowable::setCenter(center);
            resize();
        }

        void Widget::calcPosition()
        {
            engine::Vector2d position;
            engine::Vector2d center;

            bool setDimensions = false;
            engine::Vector2d dimensions = getDimensions();

            if ((m_anchor & (LEFT | RIGHT)) == (LEFT | RIGHT))
            {
                position.setX(m_parent->getAbsolutePosition().getX() + m_relativePosition.getX());
                center.setX(0);
                setDimensions = true;
                dimensions.setX(m_parent->getDimensions().getX());
            }
            else if (m_anchor & LEFT)
            {
                position.setX(m_parent->getAbsolutePosition().getX() + m_relativePosition.getX());
                center.setX(0);
            }
            else if (m_anchor & RIGHT)
            {
                position.setX(m_parent->getAbsolutePosition().getX() + m_parent->getDimensions().getX() + m_relativePosition.getX());
                center.setX(getDimensions().getX());
            }
            else // m_anchor & CENTERX
            {
                position.setX(m_parent->getAbsolutePosition().getX() + m_parent->getDimensions().getX() / 2 + m_relativePosition.getX());
                center.setX(getDimensions().getX() / 2);
            }

            if ((m_anchor & (TOP | BOTTOM)) == (TOP | BOTTOM))
            {
                position.setY(m_parent->getAbsolutePosition().getY() + m_relativePosition.getY());
                center.setY(0);
                setDimensions = true;
                dimensions.setY(m_parent->getDimensions().getY());
            }
            else if (m_anchor & TOP)
            {
                position.setY(m_parent->getAbsolutePosition().getY() + m_parent->getDimensions().getY() + m_relativePosition.getY());
                center.setY(getDimensions().getY());
            }
            else if (m_anchor & BOTTOM)
            {
                position.setY(m_parent->getAbsolutePosition().getY() + m_relativePosition.getY());
                center.setY(0);
            }
            else // m_anchor & CENTERY
            {
                position.setY(m_parent->getAbsolutePosition().getY() + m_parent->getDimensions().getY() / 2 + m_relativePosition.getY());
                center.setY(getDimensions().getY() / 2);
            }

            if (setDimensions)
                engine::graphics::TexturedShowable::setDimensions(dimensions);

            engine::graphics::TexturedShowable::setCenter(center);
            engine::graphics::TexturedShowable::setPosition(position);

            std::vector<Widget*>::iterator end = m_widgets.end();
            for (std::vector<Widget*>::iterator it = m_widgets.begin(); it != end; it++)
                (*it)->resize();
        }

        void Widget::resize()
        {
            if (m_parent != NULL)
                calcPosition();

            std::vector<Widget*>::iterator end = m_widgets.end();
            for (std::vector<Widget*>::iterator it = m_widgets.begin(); it != end; it++)
                (*it)->resize();
        }

        void Widget::show()
        {
            if (!m_destroyed && !m_hidden)
            {
                if (!m_requireMouseOverParent || m_parent->isMouseOver())
                {
                    if (hasClickListener() && isMouseOver())
                    {
                        engine::graphics::ColorAlpha(192, 192, 192, 255 * m_opacity).use();
                        showChildren();
                        engine::graphics::Color::WHITE.use();

                        if (engine::input::mouse::isJustPressed(M(LEFT)))
                        {
                            lua_State* L = lua::getState();
                            lua_rawgeti(L, LUA_REGISTRYINDEX, m_onClick);
                            lua_pushlightuserdata(L, this);
                            lua_call(L, 1, 0);
                        }
                    }
                    else
                        showChildren();
                }
            }
        }

        void Widget::showChildren()
        {
            if (!m_destroyed)
            {
                // copying children vector to allow modifications in the interface through lua code
                std::vector<Widget*> children = m_widgets;
                std::vector<Widget*>::iterator end = children.end();
                for (std::vector<Widget*>::iterator it = children.begin(); it != end; it++)
                    (*it)->show();
            }
        }

        void Widget::remove(Widget* widget)
        {
            //widget->m_parent = NULL;
            //std::remove(m_widgets.begin(), m_widgets.end(), widget);
            std::vector<Widget*>::iterator end = m_widgets.end();
            std::vector<Widget*>::iterator it = find(m_widgets.begin(), end, widget);
            if (it != end)
            {
                (*it)->m_parent = NULL;
                m_widgets.erase(it);
            }
        }

        void Widget::add(Widget* widget)
        {
            m_widgets.push_back(widget);
            widget->m_parent = this;
            calcPosition();
        }
        
        void Widget::destroyIfDestroyed()
        {
            if (m_destroyed)
                delete this;
            
            else
            {
                std::vector<Widget*> children = m_widgets;
                std::vector<Widget*>::iterator end = children.end();
                for (std::vector<Widget*>::iterator it = children.begin(); it != end; it++)
                    (*it)->destroyIfDestroyed();
            }
        }
        
        void Widget::setAllDestroyed()
        {
            m_destroyed = true;
            std::vector<Widget*>::iterator end = m_widgets.end();
            for (std::vector<Widget*>::iterator it = m_widgets.begin(); it != end; it++)
                (*it)->setAllDestroyed();
        }
        
        void Widget::clear()
        {
            std::vector<Widget*>::iterator end = m_widgets.end();
            for (std::vector<Widget*>::iterator it = m_widgets.begin(); it != end; it++)
                (*it)->m_destroyed = true;
        }

        bool Widget::isMouseOver()
        {
            if (m_hidden)
                return false;

            else
                return engine::graphics::TexturedShowable::isMouseOver();
        }

        void Widget::setOnClick(lua_State* L)
        {
            if (m_onClick != LUA_NOREF)
                luaL_unref(L, LUA_REGISTRYINDEX, m_onClick);
                
            if (lua_isnil(L, -1))
                m_onClick = LUA_NOREF;
                
            else
                m_onClick = luaL_ref(L, LUA_REGISTRYINDEX);
        }

    }
}
