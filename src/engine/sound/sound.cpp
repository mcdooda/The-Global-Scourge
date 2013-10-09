#include <SDL/SDL_mixer.h>
#include "sound.h"

namespace engine
{
    namespace sound
    {
        
        void init()
        {
            Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
        }
        
        void free()
        {
            Mix_CloseAudio();
        }
        
    }
}


