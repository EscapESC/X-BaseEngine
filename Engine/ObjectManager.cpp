#pragma once
#include <iostream>
#include "include\SDL.h"
#include <vector>
#include "GameObject.cpp"
#include "Graphics.cpp"
#include <algorithm>

class ObjectManager{
    public:

    std::vector<GameObject*> objectList;
    SDL_Texture * lightLayer;

    int addObject(GameObject* x){
        objectList.push_back(x);
        return objectList.size();
    }
    
    GameObject* createObject(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* desRect){
        GameObject* x = new GameObject();
        x->createGameObject(renderer, texture, srcRect, desRect);
        addObject(x);
        return x;
    }

    GameObject* findObjectByName(std::string name){
        for(int i = 0; i < objectList.size(); i++){
            if(objectList[i]->name == name)
            {
                return objectList[i];
            }
        }
    }

    static bool compareByZIndex(GameObject* a, GameObject* b){
        return a->z < b->z;
    }

    /** Sorts the objectList by z index, for the correct rendering order.
    */
    void sortZindex(){
        std::sort(objectList.begin(), objectList.end(), compareByZIndex);
    }

    void updateAll(float deltaTime){
        for(int i = 0; i<objectList.size();i++){
            objectList[i]->Update(deltaTime);
        }
    }

    void renderAll(float cameraX, float cameraY, float zoom){
        for(int i = 0; i<objectList.size();i++){
            objectList[i]->Render(cameraX,cameraY, zoom);
        }
    }

    void renderLights(SDL_Color ambientLight, SDL_Renderer* renderer, int w, int h, float cameraX, float cameraY, float zoom){
        Graphics gp = Graphics();
        Engine engine = Engine();
        if(!lightLayer){lightLayer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);}
        SDL_SetRenderTarget(renderer, lightLayer);
        SDL_SetTextureBlendMode(lightLayer, SDL_BLENDMODE_MUL);
        SDL_SetRenderDrawColor(renderer, ambientLight.r, ambientLight.g,ambientLight.b,ambientLight.a);
        SDL_RenderClear(renderer);
        
        for(int i = 0; i < objectList.size();i++){
            auto tempComponent = dynamic_cast<LightComponent*>(objectList[i]->findComponent(69));
            if(tempComponent != nullptr){
                if(tempComponent->visible){
                    SDL_Rect scaleRec;
                    scaleRec.x = (tempComponent->parentObject->x-cameraX+tempComponent->offsetX)*engine.scale;
                    scaleRec.y = (tempComponent->parentObject->y-cameraY+tempComponent->offsetY)*engine.scale;
                    scaleRec.w = tempComponent->w*zoom*engine.scale;
                    scaleRec.h = tempComponent->h*zoom*engine.scale;
                    SDL_RenderCopy(renderer, tempComponent->lightTexture, tempComponent->LightSrcRect, &scaleRec);
                }
            }
        }

        SDL_SetRenderTarget(renderer, gp.screenTexture);
        SDL_SetTextureBlendMode(gp.screenTexture, SDL_BLENDMODE_BLEND);
        SDL_Rect desRect = {0,0,w,h};
        SDL_RenderCopy(renderer,lightLayer, nullptr, &desRect);
        SDL_SetRenderTarget(renderer, gp.screenTexture);
    }

    int deleteObject(GameObject* x){
        auto index = std::find(objectList.begin(),objectList.end(), x);
        GameObject* go = *index; 
        go->Destroy();
        objectList.erase(index);
        return 0;
    }

    int quit(){
        for(int i = 0; i < objectList.size();i++){
            objectList[i]->Destroy();
        }
        SDL_DestroyTexture(lightLayer);
        return 0;
    }

};