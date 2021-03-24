#pragma once
#include"MovingObject.h"

class Image;
class Player;
class MonsterObject :public MovingObject
{
protected:
	Image* mImage;
	Player* mPlayer;
	vector<class Tile*> mPathList;
	D2D1_RECT_F mMovingRect;

	float mRange;
	float mAtkSpeed;
	float mAtkFrameCount;
	float mMonsterToPlayerDistance;
	float mMonsterToPlayerAngle;
	int mHitCount;
	
	bool mIsCollision;
public:
	MonsterObject(const string& name);

	void SetPathList(vector<class Tile*> pathList) { mPathList = pathList; }
	vector<class Tile*> GetPathList() { return mPathList; }
	void SetMovingRect(D2D1_RECT_F rc) { mMovingRect = rc; }
	D2D1_RECT_F GetMovingRect() { return mMovingRect; }
	
	void SetRange(float range) { mRange = range; }
	float GetRange() { return mRange; }
	void SetAtkSpeed(float atkSpeed) { mAtkSpeed = atkSpeed; }
	float GetAtkSpeed() { return mAtkSpeed; }
	void SetHitCount(int hitCount) { mHitCount = hitCount; }
	int GetHitCount() { return mHitCount; }
	void SetMonsterToPlayerDistance(float distance) { mMonsterToPlayerDistance = distance; }
	float GetMonsterToPlayerDistance() { return mMonsterToPlayerDistance; }
	void SetMonsterToPlayerAngle(float angle) { mMonsterToPlayerAngle = angle; }
	float GetMonsterToPlayerAngle() { return mMonsterToPlayerAngle; }

	void SetIsCollision(bool IsCollision) { mIsCollision = IsCollision; }
	bool GetIsCollision() { return mIsCollision; }
};

