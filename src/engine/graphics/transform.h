#ifndef ENGINE_GRAPHICS_TRANSFORM_H
 #define ENGINE_GRAPHICS_TRANSFORM_H

namespace engine
{
    namespace graphics
    {
        namespace transform
        {
            static const float PI = 3.1415926535898;
            
            void push();
            void pop();
            void rotate(float angle);
            void translate(float x, float y);
            
        }
    }
}

#endif
