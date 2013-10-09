#ifndef ENGINE_RESOURCEMANAGER_H
 #define ENGINE_RESOURCEMANAGER_H

#include <map>
#include "graphics/texture.h"
#include "graphics/font.h"
#include "sound/sample.h"
#include "sound/music.h"

namespace engine
{

    template <class T> class ResourceManager
    {
        public:
            T* get(std::string name);

        private:
            T* load(std::string name);

            std::map<std::string, T*> m_resources;
    };

    class TextureManager : public ResourceManager<graphics::Texture> {};
    class FontManager : public ResourceManager<graphics::Font> {};
    class SampleManager : public ResourceManager<sound::Sample> {};
    class MusicManager : public ResourceManager<sound::Music> {};

}

#include "resourcemanager.inl"

#endif
