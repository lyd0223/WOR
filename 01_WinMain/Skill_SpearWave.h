#pragma once
#include "SkillObject.h"

class Image;
class Animation;
class Skill_SpearWave : public SkillObject
{
	Image* mImage;
	class Player* mPlayer;

	float mEndX;
	float mEndY;
	float mImageAngle;
	float mAngle;
	float mSpeed;
	Animation* mSpearWaveAnimation;
public:
	Skill_SpearWave(const string& name) : SkillObject(name) {};
	Skill_SpearWave(const string& name, float x, float y, float angle);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};
