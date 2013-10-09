#ifndef ENGINE_SOUND_SAMPLE_H
 #define ENGINE_SOUND_SAMPLE_H

#include <SDL/SDL_mixer.h>

namespace engine
{
    namespace sound
    {
        
        class Sample
        {
            public:
                Sample(std::string filename);
                ~Sample();
                
                int play();
                
                static void stopChannel(int channel);
                static void setChannelVolume(int channel, float volume);
                static void fadeOutChannel(int channel, float duration);
                
            protected:
                
                
                Mix_Chunk* m_chunk;
        };
        
    }
}

#endif


