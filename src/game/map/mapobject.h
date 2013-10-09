#ifndef GAME_MAP_MAPOBJECT_H
 #define GAME_MAP_MAPOBJECT_H

#include "../../engine/graphics/texturedshowable.h"
#include "../../engine/graphics/color.h"

namespace game
{
    namespace map
    {

        class MapObject : public engine::graphics::TexturedShowable
        {
            public:
                MapObject();
                virtual ~MapObject();

                inline float getDepth() const { return m_depth; }
                
                inline void setColor(engine::graphics::Color* color) { delete m_color; m_color = color; }
                inline engine::graphics::Color* getColor() const { return m_color; }

            protected:
                inline void setDepth(float depth) { m_depth = depth; }
                virtual void calcDepth(float x, float y, float radius);
                
                engine::graphics::Color* m_color;

            private:
                float m_depth;
        };

    }
}

#endif
