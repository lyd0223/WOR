#pragma once
#include "GameObject.h"

enum class FireBallState : int {
	Ready,
	Fire,

	End
};

class Image;
class Animation;
class FlameEffect;
class FireBall : public GameObject
{
	Image* mImage;

	FlameEffect* mFlameEffect;
	FireBallState mState;

	class Animation* mFireBallReadyAnimation;	// 0, 0, 3, 0
	class Animation* mFireBallFireAnimation;	// 4, 0, 8, 0
	class Animation* mCurrentAnimation;

	float mAngle;
	float mSpeed;
public:
	FireBall(const string& name, float x, float y, float angle);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime);
	void AnimationChange(Animation* changeanimation);
};