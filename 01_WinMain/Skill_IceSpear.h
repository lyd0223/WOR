#pragma once
#include "SkillObject.h"

class Image;
class Animation;
class Skill_IceSpear : public SkillObject
{
	Image* mImage;
	class Player* mPlayer;

	float mEndX;
	float mEndY;
	float mImageAngle;

	float mSpeed;
	Animation* mIceSpearAnimation;
public:
	Skill_IceSpear(const string& name) : SkillObject(name) {};
	Skill_IceSpear(const string& name, float x, float y, float angle);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void SetSpeed(float speed) { mSpeed = speed; }
};
