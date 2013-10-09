#ifndef ENGINE_SINGLETON_H
 #define ENGINE_SINGLETON_H

namespace engine
{

    template <class T> inline T* getSingleton()
    {
        static T instance;
        return &instance;
    }

}

#define S(T) engine::getSingleton<T>()

#endif
