#include <iostream>
#include "Engine/Engine.cpp"
#include "Engine\include\SDL.h"
#include "Engine/Graphics.cpp"
#include "Engine\include\SDL_ttf.h"

    SDL_Window *window;
    SDL_Renderer *renderer;

int main(int argc, char *argv[]){
    Engine engine = Engine();
    Graphics gp = Graphics();
    
    engine.XInnit(SDL_INIT_EVERYTHING);
    window = gp.XCreate_Window("X-Base Engine", 800,600);
    renderer = gp.XCreate_Renderer(window);

    const char* path = "src/Lambda.png";
    SDL_Texture* Lambda = gp.XLoadTexture("src/Lambda.png", renderer);

    SDL_Rect rect;
    rect.w = 100;
    rect.h = 100;
    rect.x = 800/2-100/2;
    rect.y = 600/2-100/2;
    SDL_Rect* prect = &rect;

    gp.Xwindow_clear(renderer,0,0,0,0);
    gp.XdrawTexture(Lambda, renderer,nullptr, prect);
    SDL_DestroyTexture(Lambda);

    SDL_Vertex vertex_1 = {{100.5, 200.5}, {255, 0, 0, 255}, {1, 1}};
    SDL_Vertex vertex_2 = {{200.5, 100.5}, {0, 255, 0, 255}, {1, 1}};
    SDL_Vertex vertex_3 = {{300.5, 200.5}, {0, 0, 255, 255}, {1, 1}};

    SDL_Vertex vertices[] = {
        vertex_2,
        vertex_1,
        vertex_3
    };

    SDL_RenderGeometry(renderer, NULL,vertices, 3, NULL, 0);
    gp.Xinit_TTF();
    TTF_Font *font= TTF_OpenFont("src/fonts/Sans.ttf",24);
    SDL_Texture* text = gp.Xtext_Texture(renderer,"HELLO WORLD",font, SDL_Color {255,255,255, 255});
    SDL_Rect trect;
    rect.w = 500;
    rect.h = 500;
    rect.x = 25;
    rect.y = 25;
    SDL_Rect* tprect = &trect;

    gp.XdrawTexture(text, renderer, NULL, tprect);

    SDL_DestroyTexture(text);
    gp.Xpaint(renderer);

    bool quit;

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            
        if( event.type == SDL_QUIT )
            quit = true;
    }
    /* do some other stuff here -- draw your app, etc. */
}
    return 0;
}