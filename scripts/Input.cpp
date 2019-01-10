#include "Input.h"

Input::Input()
{
    memset(this,0,sizeof(*this));
}

void Input::UpdateEvent()
{
    SDL_Event event1;
    while(SDL_PollEvent(&event1))
    {
        switch (event1.type)
        {
        case SDL_KEYDOWN:
            key[event1.key.keysym.sym]=1;
            break;
        default:
            break;
        }
    }
}
