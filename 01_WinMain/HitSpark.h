#pragma once
#include "GameObject.h"

class Image;
class Animation;
class HitSpark : public GameObject
{
	Image* mImage;
	Animation* mHitSparkAnimation;

	int mIndexY;
public:
	HitSpark(const string& name, float x, float y, int indexY);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

