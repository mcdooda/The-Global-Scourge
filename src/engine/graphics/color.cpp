#include <GL/gl.h>
#include "color.h"

namespace engine
{
    namespace graphics
    {
    
        Color Color::WHITE = Color(255);
        Color Color::BLACK = Color(0);

        Color::Color(unsigned char r, unsigned char g, unsigned char b) :
            m_r(r),
            m_g(g),
            m_b(b)
        {

        }
        
        Color::Color(unsigned char gray) :
            m_r(gray),
            m_g(gray),
            m_b(gray)
        {
            
        }

        void Color::use()
        {
            glColor3ub(m_r, m_g, m_b);
        }
        
        void Color::unuse()
        {
            glColor3ub(255, 255, 255);
        }

        void Color::clear()
        {
            glClearColor(m_r / 255.f, m_g / 255.f, m_b / 255.f, 0);
        }
        
        Color* Color::newCopy()
        {
            return new Color(m_r, m_g, m_b);
        }

    }
}
