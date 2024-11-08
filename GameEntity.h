#pragma once
#include "MathHelper.h"

namespace SDLFramework {

	class GameEntity {

	public:
		enum Space {LOCAL = 0, WORLD};

		GameEntity(float x = 0.0f, float y = 0.0f);
		~GameEntity();

		void Position(float x, float y);
		void Position(const Vector2& pos);
		Vector2 Position(Space space = WORLD);

		void Rotation(float rot);
		float Rotation(Space space = WORLD);

		void Scale(const Vector2& scale);
		Vector2 Scale(Space space = WORLD);

		void Active(bool active);
		bool Active();

		void Parent(GameEntity* parent);
		GameEntity* Parent();

		virtual void Update() {};
		virtual void Render() {};



	private:
		Vector2 mPosition;
		float mRotation;
		Vector2 mScale;

		bool mActive;
		GameEntity* mParent;

	};

}

