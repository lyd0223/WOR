#pragma once
#include "Enemy.h"

enum class BossPattern : int {
	Idle,
	Dash,
	Kick,
	SpecialAttack,
	AttackReady,
	Throw,
	Stun,
	Refresh,
	Stemp,

	End
};

class Animation;
class FireBoss : public Enemy
{
	Animation* mLeftIdleAnm;			// 0, 1
	Animation* mRightIdleAnm;			// 0, 0
	Animation* mLeftDashAnm;			// 1, 1, 3, 1
	Animation* mRightDashAnm;			// 1, 0, 3, 0,
	Animation* mUpDashAnm;				// 4, 0
	Animation* mDownDashAnm;			// 4, 1
	Animation* mLeftSpecialAttackAnm;	// 9, 1, 11, 1
	Animation* mRightSpecialAttackAnm;	// 9, 0, 11, 0
	Animation* mLeftKickAnm;			// 0, 3, 11, 3
	Animation* mRightKickAnm;			// 0, 2, 11, 2
	Animation* mLeftAttackReadyAnm;		// 0, 5, 3, 5
	Animation* mRightAttackReadyAnm;	// 0, 4, 3, 4
	Animation* mLeftThrowAnm;			// 10, 5, 11, 5
	Animation* mRightThrowAnm;			// 10, 4, 11, 4
	Animation* mUpThrowAnm;				// 10, 7, 11, 7
	Animation* mDownThrowAnm;			// 10, 6, 11, 6
	Animation* mLeftStunAnm;			// 0, 7, 4, 7
	Animation* mRightStunAnm;			// 0, 6, 4, 6
	Animation* mRefreshAnm1;			// 0, 8, 6, 8
	Animation* mRefreshAnm2;			// 0, 9, 6, 9
	Animation* mLeftStempAnm;			// 10, 9, 11, 9
	Animation* mRightStempAnm;			// 10, 8, 11, 8
	Animation* mCurrentAnm;

	BossPattern mPattern;
public:
	FireBoss();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};