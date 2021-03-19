#pragma once
#include "GameObject.h"

class Image;
class Animation;
class WindSlash : public GameObject
{
	Image* mImage;
	class Player* mPlayer;

	float mEndX;
	float mEndY;
	float mImageAngle;
	float mAngle;
	float mSpeed;
	Animation* mSlashAnimation;
public:

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
	WindSlash(const string& name) : GameObject(name) {};
	WindSlash(const string& name, float x, float y, float angle);
};

