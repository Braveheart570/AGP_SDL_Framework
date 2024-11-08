#pragma once
#include<math.h>

namespace SDLFramework {

	//macros
#define PI 3.1415926535
#define DEG_TO_RAD PI / 180.0f

	struct Vector2 {

		float x;
		float y;
		Vector2(float _x = 0.0f, float _y = 0.0f) : x{ _x }, y{ _y } {}
		

		float Magnitude() {
			return (float)sqrt(x * x + y * y);
		}

		float MagnitudeSqr() {
			return x * x + y * y;
		}

		Vector2 Normalized() {
			float mag = Magnitude();
			return Vector2(x / mag, y / mag);
		}




	};

	// operator overloading.
	inline Vector2 operator+ (const Vector2& lhs, const Vector2& rhs) { // left hand side, right hand side
		return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	
	inline Vector2 operator- (const Vector2& lhs, const Vector2& rhs) {
		return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	inline Vector2 operator* (const Vector2& lhs, const float rhs) {
		return Vector2(lhs.x * rhs, lhs.y * rhs);
	}
	inline Vector2 operator* (const float lhs, const Vector2& rhs) {
		return Vector2(rhs.x * lhs, rhs.y * lhs);
	}

	inline Vector2 operator/ (const Vector2& lhs, const float rhs) {
		return Vector2(lhs.x / rhs, lhs.y / rhs);
	}
	inline Vector2 operator/ (const float lhs, const Vector2& rhs) {
		return Vector2(rhs.x / lhs, rhs.y / lhs);
	}

	inline Vector2 lerp(const Vector2& start, const Vector2& end, float time) {

		if (time <= 0.0f) {
			return start;
		}
		
		if (time >= 1.0f) {
			return end;
		}

		Vector2 dir = (end - start).Normalized();
		float mag = (end - start).Magnitude();

		return start + dir * mag * time;

	}

	inline Vector2 RotateVector(const Vector2& vec, float& angle) {
		//convert degrees to radians
		float radAngle = (float)(angle * DEG_TO_RAD);

		return Vector2(
			(float)vec.x * cos(radAngle) - vec.y * sin(radAngle),
			(float)vec.x * sin(radAngle) + vec.y * cos(radAngle)
		);
	}


	inline float Dot(const Vector2& vec1, const Vector2& vec2) {


		return (vec1.x * vec2.x) + (vec1.y * vec2.y);

	}

	inline float Clamp(const float& value, const float& min, const float& max) {
		
		if (value > max) {return max;}
		if (value < min) {return min;}

		return value;


	}

	const Vector2 Vect2_Zero = {0.0f,0.0f};
	const Vector2 Vect2_One = { 1.0f,1.0f };
	const Vector2 Vect2_Up = { 0.0f,1.0f };
	const Vector2 Vect2_Right = { 1.0f,0.0f };


}