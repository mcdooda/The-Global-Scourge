#include <math.h>
#include <GL/gl.h>
#include "transform.h"

namespace engine
{
    namespace graphics
    {
        namespace transform
        {
            
            void push()
            {
                glPushMatrix();
            }
            
            void pop()
            {
                glPopMatrix();
            }
            
            void rotate(float angle)
            {
                glRotatef(angle * 180 / PI, 0, 0, 1);
            }
            
            void translate(float x, float y)
            {
                glTranslatef(x, y, 0);
            }
            
        }
    }
}
