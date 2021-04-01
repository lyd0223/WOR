#pragma once
#include "SkillObject.h"

class Image;
class Skill_LightRing : public SkillObject
{
	Image* mImage;

	float mStartX;
	float mStartY;

	float mSpeed;
public:
	Skill_LightRing(const string& name, float x, float y, float angle);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

