#pragma once
#include"MovingObject.h"
//class Tile;
enum class PlayerState :int
{
	LeftIdle,
	RightIdle,
	DownIdle,
	UpIdle,
	LeftHit,
	RightHit,
	UpHit,
	DownHit,
	LeftRun,
	RightRun,
	DownRun,
	UpRun,
	LeftAttack,
	RightAttack,
	DownAttack,
	UpAttack,
	LeftDash,
	LeftDiagonalUpDash,
	LeftDiagonalDownDash,
	RightDash,
	RightDiagonalUpDash,
	RightDiagonalDownDash,
	DownDash,
	UpDash,
	Die,
	UpThrowSkill,
	DownThrowSkill,
	LeftThrowSkillandAttack,
	RightThrowSkillandAttack,
	UpThrowWating,
	DownThorwWating,
	RightThrowWating,
	LeftThrowWaitng


};
#define AnimationTime 0.1f
#define TileSize 48
#define TileCountX 100
#define TileCountY 100
#define BasicSpeed 300.f
class Player : public MovingObject
{
	PlayerState mPlayerState;
	Image* mImage;
	Image* mImage2;
	float mMoveAngle;
	int mMoveCount;
	float mMp;

	//class Tile* TileList[TileCountY][TileCountY];

	class Animation* mRightIdleAnimation;
	class Animation* mDownIdleAnimation;
	class Animation* mUpIdleAnimation;
	class Animation* mLeftIdleAnimation;
	class Animation* mLeftHitAnimation;
	class Animation* mRightHitAnimation;
	class Animation* mUpHitAnimation;
	class Animation* mDownHitAnimation;
	class Animation* mLeftRunAnimation;
	class Animation* mRightRunAnimation;
	class Animation* mDownRunAnimation;
	class Animation* mUpRunAnimation;
	class Animation* mDownAttackAnimation;
	class Animation* mUpAttackAnimation;
	class Animation* mLeftDashAnimation;
	class Animation* mLeftDiagonalUpDashAnimation;
	class Animation* mLeftDiagonalDownDashAnimation;
	class Animation* mRightDashAnimation;
	class Animation* mRightDiagonalUpDashAnimation;
	class Animation* mRightDiagonalDownDashAnimation;
	class Animation* mDownDashAnimation;
	class Animation* mUpDashAnimation;
	class Animation* mDieAnimation;
	class Animation* mUpThrowSkillAnimation;
	class Animation* mDownThrowSkillAnimation;
	class Animation* mLeftThrowSkillandAttackAnimation;
	class Animation* mRightThrowSkillandAttackAnimation;
	class Animation* mUpThrowWatingAnimation;
	class Animation* mDownThrowWatingAnimation;
	class Animation* mLeftThrowWatingAnimation;
	class Animation* mRightThrowWationgAnimation;

	class PlayerNormalShadow* mPlayerNormalShadow;
	class PlayerWideShadow* mPlayerWideShadow;
	class PlayerHeightShadow* mPlayerHeightShadow;
	class MouseTracker *mMouseTracker;
	class Image* mShadow;
	float lineX;
	float lineY;

	float mLB_ButtonSkillCool;
	float mRB_ButtonSkillCool;
	float mQ_ButtonSkillCool;


	float mFrameCount;


	bool mIsAct;
	bool mIsDashEffect;
	class Animation* mCurrentAnimation;

	string mLB_ButtonSkill;
	string mRB_ButtonSkill;
	string mSpacebar_ButtonSkill;
	string mQ_ButtonSkill;

public:
	Player(const string& name, float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
	void AnimationSet(Animation** animation, bool Reverse, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime);
	void AnimationReverseSet(Animation** animation, bool Rivers, bool Loop, int StartindexX, int StartindexY, int EndindexX, int EndindexY, float animationTime);
	void AnimationChange(Animation* changeanimation);
	float GetSpeed() { return mSpeed; }
	float GetAngle() { return mAngle; }


	void SetLB_ButtonSkill(string skillName) { mLB_ButtonSkill = skillName; }
	void SetRB_ButtonSkill(string skillName) { mRB_ButtonSkill = skillName; }
	void SetSpacebar_ButtonSkill(string skillName) { mSpacebar_ButtonSkill = skillName; }
	void SetQ_ButtonSkill(string skillName) { mQ_ButtonSkill = skillName; }

	float GetRB_ButtonSkillCool() { return mRB_ButtonSkillCool; }

	float GetMp() { return mMp; }

	string GetLB_ButtonSkill() { return mLB_ButtonSkill; }
	string GetRB_ButtonSkill() { return mRB_ButtonSkill; }
	string GetSpacebar_ButtonSkill() { return mSpacebar_ButtonSkill; }
	string GetQ_ButtonSkill() { return mQ_ButtonSkill; }

	//void SetTileList(Tile* tileList[TileCountY][TileCountX])
	//{
	//	for (int y = 0; y < TileCountY; ++y)
	//	{
	//		for (int x = 0; x < TileCountX; ++x)
	//		{
	//			TileList[y][x] = tileList[y][x];
	//		}
	//	}
	//}
};

