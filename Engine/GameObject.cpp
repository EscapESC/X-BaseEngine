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

class Component{
    public:
    virtual int GetType() = 0;
    virtual void Innit(GameObject* gameObject){};
    virtual void Update(float deltaTime){};
    virtual void Destroy(){};
};;

class GameObject{

    public:

    GameObject* parentObject;

    std::string name;

    int health;
    bool visible = true;

    float x;
    float y;

    int sizeX;
    int sizeY;

    SDL_Texture* ObjectTexture;
    SDL_Rect* ObjectSrcRect; 
    SDL_Rect* ObjectDesRect;
    SDL_Renderer* ObjectRenderer;

    std::vector<Component*> components;
    
    void createGameObject(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* desRect){
        ObjectSrcRect = srcRect;
        ObjectDesRect = desRect;

        x = desRect->x;
        y = desRect->y;

        sizeX = desRect->w;
        sizeY = desRect->h;
        ObjectRenderer = renderer;
        ObjectTexture = texture;
    }

    void Update(float deltaTime){
        for(int i = 0; i<components.size();i++){
            components[i]->Update(deltaTime);
        }
        if(parentObject){
            ObjectDesRect->x = x+parentObject->ObjectDesRect->x;
            ObjectDesRect->y = y+parentObject->ObjectDesRect->y;
        }
        else{
        ObjectDesRect->x = x;
        ObjectDesRect->y = y;
        }
    }

    void Render(){
        Engine engine = Engine();
        if(visible){
        SDL_Rect scaleRec;
        scaleRec.x = ObjectDesRect->x*engine.scale;
        scaleRec.y = ObjectDesRect->y*engine.scale;
        scaleRec.w = ObjectDesRect->w*engine.scale;
        scaleRec.h = ObjectDesRect->h*engine.scale;
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

        x = ObjectDesRect->x;
        y = ObjectDesRect->y;
    }

    //Returns float array with object dimencions.
    std::array<int, 2> getSize(){
        return {sizeX, sizeY};
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

//Component for automatic calculations of basic realtime 2D physics
class PhysicsComponent : public Component{
    public:
    GameObject* parentObject;
    float xVelocity;
    float yVelocity;
    float velocity;

    float mass; // Not implemented yet
    float xDrag;
    float yDrag;
    float xMaxVelocity = -1;
    float yMaxVelocity = -1;

    int GetType() override{return 1;}

    void Update(float deltaTime) override{
        xVelocity = xVelocity*(1-xDrag);
        yVelocity = yVelocity*(1-yDrag);

        if(xVelocity>xMaxVelocity&&xMaxVelocity!= -1){xVelocity = xMaxVelocity;}
        if(yVelocity>yMaxVelocity&&yMaxVelocity!= -1){yVelocity = yMaxVelocity;}
        if(xVelocity<-xMaxVelocity&&xMaxVelocity!= -1){xVelocity = -xMaxVelocity;}
        if(yVelocity<-yMaxVelocity&&yMaxVelocity!= -1){yVelocity = -yMaxVelocity;}
        parentObject->x = parentObject->x+xVelocity;
        parentObject->y = parentObject->y+yVelocity;
    }
    void Innit (GameObject* gameObject)override{parentObject=gameObject;}

    std::array<float, 3> getVelocity(){
        return {xVelocity,yVelocity,velocity};
    }

    void setVelocity(float xInputVelocity,float yInputVelocity){
        xVelocity = xInputVelocity;
        yVelocity = yInputVelocity;
    }

    void Destroy() override{
        delete this;
    }

};
//WIP
class RigidbodyComponent : public Component{

    GameObject* parentObject;
    void Update(float deltaTime) override{}
    void Innit (GameObject* gameObject)override{parentObject=gameObject;}

    int GetType() override{return 2;}

    void Destroy() override{
        delete this;
    }
};

//Audio component can play sounds with set volume and loops (greate for ambient sounds);
class AudioComponent : public Component{
    public:
    GameObject* parentObject;
    bool playing;
    int loops;
    int volume;
    int channelNumber;
    Mix_Chunk* sound;

    int GetType() override{return 3;}

    void Update(float deltaTime) override{
        
    }

    int playSound(Mix_Chunk* soundTrack, int loop, int channel,int fadeInMs){
        channelNumber = Mix_FadeInChannel(channel, soundTrack, loop, fadeInMs);
        if(channelNumber != -1){playing == true;}
        return channelNumber;
    }

    void pauseSound(){
        Mix_Pause(channelNumber);
    }

    void presumeSound(){
        Mix_Resume(channelNumber);
    }

    int stopSound(){
        return Mix_HaltChannel(channelNumber);
    }

    void Innit (GameObject* gameObject){parentObject=gameObject;}

    void Destroy() override{
        delete this;
    }
};

//Audio component with 2D panning and volume falloff
class Audio2DComponent : public Component{
    public:
    GameObject* parentObject;
    bool playing;
    int loops;
    int volume = 10;
    int channelNumber;
    Mix_Chunk* sound;

    GameObject* reciver;
    float xCamera;
    float yCamera;

    float area = 100;
    float falloff = 200;

    int GetType() override{return 3;}

    void Update(float deltaTime) override{
        if(playing){
        Sound s = Sound();
        std::array<float,3> panning = s.calculatePanning2D(volume,parentObject->x+parentObject->sizeX/2,parentObject->y+parentObject->sizeY/2,reciver->x+reciver->sizeX/2,reciver->y+reciver->sizeY/2,area,falloff);
        s.setChannelPanning(channelNumber,panning[1],panning[2]);
        Mix_Volume(channelNumber, (MIX_MAX_VOLUME * panning[0])/100);
        }
    }

    int playSound(Mix_Chunk* soundTrack, int loop, int channel){
        channelNumber = Mix_PlayChannel(channel, soundTrack, loop);
        if(channelNumber != -1){playing = true;}
        return channelNumber;
    }

    void pauseSound(){
        playing = false;
        Mix_Pause(channelNumber);
    }

    void presumeSound(){
        playing = true;
        Mix_Resume(channelNumber);
    }

    int stopSound(){
        playing = false;
        return Mix_HaltChannel(channelNumber);
    }

    void Innit (GameObject* gameObject){parentObject=gameObject;}

    void Destroy() override{
        delete this;
    }
};

//Planned feature
class LightComponent : public Component{
    GameObject* parentObject;

    int GetType() override{return 5;}

    void Update(float deltaTime) override{}
    void Innit (GameObject* gameObject)override{parentObject=gameObject;}
    
    void Destroy() override{
        delete this;
    }
};