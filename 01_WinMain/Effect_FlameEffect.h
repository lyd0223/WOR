#pragma once
#include "GameObject.h"

class Image;
class Animation;
class Effect_FlameEffect : public GameObject
{
	Image* mImage;
	Animation* mFlameEffectAnimation;

	float mAngle;
public:
	Effect_FlameEffect(const string& name, float x, float y, float angle);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};