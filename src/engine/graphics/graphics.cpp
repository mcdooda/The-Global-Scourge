#include <GL/gl.h>
#include <SDL/SDL.h>
#include "graphics.h"
#include "text.h"

namespace engine
{
    namespace graphics
    {

        void beginFrame()
        {
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void endFrame()
        {
            glFlush();
            SDL_GL_SwapBuffers();
        }

        void init()
        {
            Text::init();
        }

        void free()
        {
            Text::free();
        }

    }
}
