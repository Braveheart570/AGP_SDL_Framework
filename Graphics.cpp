#include "Graphics.h"

namespace SDLFramework {

	// this is how we initialize static members in a class. specifically the ones we do not want to be constants.
	// static members cannot be defined on the same line they are declared witout being const. so we do it here.
	Graphics* Graphics::sInstance = nullptr;
	bool Graphics::sInitialized = false;

	// this is where we make this class a singleton
	Graphics* Graphics::Instance() {
		// checking to see if sInsatcen already has an isntace of graphics stored in it.
		if (sInstance == nullptr) {
			sInstance = new Graphics();
		}

		// return the instance after maing sure there is one.
		return sInstance;

	}


	void Graphics::Release() {
		delete sInstance;
		sInstance = nullptr;
		sInitialized = false;
	}

	bool Graphics::Initialized() {
		return sInitialized;
	}

	void Graphics::ClearBackBuffer() {
		SDL_RenderClear(mRenderer);
	}

	void Graphics::Render() {
		SDL_RenderPresent(mRenderer);
	}

	Graphics::Graphics() : mRenderer(nullptr) {
		sInitialized = Init();
	}


	Graphics::~Graphics(){
		// destroy th renderer first, reverse order of creation.
		SDL_DestroyRenderer(mRenderer);
		SDL_DestroyWindow(mWindow);
	}

	bool Graphics::Init() {

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
		mWindow = SDL_CreateWindow(
			"Test Window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
		);

		if (mWindow == nullptr) {
			std::cerr << "unable to create a window! SDL_Error: " << SDL_GetError() << std::endl;
			return false;
		}



		// index -1 will find the first available rendering driver
		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

		if (mRenderer == nullptr) {
			std::cerr << "unable to create a renderer! SDL_Error: " << SDL_GetError() << std::endl;
			return false;
		}


		return true;

	}


}