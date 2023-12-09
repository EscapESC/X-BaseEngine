#include <iostream>
#include "include\SDL.h"

class Engine{
    public:

    //Initializes SDL
    int XInnit(Uint32 init) {
        // Need to call with SDL_INIT_EVERYTHING or any of its varyants
        SDL_Init(init);
        return 0;
    }

    //Limits the tick speed/s
    void XTick_Delay(Uint32 startFrame, int frameDelay){
        int frameNow = SDL_GetTicks() - startFrame;

        if (frameDelay > frameNow){
            SDL_Delay(frameDelay - frameNow);
        }
    }

    //Quits SDL which would have to be re Initilized again to be used.
    int XQuit(){
        SDL_Quit();
        return 0;
    }
};