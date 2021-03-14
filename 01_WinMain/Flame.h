#pragma once
#include "GameObject.h"

class Image;
class Animation;
class Flame : public GameObject
{
	Image* mImage;
	Animation* mFlameAnimation;

	float mAngle;
	float mEndPositionX;
	float mEndPositionY;
public:
	Flame(const string& name, float x, float y, float angle);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void MakeCircleFlame();

	void SetEndPositionX(float x) { mEndPositionX = x; }
	void SetEndPositionY(float y) { mEndPositionY = y; }
};

