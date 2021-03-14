#pragma once
#include "GameObject.h"

class Image;
class Animation;
class Meteor : public GameObject
{
	Image* mImage;
	Animation* mMeteorAnimation;
	
	float mEndX;
	float mEndY;
	float mAngle;
	float mSpeed;
public:
	Meteor(const string& name, float x, float y);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};

