#pragma once
#include <SDL.h>

namespace SDLFramework {


	class InputManager {
	public:
		static InputManager* Instance();
		static void Release();


		InputManager();
		~InputManager();


	private:
		static InputManager* sInstance;

	};


}