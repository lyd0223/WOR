#pragma once
#include "MonsterObject.h"

enum class FireBossState : int {
	Idle			= 0,
	AttackReady		= 1,
	Dash			= 2,
	Stemp			= 3,
	Throw			= 4,
	Kick			= 5,
	Meteor			= 6,
	DragonArc		= 7,
	SpecialAttack	= 8,
	Refresh			= 9,
	Stun			= 10,

	End
};

class Effect_FireWing;
class Animation;
class Monster_FireBoss : public MonsterObject
{
	class Animation* mLeftIdleAnimation;			// 0, 1
	class Animation* mRightIdleAnimation;			// 0, 0

	class Animation* mLeftDashStartAnimation;		// 1, 1
	class Animation* mRightDashStartAnimation;		// 0, 1

	class Animation* mLeftDashAnimation;			// 1, 1, 3, 1
	class Animation* mRightDashAnimation;			// 1, 0, 3, 0,
	class Animation* mUpDashAnimation;				// 4, 0
	class Animation* mDownDashAnimation;			// 4, 1

	class Animation* mLeftDashEndAnimation;			// 3, 1
	class Animation* mRightDashEndAnimation;		// 3, 0

	class Animation* mLeftSpecialAttackAnimation;	// 9, 1, 11, 1
	class Animation* mRightSpecialAttackAnimation;	// 9, 0, 11, 0

	class Animation* mLeftKickAnimation;			// 0, 3, 11, 3
	class Animation* mRightKickAnimation;			// 0, 2, 11, 2

	class Animation* mLeftAttackReadyAnimation;		// 0, 5, 3, 5
	class Animation* mRightAttackReadyAnimation;	// 0, 4, 3, 4

	class Animation* mLeftThrowAnimation;			// 10, 5, 11, 5
	class Animation* mRightThrowAnimation;			// 10, 4, 11, 4
	class Animation* mUpThrowAnimation;				// 10, 7, 11, 7
	class Animation* mDownThrowAnimation;			// 10, 6, 11, 6

	class Animation* mLeftStunAnimation;			// 0, 7, 4, 7
	class Animation* mRightStunAnimation;			// 0, 6, 4, 6

	class Animation* mRefreshAnimation1;			// 0, 8, 6, 8
	class Animation* mRefreshAnimation2;			// 0, 9, 6, 9

	class Animation* mLeftStempAnimation;			// 10, 9, 11, 9
	class Animation* mRightStempAnimation;			// 10, 8, 11, 8

	class Animation* mCurrentAnimation;

	Effect_FireWing* mFireWing;
	FireBossState mFireBossState;
	vector<FireBossState> mFireBossStateList;

	D2D1_RECT_F mMapRect;
	
	queue<function<void()>> mPatternList;

	int mNum;
	float mFrameCount;
	float mMoveDistance;
	float mAngle;
	float mKickAngle;
	
	bool mIsFuncEnd;
public:
	Monster_FireBoss(const string& name, float x, float y);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime);
	void AnimationChange(Animation* changeanimation);
	
	void Move();
	void AttackReady();
	void StempPattern();
	void ThreeRushPattern();
	void FireBallThrowPattern();
	void MeteorPattern();
	void DragonArcWavePattern();
	void KickPattern();
	void MakeFlame();
	void MakeFireWing();

	void BossStateChange();

	void MakePatternFuncList();
	void CallPattern();
	FireBossState FireBossStateCheck(int index);
};