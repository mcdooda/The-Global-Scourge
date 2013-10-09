#ifndef ENGINE_GRAPHICS_TEXTUREDSHOWABLE_H
 #define ENGINE_GRAPHICS_TEXTUREDSHOWABLE_H

#include "showable.h"
#include "texture.h"
#include "view.h"

namespace engine
{
    namespace graphics
    {

        class TexturedShowable : public Showable
        {
            public:
                TexturedShowable(Vector2d dimensions, Vector2d center);

                void resetTextureCoords();
                inline void setTextureCoords(float* textureCoords) { m_textureCoords = textureCoords; }
                virtual void show();
                virtual bool isVisible();
                virtual bool isMouseOver();
                inline void setPosition(Vector2d position) { m_position = position; updateVertices(); }
                virtual Vector2d getDimensions() const;
                inline Vector2d getPosition() const { return m_position; }
                inline Vector2d getAbsolutePosition() const { return m_position - m_center; }
                ColorAlpha getPixel(int x, int y);
                
                inline const std::string& getTexturePath() const { return m_texture->getPath(); }

            protected:
                TexturedShowable() {}

                inline void setTexture(Texture* texture) { m_texture = texture; }
                inline void setDimensions(Vector2d dimensions) { m_dimensions = dimensions; }
                inline void setCenter(Vector2d center) { m_center = center; }
                void updateVertices();

                inline float getLeft()   const { return m_vertices[0]; }
                inline float getRight()  const { return m_vertices[2]; }
                inline float getTop()    const { return m_vertices[5]; }
                inline float getBottom() const { return m_vertices[1]; }

            private:

                Texture* m_texture;
                float m_vertices[8];
                float* m_textureCoords;
                Vector2d m_dimensions;
                Vector2d m_center;
        };

    }
}

#endif
