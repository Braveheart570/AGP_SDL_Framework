#pragma once
#include <SDL.h>
#include <iostream>

namespace SDLFramework {
	//singleton
	class Graphics {

	public:
		static const int SCREEN_WIDTH = 640;
		static const int SCREEN_HEIGHT = 480;

		static Graphics* Instance();

		//handle releaseing/ uninitializing/ dealocating memory.
		static void Release();

		static bool Initialized();


		void ClearBackBuffer();

		void Render();

		Graphics();
		~Graphics();

		bool Init();
		
	private:
		
		//this is going to hold the one instance of our graphics class.
		static Graphics* sInstance;
		static bool sInitialized;
		SDL_Window* mWindow = nullptr;
		SDL_Renderer* mRenderer = nullptr;
	};

}