#include <SDL/SDL.h>
#include "time.h"

namespace engine
{
    namespace time
    {

        static bool timePaused;
        static float pauseTime;
        static float pauseRealTime;
        static float pauseElapsedTime;

        static float frameTime;
        static float beginFrameTime;
        static float frameDuration;

        void beginFrame()
        {
            beginFrameTime = getRealTime();
        }

        void endFrame()
        {
            float endFrameTime = getRealTime();
            frameTime = endFrameTime - beginFrameTime;
            if (frameTime < frameDuration)
            {
                sleep(frameDuration - frameTime);
                frameTime = frameDuration;
            }
        }

        void setFrameRate(float rate)
        {
            frameDuration = 1.f / rate;
        }

        void sleep(float duration)
        {
            SDL_Delay(duration * 1000);
        }

        float getRealTime()
        {
            return SDL_GetTicks() / 1000.f;
        }

        void pause()
        {
            if (!timePaused)
            {
                pauseTime = getTime();
                pauseRealTime = getRealTime();
                timePaused = true;
            }
        }

        void resume()
        {
            timePaused = false;
            pauseElapsedTime += getRealTime() - pauseRealTime;
        }

        bool isPaused()
        {
            return timePaused;
        }

        float getTime()
        {
            return timePaused ? pauseTime : getRealTime() - pauseElapsedTime;
        }

        float getFrameTime()
        {
            return timePaused ? 0 : frameTime;
        }

        /* private */
        void init()
        {
            timePaused = false;
            pauseElapsedTime = 0;

        }

        void free()
        {

        }

    }
}
