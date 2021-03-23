#pragma once
#include "GameObject.h"

// ��ų Ÿ�� ( ����, ����ü, ��ġ)
enum class SkillType : int {
	Melee,	// ���� ��ų
	Throw,	// ����ü
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
	SkillType mSkillType;
	SkillElement mSkillElement;
	float mAngle;
	int mSkillHitCount;

	bool mIsCollision;
public:
	SkillObject(const string& name) : GameObject(name) {};

	void Init() override {};
	void Release() override {};
	void Update() override {};
	void Render() override {};

	SkillType GetSkillType() { return mSkillType; }
	SkillElement GetSkillElement() { return mSkillElement; }
	void SetAngle(float angle) { mAngle = angle; }
	int GetSkillHitCount() { return mSkillHitCount; }
	
	void SetIsCollision(bool isCollision) {	mIsCollision = isCollision; }
	bool GetIsCollision() { return mIsCollision; }
};

