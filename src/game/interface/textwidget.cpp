#include <iostream>
#include "textwidget.h"

namespace game
{
    namespace interface
    {

        TextWidget::TextWidget(Widget* parent, engine::Vector2d relativePosition, int anchor, engine::graphics::Text* text) :
            ImageWidget(parent, relativePosition, anchor, text, false)
        {
            m_text = text;
        }
        
        TextWidget::~TextWidget()
        {
            delete m_text;
        }
        
        void TextWidget::setText(std::string string)
        {
            engine::graphics::Font* font = m_text->getFont();
            engine::graphics::Color color = m_text->getColor();
            delete m_text;
            m_text = new engine::graphics::Text(string, font, color);
            setTexture(m_text);
            engine::graphics::TexturedShowable::setDimensions(m_text->getDimensions());
            updateVertices();
            calcPosition();
        }
        
        void TextWidget::setColor(engine::graphics::Color color)
        {
            engine::graphics::Font* font = m_text->getFont();
            const std::string string = m_text->getString();
            delete m_text;
            m_text = new engine::graphics::Text(string, font, color);
            setTexture(m_text);
            //engine::graphics::TexturedShowable::setDimensions(m_text->getDimensions());
            //updateVertices();
        }

    }
}
