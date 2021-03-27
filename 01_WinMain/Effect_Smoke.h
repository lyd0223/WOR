#pragma once
#include "GameObject.h"

class Image;
class Animation;
class Effect_Smoke : public GameObject
{
	Image* mImage;
	Animation* mAnimation;

	float mAlpha;
	float mAngle;
	float mScale;
	float mSpeed;
public:
	Effect_Smoke(const string& name, float x, float y, float angle, float scale, float speed);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

