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

    void XCreate_Window(const char* title, int width, int height){
        window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width,height, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1,0);

    }

    void Xwindow_clear(int r, int g, int b, int a){

        SDL_SetRenderDrawColor(renderer,r,g,b,a);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
};