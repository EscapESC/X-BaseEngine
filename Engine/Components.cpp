#pragma once
#include "GameObject.cpp"
#include <iostream>

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

    bool colisionBox;
    int collisionOffsetX;
    int collisionOffsetY;
    int colliderSizeX;
    int colliderSizeY;

    bool dynamicCollision;
    bool solid = true;

    std::vector<GameObject*> *objectList;

    int GetType() override{return 1;}

    void Update(float deltaTime) override{
        xVelocity = xVelocity*(1-deltaTime*xDrag);
        yVelocity = yVelocity*(1-deltaTime*yDrag);

        if(xVelocity>xMaxVelocity&&xMaxVelocity!= -1){xVelocity = xMaxVelocity;}
        if(yVelocity>yMaxVelocity&&yMaxVelocity!= -1){yVelocity = yMaxVelocity;}
        if(xVelocity<-xMaxVelocity&&xMaxVelocity!= -1){xVelocity = -xMaxVelocity;}
        if(yVelocity<-yMaxVelocity&&yMaxVelocity!= -1){yVelocity = -yMaxVelocity;}

        if(solid && dynamicCollision && colisionBox){
            std::vector<GameObject*> oblist = *objectList;
            for(int i = 0; i < objectList->size(); i++){
                auto tempComponent = dynamic_cast<PhysicsComponent*>(oblist[i]->findComponent(1));
                if(tempComponent != nullptr && tempComponent->solid && &tempComponent->parentObject != &parentObject){

                    int newXLoc = parentObject->x+xVelocity+collisionOffsetX;
                    int newYLoc = parentObject->y+yVelocity+collisionOffsetY;

                    if(newXLoc+colliderSizeX > tempComponent->parentObject->x && newXLoc < tempComponent->parentObject->x + tempComponent->colliderSizeX &&
                    newYLoc+colliderSizeY > tempComponent->parentObject->y && newYLoc < tempComponent->parentObject->y + tempComponent->colliderSizeY )
                    {
                        xVelocity = 0;
                    }

                    if(newYLoc+colliderSizeY > tempComponent->parentObject->y && newYLoc < tempComponent->parentObject->y + tempComponent->colliderSizeY &&
                    newXLoc+colliderSizeX > tempComponent->parentObject->x && newXLoc < tempComponent->parentObject->x + tempComponent->colliderSizeX )
                    {
                        yVelocity = 0;
                    }
                }
            }
        }

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
        std::array<float,3> panning = s.calculatePanning2D(volume,parentObject->x+parentObject->w/2,parentObject->y+parentObject->h/2,reciver->x+reciver->w/2,reciver->y+reciver->h/2,area,falloff);
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