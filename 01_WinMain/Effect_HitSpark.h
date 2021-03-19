#pragma once
#include "GameObject.h"

class Image;
class Animation;
class Effect_HitSpark : public GameObject
{
	Image* mImage;
	Animation* mHitSparkAnimation;

	int mIndexY;
public:
	Effect_HitSpark(const string& name, float x, float y, int indexY);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

