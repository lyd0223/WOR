#pragma once
#include "MonsterObject.h"
#define AnimationTime 0.1f
#define TileSize 64
enum class MuscleManState
{
	Idle,
	Walk,
	AttackReady,
	Attack
};
class Monster_MuscleMan : public MonsterObject
{
protected:
	Image* mImage;
	Animation* mIdleAnimation;
	Animation* mWalkAnimation;
	Animation* mAttackAnimation;
	Animation* mAttackReadyAnimation;
	Animation* mDieAnimation;
	Animation* mCurrentAnimation;
	MuscleManState mMuscleManState;


public:
	Monster_MuscleMan(const string& name, float x, float y);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;


	float GetAngle() { return mAngle; }
	void SetAngle(float angle) { mAngle = angle; }
	float GetSpeed() { return mSpeed; }
	void SetSpeed(float speed) { mSpeed = speed; }
	void AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime);
	void AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime);
	void AnimationChange(Animation* changeanimation);

};