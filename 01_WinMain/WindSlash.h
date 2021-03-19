#pragma once
#include "GameObject.h"

class Image;
class Animation;
class WindSlash : public GameObject
{
	Image* mImage;


	float mEndX;
	float mEndY;
	float mImageAngle;
	float mAngle;
	float mSpeed;
	Animation* mSlashAnimation;
public:
	WindSlash(const string& name) : GameObject(name) {};
	WindSlash(const string& name, float x, float y, float angle);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

