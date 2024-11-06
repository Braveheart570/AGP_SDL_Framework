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

}