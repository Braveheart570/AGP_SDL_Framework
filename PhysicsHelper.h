#pragma once
#include "boxCollider.h"
#include "CircleCollider.h"
#include "MathHelper.h"

namespace SDLFramework {


	inline bool CircleVsCircleCollision(CircleCollider* circle1, CircleCollider* circle2) {

		return (circle1->Position() - circle2->Position()).Magnitude() < (circle1->GetRadius() + circle1->GetRadius());

	}

	inline bool BoxVsCircleCollision(BoxCollider* box, CircleCollider* circle) {

		Vector2 circlePos = circle->Position();
		float radius = circle->GetRadius();

		Vector2 quad[4];

		quad[0] = box->GetVertexPos(0);
		quad[1] = box->GetVertexPos(1);
		quad[2] = box->GetVertexPos(2);
		quad[3] = box->GetVertexPos(3);

		//Vertex collision Check
		for (int i = 0; i < 4; i++) {
			if ((quad[i] - circle->Position()).Magnitude() < radius) {
				//a corner is inside the circle
				return true;
			}
		}

		//edge checking
		if (PointToLineDistance(quad[0], quad[1], circlePos) < radius ||
			PointToLineDistance(quad[1], quad[2], circlePos) < radius || 
			PointToLineDistance(quad[2], quad[3], circlePos) < radius || 
			PointToLineDistance(quad[3], quad[0], circlePos) < radius
			) {
			// the circle is overlapping an edge of the box
			return true;

		}

		// chekci f circle is inside out box
		if (PointinPolygon(quad,4,circlePos)) {
			return true;
		}

		// implicite?
		//return false;

	}


	inline bool BoxVsBoxCollision(BoxCollider* box1, BoxCollider* box2) {

		Vector2 projAxes[4];
		projAxes[0] = (box1->GetVertexPos(0) - box1->GetVertexPos(1)).Normalized();
		projAxes[1] = (box1->GetVertexPos(0) - box1->GetVertexPos(2)).Normalized();
		projAxes[2] = (box2->GetVertexPos(0) - box2->GetVertexPos(1)).Normalized();
		projAxes[3] = (box2->GetVertexPos(0) - box2->GetVertexPos(2)).Normalized();

		float box1Min = 0.0f;
		float box1Max = 0.0f;
		float box2Min = 0.0f;
		float box2Max = 0.0f;

		float proj1 = 0.0f;
		float proj2 = 0.0f;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				proj1 = Dot(box1->GetVertexPos(j), projAxes[i]);
				proj1 = Dot(box2->GetVertexPos(j), projAxes[i]);

				if (j == 0) {
					box1Min = box1Max = proj1;
				}
				else {
					if (proj1 < box1Min) {
						box1Min = proj1;
					}
					if (proj1 > box1Max) {
						box1Max = proj1;
					}
					if (proj2 < box2Min) {
						box2Min = proj2;
					}
					if (proj2 > box2Max) {
						box2Max = proj2;
					}
				}
			}
			// at this time we have our two boxes projected

			float halfDist1 = (box1Max - box1Min) * 0.5;
			float midPoint1 = box1Min + halfDist1;

			float halfDist2 = (box2Max - box2Min) + 0.05f;
			float midPoint2 = box2Min + halfDist2;

			if (abs(midPoint1 - midPoint2) > (halfDist1 + halfDist2)) {
				return false; 
			}

		}

		// this funciton is using implicite return true since the ony other check is false.

	}

	inline bool ColliderVsColliderCheck(Collider* collider1, Collider* collider2) {

		if (collider1->getType() == Collider::ColliderType::Circle && collider2->getType() == Collider::ColliderType::Circle) {
			return CircleVsCircleCollision(dynamic_cast<CircleCollider*>(collider1), dynamic_cast<CircleCollider*>(collider2));

		}else if (collider1->getType() == Collider::ColliderType::Box && collider2->getType() == Collider::ColliderType::Box) {
			return BoxVsBoxCollision(dynamic_cast<BoxCollider*>(collider1), dynamic_cast<BoxCollider*>(collider2));

		}else if (collider1->getType() == Collider::ColliderType::Box && collider2->getType() == Collider::ColliderType::Circle) {
			return BoxVsCircleCollision(dynamic_cast<BoxCollider*>(collider1), dynamic_cast<CircleCollider*>(collider2));

		}else if (collider1->getType() == Collider::ColliderType::Circle && collider2->getType() == Collider::ColliderType::Box) {
			return BoxVsCircleCollision(dynamic_cast<BoxCollider*>(collider2), dynamic_cast<CircleCollider*>(collider1));

		}
		else {
			return false;
		}

	}

}