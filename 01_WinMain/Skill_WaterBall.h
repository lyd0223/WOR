#pragma once
#include "SkillObject.h"

class Image;
class Animation;
class Skill_WaterBall : public SkillObject
{
	Image* mImage;
	class Player* mPlayer;

	float mEndX;
	float mEndY;
	float mImageAngle;
	float mAngle;
	float mSpeed;
	Animation* mWaterBallAnimation;
public:
	Skill_WaterBall(const string& name) : SkillObject(name) {};
	Skill_WaterBall(const string& name, float x, float y);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};
