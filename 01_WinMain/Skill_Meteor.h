#pragma once
#include "SkillObject.h"

class Image;
class Animation;
class Skill_Meteor : public SkillObject
{
	Image* mImage;
	Animation* mMeteorAnimation;
	
	float mEndX;
	float mEndY;
	float mAngle;
	float mSpeed;
public:
	Skill_Meteor(const string& name) : SkillObject(name) {};
	Skill_Meteor(const string& name, float x, float y);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

