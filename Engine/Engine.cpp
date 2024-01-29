#include <iostream>
#include "include\SDL.h"

class Engine{
    public:

    /** Initializes SDL 
     * \param init if a SDL_INIT_* flag for initalizing diffrent systems. SDL_INIT_EVERYTHING - to init everything
     * \returns 0 on succes -1 on error
     */
    int Innit(Uint32 init) {
        // Need to call with SDL_INIT_EVERYTHING or any of its varyants
        int rtn = SDL_Init(init);
        if(rtn!=0){std::cout<<"Innig Error: "<<SDL_GetError()<<std::endl;}
        return rtn;
    }

    /** Delays the thread if its running too fast.
     * \param startFrame is a return value of SDL_getTicks(), and is a frame count from the start of the program.
     * \param frameDelay is the set ammount of delays before resuming.
    */
    void Tick_Delay(Uint32 startFrame, int frameDelay){
        int frameNow = SDL_GetTicks() - startFrame;

        if (frameDelay > frameNow){
            SDL_Delay(frameDelay - frameNow);
        }
    }

    //Calls SDL_Quit function, which cleans up all initialized sub systems.
    int Quit(){
        SDL_Quit();
        return 0;
    }
};