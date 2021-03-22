#pragma once
#include "GameObject.h"

class Image;
class Animation;
class Skill_IceSword : public GameObject
{
	Image* mImage;
	

	float mEndX;
	float mEndY;
	float mImageAngle;
	float mAngle;
	float mSpeed;
public:
	Skill_IceSword(const string& name) : GameObject(name) {};
	Skill_IceSword(const string& name, float x, float y, float angle);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

