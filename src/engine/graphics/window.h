#ifndef ENGINE_GRAPHICS_WINDOW_H
 #define ENGINE_GRAPHICS_WINDOW_H

#include <string>
#include "view.h"

namespace engine
{
    namespace graphics
    {
        namespace window
        {

            void open(int width, int height, std::string name, bool full);

            void toggleFullScreen();
            bool isFullScreen();

            int getWidth();
            int getHeight();

            int getDesktopWidth();
            int getDesktopHeight();

            void setView(View view);
            const View& getView();
            void setInterfaceView();

            void resize();

            /* private */
            void setHeight(int height);
            void setWidth(int width);

        }
    }
}

#endif
