#pragma once
#include <iostream>
#include "include\SDL.h"
#include <vector>
#include "GameObject.cpp"
#include <algorithm>

class ObjectManager{
    public:

    std::vector<GameObject*> objectList;

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

    void updateAll(float deltaTime){
        for(int i = 0; i<objectList.size();i++){
            objectList[i]->Update(deltaTime);
        }
    }

    void renderAll(){
        for(int i = 0; i<objectList.size();i++){
            objectList[i]->Render();
        }
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
        return 0;
    }

};