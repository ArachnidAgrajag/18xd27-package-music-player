#include<iostream>
#include "playMusic.hpp"
#include <cstring>
#include <string>

int main(){
        std::cout<<"Hello!! Please enter the location of the song. including the file extionsion(mp3 only)"<<std::endl;
        std::string inputFileLoc;
        std::getline(std::cin, inputFileLoc);
        const char * cstr = inputFileLoc.c_str();
        playFile(cstr);
        return 0;
}
