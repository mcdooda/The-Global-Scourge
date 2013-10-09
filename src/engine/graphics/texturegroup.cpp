#include <cstdlib>
#include "texturegroup.h"
#include "../singleton.h"
#include "../random.h"
#include "../file/directory.h"
#include "../resourcemanager.h"

namespace engine
{
    namespace graphics
    {

        TextureGroup::TextureGroup()
        {
            m_textures = NULL;
            m_numTextures = 0;
        }

        Texture* TextureGroup::getRandomTexture() const
        {
            return m_textures[random::rint(0, m_numTextures - 1)];
        }

        void TextureGroup::add(std::string filename)
        {
            Texture* t = S(TextureManager)->get(filename);
            m_textures = (Texture**) realloc(m_textures, (m_numTextures + 1) * sizeof(Texture*));
            m_textures[m_numTextures] = t;
            m_numTextures++;
        }

        void TextureGroup::addDir(std::string dirname)
        {
            file::Directory dir(dirname);
            dir.read();
            std::vector<file::File*> files = dir.getFiles();
            std::vector<file::File*>::iterator end = files.end();
            for (std::vector<file::File*>::iterator it = files.begin(); it != end; it++)
                add((*it)->getPath());
        }
    }
}

