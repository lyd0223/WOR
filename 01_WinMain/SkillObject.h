#pragma once
#include "GameObject.h"

// 스킬 타입 ( 근접, 투사체, 설치)
enum class SkillType : int {
	Melee,	// 근접 스킬
	Throw,	// 투사체
	Install,	// 설치형

	End
};

// 스킬 속성 ( 불, 물, 전기, 땅, 카오스)
enum class SkillElement : int {
	Fire,
	Water,
	Elect,
	Earth,
	Chaos,

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
public:
	SkillObject(const string& name) : GameObject(name) {};

	void Init() override {};
	void Release() override {};
	void Update() override {};
	void Render() override {};

	SkillType GetSkillType() { return mSkillType; }
	SkillElement GetSkillElement() { return mSkillElement; }
	void SetAngle(float angle) { mAngle = angle; }
};

