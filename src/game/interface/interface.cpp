#include "interface.h"
#include "../../engine/input/window.h"

namespace game
{
    namespace interface
    {

        Interface::Interface() :
            Widget(NULL, engine::Vector2d(0, 0), engine::Vector2d(0, 0), TOP | LEFT)
        {
            show();
        }

        bool Interface::isVisible()
        {
            return true;
        }

        engine::Vector2d Interface::getDimensions() const
        {
            return engine::Vector2d(engine::input::window::getWidth(), engine::input::window::getHeight());
        }

        bool Interface::isMouseOver()
        {
            bool mouseOver = false;
            std::vector<Widget*>::iterator end = m_widgets.end();
            for (std::vector<Widget*>::iterator it = m_widgets.begin(); !mouseOver && it != end; it++)
                mouseOver = (*it)->isMouseOver();

            return mouseOver;
        }

    }
}
