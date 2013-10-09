#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "texture.h"

namespace engine
{
    namespace graphics
    {

        Texture::Texture(std::string filename) :
            m_path(filename)
        {
            m_surface = IMG_Load(filename.c_str());
            
            if (m_surface != NULL)
                load();
                
            else
                std::cout << "error in IMG_Load(" << filename.c_str() << ") : " << IMG_GetError() << std::endl;
        }
        
        ColorAlpha Texture::getPixel(int x, int y)
        {
            Uint32 pixel = *((Uint32*) m_surface->pixels + (m_surface->h - y) * m_surface->w + x);
            Uint8 r, g, b, a;
            SDL_GetRGBA(pixel, m_surface->format, &r, &g, &b, &a);
            return ColorAlpha(r, g, b, a);
        }

        void Texture::load()
        {
            glGenTextures(1, &m_id);
            glBindTexture(GL_TEXTURE_2D, m_id);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_surface->w, m_surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_surface->pixels);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }

        void Texture::free()
        {
            glDeleteTextures(1, &m_id);
            SDL_FreeSurface(m_surface);
        }

    }
}
