#include "displaymanager.h"

#define MAX_SHOWABLES 120000
#define MAX_TEMPORARIES 10

namespace game
{
    namespace map
    {
        namespace displaymanager
        {

            static MapObject* objects[MAX_SHOWABLES];
            static int numObjects = 0;
            static int numShown = 0;
            
            static MapObject* temporaryObjects[MAX_TEMPORARIES];
            static int numTemporaries = 0;

            void clearAll()
            {
                numObjects = 0;
                numShown = 0;
                
                for (int i = 0; i < numTemporaries; i++)
                    delete temporaryObjects[i];
                    
                numTemporaries = 0;
            }

            void showAll()
            {
                insertionSort();
                for (int i = 0; i < numShown; i++)
                    objects[i]->show();
            }

            bool add(MapObject* object)
            {
                numObjects++;
                if (object->isVisible() && numObjects < MAX_SHOWABLES)
                {
                    objects[numShown++] = object;
                    return true;
                }
                else
                    return false;
            }
            
            bool addTemporary(MapObject* object)
            {
                bool added = add(object);
                
                return added;
            }

            void insertionSort()
            {
                for (int i = 1; i < numShown; i++)
                    for (int k = i; k > 1 && objects[k]->getDepth() < objects[k - 1]->getDepth(); k--)
                        swap(&objects[k], &objects[k - 1]);
            }

            void swap(MapObject** a, MapObject** b)
            {
                MapObject* c = *a;
                *a = *b;
                *b = c;
            }

            int getNumShown()
            {
                return numShown;
            }

            int getNumObjects()
            {
                return numObjects;
            }

        }
    }
}
