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
class Skill_FireBall : public GameObject
{
	Image* mImage;

	FlameEffect* mFlameEffect;
	FireBallState mState;

	class Animation* mFireBallReadyAnimation;	// 0, 0, 3, 0
	class Animation* mFireBallFireAnimation;	// 4, 0, 8, 0
	class Animation* mCurrentAnimation;

	int mDelay;
	float mFrameCount;
	float mAngle;
	float mSpeed;
public:
	Skill_FireBall(const string& name) : GameObject(name) {};
	Skill_FireBall(const string& name, float x, float y, float angle);
	Skill_FireBall(const string& name, float x, float y, float angle, int delay);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void SetDelay(int delay) { mDelay = delay; }
	void AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime);
	void AnimationChange(Animation* changeAnimation);
};