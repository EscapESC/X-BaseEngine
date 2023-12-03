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
    window = gp.XCreate_Window("X-Base Engine", 800,600);
    renderer = gp.XCreate_Renderer(window);
    gp.Xwindow_clear(renderer, 255,255,255,255);

    const char* path = "src/Lambda.png";
    SDL_Texture* Lambda = gp.XLoadTexture("src/Lambda.png", renderer);

    SDL_Rect rect;
    rect.w = 100;
    rect.h = 100;
    rect.x = 800/2-100/2;
    rect.y = 600/2-100/2;
    SDL_Rect* prect = &rect;

    gp.Xwindow_clear(renderer,0,0,0,0);
    gp.XdrawImage(Lambda, renderer,nullptr, prect);

    SDL_Vertex vertex_1 = {{100.5, 200.5}, {255, 0, 0, 255}, {1, 1}};
    SDL_Vertex vertex_2 = {{200.5, 100.5}, {0, 255, 0, 255}, {1, 1}};
    SDL_Vertex vertex_3 = {{300.5, 200.5}, {0, 0, 255, 255}, {1, 1}};

    SDL_Vertex vertices[] = {
        vertex_2,
        vertex_1,
        vertex_3
    };

    SDL_RenderGeometry(renderer, NULL,vertices, 3, NULL, 0);
    gp.Xpaint(renderer);
    
    SDL_Delay(10000);
    return 0;
}