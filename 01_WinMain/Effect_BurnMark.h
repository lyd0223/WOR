#pragma once
#include "GameObject.h"

class Image;
class Animation;
class Effect_BurnMark : public GameObject
{
	Image* mImage;
	Animation* mBurnMarkAnimation;

	int mRandomY;
public:
	Effect_BurnMark(const string& name, float x, float y);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};