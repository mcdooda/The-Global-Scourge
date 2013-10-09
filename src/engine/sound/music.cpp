#include "music.h"

namespace engine
{
    namespace sound
    {
        
        Music::Music(std::string filename)
        {
            m_music = Mix_LoadMUS(filename.c_str());
        }
        
        Music::~Music()
        {
            Mix_FreeMusic(m_music);
        }
        
        void Music::play()
        {
            Mix_PlayMusic(m_music, -1);
        }
        
        void Music::fadeIn(float duration)
        {
            Mix_FadeInMusic(m_music, -1, duration * 1000);
        }
        
        void Music::setVolume(float volume)
        {
            Mix_VolumeMusic(volume * MIX_MAX_VOLUME);
        }
        
        void Music::fadeOut(float duration)
        {
            Mix_FadeOutMusic(duration * 1000);
        }
        
        bool Music::isPaused()
        {
            return Mix_PausedMusic();
        }
        
        void Music::pause()
        {
            Mix_PauseMusic();
        }
        
        void Music::resume()
        {
            Mix_ResumeMusic();
        }
        
        void Music::rewind()
        {
            Mix_RewindMusic();
        }
        
        void Music::stop()
        {
            Mix_HaltMusic();
        }
        
    }
}


