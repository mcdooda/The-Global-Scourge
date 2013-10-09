#include <GL/gl.h>
#include "coloralpha.h"

namespace engine
{
    namespace graphics
    {
        ColorAlpha::ColorAlpha(unsigned char r, unsigned char g, unsigned char b, unsigned char a) :
            Color(r, g, b),
            m_a(a)
        {

        }
        
        ColorAlpha::ColorAlpha(unsigned char gray) :
            Color(gray),
            m_a(255)
        {
            
        }

        void ColorAlpha::use()
        {
            glColor4ub(m_r, m_g, m_b, m_a);
        }
        
        void ColorAlpha::unuse()
        {
            glColor4ub(255, 255, 255, 255);
        }
        
        Color* ColorAlpha::newCopy()
        {
            return new ColorAlpha(m_r, m_g, m_b, m_a);
        }

    }
}
