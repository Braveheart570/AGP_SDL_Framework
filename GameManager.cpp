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


		if (mInputManager->KeyDown(SDL_SCANCODE_W)) {
			mPhys1->Translate(Vect2_Up * -80 * mTimer->DeltaTime(), GameEntity::LOCAL);
		}
		else if(mInputManager->KeyDown(SDL_SCANCODE_S)){
			mPhys1->Translate(Vect2_Up * 80 * mTimer->DeltaTime(), GameEntity::LOCAL);
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_A)) {
			mPhys1->Translate(Vect2_Right * -80 * mTimer->DeltaTime(), GameEntity::LOCAL);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_D)) {
			mPhys1->Translate(Vect2_Right * 80 * mTimer->DeltaTime(), GameEntity::LOCAL);
		}
		
		if (mInputManager->KeyDown(SDL_SCANCODE_Q)) {
			mPhys1->Rotate(-2);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_E)) {
			mPhys1->Rotate(2);
		}



	}

	void GameManager::LateUpdate() {
		mPhysicsManager->Update();
		mInputManager->updatePreviewInput();
		
	}

	void GameManager::Render() {
		//old frame to clear
		mGraphics->ClearBackBuffer();


		mPhys1->Render();
		mPhys1Tex->Render();
		mPhys2->Render();
		mPhys2Tex->Render();
		mPhys3->Render();
		mPhys3Tex->Render();
		mPhys4->Render();
		mPhys4Tex->Render();

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
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::HostileProjectile,
			PhysicsManager::CollisionFlags::Friendly
		);
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::FriendlyProjectile,
			PhysicsManager::CollisionFlags::Hostile
		);


		const int labelTextSize = 26;

		mPhys1 = new PhysEntity();
		mPhys1->Position(Vector2(Graphics::SCREEN_WIDTH * 0.3f,Graphics::SCREEN_HEIGHT * 0.3f));
		mPhys1->AddCollider(new BoxCollider(Vector2(30.0f,30.0f)));
		mPhys1->mId = mPhysicsManager->RegisterEntity(mPhys1, PhysicsManager::CollisionLayers::Friendly);

		mPhys1Tex = new Texture("Friendly", "ARCADE.TTF", labelTextSize, {255,255,255});
		mPhys1Tex->Parent(mPhys1);
		mPhys1Tex->Position(Vect2_Zero);

		mPhys2 = new PhysEntity();
		mPhys2->Position(Vector2(Graphics::SCREEN_WIDTH * 0.7f, Graphics::SCREEN_HEIGHT * 0.3f));
		mPhys2->AddCollider(new BoxCollider(Vector2(30.0f,30.0f)));
		mPhys2->mId = mPhysicsManager->RegisterEntity(mPhys2, PhysicsManager::CollisionLayers::Hostile);

		mPhys2Tex = new Texture("Hostile", "ARCADE.TTF", labelTextSize, { 255,255,255 });
		mPhys2Tex->Parent(mPhys2);
		mPhys2Tex->Position(Vect2_Zero);

		mPhys3 = new PhysEntity();
		mPhys3->Position(Vector2(Graphics::SCREEN_WIDTH * 0.7f, Graphics::SCREEN_HEIGHT * 0.7f));
		mPhys3->AddCollider(new BoxCollider(Vector2(30.0f, 30.0f)));
		mPhys3->mId = mPhysicsManager->RegisterEntity(mPhys3, PhysicsManager::CollisionLayers::HostileProjectile);

		mPhys3Tex = new Texture("HostileProjectile", "ARCADE.TTF", labelTextSize, { 255,255,255 });
		mPhys3Tex->Parent(mPhys3);
		mPhys3Tex->Position(Vect2_Zero);

		mPhys4 = new PhysEntity();
		mPhys4->Position(Vector2(Graphics::SCREEN_WIDTH * 0.3f, Graphics::SCREEN_HEIGHT * 0.7f));
		mPhys4->AddCollider(new BoxCollider(Vector2(30.0f, 30.0f)));
		mPhys4->mId = mPhysicsManager->RegisterEntity(mPhys4, PhysicsManager::CollisionLayers::FriendlyProjectile);

		mPhys4Tex = new Texture("FriendlyProjectile", "ARCADE.TTF", labelTextSize, { 255,255,255 });
		mPhys4Tex->Parent(mPhys4);
		mPhys4Tex->Position(Vect2_Zero);

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

		

		delete mPhys1;
		mPhys1 = nullptr;
		delete mPhys1Tex;
		mPhys1Tex = nullptr;

		delete mPhys2;
		mPhys2 = nullptr;
		delete mPhys2Tex;
		mPhys2Tex = nullptr;

		delete mPhys3;
		mPhys3 = nullptr;
		delete mPhys3Tex;
		mPhys3Tex = nullptr;

		delete mPhys4;
		mPhys4 = nullptr;
		delete mPhys4Tex;
		mPhys4Tex = nullptr;



		//quit sdl subsystems
		SDL_Quit();
	}

}