#include"playMusic.hpp"
#include "SDL.h"
#include "SDL_mixer.h"
#include<iostream>

bool playFile(const char* fileName){
        std::cout<<"1"<<std::endl;
        int result =0;
        int flags=MIX_INIT_MP3;
        //initialises SDL2 audio
        if(SDL_Init(SDL_INIT_AUDIO)<0){
                std::cout<< "Failed to initialise SDL";
                return false;
        }
        //initialise SDL Mixer
        if(flags !=(result = Mix_Init(flags))){
                std::cout<<"Could not intialise mixer (result : "<<result<<")\nMix_Init: "<<Mix_GetError()<<std::endl;
                return false;
        }
        std::cout<<"2"<<std::endl;
        Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
        Mix_Music *music = Mix_LoadMUS(fileName);
        std::cout<<"3"<<std::endl;
        Mix_PlayMusic(music, 1);
        std::cout<<"4"<<std::endl;
        while (!SDL_QuitRequested()) {
                std::cout<<"5"<<std::endl;
                SDL_Delay(250);
        }
        std::cout<<"6"<<std::endl;
        Mix_FreeMusic(music);
        std::cout<<"7"<<std::endl;
        SDL_Quit();
        std::cout<<"8"<<std::endl;
        return true;
   }

