#ifndef ENGINE_GRAPHICS_COLORALPHA_H
 #define ENGINE_GRAPHICS_COLORALPHA_H

#include "color.h"

namespace engine
{
    namespace graphics
    {

        class ColorAlpha : public Color
        {
            public:
                ColorAlpha(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
                ColorAlpha(unsigned char gray);

                inline unsigned char getA() const { return m_a; }

                inline void setA(unsigned char a) { m_a = a; }

                virtual void use();
                virtual void unuse();
                virtual Color* newCopy();

            private:
                unsigned char m_a;
        };

    }
}

#endif
