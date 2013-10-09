#ifndef ENGINE_VECTOR2D_H
 #define ENGINE_VECTOR2D_H

#ifndef M_PI
    #define M_PI 3.1415926535897932384626433832795
#endif

namespace engine
{

    class Vector2d
    {
        public:
            Vector2d(float x, float y);
            Vector2d(float alpha);
            Vector2d();

            float distance() const;
            float distanceSquared() const;
            float angle() const;
            Vector2d normalize() const;

            Vector2d operator+(const Vector2d& v) const;
            Vector2d operator-(const Vector2d& v) const;
            Vector2d operator*(const float& f) const;
            Vector2d operator/(const float& f) const;

            void operator+=(const Vector2d& v);
            void operator-=(const Vector2d& v);
            void operator*=(const float& f);
            void operator/=(const float& f);

            inline void setX(float x) { m_x = x; }
            inline void setY(float y) { m_y = y; }

            inline float getX() const { return m_x; }
            inline float getY() const { return m_y; }

            int getRoundX() const;
            int getRoundY() const;

        private:
            float m_x;
            float m_y;
    };

}

#endif

