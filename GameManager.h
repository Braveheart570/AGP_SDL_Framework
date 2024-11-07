#pragma once
#include "Graphics.h"

namespace SDLFramework {

	//Singleton
	class GameManager {
	public:
		// these functions are key in singletons
		static GameManager* Instance();
		static void Release();


		GameManager();
		~GameManager();


		void Update();
		void LateUpdate();

		void Render();

		void Run();


	private:
		// this is how we are creating this as a singleton
		static GameManager* sInstance;
		//loop cotrol
		bool mQuit;

		//modules
		Graphics* mGraphics;

		SDL_Event mEvents;
	};

}