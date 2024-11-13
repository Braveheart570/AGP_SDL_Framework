#pragma once
#include "Texture.h"
#include "Timer.h"

namespace SDLFramework {

	class AnimatedTexture : public Texture {
	public:
		enum WrapMode { Once = 0, loop };
		enum AnimDir{Horizontal = 0, Vertical};

		AnimatedTexture(std::string filename, int x, int y, int width, int height, int frameCount, float animatedSpeed, float AnimDir, float AnimationDir, bool managed = false);
		~AnimatedTexture();


	private:
		Timer* mTimer;
		int mStartX;
		int mStartY;
		int mFrameCount;
		float mAnimationSpeed; // in seconds
		float mTimePerFrame; // time to display
		float mAnimationTimer; // time displayed

		WrapMode mWrapMode;
		AnimDir mAnimationDirection;

		bool mAnimationDone;

	};


}
