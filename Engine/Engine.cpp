#include <iostream>
#include "include\SDL.h"

class Engine{
    public:
        SDL_Window *window;
        SDL_Renderer *renderer;

    //Initializes SDL
    int XInnit(Uint32 init) {
        // Need to call with SDL_INIT_EVERYTHING or any of its varyants
        SDL_Init(init);
        return 0;
    }

    //Generate a Window and return its pointer back;
    SDL_Window* XCreate_Window(const char* title, int width, int height){
        SDL_Window *wind = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width,height, SDL_WINDOW_SHOWN);
        return wind;
    }

    //Generate renderer for a window. Renderer - needed for drawing
    SDL_Renderer* XCreate_Renderer(SDL_Window *wind){
        renderer = SDL_CreateRenderer(wind, -1,0);
        return renderer;
    }
    //Clears the render of a window with a rgba color.
    void Xwindow_clear(SDL_Renderer *rend, int r, int g, int b, int a){

        SDL_SetRenderDrawColor(rend,r,g,b,a);
        SDL_RenderClear(rend);
        SDL_RenderPresent(rend);
    }

    //Destroys window (What did you expect?)
    void XDestroyWindow(SDL_Window *x){
        SDL_DestroyWindow(x);
    }

    //Quits SDL which would have to be re Initilized again to be used.
    int XQuit(){
        SDL_Quit();
        return 0;
    }
};