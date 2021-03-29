#pragma once
#include "GameObject.h"

enum class SkillArcana : int {
	Basic = 0,
	Dash = 1,
	Standard = 2,
	Signature = 3,

	End
};

// ��ų ��� ��� ( �÷��̾�, ��)
enum class SkillTarget : int{
	Player,
	Enemy,

	End
};

// ��ų Ÿ�� ( ����, ����ü, ��ġ)
enum class SkillType : int {
	Melee,	// ���� ��ų
	Throw,	// ����ü
	Hold,	// Ȧ��
	Install,	// ��ġ��

	End
};

// ��ų �Ӽ� ( ��, ��, ����, ��, ī����)
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
	float mAngle;
	float mSkillDamege;
	float mSkillPower;
	float mSkillCool;
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
	void SetAngle(float angle) { mAngle = angle; }
	float GetAngle() { return mAngle; }
	void SetSkillDamege(float damege) { mSkillDamege = damege; }
	float GetSkillDamege() { return mSkillDamege; }
	void SetSkillPower(float skillPower) { mSkillPower = skillPower; }
	float GetSkillPower() { return mSkillPower; }
	int GetSkillHitCount() { return mSkillHitCount; }
	float GetSkillCool() { return mSkillCool; }
	
	void SetIsCollision(bool isCollision) {	mIsCollision = isCollision; }
	bool GetIsCollision() { return mIsCollision; }
};

