#include <iostream>
#include <SDL/SDL_mixer.h>
#include "sample.h"

namespace engine
{
    namespace sound
    {
        
        Sample::Sample(std::string filename)
        {
            m_chunk = Mix_LoadWAV(filename.c_str());
            
            if (m_chunk == NULL)
                std::cout << "error in Mix_LoadWAV(" << filename.c_str() << ") : " << Mix_GetError() << std::endl;
        }
        
        Sample::~Sample()
        {
            Mix_FreeChunk(m_chunk);
        }
        
        int Sample::play()
        {
            return Mix_PlayChannel(-1, m_chunk, 0);
        }
        
        void Sample::stopChannel(int channel)
        {
            Mix_HaltChannel(channel);
        }
        
        void Sample::setChannelVolume(int channel, float volume)
        {
            Mix_Volume(channel, volume * MIX_MAX_VOLUME);
        }
        
        void Sample::fadeOutChannel(int channel, float duration)
        {
            Mix_FadeOutChannel(channel, duration * 1000);
        }
        
    }
}


