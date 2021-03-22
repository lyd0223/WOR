#pragma once
#include "SkillObject.h"

class Image;
class Animation;
class Skill_SummonIceSpear : public SkillObject
{
	Image* mImage;
	class Player* mPlayer;

	float mEndX;
	float mEndY;
	float mImageAngle;
	float mAngle;
	float mSpeed;
	Animation* mSummonIceSpearAnimation;
public:
	Skill_SummonIceSpear(const string& name) : SkillObject(name) {};
	Skill_SummonIceSpear(const string& name, float x, float y, float angle);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};
