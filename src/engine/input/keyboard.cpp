#include <iostream>
#include "keyboard.h"

namespace engine
{
    namespace input
    {
        namespace keyboard
        {

            static int numKeys;
            static bool* justPressedKeys;
            static bool* justReleasedKeys;

            static Uint16 unicodeText[SDLK_LAST];
            static int unicodeLength = 0;

            bool isPressed(Key k)
            {
                Uint8* pressedKeys = SDL_GetKeyState(NULL);
                return (bool) pressedKeys[k];
            }

            bool isJustPressed(Key k)
            {
                return justPressedKeys[k];
            }

            bool isJustReleased(Key k)
            {
                return justReleasedKeys[k];
            }

            Uint16* getUnicodeText(int* length)
            {
                *length = unicodeLength;
                return unicodeText;
            }
            
            std::vector<Key> getPressedKeys()
            {
                std::vector<Key> pressedKeysVector;
                Uint8* pressedKeys = SDL_GetKeyState(NULL);
                for (int k = 0; k < numKeys; k++)
                {
                    if (pressedKeys[k])
                        pressedKeysVector.push_back((Key) k);
                }
                return pressedKeysVector;
            }
            
            std::vector<Key> getJustPressedKeys()
            {
                std::vector<Key> justPressedKeysVector;
                for (int k = 0; k < numKeys; k++)
                {
                    if (justPressedKeys[k])
                        justPressedKeysVector.push_back((Key) k);
                }
                return justPressedKeysVector;
            }
            
            std::vector<Key> getJustReleasedKeys()
            {
                std::vector<Key> justReleasedKeysVector;
                for (int k = 0; k < numKeys; k++)
                {
                    if (justReleasedKeys[k])
                        justReleasedKeysVector.push_back((Key) k);
                }
                return justReleasedKeysVector;
            }
            
            bool* getJustPressedKeys(int* length)
            {
                *length = numKeys;
                return justPressedKeys;
            }

            /* private */
            void clearEvents()
            {
                memset(justPressedKeys, 0, numKeys * sizeof(bool));
                memset(justReleasedKeys, 0, numKeys * sizeof(bool));
                unicodeLength = 0;
            }

            void addEvent(const SDL_Event& e)
            {
                switch (e.type)
                {
                    case SDL_KEYDOWN:
                    justPressedKeys[e.key.keysym.sym] = 1;
                    unicodeText[unicodeLength] = e.key.keysym.unicode;
                    unicodeLength++;
                    break;

                    case SDL_KEYUP:
                    justReleasedKeys[e.key.keysym.sym] = 1;
                    break;
                }
            }

            void init()
            {
                SDL_EnableUNICODE(1);
                SDL_GetKeyState(&numKeys);
                justPressedKeys = new bool[numKeys];
                justReleasedKeys = new bool[numKeys];
                clearEvents();
            }

            void free()
            {
                delete justPressedKeys;
                delete justReleasedKeys;
            }

        }
    }
}
