#include <iostream>
#include "Engine/Engine.cpp"
#include "Engine\include\SDL.h"
#include "Engine/Graphics.cpp"

    SDL_Window *window;
    SDL_Renderer *renderer;

int main(int argc, char *argv[]){
    Engine engine = Engine();
    Graphics gp = Graphics();
    
    engine.XInnit(SDL_INIT_EVERYTHING);
    window = engine.XCreate_Window("X-Base Engine", 800,600);
    renderer = engine.XCreate_Renderer(window);
    engine.Xwindow_clear(renderer, 255,255,255,255);

    const char* path = "src/Lambda.png";
    SDL_Texture* Lambda = gp.LoadTexture("src/Lambda.png", renderer);

    SDL_Rect rect;
    rect.w = 100;
    rect.h = 100;
    rect.x = 0;
    rect.y = 0;
    SDL_Rect* prect = &rect;

    engine.Xwindow_clear(renderer,0,0,0,0);
    gp.drawImage(Lambda, renderer,nullptr, prect);
    gp.paint(renderer);
    
    SDL_Delay(10000);
    return 0;
}