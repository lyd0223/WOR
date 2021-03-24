#pragma once
#include "SkillObject.h"

class Image;
class Animation;
class Skill_Spear : public SkillObject
{
	Image* mImage;
	class Player* mPlayer;

	float mEndX;
	float mEndY;
	float mImageAngle;
	float mAngle;
	float mSpeed;
	Animation* mSpearAnimation;
public:
	Skill_Spear(const string& name) : SkillObject(name) {};
	Skill_Spear(const string& name, float x, float y, float angle);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};
