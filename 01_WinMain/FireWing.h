#pragma once
#include "GameObject.h"

class Image;
class Animation;
class FireWing : public GameObject
{
	Image* mImage;
	Animation* mFireWingAnimation;

	int mFrameIndexX;
public:
	FireWing(const string& name, float x, float y);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	int GetFrameIndexX() { return mFrameIndexX; }
};

