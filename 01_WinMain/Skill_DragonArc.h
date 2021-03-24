#pragma once
#include "SkillObject.h"

class Image;
class Skill_DragonArc : public SkillObject
{
	Image* mImage;

	float mSpeed;
	float mFrameCount;

	float mMoveAngle;
	float mUpAngle;
	float mDownAngle;

	float mLineX;
	float mLineY;

	bool mIsUp;
public:
	Skill_DragonArc(const string& name, float x, float y, float angle, bool isUp);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

