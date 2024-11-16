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

		mTex2->Update();


		if (mInputManager->KeyDown(SDL_SCANCODE_W)) {
			mTex->Translate(Vect2_Up * -80 * mTimer->DeltaTime(), GameEntity::LOCAL);
		}
		else if(mInputManager->KeyDown(SDL_SCANCODE_S)){
			mTex->Translate(Vect2_Up * 80 * mTimer->DeltaTime(), GameEntity::LOCAL);
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_A)) {
			mTex->Translate(Vect2_Right * -80 * mTimer->DeltaTime(), GameEntity::LOCAL);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_D)) {
			mTex->Translate(Vect2_Right * 80 * mTimer->DeltaTime(), GameEntity::LOCAL);
		}
		
		if (mInputManager->KeyDown(SDL_SCANCODE_Q)) {
			mTex->Rotate(-2);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_E)) {
			mTex->Rotate(2);
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_Z)) {
			mTex->Scale(mTex->Scale()-= Vect2_One * 80 * mTimer->DeltaTime());
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_C)) {
			mTex->Scale(mTex->Scale()+= Vect2_One * 80 * mTimer->DeltaTime());
		}


		

		if (mInputManager->KeyDown(SDL_SCANCODE_I)) {
			mTex2->Translate(Vect2_Up * -80 * mTimer->DeltaTime(), GameEntity::LOCAL);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_K)) {
			mTex2->Translate(Vect2_Up * 80 * mTimer->DeltaTime(), GameEntity::LOCAL);
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_J)) {
			mTex2->Translate(Vect2_Right * -80 * mTimer->DeltaTime(), GameEntity::LOCAL);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_L)) {
			mTex2->Translate(Vect2_Right * 80 * mTimer->DeltaTime(), GameEntity::LOCAL);
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_U)) {
			mTex2->Rotate(-80 * mTimer->DeltaTime());
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_O)) {
			mTex2->Rotate(80 * mTimer->DeltaTime());
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_N)) {
			mTex2->Scale(mTex2->Scale() -= Vect2_One * 80 * mTimer->DeltaTime());
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_M)) {
			mTex2->Scale(mTex2->Scale() += Vect2_One * 80 * mTimer->DeltaTime());
		}





		if (mInputManager->KeyPressed(SDL_SCANCODE_SPACE)) {
			std::cout << "Space Pressed!" << std::endl;
			mAudioManager->PlaySFX("coin_credit.wav");
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
		mTex2->Render();
		mFontText->Render();

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
		mAudioManager = AudioManager::Instance();


		mTex = new Texture("SpriteSheet.png",160,55,16,16);
		mTex->Scale(Vector2(3,3));
		mTex->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.5f);

		mTex2 = new AnimatedTexture("SpriteSheet.png", 204, 45, 40, 38, 4, 1,AnimatedTexture::Horizontal);
		mTex2->Scale(Vector2(3, 3));
		mTex2->Position(Graphics::SCREEN_WIDTH * 0.6f, Graphics::SCREEN_HEIGHT * 0.5f);

		mFontText = new Texture("Galaga", "ARCADE.TTF", 72, {225,255,255});
		mFontText->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.15f);


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

		AudioManager::Release();
		mAudioManager = nullptr;

		delete mTex;
		mTex = nullptr;

		delete mTex2;
		mTex2 = nullptr;

		delete mFontText;
		mFontText = nullptr;

		//quit sdl subsystems
		SDL_Quit();
	}

}