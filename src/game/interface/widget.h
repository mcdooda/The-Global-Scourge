#ifndef GAME_INTERFACE_WIDGET_H
 #define GAME_INTERFACE_WIDGET_H

#include <vector>
#include "../../engine/graphics/texturedshowable.h"
#include "../../engine/graphics/window.h"
#include "../../engine/vector2d.h"
#include "../lua/lua.h"

namespace game
{
    namespace interface
    {

        class Widget : public engine::graphics::TexturedShowable
        {
            public:
                enum
                {
                    LEFT     = 0x01,
                    RIGHT    = 0x02,
                    CENTERX  = 0x04,
                    TOP      = 0x08,
                    BOTTOM   = 0x10,
                    CENTERY  = 0x20
                };

            public:
                Widget(Widget* parent, engine::Vector2d relativePosition, engine::Vector2d dimensions, int anchor);
                virtual ~Widget();

                inline engine::Vector2d getPosition() const { return m_position; }
                
                void setAnchor(int anchor);
                inline int getAnchor() const { return m_anchor; }
                
                inline float getOpacity() const { return m_opacity; }
                inline void setOpacity(float opacity) { m_opacity = opacity; }
                
                void setRelativePosition(engine::Vector2d relativePosition);
                inline engine::Vector2d getRelativePosition() const { return m_relativePosition; }
                
                inline void setAngle(float angle) { m_angle = angle; }
                
                void setDimensions(engine::Vector2d dimensions);
                void setCenter(engine::Vector2d center);

                void resize();
                virtual void show();
                void showChildren();
                
                inline Widget* getParent() const { return m_parent; }
                inline const std::vector<Widget*> getChildren() const { return m_widgets; }
                
                void remove(Widget* widget);
                void add(Widget* widget);
                void destroyIfDestroyed(); // weird name =)
                inline void setDestroyed() { m_destroyed = true; }
                void setAllDestroyed();
                void clear();

                inline void setHidden(bool hidden) { m_hidden = hidden; }
                inline bool isHidden() const { return m_hidden; }

                virtual bool isMouseOver();

                void setOnClick(lua_State* L);
                
                inline bool hasClickListener() const { return m_onClick != LUA_NOREF; }
                
                inline void setRequireMouseOverParent(bool requireMouseOverParent) { m_requireMouseOverParent = requireMouseOverParent; }

            protected:
                void calcPosition();

                Widget* m_parent;
                engine::Vector2d m_relativePosition;
                float m_angle;
                int m_anchor;
                float m_opacity;
                std::vector<Widget*> m_widgets;
                bool m_hidden;
                bool m_destroyed;
                bool m_requireMouseOverParent;
                int m_onClick;
        };

    }
}

#endif
