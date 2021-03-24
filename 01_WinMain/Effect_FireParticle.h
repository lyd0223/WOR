#pragma once
#include "GameObject.h"

class Image;
class Animation;
class Effect_FireParticle : public GameObject
{
	Image* mImage;
	Animation* mFireParticleAnimation;
	
	float mRandomAngle;
	float mAngle;
	float mDistance;
	float mSpeed;

	bool mIsMove;
public:
	Effect_FireParticle(const string& name, float x, float y, float angle);

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void SetSpeed(float speed) { mSpeed = speed; }
	void SetIsMove() { mIsMove = true; }
};
