#pragma once
#include "SkillObject.h"

class Image;
class Animation;
class Skill_ThunderBolt : public SkillObject
{
	Image* mImage;
	class Player* mPlayer;

	float mEndX;
	float mEndY;
	float mImageAngle;

	float mSpeed;
	Animation* mThunderBoltAnimation;
public:
	Skill_ThunderBolt(const string& name) : SkillObject(name) {};
	Skill_ThunderBolt(const string& name, float x, float y, float angle);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};
