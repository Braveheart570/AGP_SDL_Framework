#include "GameEntity.h"


namespace SDLFramework {

	GameEntity::GameEntity(float x = 0.0f, float y = 0.0f) {
		mPosition = Vector2(x, y);
	}

	GameEntity::~GameEntity() {
		mParent = nullptr;
	}

	void GameEntity::Position(float x, float y) {
		mPosition.x = x;
		mPosition.y = y;

	}

	void GameEntity::Position(const Vector2& pos) {
		mPosition.x = pos.x;
		mPosition.y = pos.y;
	}

	Vector2 GameEntity::Position(Space space = WORLD) {
		switch (space) {
		case WORLD:
			return mPosition;
			break;
		case LOCAL:
			return mPosition - mParent->Position(WORLD);
			break;
		default:
			return mPosition;
		}
	}

	void GameEntity::Rotation(float rot) {
		mRotation = rot;
	}

	float GameEntity::Rotation(Space space = WORLD) {
		switch (space) {
		case WORLD:
			return mRotation;
			break;
		case LOCAL:
			return mRotation + mParent->Rotation(WORLD);
		}
	}

	void GameEntity::Scale(const Vector2& scale) {
		mScale.x = scale.x;
		mScale.y = scale.y;
	}

	Vector2 GameEntity::Scale(Space space = WORLD) {
		switch (space) {
		case WORLD:
			return mScale;
			break;
		case LOCAL:
			return mScale - mParent->Scale(WORLD);
			break;
		default:
			return mScale;
		}
	}


	void GameEntity::Active(bool active){
		mActive = active;
	}

	bool GameEntity::Active() {
		return mActive;
	}

	void GameEntity::Parent(GameEntity* parent) {
		mParent = parent;
	}

	GameEntity* GameEntity::Parent() {
		return mParent;
	}

}