#ifndef ENGINE_GRAPHICS_TEXTURE_H
 #define ENGINE_GRAPHICS_TEXTURE_H

#include <string>
#include <SDL/SDL.h>
#include "../vector2d.h"
#include "coloralpha.h"

namespace engine
{
    namespace graphics
    {

        class Texture
        {
            public:
                Texture(std::string filename);

                inline unsigned int getId() const { return m_id; }
                inline unsigned int getWidth() const { return m_surface->w; }
                inline unsigned int getHeight() const { return m_surface->h; }
                inline Vector2d getDimensions() const { return Vector2d(m_surface->w, m_surface->h); }

                inline const std::string& getPath() const { return m_path; }
                
                ColorAlpha getPixel(int x, int y);

            protected:
                Texture() {}

                void load();
                void free();
                
                SDL_Surface* m_surface;
                
                unsigned int m_id;

                std::string m_path;
        };

    }
}

#endif
