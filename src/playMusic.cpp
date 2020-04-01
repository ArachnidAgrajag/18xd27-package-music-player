#include"playMusic.hpp"
#include "SDL.h"
#include "SDL_mixer.h"
#include<iostream>

bool playFile(const char* fileName){
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

        Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
        Mix_Music *music = Mix_LoadMUS(fileName);
        Mix_PlayMusic(music, 1);

        while (!SDL_QuitRequested()) {
                SDL_Delay(250);
        }

        Mix_FreeMusic(music);
        SDL_Quit();
        return true;
   }

