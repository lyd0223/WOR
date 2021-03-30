#pragma once
#include "MonsterObject.h"
#define AnimationTime 0.1f
#define TileSize 48
class Monster_CrowScare : public MonsterObject
{
protected:
	Image* mImage;
	MonsterActState mMonsterActState;
	MonsterState mMonsterState;
	bool mIsAct;
	float lineX;
	float lineY;

public:
	Monster_CrowScare(const string& name, float x, float y);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;


	float GetAngle() { return mAngle; }
	void SetAngle(float angle) { mAngle = angle; }
	float GetSpeed() { return mSpeed; }
	void SetSpeed(float speed) { mSpeed = speed; }
	

};