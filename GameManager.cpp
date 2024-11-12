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

		std::cout << "Delta Time: " << mTimer->DeltaTime() << std::endl;

	}

	void GameManager::LateUpdate() {

	}

	void GameManager::Render() {
		//old frame to clear
		mGraphics->ClearBackBuffer();

		mTex->Render();
		mTex2->Render();
		mTex3->Render();

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


		mTex = new Texture("SpriteSheet.png",160,55,16,16);
		mTex->Scale(Vector2(3,3));
		mTex->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.5f);

		mTex2 = new Texture("SpriteSheet.png", 160, 79, 16, 16);
		mTex2->Scale(Vector2(3, 3));
		mTex2->Position(Graphics::SCREEN_WIDTH * 0.6f, Graphics::SCREEN_HEIGHT * 0.5f);

		mTex3 = new Texture("SpriteSheet.png", 161, 319, 13, 16);
		mTex3->Scale(Vector2(3, 3));
		mTex3->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.6f);


	}

	GameManager::~GameManager() {
		//release modules
		Graphics::Release();
		mGraphics = nullptr;

		Timer::Release();
		mTimer = nullptr;

		AssetManager::Release();
		mAssetManager = nullptr;

		delete mTex;
		mTex = nullptr;

		delete mTex2;
		mTex2 = nullptr;

		delete mTex3;
		mTex3 = nullptr;


		//quit sdl subsystems
		SDL_Quit();
	}

}