#pragma once
#include "SkillObject.h"

class Image;
class Animation;
class Skill_WindSlash : public SkillObject
{
	Image* mImage;
	class Player* mPlayer;
	float mEndX;
	float mEndY;
	float mImageAngle;
	float mAngle;
	float mSpeed;
	Animation* mSlashAnimation;
public:
	Skill_WindSlash(const string& name) : SkillObject(name) {};
	Skill_WindSlash(const string& name, float x, float y, float angle);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

