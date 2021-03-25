#pragma once
#include "GameObject.h"

class Image;
class Animation;
class Effect_DashEffect : public GameObject
{
	Image* mImage;
	Animation* mAnimation;

	float mAngle;
	
public:
	Effect_DashEffect(const string& name, float x, float y, float angle);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

