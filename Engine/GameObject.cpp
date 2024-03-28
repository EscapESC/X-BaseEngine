#pragma once
#include <iostream>
#include "include\SDL.h"
#include "Engine.cpp"
#include "include\SDL_mixer.h"
#include "Sound.cpp"
#include <array>
#include <vector>
#include <algorithm>

class GameObject;

class CameraComponent;

class Component{
    public:
    virtual int GetType() = 0;
    virtual void Innit(GameObject* gameObject){};
    virtual void Update(float deltaTime){};
    virtual void Destroy(){};
};;

class GameObject{

    SDL_Rect* ObjectDesRect;

    public:

    GameObject* parentObject;

    std::string name;

    int health;
    bool visible = true;

    float x;
    float y;

    int w;
    int h;

    SDL_Texture* ObjectTexture;
    SDL_Rect* ObjectSrcRect; 
    SDL_Renderer* ObjectRenderer;

    std::vector<Component*> components;
    
    void createGameObject(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* desRect){
        ObjectSrcRect = srcRect;
        ObjectDesRect = desRect;

        x = desRect->x;
        y = desRect->y;

        w = desRect->w;
        h = desRect->h;
        ObjectRenderer = renderer;
        ObjectTexture = texture;
    }

    void Update(float deltaTime){
        for(int i = 0; i<components.size();i++){
            components[i]->Update(deltaTime);
        }
        if(parentObject){
            x = x+parentObject->x;
            y = y+parentObject->y;
        }
    }

    void Render(float cameraX, float cameraY, float zoom){
        Engine engine = Engine();
        if(visible){
        SDL_Rect scaleRec;
        scaleRec.x = (x-cameraX)*engine.scale;
        scaleRec.y = (y-cameraY)*engine.scale;
        scaleRec.w = w*zoom*engine.scale;
        scaleRec.h = h*zoom*engine.scale;
        SDL_RenderCopy(ObjectRenderer, ObjectTexture, ObjectSrcRect, &scaleRec);
        }
    }

    //Returns float array with x and y positions.
    std::array<float, 2> getPosition(){
        return {x,y};
    }

    void setPosition(float xPos, float yPos){
        x = xPos;
        y = yPos;
    }

    //Returns float array with object dimencions.
    std::array<int, 2> getSize(){
        return {w, h};
    }

    int addComponent(Component* AddComponent){
        for(int i; i<components.size();i++){
            if(components[i]->GetType()==AddComponent->GetType()){
                return -1;
            }
        }
        components.push_back(AddComponent);
        return 0;
    }

    Component* findComponent(int type){
        for(int i; i<components.size();i++){
            if(components[i]->GetType()==type){
                return components[i];
            }
        }
    }

    int removeComponent(Component* RemoveComponent){
        auto position = std::find(components.begin(),components.end(), RemoveComponent);
        components.erase(position);
        return 0;
    }

    void Destroy(){
        for(int i; i<components.size();i++){
            components[i]->Destroy();
        }
        delete this;
    }
};

class CameraComponent : public Component{

    public: 
    GameObject* parentObject;

    int x = 0;
    int y = 0;

    float offsetX = 0;
    float offsetY = 0;

    float zoom = 0;

    int GetType() override{return 99;}

    void Update(float deltaTime) override{x = parentObject->x+offsetX; y = parentObject->y+offsetY;}
    void Innit (GameObject* gameObject)override{parentObject=gameObject;}
    
    void Destroy() override{
        delete this;
    }
};