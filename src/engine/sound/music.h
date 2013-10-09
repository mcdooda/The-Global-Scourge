#ifndef ENGINE_SOUND_MUSIC_H
 #define ENGINE_SOUND_MUSIC_H

#include <string>
#include <SDL/SDL_mixer.h>

namespace engine
{
    namespace sound
    {
        
        class Music
        {
            public:
                Music(std::string filename);
                ~Music();
                
                void play();
                void fadeIn(float duration);
                
                static void setVolume(float volume);
                static void fadeOut(float duration);
                static bool isPaused();
                static void pause();
                static void resume();
                static void rewind();
                static void stop();
                
            protected:
                Mix_Music* m_music;
        };
        
    }
}

#endif


