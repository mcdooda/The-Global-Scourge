#ifndef GAME_CAMERA_CAMERA_H
 #define GAME_CAMERA_CAMERA_H

#include "../../engine/vector2d.h"

namespace game
{
    namespace camera
    {
        
        void lookAt(engine::Vector2d position);
        engine::Vector2d getCenter();
        
        void move();
        void zoom(float min, float max);
        
        void setZoom(float zoom);
        
        void setGameView();
        void setInterfaceView();
        
        void lock();
        void unlock();
        bool isLocked();
        
    }
}

#endif
