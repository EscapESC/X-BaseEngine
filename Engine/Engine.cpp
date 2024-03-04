#pragma once
#include <iostream>
#include "include\SDL.h"
#include <vector>
#include <algorithm>

class Engine{
    public:

    static float scale;
    
    Uint64 LastDeltaTimeUpdate = 0;

    void setScale(float scaleFactor){
        scale = scaleFactor;
    }

    std::vector<int> keyboardInput;
    /** Initializes SDL 
     * \param init if a SDL_INIT_* flag for initalizing diffrent systems. SDL_INIT_EVERYTHING - to init everything
     * \returns 0 on succes -1 on error
     */
    int Innit(Uint32 init) {
        scale = 1;
        
        // Need to call with SDL_INIT_EVERYTHING or any of its varyants
        int rtn = SDL_Init(init);
        if(rtn!=0){std::cout<<"Innit Error: "<<SDL_GetError()<<std::endl;}
        return rtn;
    }

    /** Delays the thread if its running too fast.
     * \param startFrame is a return value of SDL_getTicks(), and is a frame count from the start of the program.
     * \param frameDelay is the set ammount of delays before resuming.
    */
    void Tick_Delay(Uint32 startFrame, int FPS){
        float frameDelay = 1000/FPS;
        float frameNow = SDL_GetTicks() - startFrame;

        if (frameDelay > frameNow){
            SDL_Delay(frameDelay - frameNow);
        }
    }

    void KeyDownUpdate(SDL_Event event){
        if(std::find(keyboardInput.begin(),keyboardInput.end(),event.key.keysym.scancode) == keyboardInput.end()){
            keyboardInput.insert(keyboardInput.begin(),event.key.keysym.scancode);
        }
    }

    void KeyUpUpdate(SDL_Event event){
        auto position = std::find(keyboardInput.begin(),keyboardInput.end(),event.key.keysym.scancode);
        keyboardInput.erase(position);
    }

    double DeltaTime(){
        Uint64 NOW = SDL_GetPerformanceCounter();
        LastDeltaTimeUpdate = NOW;
        NOW = SDL_GetPerformanceCounter();

        return (double)((NOW - LastDeltaTimeUpdate)*1000 / (double)SDL_GetPerformanceFrequency() );
    }

    //Calls SDL_Quit function, which cleans up all initialized sub systems.
    int Quit(){
        SDL_Quit();
        return 0;
    }
};

float Engine::scale;