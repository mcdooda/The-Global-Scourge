#include "camera.h"
#include "../../engine/singleton.h"
#include "../../engine/input/mouse.h"
#include "../../engine/input/keyboard.h"
#include "../../engine/graphics/window.h"
#include "../../engine/time.h"
#include "../game.h"
#include "../mod/mod.h"

namespace game
{
    namespace camera
    {
        static bool locked = false;
        
        void lookAt(engine::Vector2d position)
        {
            int tileWidth = S(Mod)->getTileWidth();
            engine::Vector2d cameraCenter((engine::Vector2d(-2, -1) * position.getX() + engine::Vector2d(2, -1) * position.getY()) * tileWidth / 4);
            S(Game)->getView()->setCenter(cameraCenter);
        }
        
        engine::Vector2d getCenter()
        {
            map::Map* map = S(Game)->getMap();
            engine::graphics::View* view = S(Game)->getView();
            return map->getMapPosition(view->getRelativePosition(engine::graphics::window::getWidth() / 2, engine::graphics::window::getHeight() / 2));
        }
        
        void move()
        {
            if (!locked)
            {
                engine::Vector2d move;
                
                int tileWidth = S(Mod)->getTileWidth();
                int tileHeight = S(Mod)->getTileHeight();
                
                static const int m = 10;
                int mouseX = engine::input::mouse::getX();
                int mouseY = engine::input::mouse::getY();
                
                if (engine::input::keyboard::isPressed(K(LEFT)) || mouseX < m)
                    move.setX(-tileWidth);
                
                else if (engine::input::keyboard::isPressed(K(RIGHT)) || mouseX > engine::graphics::window::getWidth() - m)
                    move.setX(tileWidth);
                
                
                if (engine::input::keyboard::isPressed(K(UP)) || mouseY > engine::graphics::window::getHeight() - m)
                    move.setY(tileHeight);
                
                else if (engine::input::keyboard::isPressed(K(DOWN)) || mouseY < m)
                    move.setY(-tileHeight);
                
                S(Game)->getView()->move(move * (40 * engine::time::getFrameTime()));
                
                map::Map* map = S(Game)->getMap();
                
                S(Game)->getView()->updateBorders();
                engine::Vector2d center = getCenter();
                bool moved = false;
                static const float margin = 4;
                
                if (center.getX() < -margin)
                {
                    center.setX(-margin);
                    moved = true;
                }
                else if (center.getX() > map->getWidth() - 1 + margin)
                {
                    center.setX(map->getWidth() - 1 + margin);
                    moved = true;
                }
                
                if (center.getY() < -margin)
                {
                    center.setY(-margin);
                    moved = true;
                }
                else if (center.getY() > map->getHeight() - 1 + margin)
                {
                    center.setY(map->getHeight() - 1 + margin);
                    moved = true;
                }
                
                if (moved)
                    lookAt(center);
            }
        }
        
        void zoom(float min, float max)
        {
            if (!locked)
            {
                if (engine::input::keyboard::isPressed(K(LCTRL)))
                {
                    if (engine::input::mouse::isJustPressed(M(WHEELUP)))
                        S(Game)->getView()->zoom(1 + engine::time::getFrameTime() * 7, max);

                    else if (engine::input::mouse::isJustPressed(M(WHEELDOWN)))
                        S(Game)->getView()->zoom(1 - engine::time::getFrameTime() * 7, min);

                    else if (engine::input::mouse::isJustPressed(M(MIDDLE)))
                        S(Game)->getView()->setScale(1);
                }
            }
        }
        
        void setZoom(float zoom)
        {
            S(Game)->getView()->setScale(zoom);
        }
        
        void setGameView()
        {
            engine::graphics::window::setView(*S(Game)->getView());
        }
        
        void setInterfaceView()
        {
            engine::graphics::window::setInterfaceView();
        }
        
        void lock()
        {
            locked = true;
        }
        
        void unlock()
        {
            locked = false;
        }
        
        bool isLocked()
        {
            return locked;
        }
        
    }
}
