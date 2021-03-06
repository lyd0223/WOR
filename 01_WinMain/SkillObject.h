#pragma once
#include "GameObject.h"

enum class SkillArcana : int {
	Basic = 0,
	Dash = 1,
	Standard = 2,
	Signature = 3,

	End
};

// 스킬 쏘는 대상 ( 플레이어, 적)
enum class SkillTarget : int{
	Player,
	Enemy,

	End
};

// 스킬 타입 ( 근접, 투사체, 설치)
enum class SkillType : int {
	Melee,	// 근접 스킬
	Throw,	// 투사체
	Hold,	// 홀딩
	Install,	// 설치형

	End
};

// 스킬 속성 ( 불, 물, 전기, 땅, 카오스)
enum class SkillElement : int {
	Fire,
	Wind,
	Earth,
	Elect,
	Water,

	End
};

class Image;
class SkillObject : public GameObject
{
protected:
	Image* mImage;
	SkillArcana mSkillArcana;
	SkillType mSkillType;
	SkillTarget mSkillTarget;
	SkillElement mSkillElement;

	vector<GameObject*> mSkillCollisionList;

	float mAngle;
	float mSkillDamege;
	float mSkillPower;
	float mSkillCool;
	float mDelay;

	int mSkillStack;
	int mSkillHitCount;

	bool mIsCollision;
public:
	SkillObject(const string& name) : GameObject(name) {};

	void Init() override {};
	void Release() override {}; 
	void Update() override {};
	void Render() override {};

	void SetSkillType(SkillType type) { mSkillType = type; }
	SkillArcana GetSkillArcana() { return mSkillArcana; }
	SkillTarget GetSkillTarget() { return mSkillTarget; }
	SkillType GetSkillType() { return mSkillType; }
	SkillElement GetSkillElement() { return mSkillElement; }
	vector<GameObject*> GetSkillCollisionList() { return mSkillCollisionList; }
	void SetSkillCollisionList(vector<GameObject*> list) { mSkillCollisionList = list; }
	void SetAngle(float angle) { mAngle = angle; }
	float GetAngle() { return mAngle; }
	void SetSkillDamege(float damege) { mSkillDamege = damege; }
	float GetSkillDamege() { return mSkillDamege; }
	void SetSkillPower(float skillPower) { mSkillPower = skillPower; }
	float GetSkillPower() { return mSkillPower; }
	int GetSkillHitCount() { return mSkillHitCount; }
	float GetSkillCool() { return mSkillCool; }
	float GetDelay() { return mDelay; }
	void SetDelay(float delay) { mDelay = delay; }
	
	void SetskillStack(int stack) { mSkillStack = stack; }
	int GetSkillStack() { return mSkillStack; }
	
	void SetIsCollision(bool isCollision) {	mIsCollision = isCollision; }
	bool GetIsCollision() { return mIsCollision; }
};

