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
	RightDash,
	DownDash,
	UpDash,
	Die,
	UpThrowSkill,
	DownThrowSkill,
	LeftThrowSkillandAttack,
	RightThrowSkillandAttack


};
#define AnimationTime 0.1f
#define TileSize 64
class Player : public MovingObject
{
	PlayerState mPlayerState;
	Image* mImage;

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
	class Animation* mRightDashAnimation;
	class Animation* mDownDashAnimation;
	class Animation* mUpDashAnimation;
	class Animation* mDieAnimation;
	class Animation* mUpThrowSkillAnimation;
	class Animation* mDownThrowSkillAnimation;
	class Animation* mLeftThrowSkillandAttackAnimation;
	class Animation* mRightThrowSkillandAttackAnimation;


	class Animation* mCurrentAnimation;
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

