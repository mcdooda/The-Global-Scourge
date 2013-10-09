#ifndef ENGINE_GRAPHICS_TEXTUREGROUP_H
 #define ENGINE_GRAPHICS_TEXTUREGROUP_H

#include "texture.h"

namespace engine
{
    namespace graphics
    {

        class TextureGroup
        {
            public:
                TextureGroup();

                Texture* getRandomTexture() const;
                inline Texture* getTexture(int index) const { return m_textures[index]; }
                inline Texture* getFirstTexture() const { return m_textures[0]; }

                void add(std::string filename);
                void addDir(std::string dirname);

                inline int getNumTextures() const { return m_numTextures; }

            private:
                Texture** m_textures;
                int m_numTextures;
        };

    }
}

#endif
