#pragma once
#include "boxCollider.h"
#include "CircleCollider.h"
#include "MathHelper.h"

namespace SDLFramework {


	inline bool CircleVsCircleCollision(CircleCollider* circle1, CircleCollider* circle2) {

		return (circle1->Position() - circle2->Position()).Magnitude() < (circle1->GetRadius() + circle1->GetRadius());

	}



}