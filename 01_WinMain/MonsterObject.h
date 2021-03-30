#pragma once
#include"MovingObject.h"
#include "RandomMapGeneration.h"
class Image;
class Player;
enum class MonsterType
{
	Normal,
	MiddleBoss,
	Boss
};

enum class MonsterName
{
	BigZombie,
	Golem,
	Mazition,
	RapidZombie,
	Slime,
	SwoardMan,
	Zombie
};
class MonsterObject :public MovingObject
{
protected:
	Image* mImage;
	Player* mPlayer;
	vector<class Tile*> mPathList;

	float mRange;
	float mAtkSpeed;
	float mAtkFrameCount;
	float mMonsterToPlayerDistance;
	float mMonsterToPlayerAngle;
	float mHitTime;

	class Room* mRoom;
	MonsterType mMonsterType;
	MonsterName mMonsterName;
	int mHitCount;

	bool mIsCollision;
	bool mIsHit;
public:
	MonsterObject(const string& name);

	void SetPathList(vector<class Tile*> pathList) { mPathList = pathList; }
	vector<class Tile*> GetPathList() { return mPathList; }
	
	void SetRoom(Room* room) { mRoom = room; };
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
	void SetIsHit(bool isHit) { mIsHit = isHit; }
	bool GetIsHit() { return mIsHit; }
		
};

