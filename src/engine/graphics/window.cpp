#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include "window.h"

namespace engine
{
    namespace graphics
    {
        namespace window
        {

            static int windowWidth;
            static int windowHeight;
            static int oldWindowWidth;
            static int oldWindowHeight;
            static bool fullScreen;
            static SDL_Surface* screen;

            static View windowView(Vector2d(0, 0), 1);

            void open(int width, int height, std::string name, bool full)
            {
                int flags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE;

                if (full)
                    flags |= SDL_FULLSCREEN;

                screen = SDL_SetVideoMode(width, height, 32, flags);
                SDL_WM_SetCaption(name.c_str(), name.c_str());
                SDL_WarpMouse(width / 2, height / 2);

                windowWidth = width;
                windowHeight = height;

                oldWindowWidth = width;
                oldWindowHeight = height;

                fullScreen = full;

                glEnableClientState(GL_VERTEX_ARRAY);
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                glEnable(GL_TEXTURE_2D);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                resize();
            }

            void toggleFullScreen()
            {
                SDL_WM_ToggleFullScreen(screen);
                /*
                fullScreen = !fullScreen;

                int flags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE;

                int width;
                int height;

                if (fullScreen)
                {
                    flags |= SDL_FULLSCREEN;
                    oldWindowWidth = windowWidth;
                    oldWindowHeight = windowHeight;
                    width = getDesktopWidth();
                    height = getDesktopHeight();
                }
                else
                {
                    width = oldWindowWidth;
                    height = oldWindowHeight;
                }

                SDL_FreeSurface(screen);
                screen = SDL_SetVideoMode(width, height, 32, flags);

                resize();
                */
            }

            bool isFullScreen()
            {
                return fullScreen;
            }

            int getWidth()
            {
                return windowWidth;
            }

            int getHeight()
            {
                return windowHeight;
            }

            int getDesktopWidth()
            {
                const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
                return videoInfo->current_w;
            }

            int getDesktopHeight()
            {
                const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
                return videoInfo->current_h;
            }

            void setView(View view)
            {
                windowView = view;
                windowView.updateBorders();
                glLoadIdentity();
                gluOrtho2D(windowView.getLeft(), windowView.getRight(), windowView.getBottom(), windowView.getTop());
            }

            const View& getView()
            {
                return windowView;
            }

            void setInterfaceView()
            {
                windowView = View(Vector2d((float) windowWidth / 2, (float) windowHeight / 2), 1);
                glLoadIdentity();
                gluOrtho2D(0, windowWidth, 0, windowHeight);
            }

            void resize()
            {
                glViewport(0, 0, windowWidth, windowHeight);
                setView(windowView);
            }

            /* private */
            void setWidth(int width)
            {
                windowWidth = width;
            }

            void setHeight(int height)
            {
                windowHeight = height;
            }

        }
    }
}


