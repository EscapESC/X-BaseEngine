#include <iostream>
#include "Engine/Engine.cpp"
#include "Engine\include\SDL.h"
#include "Engine/Graphics.cpp"
#include "Engine\include\SDL_ttf.h"
#include "Engine/Sound.cpp"
#include "Engine\include\SDL_mixer.h"
#include "Engine\GameObject.cpp"
#include "Engine\ObjectManager.cpp"
#include <array>

    SDL_Window *window;
    SDL_Renderer *renderer;

    const int FPS = 60;

int main(int argc, char *argv[]){
    ObjectManager om = ObjectManager();
    Engine engine = Engine();
    Graphics gp = Graphics();
    Sound s = Sound();
    
    engine.Innit(SDL_INIT_EVERYTHING);
    window = gp.Create_Window("X-Base Engine", 800,600, SDL_WINDOW_SHOWN);
    renderer = gp.Create_Renderer(window);
    
    SDL_Texture* Lambda = gp.loadTexture("src/Lambda.png", renderer);
    SDL_Texture* Flashlight = gp.loadTexture("src/flashlight.png", renderer);
    SDL_Rect rect;
    rect.w = 100;
    rect.h = 100;
    rect.x = 800/2-100/2;
    rect.y = 600/2-100/2;
    SDL_Rect* prect = &rect;

    gp.window_clear(renderer,0,0,0,0);

    GameObject* go = om.createObject(renderer,Lambda, nullptr,prect);
    go->Render();
    //SDL_DestroyTexture(Lambda);

    SDL_Vertex vertex_1 = {{100.5, 200.5}, {255, 0, 0, 255}, {1, 1}};
    SDL_Vertex vertex_2 = {{200.5, 100.5}, {0, 255, 0, 255}, {1, 1}};
    SDL_Vertex vertex_3 = {{300.5, 200.5}, {0, 0, 255, 255}, {1, 1}};

    SDL_Vertex vertices[] = {
        vertex_2,
        vertex_1,
        vertex_3
    };
    
    SDL_RenderGeometry(renderer, NULL,vertices, 3, NULL, 0);
    gp.init_TTF();
    TTF_Font *font= TTF_OpenFont("src/fonts/Sans.ttf",50);
    SDL_Texture* text = gp.text_Texture(renderer,"HELLO WORLD",font, SDL_Color {255,255,255, 255});
    SDL_Rect trect;
    trect.w = 200;
    trect.h = 50;
    trect.x = 25;
    trect.y = 25;
    SDL_Rect* tprect = &trect;

    gp.drawTexture(text, renderer, NULL, tprect);

    

    SDL_Rect frect;
    frect.w = 100;
    frect.h = 100;
    frect.x = 400/2-100/2;
    frect.y = 200/2;
    SDL_Rect* fprect = &frect;

    gp.drawTexture(Flashlight, renderer,nullptr, fprect);

    s.initSound();
    Mix_Chunk* sound = s.loadSound("src/sound.mp3");
    int ch = s.playSound(sound, -1,100, -1);



    gp.paint(renderer);

    bool quit;

    int srcX=-10000;
    int srcY=0;

    Uint32 startFrame = SDL_GetTicks();
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            
        if( event.type == SDL_QUIT ){
            quit = true;
        }

        if(event.type == SDL_KEYDOWN){
            std::cout << "Key Pressed" << std::endl;
        }
        }
        gp.window_clear(renderer,0,0,0,0);
        go->setPosition(go->getPosition()[0]+0.01,go->getPosition()[1]);
        go->Update();
        go->Render();

        SDL_RenderGeometry(renderer, NULL,vertices, 3, NULL, 0);
        gp.drawTexture(text, renderer, NULL, tprect);
        gp.drawTexture(Flashlight, renderer,nullptr, fprect);

        gp.paint(renderer);
        //std::cout << go.getPosition()[0] << " " << go.getPosition()[1] << std::endl;
        srcX =srcX + 1;
        std::array<float,3> panning= s.calculatePanning2D(100,srcX,srcY,0,0,10000,10000);
        //std::cout << panning[0] << " " << panning[1] << " " <<panning[2] << " " << std::endl;
        s.setVolume(ch,panning[0]);
        s.setChannelPanning(ch, panning[1],panning[2]);

        engine.Tick_Delay(startFrame, FPS);
    }
    om.quit();
    gp.quit();
    s.quitSound();
    engine.Quit();
    return 0;
}