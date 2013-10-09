#ifndef ENGINE_GRAPHICS_VIEW_H
 #define ENGINE_GRAPHICS_VIEW_H

#include "../vector2d.h"

namespace engine
{
    namespace graphics
    {

        class View
        {
            public:
                View(Vector2d center, float scale);
                View();

                void zoom(float factor, float minOrMax);
                void move(Vector2d position);
                inline void setCenter(Vector2d center) { m_center = center; }
                inline void setScale(float scale) { m_scale = scale; }

                inline Vector2d getCenter() const { return m_center; }
                inline float getScale() const { return m_scale; }

                inline float getLeft()   const { return m_left; }
                inline float getRight()  const { return m_right; }
                inline float getBottom() const { return m_bottom; }
                inline float getTop()    const { return m_top; }

                inline float getWidth()  const { return m_width; }
                inline float getHeight() const { return m_height; }
                
                float getRelativeX(int screenX) const;
                float getRelativeY(int screenY) const;
                engine::Vector2d getRelativePosition(int screenX, int screenY) const;

                void updateBorders();

            private:

                Vector2d m_center;
                float m_scale;

                float m_left;
                float m_right;
                float m_bottom;
                float m_top;

                float m_width;
                float m_height;
        };

    }
}

#endif
