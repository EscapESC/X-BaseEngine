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

    }

    void Render(){
        SDL_RenderCopy(ObjectRenderer, ObjectTexture, ObjectSrcRect, ObjectDesRect);
    }

    std::array<int, 2> getPosition(){
        return {x,y};
    }

    void setPosition(int xPos, int yPos){
        x = xPos;
        y = yPos;

    }

    std::array<int, 2> getSize(){
        return {sizeX, sizeY};
    }

    std::array<int, 3> getVelocity(){
        return {Xvelocity,Yvelocity,Velocity};
    }

    private:

    int x;
    int y;

    int sizeX;
    int sizeY;

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