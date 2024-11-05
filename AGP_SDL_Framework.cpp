#include <iostream>
#include <SDL.h>

int main(int argc, char* args[])
{

    //initialize SDL subsystems
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
        //failed to initialize
        std::cerr << "SDL could not init video: " << SDL_GetError() << std::endl;
        return -1;
    }
    else {
        std::cout << "video init sucessfull" << std::endl;
    }

    //terminate SDL subsystems
    SDL_Quit();
}