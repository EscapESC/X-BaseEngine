#include <iostream>

#include "include\SDL.h"
#include "include\SDL_image.h"
#include "include\SDL_ttf.h"

class Graphics{

    public:

    //Generate a Window and return its pointer back;
    SDL_Window* XCreate_Window(const char* title, int width, int height){
        SDL_Window *wind = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width,height, SDL_WINDOW_SHOWN);
        return wind;
    }

    //Generate renderer for a window. Renderer - needed for drawing
    SDL_Renderer* XCreate_Renderer(SDL_Window *wind){
        SDL_Renderer* rend = SDL_CreateRenderer(wind, -1,0);
        return rend;
    }

    //Generates surface -> texture -> return
    SDL_Texture* Xtext_Texture(SDL_Renderer* Renderer, const char* Text, TTF_Font *Font, SDL_Color Color){
        if(Font == NULL){std::cout << "Error: Empty Font given!" << std::endl;}
        SDL_Surface* temp = TTF_RenderText_Solid(Font, Text, Color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer, temp);
        SDL_FreeSurface(temp);

        return texture;
    }

    //Clears the render of a window with a rgba color.
    void Xwindow_clear(SDL_Renderer *rend, int r, int g, int b, int a){

        SDL_SetRenderDrawColor(rend,r,g,b,a);
        SDL_RenderClear(rend);
        SDL_RenderPresent(rend);
    }

    //Destroys window (What did you expect?)
    void XDestroyWindow(SDL_Window *x){
        SDL_DestroyWindow(x);
    }

    void XdrawTexture(SDL_Texture* img, SDL_Renderer *rend, SDL_Rect* srcRect, SDL_Rect* dstRect){

        SDL_RenderCopy(rend, img, srcRect,dstRect);

    }

    SDL_Texture* XLoadTexture(const char *path, SDL_Renderer* rend){
        SDL_Surface* tmp = IMG_Load(path);

        SDL_Texture* loadedTexture = SDL_CreateTextureFromSurface(rend, tmp);
        SDL_FreeSurface(tmp);
    return loadedTexture;
    }

    void Xpaint(SDL_Renderer* rend){

        SDL_RenderPresent(rend);
    }
};