#include <iostream>
#include "Engine/Engine.cpp"
#include "Engine/include\SDL.h"
#include "Engine/Graphics.cpp"
#include "Engine/include\SDL_ttf.h"
#include "Engine/Sound.cpp"
#include "Engine/include\SDL_mixer.h"
#include "Engine/GameObject.cpp"
#include "Engine/ObjectManager.cpp"
#include "Engine/Components.cpp"
#include <array>
#include <thread>


    SDL_Window *window;
    SDL_Renderer *renderer;

    bool framequit = false;

    const int TPS = 60;

int main(int argc, char *argv[]){

    //The essentials
    Engine engine = Engine();
    Graphics graphics = Graphics();
    Sound sound = Sound();
    ObjectManager objectManger = ObjectManager();
    engine.Innit(SDL_INIT_EVERYTHING);
    sound.initSound();
    engine.setScale(6);

    //Create grpahics interface for the user
    window = graphics.Create_Window("Test", 1920, 1080, SDL_WINDOW_SHOWN);
    //Renderer will be used for every graphics functions
    renderer = graphics.Create_Renderer(window);

    //Load assets
    SDL_Texture* playerTexture = graphics.loadTexture("src/Lambda.png", renderer);
    SDL_Texture* speakertexture = graphics.loadTexture("src/speaker.png", renderer);
    SDL_Texture* lightTexture = graphics.loadTexture("src/flashlight2.png", renderer);
    SDL_Texture* lightBulb = graphics.loadTexture("src/lightbulb.png", renderer);
    Mix_Chunk* speakerSound = sound.loadSound("src/sound.mp3");
    // . . . 

    //player position rect
    SDL_Rect rect;
    rect.w = 32;
    rect.h = 32;
    rect.x = 0;
    rect.y = 0;
    SDL_Rect* playerRect = &rect;
    
    //Create game objects
    GameObject* player = objectManger.createObject(renderer,playerTexture,nullptr,playerRect);
    PhysicsComponent* playerPhysicsComponent = new PhysicsComponent();
    playerPhysicsComponent->Innit(player);
    playerPhysicsComponent->xDrag = 0.005;
    playerPhysicsComponent->yDrag = 0.005;
    playerPhysicsComponent->xMaxVelocity = 0.1;
    playerPhysicsComponent->yMaxVelocity = 0.1;
    player->addComponent(playerPhysicsComponent);

    //Speaker Object Rect
    SDL_Rect speakerrect;
    speakerrect.w = 32;
    speakerrect.h = 32;
    speakerrect.x = 144;
    speakerrect.y = 74;
    SDL_Rect* pSpeakRect = &speakerrect;

    //Speaker GameObject
    GameObject* speaker = objectManger.createObject(renderer,speakertexture,nullptr, pSpeakRect);
    //Speaker physics component - Useless for now
    PhysicsComponent* speakerPhysComponent = new PhysicsComponent();
    speakerPhysComponent->Innit(speaker);
    speakerPhysComponent->xDrag = 0.005;
    speakerPhysComponent->yDrag = 0.005;
    speakerPhysComponent->xMaxVelocity = 0.1;
    speakerPhysComponent->yMaxVelocity = 0.1;
    speaker->addComponent(speakerPhysComponent);
    //Speaker audio component
    Audio2DComponent* speakerAudio2D = new Audio2DComponent();
    speakerAudio2D->Innit(speaker);
    speakerAudio2D->reciver = player;
    speakerAudio2D->area = 100;
    speakerAudio2D->falloff = 200;
    speakerAudio2D->playSound(speakerSound, -1, -1);
    speaker->addComponent(speakerAudio2D);
    
    //LightBulb

    SDL_Rect lightRect;
    lightRect.w = 16;
    lightRect.h = 16;
    lightRect.x = 0;
    lightRect.y = 74;
    SDL_Rect* lightPtr = &lightRect;

    GameObject* lightObject = objectManger.createObject(renderer, lightBulb, nullptr, lightPtr);
    LightComponent* lightComp = new LightComponent();
    lightComp->Innit(lightObject);
    lightComp->w = 64;
    lightComp->h = 64;
    lightComp->offsetX = -16-8;
    lightComp->offsetY = -16-8;
    lightComp->lightTexture = lightTexture;
    lightObject->addComponent(lightComp);

    //Camera
    CameraComponent* camera = new CameraComponent();
    camera->offsetX=-160+16;
    camera->offsetY=-90+16;
    player->addComponent(camera);
    camera->Innit(player);

    //Essentials for the gameloop
    Uint32 startFrame = SDL_GetTicks();
    bool quit = false;

    objectManger.sortZindex();

    //The game loop
    while(!quit){
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            
            if( event.type == SDL_QUIT ){
                quit = true;
            }
            if( event.type == SDL_KEYDOWN){

                engine.KeyDownUpdate(event);
            }
            if( event.type == SDL_KEYUP){
                engine.KeyUpUpdate(event);
            }
        }
        
        float deltaTime = engine.DeltaTime();

        //Custom input handling
        if(std::find(engine.keyboardInput.begin(), engine.keyboardInput.end(), SDL_SCANCODE_W)!= engine.keyboardInput.end()){
            playerPhysicsComponent->setVelocity(playerPhysicsComponent->getVelocity()[0],playerPhysicsComponent->getVelocity()[1]-0.15);
        }
        if(std::find(engine.keyboardInput.begin(), engine.keyboardInput.end(), SDL_SCANCODE_A)!= engine.keyboardInput.end()){
            playerPhysicsComponent->setVelocity(playerPhysicsComponent->getVelocity()[0]-0.15,playerPhysicsComponent->getVelocity()[1]);
        }
        if(std::find(engine.keyboardInput.begin(), engine.keyboardInput.end(), SDL_SCANCODE_S)!= engine.keyboardInput.end()){
            playerPhysicsComponent->setVelocity(playerPhysicsComponent->getVelocity()[0],playerPhysicsComponent->getVelocity()[1]+0.15);
        }
        if(std::find(engine.keyboardInput.begin(), engine.keyboardInput.end(), SDL_SCANCODE_D)!= engine.keyboardInput.end()){
            playerPhysicsComponent->setVelocity(playerPhysicsComponent->getVelocity()[0]+0.15,playerPhysicsComponent->getVelocity()[1]);
        }
        if(std::find(engine.keyboardInput.begin(), engine.keyboardInput.end(), SDL_SCANCODE_SPACE)!= engine.keyboardInput.end()){
        }

        //Updating engine cycle
        graphics.window_clear(renderer,10,10,10,155);
        objectManger.updateAll(deltaTime);
        objectManger.renderAll(camera->x, camera->y,1.0);
        objectManger.renderLights({0x0,0x0,0x0,200},renderer, 1920,1080, camera->x, camera->y, 1.0);
        graphics.paint(renderer,1920,1080);
        //Tick delay
        engine.Tick_Delay(&startFrame, TPS);
    }

    framequit = true;
    engine.Quit();
    graphics.quit();
    sound.quitSound();
    objectManger.quit();

    return 0;
}
