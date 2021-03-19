#pragma once
#include "GameObject.h"

class Image;
class Animation;
class IceSword : public GameObject
{
	Image* mImage;
	

	float mEndX;
	float mEndY;
	float mImageAngle;
	float mAngle;
	float mSpeed;
public:
	IceSword(const string& name) : GameObject(name) {};
	IceSword(const string& name, float x, float y);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

