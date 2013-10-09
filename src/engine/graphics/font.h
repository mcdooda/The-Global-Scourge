#ifndef ENGINE_GRAPHICS_FONT_H
 #define ENGINE_GRAPHICS_FONT_H

#include <string>
#include <SDL/SDL_ttf.h>

namespace engine
{
    namespace graphics
    {

        class Font
        {
            public:
                Font(std::string font);
                ~Font();
                
            protected:
                friend class Text;
                
                TTF_Font* m_font;
        };

    }
}

#endif
