#include <iostream>
#include "Engine/Engine.cpp"
#include "Engine\include\SDL.h"

    SDL_Window *window;
    SDL_Renderer *renderer;

int main(int argc, char *argv[]){
    Engine engine = Engine();
    
    engine.XInnit();
    window = engine.XCreate_Window("X-Base Engine", 800,600);
    renderer = engine.XCreate_Renderer(window);
    engine.Xwindow_clear(renderer, 255,255,255,255);

    return 0;
}