#include <iostream>
#include "include\SDL.h"

class Engine{
    public:
        SDL_Window *window;
        SDL_Renderer *renderer;

    int XInnit() {

        SDL_Init(SDL_INIT_EVERYTHING);
        return 0;
    }

    SDL_Window* XCreate_Window(const char* title, int width, int height){
        SDL_Window *wind = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width,height, SDL_WINDOW_SHOWN);
        return wind;
    }

    SDL_Renderer* XCreate_Renderer(SDL_Window *wind){
        renderer = SDL_CreateRenderer(wind, -1,0);
        return renderer;
    }

    void Xwindow_clear(SDL_Renderer *rend, int r, int g, int b, int a){

        SDL_SetRenderDrawColor(rend,r,g,b,a);
        SDL_RenderClear(rend);
        SDL_RenderPresent(rend);
    }

    void XDestroyWindow(SDL_Window *x){
        SDL_DestroyWindow(x);
    }

    int XQuit(){
        SDL_Quit();
        return 0;
    }
};