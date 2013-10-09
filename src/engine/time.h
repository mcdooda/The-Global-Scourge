#ifndef ENGINE_TIME_H
 #define ENGINE_TIME_H

namespace engine
{
    namespace time
    {

        void beginFrame();
        void endFrame();
        void setFrameRate(float rate);

        void sleep(float duration);
        float getRealTime();

        void pause();
        void resume();
        bool isPaused();

        float getTime();
        float getFrameTime();

        /* private */
        void init();
        void free();

    }
}

#endif
