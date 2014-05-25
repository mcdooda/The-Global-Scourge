#ifndef GAME_BRUSH_BRUSH_H
 #define GAME_BRUSH_BRUSH_H

#include "../lua/lua.h"
#include "../map/map.h"

namespace game
{
    namespace brush
    {

        class Brush
        {
            public:
                Brush();
                virtual ~Brush();

                inline float getSize() const { return m_size; }
                inline void setSize(float size) { m_size = size; }
                inline void growSize(float growth) { m_size += growth; }
                
                inline float getLimitWidth() const { return m_limitWidth < m_size ? m_limitWidth : m_size; }
                inline void setLimitWidth(float limitWidth) { m_limitWidth = limitWidth; }
                inline void growLimitWidth(float growth) { m_limitWidth += growth; }

                void incrementSize();
                void decrementSize();

                virtual float getEffect(float dx, float dy) const = 0;
                
                virtual void getTiles(map::Map* map, float x, float y, lua_State* L) const;
                virtual void getEntities(map::Map* map, float x, float y, float minEffect, const char* modelName, lua_State* L);
                
                static const float MAX_SIZE = 20;

            protected:

                float m_size;
                float m_limitWidth;
        };

    }
}

#endif
