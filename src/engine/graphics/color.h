#ifndef ENGINE_GRAPHICS_COLOR_H
 #define ENGINE_GRAPHICS_COLOR_H

namespace engine
{
    namespace graphics
    {

        class Color
        {
            public:
                Color(unsigned char r, unsigned char g, unsigned char b);
                Color(unsigned char gray);
                virtual ~Color();

                inline unsigned char getR() const { return m_r; }
                inline unsigned char getG() const { return m_g; }
                inline unsigned char getB() const { return m_b; }

                inline void setR(unsigned char r) { m_r = r; }
                inline void setG(unsigned char g) { m_g = g; }
                inline void setB(unsigned char b) { m_b = b; }

                virtual void use();
                virtual void unuse();
                
                void clear();
                
                virtual Color* newCopy();
                
                static Color WHITE;
                static Color BLACK;

            protected:
                unsigned char m_r;
                unsigned char m_g;
                unsigned char m_b;
        };

    }
}

#endif
