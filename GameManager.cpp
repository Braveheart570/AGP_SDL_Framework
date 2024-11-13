#include "GameManager.h"

namespace SDLFramework {

	GameManager* GameManager::sInstance = nullptr;

	GameManager* GameManager::Instance() {

		if (sInstance == nullptr) {
			sInstance = new GameManager();
		}

		return sInstance;

	}

	void GameManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}


	void GameManager::Run() {
		//main game loops
		while (!mQuit) {

			mTimer->Update();

			// while there are events inside of events variable.
			while (SDL_PollEvent(&mEvents)) {
				switch (mEvents.type) {
				case SDL_QUIT:
					mQuit = true;
					break;
				}
			}

			// frame rate independence
			if (mTimer->DeltaTime() >= 1.0f / FRAME_RATE) {
				
				mTimer->Reset();
				Update();
				LateUpdate();
				Render();

			}

			



		}
	}


	void GameManager::Update() {

		mInputManager->Update();

		if (mInputManager->KeyDown(SDL_SCANCODE_W)) {
			mTex->Translate(Vector2(0, -40.0f) * mTimer->DeltaTime(), GameEntity::WORLD);
		}
		else if(mInputManager->KeyDown(SDL_SCANCODE_S)){
			mTex->Translate(Vector2(0, 40.0f) * mTimer->DeltaTime(), GameEntity::WORLD);
		}

		if (mInputManager->KeyPressed(SDL_SCANCODE_SPACE)) {
			std::cout << "Space Pressed!" << std::endl;
		}
		if (mInputManager->keyReleased(SDL_SCANCODE_SPACE)) {
			std::cout << "Space Released!" << std::endl;
		}

		if (mInputManager->MouseButtonPressed(InputManager::Left)) {
			std::cout << "LMB Pressed!" << std::endl;
		}
		if (mInputManager->MouseButtonReleased(InputManager::Left)) {
			std::cout << "LMB Released!" << std::endl;
		}



	}

	void GameManager::LateUpdate() {
		mInputManager->updatePreviewInput();
	}

	void GameManager::Render() {
		//old frame to clear
		mGraphics->ClearBackBuffer();

		mTex->Render();

		//draw to screem
		mGraphics->Render();
	}

	GameManager::GameManager() : mQuit(false) {
		// this is how you access a singleton;
		mGraphics = Graphics::Instance();

		if (!Graphics::Initialized()) {
			mQuit = true;
		}


		mTimer = Timer::Instance();
		mAssetManager = AssetManager::Instance();
		mInputManager = InputManager::Instance();


		mTex = new Texture("SpriteSheet.png",160,55,16,16);
		mTex->Scale(Vector2(3,3));
		mTex->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.5f);


	}

	GameManager::~GameManager() {
		//release modules
		Graphics::Release();
		mGraphics = nullptr;

		Timer::Release();
		mTimer = nullptr;

		AssetManager::Release();
		mAssetManager = nullptr;

		InputManager::Release();
		mInputManager = nullptr;

		delete mTex;
		mTex = nullptr;


		//quit sdl subsystems
		SDL_Quit();
	}

}