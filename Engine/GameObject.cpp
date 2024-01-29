#include <iostream>
#include "include\SDL.h"
#include <array>

class GameObject{

    public:

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

    void Update(){
        ObjectDesRect->x =x;
        ObjectDesRect->y =y;
    }

    void Render(){
        SDL_RenderCopy(ObjectRenderer, ObjectTexture, ObjectSrcRect, ObjectDesRect);
    }

    std::array<float, 2> getPosition(){
        return {x,y};
    }

    void setPosition(float xPos, float yPos){
        x = xPos;
        y = yPos;

    }

    void destriy(){
        
    }

    std::array<int, 2> getSize(){
        return {sizeX, sizeY};
    }

    std::array<float, 3> getVelocity(){
        return {Xvelocity,Yvelocity,Velocity};
    }

    private:

    float x;
    float y;

    int sizeX;
    int sizeY;

    int textureArray;

    float Xvelocity;
    float Yvelocity;
    float Velocity;
    float maxVelocity;

    const char* name;
    SDL_Texture* ObjectTexture;
    SDL_Rect* ObjectSrcRect; 
    SDL_Rect* ObjectDesRect;
    SDL_Renderer* ObjectRenderer;
};