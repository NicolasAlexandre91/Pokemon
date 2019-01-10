#ifndef INPUT_H
#define INPUT_H

#include <SDL/SDL.h>

class Input
{
    public:
        Input();
        ~Input(){};
        char key[SDLK_LAST];
        void UpdateEvent();
        int mousex,mousey;
        int mousexrel,mouseyrel;
        char mousebuttons[8];
        char quit;
};

#endif // INPUT_H
