#pragma once
#include"GameObject.h"

enum class MonsterState
{
	Idle,
	Chase,
	Attack
};
enum class MonsterActState
{
	LeftIdle,
	RightIdle,
	LeftHit,
	RightHit,
	LeftWalk,
	RightWalk,
	LeftAttack,
	RightAttack,
	UpAttack,
	DownAttack,
	SpecialAttack,
	Die
};

class MovingObject : public GameObject
{
protected:
	int mDMG;
	int mHp;
	float mSpeed;
	float mAngle;
	MonsterActState mMonsterActState;
	
	


public:
	void Init()override {};
	void Release()override {};
	void Update()override{};
	void Render()override{};
	float GetSpeed() { return mSpeed; }
	float GetAngle() { return mAngle; }

	
};

