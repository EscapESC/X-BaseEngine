#include <iostream>
#include "include\SDL.h"

int main(int argc, char *argv[]){
    
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("X-Base Engine",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 800,600, SDL_WINDOW_SHOWN);

    return 0;
}