#pragma once
#include "GameObject.h"

class Image;
class Animation;
class BurnMark : public GameObject
{
	Image* mImage;
	Animation* mBurnMarkAnimation;

	int mRandomY;
public:
	BurnMark(const string& name, float x, float y);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};