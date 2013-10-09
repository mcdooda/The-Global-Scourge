#include <cmath>
#include "vector2d.h"

namespace engine
{

    Vector2d::Vector2d(float x, float y) :
        m_x(x),
        m_y(y)
    {

    }

    Vector2d::Vector2d(float alpha)
    {
        m_x = cos(alpha);
        m_y = sin(alpha);
    }

    Vector2d::Vector2d() :
        m_x(0),
        m_y(0)
    {

    }

    float Vector2d::distance() const
    {
        return sqrt(m_x * m_x + m_y * m_y);
    }

    float Vector2d::distanceSquared() const
    {
        return m_x * m_x + m_y * m_y;
    }

    float Vector2d::angle() const
    {
        float angle = atan(m_y / m_x);

        if (m_x < 0)
            angle += M_PI;

        return angle;
    }

    Vector2d Vector2d::normalize() const
    {
        float d = distance();

        if (d != 0)
            return Vector2d(m_x / d, m_y / d);

        else
            return *this;
    }

    Vector2d Vector2d::operator+(const Vector2d& v) const
    {
        return Vector2d(m_x + v.m_x, m_y + v.m_y);
    }

    Vector2d Vector2d::operator-(const Vector2d& v) const
    {
        return Vector2d(m_x - v.m_x, m_y - v.m_y);
    }

    Vector2d Vector2d::operator*(const float& f) const
    {
        return Vector2d(m_x * f, m_y * f);
    }

    Vector2d Vector2d::operator/(const float& f) const
    {
        if (f != 0)
            return Vector2d(m_x / f, m_y / f);

        else
            return *this;
    }

    void Vector2d::operator+=(const Vector2d& v)
    {
        m_x += v.m_x;
        m_y += v.m_y;
    }

    void Vector2d::operator-=(const Vector2d& v)
    {
        m_x -= v.m_x;
        m_y -= v.m_y;
    }

    void Vector2d::operator*=(const float& f)
    {
        m_x *= f;
        m_y *= f;
    }

    void Vector2d::operator/=(const float& f)
    {
        if (f != 0)
        {
            m_x /= f;
            m_y /= f;
        }
    }

    int Vector2d::getRoundX() const
    {
        return round(m_x);
    }

    int Vector2d::getRoundY() const
    {
        return round(m_y);
    }

}

