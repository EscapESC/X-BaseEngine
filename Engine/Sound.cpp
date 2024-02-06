#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include "include\SDL.h"
#include "include\SDL_mixer.h"

class Sound{

    public:

    /*MAIN VOIDS ------------------------------------------------------------------*/

    //Initalizes SDL_mixer library.
    void initSound(){
        Mix_Init(MIX_INIT_MP3);
        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){ std::cout << "XinitSound ERROR: "<< Mix_GetError() << std::endl;}
        
    }

    //Calls Mix_Quit function.
    void quitSound(){
        //Fucking Pray for no memory leaks
        Mix_Quit();
    }

    //Just calculates whitch number to throw to the mixer. Could be private
    int calculateVolume(float volume){
        float v = (MIX_MAX_VOLUME * volume/100);
        return v;
    }

    std::array<float,3> calculatePanning2D(int Volume, int srcX, int srcY, int recX, int recY, float panningFalloff, float falloff){
        int locX = (srcX - recX);
        int locY = (srcY - recY);
        int dist = std::sqrt(locX*locX+locY*locY);

        panningFalloff = panningFalloff ;
        falloff = falloff;

        float finalVolume = Volume*((falloff-std::abs(dist))/(falloff));
        float right;
        float left;
        if (locX>0){right = 1*255; left = (1-(locX/panningFalloff))*255;}
        if (locX<0){left = 1*255; right = (1-(-locX/panningFalloff))*255;}
        if(right<0){right=0;}
        if(left<0){left=0;}
        if(right>255){right=255;}
        if(left>255){left=255;}
        if(finalVolume<0){finalVolume=0;}
        if(finalVolume>Volume){finalVolume=Volume;}
        return {finalVolume, left, right};
    }

    /*SOUND VOIDS -----------------------------------------------------------------*/

    Mix_Music* loadMusic(const char* filepath){
        Mix_Music *m;
        m = Mix_LoadMUS(filepath);
        if(m==NULL){std::cout<<"loadMusic Error: "<<Mix_GetError()<<std::endl;}
        return m;
    }

    Mix_Chunk* loadSound(const char* filepath){
        Mix_Chunk *ch;
        ch = Mix_LoadWAV(filepath);
        if(ch==NULL){std::cout<<"loadSound Error: "<<Mix_GetError()<<std::endl;}
        return ch;
    }

    //The most basic, dont see much potencial.
    int playMusic(Mix_Music* music, int volume, int loops){
        Mix_VolumeMusic(calculateVolume(volume));
        return Mix_PlayMusic(music, loops);
    }

    //The best of all for all situations. Noises, soundtracks everything.
    int playSound(Mix_Chunk* sound,int channel, int volume, int loops){
        int ch = Mix_PlayChannel(channel, sound, loops);
        Mix_Volume(ch, calculateVolume(volume));
        return ch;
    }

    //Panned version of the playSound.
    int playSoundPanned(Mix_Chunk* sound, int channel, Uint8 left, Uint8 right, int volume, int loops){
        int ch = Mix_PlayChannel(channel, sound, loops);
        Mix_Volume(ch, calculateVolume(volume));
        Mix_SetPanning(ch, left, right);
        return ch;
    }

    //Play sound the same way as playSound() but with a fade in period.
    int fadeInSound(Mix_Chunk* sound,int channel, int volume, int loops, int time){
        int ch = Mix_FadeInChannel(channel, sound, loops, time);
        Mix_Volume(ch, calculateVolume(volume));
        return ch;
    }

    //Halts channel with a fadeout
    int fadeOutChannel(int channel, int time){
        return Mix_FadeOutChannel(channel, time);
    }

    void pauseChannel(int channel){
        Mix_Pause(channel);
    }

    void playChannel(int channel){
        Mix_Resume(channel);
    }

    int stopChannel(int channel){
        return Mix_HaltChannel(channel);
    }

    /*SETTINGS VOIDS ------------------------------------------------------------------*/

    int setChannelPanning(int channel, Uint8 left, Uint8 right){
        return Mix_SetPanning(channel, left, right);
    }

    int setVolume(int channel, int volume){
        return Mix_Volume(channel, calculateVolume(volume));
    }
};