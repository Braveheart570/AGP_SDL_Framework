#pragma once
#include "Collider.h"
#include <vector>

namespace SDLFramework {

	class PhysEntity : public GameEntity {

	public:
		PhysEntity();
		virtual ~PhysEntity();

		unsigned long GetId();

		bool CheckCollision(PhysEntity* other);

		virtual void Hit(PhysEntity* other);

		virtual void Render() override;


	protected:


		virtual bool IgnoreCollisions();

		void AddCollider(Collider* colliderm, Vector2 localPos = Vect2_Zero);


		unsigned long int mId;

		std::vector<Collider*> mColliders;

		Collider* mBroadPhaseCollider;



	};

}