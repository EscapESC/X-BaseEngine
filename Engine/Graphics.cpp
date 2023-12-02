#include <iostream>

#include "include\SDL.h"
#include "include\SDL_image.h"

class Graphics{

    public:

    void drawImage(SDL_Texture* img, SDL_Renderer *rend, SDL_Rect* srcRect, SDL_Rect* dstRect){

        SDL_RenderCopy(rend, img, NULL,dstRect);

    }

    SDL_Texture* LoadTexture(const char *path, SDL_Renderer* rend){
        SDL_Surface* tmp = IMG_Load(path);

        SDL_Texture* loadedTexture = SDL_CreateTextureFromSurface(rend, tmp);
        SDL_FreeSurface(tmp);
    return loadedTexture;
    }

    void paint(SDL_Renderer* rend){

        SDL_RenderPresent(rend);
    }
};