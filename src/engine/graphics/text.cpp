#include <iostream>
#include <SDL/SDL_ttf.h>
#include "text.h"

namespace engine
{
    namespace graphics
    {

        Text::Text(std::string string, Font* font, Color color) :
            m_string(string),
            m_font(font),
            m_color(color)
        {
            SDL_Color sdlColor = { color.getB(), color.getG(), color.getR() };
            m_surface = TTF_RenderUTF8_Blended(font->m_font, string.c_str(), sdlColor);
            if (m_surface != NULL)
                load();
                
            else
                std::cout << "error in TTF_RenderText_Blended(" << string.c_str() << ") : " << TTF_GetError() << std::endl;
        }
        
        Text::~Text()
        {
            Texture::free();
        }

    }
}
