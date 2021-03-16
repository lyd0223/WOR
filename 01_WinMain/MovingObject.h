#pragma once
#include"GameObject.h"
enum class MonsterState
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
	MonsterState mMonsterState;
	
	


public:
	void Init()override {};
	void Release()override {};
	void Update()override{};
	void Render()override{};

	
};

