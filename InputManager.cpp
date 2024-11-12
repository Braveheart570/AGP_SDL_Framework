#include "InputManager.h"


namespace SDLFramework {

	InputManager* InputManager::sInstance = nullptr;

	InputManager* InputManager::Instance() {
		if (sInstance == nullptr) {
			sInstance = new InputManager();
		}

		return sInstance;
	}

	void InputManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}


	InputManager::InputManager() {

	}

	InputManager::~InputManager() {

	}


}