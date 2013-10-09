#include <iostream>
#include "imagewidget.h"
#include "../../engine/graphics/color.h"
#include "../../engine/graphics/transform.h"
#include "../../engine/input/mouse.h"

namespace game
{
    namespace interface
    {

        ImageWidget::ImageWidget(Widget* parent, engine::Vector2d relativePosition, int anchor, engine::graphics::Texture* texture, bool pixelPerfect) :
            Widget(parent, relativePosition, texture->getDimensions(), anchor),
            m_pixelPerfect(pixelPerfect)
        {
            setTexture(texture);
            resetTextureCoords();
        }
        
        void ImageWidget::show()
        {
            if (!m_destroyed && !m_hidden)
            {
                if (!m_requireMouseOverParent || m_parent->isMouseOver())
                {
                    if (hasClickListener() && isMouseOver())
                    {
                        engine::graphics::ColorAlpha(192, 192, 192, 255 * m_opacity).use();
                        
                        showTexture();
                        showChildren();
                        engine::graphics::Color::WHITE.use();

                        if (engine::input::mouse::isJustPressed(M(LEFT)))
                        {
                            lua_State* L = lua::getState();
                            lua_rawgeti(L, LUA_REGISTRYINDEX, m_onClick);
                            lua_pushlightuserdata(L, this);
                            lua_call(L, 1, 0);
                        }
                    }
                    else
                    {
                        if (m_parent != NULL && m_parent->hasClickListener() && m_parent->isMouseOver())
                            engine::graphics::ColorAlpha(192, 192, 192, 255 * m_opacity).use();
                            
                        else
                            engine::graphics::ColorAlpha(255, 255, 255, 255 * m_opacity).use();
                        
                        showTexture();
                        showChildren();
                    }
                    }
            }
        }
        
        void ImageWidget::setTextureCoords(float lX, float bY, float rX, float tY)
        {
            m_textureCoords[0] = lX;
            m_textureCoords[1] = bY;
            m_textureCoords[2] = rX;
            m_textureCoords[3] = bY;
            m_textureCoords[4] = rX;
            m_textureCoords[5] = tY;
            m_textureCoords[6] = lX;
            m_textureCoords[7] = tY;
            Widget::setTextureCoords(m_textureCoords);
        }
        
        void ImageWidget::resetTextureCoords()
        {
            setTextureCoords(0, 1, 1, 0);
        }
        
        bool ImageWidget::isMouseOver()
        {
            bool mouseOver = Widget::isMouseOver();
            
            if (mouseOver && m_pixelPerfect)
            {
                int x = engine::input::mouse::getX() - getLeft();
                int y = engine::input::mouse::getY() - getBottom();
                if (getPixel(x, y).getA() < 128)
                    mouseOver = false;
            }
            
            return mouseOver;
        }
        
        void ImageWidget::showTexture()
        {
            if (m_angle != 0)
            {
                engine::Vector2d position = engine::graphics::TexturedShowable::getPosition();
                engine::graphics::TexturedShowable::setPosition(engine::Vector2d(0, 0));
                engine::graphics::transform::push();
                engine::graphics::transform::translate(position.getX(), position.getY());
                engine::graphics::transform::rotate(m_angle);
                engine::graphics::TexturedShowable::show();
                engine::graphics::transform::pop();
                engine::graphics::TexturedShowable::setPosition(position);
            }
            else
                engine::graphics::TexturedShowable::show();
        }

    }
}
