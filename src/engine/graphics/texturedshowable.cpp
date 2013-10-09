#include <GL/gl.h>
#include "texturedshowable.h"
#include "window.h"
#include "../input/mouse.h"

namespace engine
{
    namespace graphics
    {

        TexturedShowable::TexturedShowable(Vector2d dimensions, Vector2d center)
        {
            m_dimensions = dimensions;
            m_center = center;
            resetTextureCoords();
            updateVertices();
        }

        void TexturedShowable::resetTextureCoords()
        {
            static float textureCoords[8] = {0,1, 1,1, 1,0, 0,0};
            m_textureCoords = textureCoords;
        }

        void TexturedShowable::show()
        {
            glBindTexture(GL_TEXTURE_2D, m_texture->getId());
            glVertexPointer(2, GL_FLOAT, 0, m_vertices);
            glTexCoordPointer(2, GL_FLOAT, 0, m_textureCoords);
            glDrawArrays(GL_QUADS, 0, 4);
        }

        bool TexturedShowable::isVisible()
        {
            const View& view = window::getView();
            return getRight() > view.getLeft()
                && getLeft() < view.getRight()
                && getTop() > view.getBottom()
                && getBottom() < view.getTop();
        }

        bool TexturedShowable::isMouseOver()
        {
            const float x = input::mouse::getX();
            const float y = input::mouse::getY();
            return x >= getLeft()
                && x <= getRight()
                && y >= getBottom()
                && y <= getTop();
        }

        Vector2d TexturedShowable::getDimensions() const
        {
            return m_dimensions;
        }
        
        ColorAlpha TexturedShowable::getPixel(int x, int y)
        {
            int spriteX = x + m_textureCoords[0] * m_texture->getWidth();
            int spriteY = y + m_textureCoords[5] * m_texture->getHeight();
            return m_texture->getPixel(spriteX, spriteY);
        }

        void TexturedShowable::updateVertices()
        {
            m_vertices[0] = m_position.getX() - m_center.getX();
            m_vertices[1] = m_position.getY() - m_center.getY();

            m_vertices[2] = m_position.getX() - m_center.getX() + m_dimensions.getX();
            m_vertices[3] = m_position.getY() - m_center.getY();

            m_vertices[4] = m_position.getX() - m_center.getX() + m_dimensions.getX();
            m_vertices[5] = m_position.getY() - m_center.getY() + m_dimensions.getY();

            m_vertices[6] = m_position.getX() - m_center.getX();
            m_vertices[7] = m_position.getY() - m_center.getY() + m_dimensions.getY();
        }



    }
}
