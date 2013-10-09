#ifndef GAME_DISPLAYMANAGER_H
 #define GAME_DISPLAYMANAGER_H

#include "mapobject.h"

namespace game
{
    namespace map
    {
        namespace displaymanager
        {

            void clearAll();
            void showAll();
            bool add(MapObject* object);
            bool addTemporary(MapObject* object);

            void insertionSort();
            void quickSort();
            void swap(MapObject** a, MapObject** b);

            int getNumShown();
            int getNumObjects();

        }
    }
}

#endif
