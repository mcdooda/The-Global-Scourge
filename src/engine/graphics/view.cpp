#include <iostream>
#include "view.h"
#include "window.h"

namespace engine
{
    namespace graphics
    {

        View::View(Vector2d center, float scale) :
            m_center(center),
            m_scale(scale)
        {

        }

        View::View() :
            m_center(0, 0),
            m_scale(1)
        {

        }

        void View::zoom(float factor, float minOrMax)
        {
            m_scale *= factor;

            if (factor < 1 && m_scale < minOrMax)
                m_scale = minOrMax;

            else if (factor > 1 && m_scale > minOrMax)
                m_scale = minOrMax;
        }

        void View::move(Vector2d move)
        {
            m_center += move;
        }

        void View::updateBorders()
        {
            m_left = m_center.getX() - (float) window::getWidth() / 2 / m_scale;
            m_right = m_center.getX() + (float) window::getWidth() / 2 / m_scale;
            m_bottom = m_center.getY() - (float) window::getHeight() / 2 / m_scale;
            m_top = m_center.getY() + (float) window::getHeight() / 2 / m_scale;
            m_width = (float) window::getWidth() / m_scale;
            m_height = (float) window::getHeight() / m_scale;
        }
        
        float View::getRelativeX(int screenX) const
        {
            return (float) m_left + (m_right - m_left) * ((float) screenX / graphics::window::getWidth());
        }
        
        float View::getRelativeY(int screenY) const
        {
            return (float) m_bottom + (m_top - m_bottom) * ((float) screenY / graphics::window::getHeight());
        }
        
        engine::Vector2d View::getRelativePosition(int screenX, int screenY) const
        {
            return engine::Vector2d((float) m_left + (m_right - m_left) * ((float) screenX / graphics::window::getWidth()), (float) m_bottom + (m_top - m_bottom) * ((float) screenY / graphics::window::getHeight()));
        }

    }
}
