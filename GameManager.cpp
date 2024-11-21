#include "GameManager.h"
//TODO remove
#include "boxcollider.h"

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
			mPhys2->Translate(Vect2_Up * -80 * mTimer->DeltaTime(), GameEntity::LOCAL);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_K)) {
			mPhys2->Translate(Vect2_Up * 80 * mTimer->DeltaTime(), GameEntity::LOCAL);
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_J)) {
			mPhys2->Translate(Vect2_Right * -80 * mTimer->DeltaTime(), GameEntity::LOCAL);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_L)) {
			mPhys2->Translate(Vect2_Right * 80 * mTimer->DeltaTime(), GameEntity::LOCAL);
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_U)) {
			mPhys2->Rotate(-80 * mTimer->DeltaTime());
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_O)) {
			mPhys2->Rotate(80 * mTimer->DeltaTime());
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_N)) {
			mPhys2->Scale(mTex2->Scale() -= Vect2_One * 80 * mTimer->DeltaTime());
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_M)) {
			mPhys2->Scale(mTex2->Scale() += Vect2_One * 80 * mTimer->DeltaTime());
		}





		if (mInputManager->KeyPressed(SDL_SCANCODE_SPACE)) {
			std::cout << "Space Pressed!" << std::endl;
			mAudioManager->PlaySFX("coin_credit.wav");
			mAudioManager->PauseMusic();
		}
		if (mInputManager->keyReleased(SDL_SCANCODE_SPACE)) {
			std::cout << "Space Released!" << std::endl;
			mAudioManager->ResumeMusic();
		}

		if (mInputManager->MouseButtonPressed(InputManager::Left)) {
			std::cout << "LMB Pressed!" << std::endl;
		}
		if (mInputManager->MouseButtonReleased(InputManager::Left)) {
			std::cout << "LMB Released!" << std::endl;
		}



	}

	void GameManager::LateUpdate() {
		mPhysicsManager->Update();
		mInputManager->updatePreviewInput();
		
	}

	void GameManager::Render() {
		//old frame to clear
		mGraphics->ClearBackBuffer();

		//mTex->Render();
		//mTex2->Render();
		//mFontText->Render();
		mPhys1->Render();
		mPhys2->Render();

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
		mPhysicsManager = PhysicsManager::Instance();


		//Create Physics Layers
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Friendly, 
			PhysicsManager::CollisionFlags::Hostile | 
			PhysicsManager::CollisionFlags::HostileProjectile
		);
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Hostile,
			PhysicsManager::CollisionFlags::Friendly |
			PhysicsManager::CollisionFlags::FriendlyProjectile
		);

		

		mTex = new Texture("SpriteSheet.png",160,55,16,16);
		mTex->Scale(Vector2(3,3));
		mTex->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.5f);

		mTex2 = new Texture("BoxCollider.png");
		mTex2->Scale(Vector2(20, 20));
		mTex2->Position(Graphics::SCREEN_WIDTH * 0.6f, Graphics::SCREEN_HEIGHT * 0.5f);

		mFontText = new Texture("Galaga", "ARCADE.TTF", 72, {225,255,255});
		mFontText->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.15f);

		//mAudioManager->PlayMusic("Map.wav");



		mPhys1 = new PhysEntity();
		mPhys1->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f,Graphics::SCREEN_HEIGHT * 0.5f));
		mPhys1->AddCollider(new BoxCollider(Vector2(20.0f,20.0f)));
		mPhys1->mId = mPhysicsManager->RegisterEntity(mPhys1, PhysicsManager::CollisionLayers::Friendly);

		mPhys2 = new PhysEntity();
		mPhys2->Position(Vector2(Graphics::SCREEN_WIDTH * 0.6f, Graphics::SCREEN_HEIGHT * 0.6f));
		mPhys2->AddCollider(new BoxCollider(Vector2(50.0f,50.0f)));
		mPhys2->mId = mPhysicsManager->RegisterEntity(mPhys2, PhysicsManager::CollisionLayers::Hostile);

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

		PhysicsManager::Release();
		mPhysicsManager = nullptr;

		delete mTex;
		mTex = nullptr;

		delete mTex2;
		mTex2 = nullptr;

		delete mFontText;
		mFontText = nullptr;

		delete mPhys1;
		mPhys1 = nullptr;

		delete mPhys2;
		mPhys2 = nullptr;

		//quit sdl subsystems
		SDL_Quit();
	}

}