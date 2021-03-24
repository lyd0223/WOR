#pragma once
#include"GameObject.h"

enum class MonsterState
{
	Idle,
	Chase,
	Attack,
	Die,

	End
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
	D2D1_RECT_F mMovingRect;
	
	


public:
	MovingObject(const string& name) : GameObject(name) {};

	void Init()override {};
	void Release()override {};
	void Update()override{};
	void Render()override{};
	float GetSpeed() { return mSpeed; }
	float GetAngle() { return mAngle; }
	void SetMovingRect(D2D1_RECT_F rc) { mMovingRect = rc; }
	D2D1_RECT_F GetMovingRect() { return mMovingRect; }
	
};

