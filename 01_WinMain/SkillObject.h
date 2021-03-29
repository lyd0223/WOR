#pragma once
#include "GameObject.h"

enum class Skill : int {
	Basic,
	Dash,
	Standard,
	Signature,

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
	Water,
	Elect,
	Earth,
	Wind,

	End
};

class Image;
class SkillObject : public GameObject
{
protected:
	Image* mImage;
	Skill mSkill;
	SkillType mSkillType;
	SkillTarget mSkillTarget;
	SkillElement mSkillElement;
	float mAngle;
	float mSkillDamege;
	float mSkillPower;
	int mSkillHitCount;

	bool mIsCollision;
public:
	SkillObject(const string& name) : GameObject(name) {};

	void Init() override {};
	void Release() override {}; 
	void Update() override {};
	void Render() override {};

	void SetSkillType(SkillType type) { mSkillType = type; }
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
	
	void SetIsCollision(bool isCollision) {	mIsCollision = isCollision; }
	bool GetIsCollision() { return mIsCollision; }
};

