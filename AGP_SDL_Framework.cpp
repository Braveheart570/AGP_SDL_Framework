#include <iostream>
#include <SDL.h>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
bool quit = false;

//SDL redifines the main function?
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

    //Draw a Window
    window = SDL_CreateWindow(
        "test window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        std::cerr << "unable to create a window! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }




    // index -1 will find the first available rendering driver
    renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        std::cerr << "unable to create a renderer! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_SetRenderDrawColor(renderer, 102, 66, 245, 255);
    SDL_Event events = {};
    
    //main game loops
    while (!quit) {
        // while there are events inside of events variable.
        while (SDL_PollEvent(&events)) {
            switch (events.type) {
            case SDL_QUIT:
                quit = true;
                break;
            }
        }

        //render code
        SDL_RenderFillRect(renderer, nullptr);

        // draw to window
        SDL_RenderPresent(renderer);



    }

    SDL_DestroyWindow(window);

    SDL_DestroyRenderer(renderer);

    //terminate SDL subsystems
    SDL_Quit();
}