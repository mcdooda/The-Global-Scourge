#ifndef ENGINE_GRAPHICS_TEXT_H
 #define ENGINE_GRAPHICS_TEXT_H

#include <string>
#include <SDL/SDL_ttf.h>
#include "texture.h"
#include "color.h"
#include "font.h"

namespace engine
{
    namespace graphics
    {

        class Text : public Texture
        {
            public:
                Text(std::string string, Font* font, Color color);
                ~Text();

                static void init()
                {
                    TTF_Init();
                }

                static void free()
                {
                    TTF_Quit();
                }
                
                inline const std::string& getString() const { return m_string; }
                inline Font* getFont() const { return m_font; }
                inline Color getColor() const { return m_color; }
                
            protected:
                std::string m_string;
                Font* m_font;
                Color m_color;
        };

    }
}

#endif
